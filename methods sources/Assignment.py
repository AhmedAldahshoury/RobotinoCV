import cv2

#Let the show begins =D


img1 = cv2.imread('image1.png',cv2.CV_LOAD_IMAGE_GRAYSCALE)
img2 = cv2.imread('image2.png',cv2.CV_LOAD_IMAGE_GRAYSCALE)

#Contrast Stretching

def contrastStretching(image,B,A):
    newImage = image.copy()
    C = minmax(image)[0]
    D = minmax(image)[1]
    scalingFactor = (B-A)*1.0/(D-C)*1.0
    for i in range(0, image.shape[0]):
        for j in range(0, image.shape[1]):
            newImage[i][j]=(getPixelIntensity(image,i,j)-C)*scalingFactor+A

    return newImage

#Histogram Equalization

def histogramEqualization(image,n):
    pixels=image.size
    a= (n*1.0)/(pixels*1.0)
    his = histogram(image,n)
    newImage = image.copy()
    for i in range(0, image.shape[0]):
        for j in range(0, image.shape[1]):
            cumHis=cumulativeHistogram(his,image[i][j])
            newImage[i][j]=cumHis*a
    return newImage

def histogram(image,n):
    His= [0] * n
    for i in range(0, image.shape[0]):
        for j in range(0, image.shape[1]):
            pixel = getPixelIntensity(image,i,j)
            His[pixel]=His[pixel]+1;
    return His

def cumulativeHistogram(His,index):
    cumHis=0
    for i in range(0, index):
        cumHis = cumHis+His[i]
    return cumHis

#Sobel detector

def sobelDetector(image):
    newImage=image.copy()
    for x in range(0,image.shape[0]):
        for y in range(0,image.shape[1]):
            newImage[x][y]=abs(sobelGx(image,y,x))+abs(sobelGy(image,y,x))
    return newImage

def sobelGx(image,x,y):


    a = getPixelIntensity(image,y + 1,x - 1)
    b = getPixelIntensity(image,y + 1,x)
    c = getPixelIntensity(image,y + 1,x + 1)
    d = getPixelIntensity(image,y - 1,x - 1)
    e = getPixelIntensity(image,y - 1,x)
    f = getPixelIntensity(image,y - 1,x + 1)

    return (a+(2*b)+c)-(d+(2*e)+f)

def sobelGy(image,x,y):

    a = getPixelIntensity(image,y - 1,x - 1)
    b = getPixelIntensity(image,y,x - 1)
    c = getPixelIntensity(image,y + 1,x - 1)
    d = getPixelIntensity(image,y - 1,x + 1)
    e = getPixelIntensity(image,y,x + 1)
    f = getPixelIntensity(image,y + 1,x + 1)

    return (a+(2*b)+c)-(d+(2*e)+f)

#Canny Detector

def cannyDetector(image,t1,t2):

    newImage = nonMaximalSuppression(sobelDetector(gaussianFilter(image)),t1,t2)

    return newImage

def nonMaximalSuppression(image,t1,t2):

    newImage = image.copy()
    for x in range(0, (image.shape[0])-1):
        for y in range(0, (image.shape[1])):
            if(getPixelIntensity(image,x,y)<t2):
                newImage[x][y]=0
            if(getPixelIntensity(image,x,y)>t1):
                newImage[x][y]=getPixelIntensity(image,x,y)
            if(getPixelIntensity(image,x,y)>t2 and getPixelIntensity(image,x,y)<t1):
                for z in range(0,7):
                    if(getNeighbourPixels(image,x,y)[z]>t1):
                        newImage[x][y] = getPixelIntensity(image, x, y)
                    else:
                        newImage[x][y] =0
    return newImage

