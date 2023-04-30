// ImageBrowser.cpp:	This program demonstrates the effects of different up and down sampling algorithms, as well as intensity down sampling
// Author:				Jon Eman
// Date:				10/4/2022

#include "main.h"

int main(int argc, char **argv) {
    String imageFile;
    int samplingMethod;
    int depth;
    int intensityLevels;
    int up = 1;

    parseParameters(argc, argv, &imageFile, &samplingMethod, &depth, &intensityLevels);

    try {
        Mat image = imread(imageFile);
        if (image.empty())
            throw (string("Cannot open input image ") + argv[1]);
        if(depth < 0){
            up = 0;
            depth = depth * -1;
        }
        for(int i = 0; i < depth; i++){
            cout << i << endl;
            if(samplingMethod==1) {
                image = basicSampling(image, up);
            }
            if(samplingMethod==2 && up) {
                image = interpolateUpSampling(image);
            }
            if(samplingMethod==2 && !up) {
                image = averageDownSampling(image);
            }
            imshow("Step " + to_string(i + 1), image);
            waitKey();
        }

        for (int i=0;i<image.cols;i++) {
            for (int j = 0; j < image.rows; j++) {
                for (int k = 0; k < image.channels(); k++) {
                    image.at<Vec3b>(j, i)[k] = (image.at<Vec3b>(j, i)[k] >> intensityLevels) << intensityLevels;
                }
            }
        }
        imshow("Deep fried by " + to_string(intensityLevels) + " bits", image);
        // imwrite("output5.jpg", image);
        waitKey();

    }
    catch (string &str) {
        cerr << "Error: " << argv[0] << ": " << str << endl;
        return (1);
    }
    catch (Exception &e) {
        cerr << "Error: " << argv[0] << ": " << e.msg << endl;
        return (1);
    }
    return (0);
}

static int parseParameters(int argc, char** argv, String* imageFile, int* samplingMethod, int* depth, int* intensityLevels)
{
    String keys =
            {
                    "{help h usage ? |                            | print this message   }"
                    "{@imagefile      | | image you want to use	}"
                    "{s           |1| sampling method	}"
                    "{d        |1| depth	}"
                    "{i       |1| intensity levels to downsample	}"
            };

    // Get required parameters. If any are left blank, defaults are set based on the above table
    // If no directory is passed in, or if the user passes in a help param, usage info is printed
    CommandLineParser parser(argc, argv, keys);
    parser.about("ImageSampler v1.0");

    if (!parser.has("@imagefile") || parser.has("help"))
    {
        parser.printMessage();
        return(0);
    }

    if (parser.has("s"))
    {
        *samplingMethod = parser.get<int>("s");
    }

    if (parser.has("d"))
    {
        *depth = parser.get<int>("d");
    }

    if (parser.has("i"))
    {
        *intensityLevels = parser.get<int>("i");
    }

    *imageFile = parser.get<String>("@imagefile");
    return(1);
}

static Mat basicSampling(Mat image, int up){
    double factor;
    if (up){
        factor = 2;
    }
    else{
        factor = .5;
    }
    int newcols = round(image.cols*factor);
    int newrows = round(image.rows*factor);
    Mat newmat = Mat(newrows, newcols, image.type());
    for (int i=0;i<newcols;i++){
        for (int j=0;j<newrows;j++){
            newmat.at<Vec3b> (j, i) = image.at<Vec3b>(j/factor, i/factor);
        }
    }
    return newmat;
};

static Mat averageDownSampling(Mat image){
    int newCols = round(image.cols*.5);
    int newRows = round(image.rows*.5);
    Mat newImage = Mat(newCols, newRows, image.type());
    for (int i=0;i<newCols;i++) {
        for (int j = 0; j < newRows; j++) {
            newImage.at<Vec3b>(j, i) =
                    (image.at<Vec3b>(2 * j, 2 * i + 1)/4 + image.at<Vec3b>(2 * j, 2 * i)/4 + image.at<Vec3b>(2 * j + 1, 2 * i)/4 +
                     image.at<Vec3b>(2 * j, 2 * i)/4);
        }
    }
    return newImage;
};

static Mat interpolateUpSampling(Mat image){
    int newCols = round(image.cols*2);
    int newRows = round(image.rows*2);
    Mat newImage = Mat(newCols, newRows, image.type());
    for (int i = 0;i<newCols;i++) {
        for (int j = 0; j < newRows; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0){
                    newImage.at<Vec3b> (j, i) = image.at<Vec3b>(.5 * j, .5 * i);
                }
                else {
                    newImage.at<Vec3b> (j, i) = image.at<Vec3b>(.5 * j, .5 * i)/2 + image.at<Vec3b>(.5 * j + 1, .5 * i)/2;
                }
            }
            else {
                if (j % 2 == 0){
                    newImage.at<Vec3b> (j, i) = image.at<Vec3b>(.5 * j, .5 * i)/2 + image.at<Vec3b>(.5 * j, .5 * i + 1)/2;
                }
                else {
                    newImage.at<Vec3b> (j, i) = image.at<Vec3b>(.5 * j, .5 * i)/4 + image.at<Vec3b>(.5 * j, .5 * i + 1)/4 + image.at<Vec3b>(.5 * j + 1, .5 * i)/4+ image.at<Vec3b>(.5 * j + 1, .5 * i + 1)/4;
                }
            }
        }
    }
    return newImage;
}