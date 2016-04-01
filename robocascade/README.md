steps for training classifier :

    Creating the description file of positive samples

        The description file is just a text file, with each line corresponding to each
        image.The fields in a line of the positive description file are: the image name,
        followed by the number of objects to be detected in the image, which is followed by
        the x,y coordinates of the location of the object in the image.Some images may
        contain more than one objects.

        The description file of positive images can be created using the objectmarker.py
        by giving the outfile path (the text file to be written in) ,and the input directory
        path (the directory containing the positive images) . this can be done by next command:

        $   python objectmarker.py <output file > <input directory>

    Creating the description file of negative samples

        The description file of negative samples contain only the filenames of the negative
        images.can be done by command (inside the directory containing the negative images):

        $   ls > negative.txt

    Packing the positive samples into a vec file

        All the positive images in the description file are packed into a .vec file.
        can be dome by command :

        $   opencv_createsamples -info positive.txt -vec vecfile.vec -w 60 -h 60

        can show the .vec file using command :

        $   opencv_createsamples -vec vecfile.vec -show

    Training the classifier

       $ opencv_traincascade -data data -vec vecfile.vec -bg neg/negative.txt -numStages 8
       -featureType LBP -w 60 -h 60 -mode all -precalcValBufSize 4096 -precalcIdxBufSize 4096
       -numPos 440 -numNeg 240

    Using the xml file to detect the object

        get the path of the cascade file created in the data directory and write it in the
        robodetect file .
