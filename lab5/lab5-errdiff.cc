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

	Image errorImage;
	errorImage.Resize(image.Width(), image.Height());

	double mse = 0;

	for(int x = 0; x < image.Width(); x++){
		for(int y = 0; y < image.Height(); y++){
			errorImage.Pixel(x,y) = 0;
		}
	}


	// dither the image (note we must traverse in raster-scan order here)
	for (int y = 0; y < image.Height (); y++)
	{
		for (int x = 0; x < image.Width (); x++)
		{
			/*===
	
			Insert Lab 5 error diffusion code here
	
			===*/	
			double temp = 0;
			if(x > 0){
				temp += 7.0*errorImage.Pixel(x-1,y)/16.0;
			}
			if(y > 0){
				temp += 5.0*errorImage.Pixel(x,y-1)/16.0;
			}
			if(x>0 && y>0){
				temp += errorImage.Pixel(x-1,y-1)/16.0;
			}
			if(x<(image.Width() - 1) && y > 0){
				temp += 3.0*errorImage.Pixel(x+1, y-1)/16.0;
			}

			double orig_val = image.Pixel(x,y);
			image.Pixel(x,y) = image.Pixel(x,y) - temp;
			double output = image.Pixel(x,y);
			int &value = image.Pixel(x,y);
			value = (value < 128) ? 0 : 255;
			errorImage.Pixel(x,y) = image.Pixel(x,y) - output;
			mse += (image.Pixel(x,y) - orig_val)*(image.Pixel(x,y) - orig_val);
			
		}
	}
	

	mse = mse/(image.Height()*image.Width());
	cout<<"MSE of image is: "<<mse<<"\n";

	// save the image
	image.SavePng ("ca_coast_errdiff.png");

	return 0;
}