def gaussianFilter(image):
    #filter = [0,1,4,7,4,1,4,16,26,16,4,7,26,40,26,7,4,16,26,16,4,1,4,7,4,1]
    filter = [0,3,5,3,5,9,5,3,5,3]

    newImage = image.copy()
    for x in range(0, (image.shape[0])-1):
        for y in range(0, (image.shape[1])):

            kernel = [0,
                      getPixelIntensity(image,y - 1,x - 1),
                      getPixelIntensity(image,y - 1,x),
                      getPixelIntensity(image,y - 1,x + 1),
                      getPixelIntensity(image,y,x - 1),
                      getPixelIntensity(image,y,x),
                      getPixelIntensity(image,y,x + 1),
                      getPixelIntensity(image,y + 1,x - 1),
                      getPixelIntensity(image,y + 1,x),
                      getPixelIntensity(image,y + 1,x + 1)]

            sum = (kernel[1] * filter[1]) + \
                       (kernel[2] * filter[2]) + \
                       (kernel[3] * filter[3]) + \
                       (kernel[4] * filter[4]) + \
                       (kernel[5] * filter[5]) + \
                       (kernel[6] * filter[6]) + \
                       (kernel[7] * filter[7]) + \
                       (kernel[8] * filter[8]) + \
                       (kernel[9] * filter[9])
            gradient = sum/41
            print y,x
            newImage[y][x]=gradient

    return newImage

#Prewitt Detector

def prewittDetector(image):
    newImage = image.copy()
    for x in range(0, image.shape[0]-1):
        for y in range(0, (image.shape[1])):
            gradients=[prewittkernel1(image,x,y),
                       prewittkernel2(image,x,y),
                       prewittkernel3(image,x,y),
                       prewittkernel4(image,x,y),
                       prewittkernel5(image,x,y),
                       prewittkernel6(image,x,y),
                       prewittkernel7(image,x,y),
                       prewittkernel8(image,x,y)]
            newImage[y][x]=max(gradients)
    return newImage

def prewittkernel1(image,x,y):

    kernel = [0 , getPixelIntensity(image,y-1,x-1) ,
              getPixelIntensity(image,y-1,x),
              getPixelIntensity(image,y-1,x+1) ,
              getPixelIntensity(image,y,x-1),
              getPixelIntensity(image,y,x),
              getPixelIntensity(image,y,x+1),
              getPixelIntensity(image,y+1,x-1),
              getPixelIntensity(image,y+1,x),
              getPixelIntensity(image,y+1,x+1)]

    gradient = (kernel[1]*-1)+\
               (kernel[2]*+1)+\
               (kernel[3]*+1)+\
               (kernel[4]*-1)+\
               (kernel[5]*-2)+\
               (kernel[6]*+1)+\
               (kernel[7]*-1)+\
               (kernel[8]*+1)+\
               (kernel[9]*+1)

    return gradient
def prewittkernel2(image,x,y):
    kernel = [0,
              getPixelIntensity(image,y - 1,x - 1),
              getPixelIntensity(image,y - 1,x),
              getPixelIntensity(image,y - 1,x + 1),
              getPixelIntensity(image,y,x - 1),
              getPixelIntensity(image,y,x),
              getPixelIntensity(image,y,x + 1),
              getPixelIntensity(image,y + 1,x - 1),
              getPixelIntensity(image,y + 1,x),
              getPixelIntensity(image,y + 1,x + 1)]

    gradient = (kernel[1] * +1) + \
               (kernel[2] * +1) + \
               (kernel[3] * +1) + \
               (kernel[4] * -1) + \
               (kernel[5] * -2) + \
               (kernel[6] * +1) + \
               (kernel[7] * -1) + \
               (kernel[8] * -1) + \
               (kernel[9] * +1)

    return gradient
def prewittkernel3(image,x,y):
    kernel = [0,
              getPixelIntensity(image,y - 1,x - 1),
              getPixelIntensity(image,y - 1,x),
              getPixelIntensity(image,y - 1,x + 1),
              getPixelIntensity(image,y,x - 1),
              getPixelIntensity(image,y,x),
              getPixelIntensity(image,y,x + 1),
              getPixelIntensity(image,y + 1,x - 1),
              getPixelIntensity(image,y + 1,x),
              getPixelIntensity(image,y + 1,x + 1)]

    gradient = (kernel[1] * +1) + \
               (kernel[2] * +1) + \
               (kernel[3] * +1) + \
               (kernel[4] * +1) + \
               (kernel[5] * -2) + \
               (kernel[6] * -1) + \
               (kernel[7] * +1) + \
               (kernel[8] * -1) + \
               (kernel[9] * -1)

    return gradient
