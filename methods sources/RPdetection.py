import cv2
import urllib
import numpy as np

TRAINSET1 = "/home/festo/ClionProjects/RobotinoCV/Cascade trials/pucktrial2/cascade.xml"
TRAINSET2 = "/home/festo/ClionProjects/RobotinoCV/Cascade trials/datarobotino1/cascade.xml"
DOWNSCALE = 1
puckclassifier = cv2.CascadeClassifier(TRAINSET1)
roboclassifier = cv2.CascadeClassifier(TRAINSET2)

bytes=''
x=1
while True:

    #stream from robotino

    #stream=urllib.urlopen('http://172.26.1.1/fcgi-bin/?{%22TYPE%22:%22getimage%22,%22A%22:1532857915}')


    #stream from mobile

    stream=urllib.urlopen('http://172.26.1.119:8080/shot.jpg?rnd=214398')


    jpg = stream.read()
    #a = bytes.find('\xff\xd8')
    #b = bytes.find('\xff\xd9')
    #if a!=-1 and b!=-1:
        #jpg = bytes[a:b+2]
        #bytes= bytes[b+2:]
    i = cv2.imdecode(np.fromstring(jpg, dtype=np.uint8),cv2.COLOR_BGR2GRAY)
    minisize = (i.shape[1]/DOWNSCALE,i.shape[0]/DOWNSCALE)
    miniframe = cv2.resize(i, minisize)
    x+=1
    cv2.imwrite("img/image_processed"+str(x)+".jpg",miniframe)
    pucks = puckclassifier.detectMultiScale(miniframe ,minNeighbors =10)
    robotinos = roboclassifier.detectMultiScale(miniframe ,minNeighbors =10)
    #faces = classifier.detectMultiScale(miniframe, scaleFactor = 1.9, minNeighbors = 3, minisize, flags = cv2.cv.CV_HAAR_SCALE_IMAGE)
    for p in pucks:
        x, y, w, h = [ v*DOWNSCALE for v in p ]
        cv2.rectangle(i, (x,y), (x+w,y+h), (255,0,0),3,8,0)
    for r in robotinos:
        x, y, w, h = [ v*DOWNSCALE for v in r ]
        cv2.rectangle(i, (x,y), (x+w,y+h), (0,255,0),3,8,0)
    cv2.imshow('i',i)
    if cv2.waitKey(1) ==27:
        exit(0)
