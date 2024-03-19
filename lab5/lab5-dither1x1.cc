/*===
lab5-dither1x1.cc

Abstract: Implementation of a 1x1 dithering scheme
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

	double mse = 0;
	
	// do 1x1 dithering
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			double orig_val = image.Pixel(x,y);
			int& value = image.Pixel (x, y);
			value = (value < 128) ? 0 : 255;
			mse += (image.Pixel(x,y) - orig_val)*(image.Pixel(x,y) - orig_val);
		}
	}

	mse = mse/(image.Width()*image.Height());
	cout<<"MSE of image is: "<<mse;
	
	// save the image
	image.SavePng ("ca_coast_dither1x1.png");

	return 0;
}