def prewittkernel4(image,x,y):

    kernel = [0,
              getPixelIntensity(image,y - 1,x - 1),
              getPixelIntensity(image,y - 1,x),
              getPixelIntensity(image,y - 1,x + 1),
              getPixelIntensity(image,y,x - 1),
              getPixelIntensity(image,y,x),
              getPixelIntensity(image,y,x + 1),
              getPixelIntensity(image,y + 1,x - 1),
              getPixelIntensity(image,y + 1,x),
              getPixelIntensity(image,y + 1,x + 1)]

    gradient = (kernel[1] * +1) + \
               (kernel[2] * +1) + \
               (kernel[3] * +1) + \
               (kernel[4] * +1) + \
               (kernel[5] * -2) + \
               (kernel[6] * -1) + \
               (kernel[7] * +1) + \
               (kernel[8] * -1) + \
               (kernel[9] * -1)

    return gradient
def prewittkernel5(image,x,y):

    kernel = [0,
              getPixelIntensity(image,y - 1,x - 1),
              getPixelIntensity(image,y - 1,x),
              getPixelIntensity(image,y - 1,x + 1),
              getPixelIntensity(image,y,x - 1),
              getPixelIntensity(image,y,x),
              getPixelIntensity(image,y,x + 1),
              getPixelIntensity(image,y + 1,x - 1),
              getPixelIntensity(image,y + 1,x),
              getPixelIntensity(image,y + 1,x + 1)]

    gradient = (kernel[1] * +1) + \
               (kernel[2] * +1) + \
               (kernel[3] * -1) + \
               (kernel[4] * +1) + \
               (kernel[5] * -2) + \
               (kernel[6] * -1) + \
               (kernel[7] * +1) + \
               (kernel[8] * +1) + \
               (kernel[9] * -1)

    return gradient
def prewittkernel6(image,x,y):

    kernel = [0,
              getPixelIntensity(image,y - 1,x - 1),
              getPixelIntensity(image,y - 1,x),
              getPixelIntensity(image,y - 1,x + 1),
              getPixelIntensity(image,y,x - 1),
              getPixelIntensity(image,y,x),
              getPixelIntensity(image,y,x + 1),
              getPixelIntensity(image,y + 1,x - 1),
              getPixelIntensity(image,y + 1,x),
              getPixelIntensity(image,y + 1,x + 1)]

    gradient = (kernel[1] * +1) + \
               (kernel[2] * -1) + \
               (kernel[3] * -1) + \
               (kernel[4] * +1) + \
               (kernel[5] * -2) + \
               (kernel[6] * -1) + \
               (kernel[7] * +1) + \
               (kernel[8] * +1) + \
               (kernel[9] * +1)

    return gradient
def prewittkernel7(image,x,y):
    kernel = [0,
              getPixelIntensity(image,y - 1,x - 1),
              getPixelIntensity(image,y - 1,x),
              getPixelIntensity(image,y - 1,x + 1),
              getPixelIntensity(image,y,x - 1),
              getPixelIntensity(image,y,x),
              getPixelIntensity(image,y,x + 1),
              getPixelIntensity(image,y + 1,x - 1),
              getPixelIntensity(image,y + 1,x),
              getPixelIntensity(image,y + 1,x + 1)]

    gradient = (kernel[1] * -1) + \
               (kernel[2] * -1) + \
               (kernel[3] * -1) + \
               (kernel[4] * +1) + \
               (kernel[5] * -2) + \
               (kernel[6] * +1) + \
               (kernel[7] * +1) + \
               (kernel[8] * +1) + \
               (kernel[9] * +1)

    return gradient
