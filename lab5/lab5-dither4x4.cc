/*===
lab5-dither4x4-skeleton.cc

Abstract: Skeleton code for a 4x4 dithering scheme
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
	// load the input image
	Image image;
	image.LoadPng ("ca_coast.png");

	// the dithering matrix (to access the pixel at column x, row y, the
	// index in this structure is [x][y]
	static short ditherMatrix[4][4] = {
		{8,   200, 56,  248},
		{136, 72,  184, 120},
		{40,  232, 24,  216},
		{168, 104, 152, 88} };

	double mse = 0;

	// dither the image
	for (int x = 0; x < (image.Width ()/4); x++)
	{
		for (int y = 0; y < (image.Height ()/4); y++)
		{
			/*===
	
			Insert Lab 5 4x4 dithering code here
	
			===*/	

			for(int i = 0; i < 4; i++){
				for(int j = 0; j < 4; j++){
					double orig_val = image.Pixel((4*x) + i,(4*y) + j);
					int& value = image.Pixel ((4*x) + i,(4*y) + j);
					value = (value < ditherMatrix[i][j]) ? 0 : 255;
					mse += (image.Pixel((4*x) + i,(4*y) + j) - orig_val)*(image.Pixel((4*x) + i,(4*y) + j) - orig_val);
				}
			}


		}
	}

	mse = mse/(image.Height()*image.Width());

	cout<<"MSE of image is: "<<mse<<"\n";
	
	// save the image
	image.SavePng ("ca_coast_dither4x4.png");

	return 0;
}
