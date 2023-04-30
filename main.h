// main.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <locale.h>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <opencv2/core/utility.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

static int parseParameters(int argc, char** argv, String* imageFile, int* samplingMethod, int* depth, int* intensityLevels);

static Mat basicSampling(Mat image, int up);
static Mat averageDownSampling(Mat image);
static Mat interpolateUpSampling(Mat image);