def prewittkernel8(image,x,y):

    kernel = [0,
              getPixelIntensity(image,y - 1,x - 1),
              getPixelIntensity(image,y - 1,x),
              getPixelIntensity(image,y - 1,x + 1),
              getPixelIntensity(image,y,x - 1),
              getPixelIntensity(image,y,x),
              getPixelIntensity(image,y,x + 1),
              getPixelIntensity(image,y + 1,x - 1),
              getPixelIntensity(image,y + 1,x),
              getPixelIntensity(image,y + 1,x + 1)]

    gradient = (kernel[1] * -1) + \
               (kernel[2] * -1) + \
               (kernel[3] * +1) + \
               (kernel[4] * -1) + \
               (kernel[5] * -2) + \
               (kernel[6] * +1) + \
               (kernel[7] * +1) + \
               (kernel[8] * +1) + \
               (kernel[9] * +1)

    return gradient

#helping methods

def minmax(image):
    min = image[0, 0]
    max = image[0, 0]
    for i in range(0, image.shape[0]):
        for j in range(0, image.shape[1]):
            if (image[i,j]<min):
                min=image[i][j]
            if (image[i,j]>max):
                max=image[i][j]
    return min,max

def getNeighbourPixels(image,x,y):
    neighbours =[getPixelIntensity(image,x-1,y-1) ,
                 getPixelIntensity(image,x-1,y),
                 getPixelIntensity(image,x-1,y+1),
                 getPixelIntensity(image,x,y-1),
                 getPixelIntensity(image,x,y+1),
                 getPixelIntensity(image,x+1,y-1),
                 getPixelIntensity(image,x+1,y),
                 getPixelIntensity(image,x+1,y+1)]
    return neighbours

def getPixelIntensity(image,x,y):

    if((x>=image.shape[0])or (x<0)):
        return 0

    if((y>=image.shape[1])or(y<0)):
        return 0

    return image[x][y]

def binarization(image,factor):
    newImage = image.copy()
    for i in range(0, image.shape[0]):
        for j in range(0, image.shape[1]):
            if(getPixelIntensity(image,i,j)<factor):
                newImage[i][j]=0
            else:
                newImage[i][j]=255
    return newImage


#showing result images

def showTime():
    cv2.imshow( "Contrast Stretching (0-255).jpg", contrastStretching(img1,255,0))
    threshold=30
    cv2.imshow( 'Sobel Detection with threshold=30', binarization(sobelDetector(img2),threshold))
    cv2.imshow( 'Sobel Detection without binarization',sobelDetector(img2))
    cv2.imshow( 'Prewitt Compass Detector without binarization', prewittDetector(img2))
    cv2.imshow( 'Prewitt Compass Detector with theshold=30', binarization(prewittDetector(img2),threshold))
    cv2.imshow( 'Gaussian filter 3x3', gaussianFilter(img2))
    cv2.imshow( 'Canny detector t1=100 t2=50 without binarization', cannyDetector(img2,100,50))
    cv2.imshow( 'Canny detector t1=100 t2=50 threshold=30', binarization(cannyDetector(img2,100,50),threshold))
    cv2.imshow( 'Histogram Equalization', histogramEqualization(img1,255))
    return

#writing output images to dir


#cv2.imwrite( "Contrast Stretching (0-255).jpg", contrastStretching(img1,255,0))
#threshold=30
#cv2.imwrite( "Sobel Detection with threshold=30.jpg", binarization(sobelDetector(img2),threshold))
#cv2.imwrite( "Sobel Detection without binarization.jpg",sobelDetector(img2))
#cv2.imwrite( "Prewitt Compass Detector without binarization.jpg", prewittDetector(img2))
#cv2.imwrite( "Prewitt Compass Detector with theshold=30.jpg", binarization(prewittDetector(img2),threshold))
#cv2.imwrite( "Gaussian filter 3x3.jpg", gaussianFilter(img2))
#cv2.imwrite( "Canny detector t1=100 t2=50.jpg without binarization", cannyDetector(img2,100,50))
#cv2.imwrite( "Canny detector t1=100 t2=50.jpg threshold=30", binarization(cannyDetector(img2,100,50),threshold))
#cv2.imwrite( "Histogram Equalization.jpg", histogramEqualization(img1,255))
#print cumulativeHistogram(img1,256)
#print img2.shape[0]

showTime()

cv2.waitKey(0)
cv2.destroyAllWindows()

