/*===
lab3-skeleton.cc

Abstract: Skeleton for Lab 3 parts (a), (b), and (c)
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "imagefft.h"
using namespace std;

int main (int argc, char* argv[])
{
	// check parameters' correctness [for parts (a) and (b) -- this needs to be changed for (c)]
	if (argc < 3) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png [top] [left]" << endl;
		return 1;
	}

	// read the top row and left column that will be used [remove this for part (c)]
	int topLeftRow = atoi(argv[3]);
	int topLeftColumn = atoi(argv[4]);

	// load the input image
	ComplexFFTImage inputImage;
	inputImage.LoadPng (argv[1]);
	
	// initialize the output interpolated image
	ComplexFFTImage outputImage;
	//outputImage.Resize (outputImage.Width (), outputImage.Height ());
	outputImage.Resize(512,512);
	/*===

	Insert Lab 3 code here
	
	Note that in this lab if you want to take the FFT of a ComplexFFTImage called image, 
	you only have to call image.FourierTransform () or image.InverseFourierTransform ()
	
	===*/
	for(int i = topLeftRow; i < (topLeftRow + 128); i++){
	  for(int j = topLeftColumn; j < (topLeftColumn + 128); j++){
	    Complex pixel = inputImage.Pixel(i,j);
	    outputImage.Pixel(4*(i - topLeftRow), 4*(j - topLeftColumn)) = pixel;
	  }
	}
	
	for(int i = 0; i < 127; i++){
	  for(int j = 0; j < 127; j++){
	    Complex A = outputImage.Pixel(4*i,4*j);
	    Complex B = outputImage.Pixel(4*i, 4*(j+1));
	    for(int k = 1; k < 4; k++){
	      outputImage.Pixel((4*i), (4*j) + k) = ((double(1) - (double(k)/double(4)))*A) + ((double(k)/double(4))*B);
	    }
	  }
	}

	// for(int i = 0; i < 512-4; i++){
	//   for(int j = 0; j < 127; j++){
	//     Complex A = outputImage.Pixel(4*i,4*j);
	//     Complex B = outputImage.Pixel(4*(i+1), 4*j);
	//     for(double  k = 1; k < 4; k++){
	//       outputImage.Pixel((i) + k, 4*j) = ((double(1) - (double(k)/double(4)))*A) + ((double(k)/double(4))*B);
	//     }
	//   }
	// }

	for(int i = 0; i < 127; i++){
	  for(int j = 0; j < 512-4; j++){
	    Complex A = outputImage.Pixel(4*i, j);
	    Complex B = outputImage.Pixel(4*(i+1), j);
	    for(int k = 1; k < 4; k++){
	      outputImage.Pixel((4*i) + k, j) = ((double(1) - (double(k)/double(4)))*A) + ((double(k)/double(4))*B);
	    }
	  }
	}
	
	// save the image
	outputImage.SavePng (argv[2]);

	return 0;
}
