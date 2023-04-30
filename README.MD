### Image Resampler
### Author: Jon Eman
### Date: 10/4/2022

### Build
##### To build, install OpenCV on your computer, change the OpenCV path in the CMAKE file, and use the standard CMAKE commands for building.

### Usage

##### Run the program with the following command structure:
    Resampler <input image> --s=<sampling method> --d=<sampling depth> --i=<intensity downsampling bits>

##### s = 1 for basic delete/add down/up sampling, and 2 for averaging/interpolation down/up sampling