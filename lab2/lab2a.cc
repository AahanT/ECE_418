/*===
lab2ab-skeleton.cc

Abstract: Skeleton for Lab 2 parts (a) and (b).
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
	if (argc != 3) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png" << endl;
		return 1;
	}

	// load the image
	ComplexImage image;
	image.LoadPng (argv[1]);
	
	/*===
	
	Insert Lab 2 code here:
	
	1. Compute the 2D FFT of the image
	2. Perform the frequency domain operation(s)
	3. Compute the inverse 2D FFT of the image
	4. For parts (b) and (c), re-normalize the image
	
	===*/
	// First Step: Computing DFT
	
	for(int i = 0; i < image.Height(); i++){
	  vector<Complex> rowsig;
	  rowsig.resize(image.Width());
	  for(int j = 0; j < image.Width(); j++){
	    rowsig[j] = image.Pixel(i,j);
	  }
	  FFT::Transform(rowsig);
	  for(int j = 0; j < image.Width(); j++){
	    image.Pixel(i,j) = rowsig[j];
	  }
	}

	for(int j = 0; j < image.Width(); j++){
	  vector<Complex> colsig;
	  colsig.resize(image.Height());
	  for(int i = 0; i < image.Height(); i++){
	    colsig[i] = image.Pixel(i,j);
	  }
	  FFT::Transform(colsig);
	  for(int i = 0; i < image.Height(); i++){
	    image.Pixel(i,j) = colsig[i];
	  }
	}

	// Second Step: Removing Phase

	for(int  i = 0; i < image.Height(); i++){
	  for(int j = 0; j < image.Width(); j++){
	    Complex temp;
	    temp = image.Pixel(i,j);
	    image.Pixel(i,j) = abs(temp);
	  }
	}

	// Third Setp: Inverse DFT

	for(int i = 0; i < image.Height(); i++){
	  vector<Complex> rowsig;
	  rowsig.resize(image.Width());
	  for(int j = 0; j < image.Width(); j++){
	    rowsig[j] = image.Pixel(i,j);
	  }
	  FFT::InverseTransform(rowsig);
	  for(int j = 0; j < image.Width(); j++){
	    image.Pixel(i,j) = rowsig[j];
	  }
	}

	for(int j = 0; j < image.Width(); j++){
	  vector<Complex> colsig;
	  colsig.resize(image.Height());
	  for(int i = 0; i < image.Height(); i++){
	    colsig[i] = image.Pixel(i,j);
	  }
	  FFT::InverseTransform(colsig);
	  for(int i = 0; i < image.Height(); i++){
	    image.Pixel(i,j) = colsig[i];
	  }
	}

	
	// save the image
	image.SavePng (argv[2]);
	
	return 0;
}
