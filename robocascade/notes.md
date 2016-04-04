

notes:


1) number of positive samples should related be to negative around 2:1 (positive samples should be more

2) The precision of your cascade is shown by acceptanceRatio on the last stage it should be around this value 0.000412662 or less.
    But if you get acceptanceRatio like this 7.83885e-07 your cascade is probably overtrained and it wont find anything, try to set less stages.

3) How many negatives and positive images should I have?

      It all depends on your application so start by clearly defining what application area you have
      Things to consider in this case are the amount of variation in object instances, the fact if you have a known/static background or not, is your lighting controlled or not, ...
      But a general rule that works for a variety of setups is to take a numPos:numNeg ration of 1:2.
      Keep in mind that increase the number of positives will increase the generalization of your model, it will look for better general features and will less likely overfit on your training data. Increasing the number of negative images is needed to remove the large amount of false positive detections. You want to supply as many situations as possible that don't look like your object here! Generally speaking they supply thousand of samples here to try to model general background noise for your application.
      Always keep in mind to carefully select your training data. It is better to 100 good natural occuring samples, than to use 1 good image and transform it 100 times with the available tools.

  Should positives be more than negatives? If yes what is the best proportion between negatives and positives?

  Like said above that kind of depens on your application. A ratio of 1:2 is good but I have applications where there are ratios of 100:1 and applications where the ratio is 1:100. It all makes sense once you know what training does for your application.

  Is there a preferable format for the pictures (bmp, jpg, png etc)?

  Actually there is not a general rule for this, but I always suggest users to use a file format that doesn't have lossy compression, like png. This will ensure that you do not incorporate compression artefacts as actual features of the object. This is especially the case when resizing your training data.

  What should be the size of negative pictures and what should be the size of positive images?

      Lets say my negative images are 640x320, and the "to be detected" object is 100x50. In negatives folder the images should all be 640x320?In positives folder should be 640x320 cropped images with visible on the object?Or should i place in positives folder images of 100x50 with the object only?

  In your positives folder you keep images that contain objects. Then your positives.txt file will be formatted image_location number_objects x1 y1 w1 h1 x2 y2 w2 h2 ... xN yN wN hN. This means that those regions will be cut out by the create samples tool and then resized to the model dimensions given at the -h and -w parameters of the tool. For your negative images just supply a folder with tons of images that are larger than your model size your selected. During training negative windows will get sampled from those larger images. At training time the -numNeg windows can thus be quite larger ... (more)
