/*===
lab5-errdiff-skeleton.cc

Abstract: Skeleton code for an error diffusion scheme
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

	/*===

	You may want to set up an image (doubles as pixel values) to store 
	the error at each pixel
	
	ImageTemplate<double> error;
	error.Resize (image.Width (), image.Height () );

	===*/

	// dither the image (note we must traverse in raster-scan order here)
	for (int y = 0; y < image.Height (); y++)
	{
		for (int x = 0; x < image.Width (); x++)
		{
			/*===
	
			Insert Lab 5 error diffusion code here
	
			===*/	
		}
	}
	
	// save the image
	image.SavePng ("ca_coast_errdiff.png");

	return 0;
}
