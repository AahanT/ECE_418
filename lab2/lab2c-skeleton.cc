/*===
lab2c-skeleton.cc

Abstract: Skeleton for Lab 2 part (c)
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
#include "fft.h"
using namespace std;

int main (int argc, char* argv[])
{
	// check parameters' correctness
	if (argc != 4) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png frequency" << endl;
		return 1;
	}
	double frequency = atof (argv[3]);
	if (frequency < 0 || frequency > 0.5)
	{
		cerr << "Cutoff frequency must be in [0,0.5]" << endl;
		return 1;
	}

	// load the image
	ComplexImage image;
	image.LoadPng (argv[1]);
	
	/*===
	
	Insert Lab 2 code here:
	
	1. Compute the 2D FFT of the image
	2. Perform the frequency domain operation
	3. Compute the inverse 2D FFT of the image
	4. Re-normalize the image
	
	===*/
	
	// save the image
	image.SavePng (argv[2]);
	
	return 0;
}
