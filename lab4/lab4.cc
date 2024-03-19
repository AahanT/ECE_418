/*===
lab4-skeleton.cc

Abstract: Skeleton for Lab 4
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <cmath>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
  //Image image;
  //image.Resize (512, 512);

	/*===
	
	Insert Lab 4 code here

	===*/

  // Part A1
	Image image1;
	image1.Resize(512,512);
	for(int i = 0; i < 16; i++){
	  double pixel = (double)(i * 255 / 15);
	  for(int r = 0; r < image1.Height(); r++){
	    for(int c  = 0; c < (image1.Width()/16); c++){
	      image1.Pixel((i*image1.Width()/16) + c,r) = pixel;
	    }
	  }
	}

	image1.SavePng("day-name-test-A1.png");

	////////

	// Part A2

	Image image2;
	image2.Resize(512,512);
	for(int i = 0; i < 16; i++){
	  double pixel = (double)(i * 255 / 15);
	  for(int r = 0; r < image1.Height()/16; r++){
	    for(int c  = 0; c < (image1.Width()); c++){
	      image2.Pixel(c,(i*image1.Height()/16) + r) = pixel;
	    }
	  }
	}

	image2.SavePng("day-name-test-A2.png");

	////////

	// Part B

	Image image3;
	image3.Resize(1024,512);
	for(int i = 0; i < image3.Width(); i++){
	  for(int j = 0; j < image3.Height(); j++){
	    double amplitude = (double)(((double)(image3.Height() -1 -j)/(double)(image3.Height()-1))*(double)127.5);
	    double frequency = (double)(((double)i/(double)(image3.Width()-1))*((double)M_PI/(double)2));
	    double pixel = amplitude*((double)1 + (double)sin(frequency * (double)i));
	    image3.Pixel(i,j) = pixel;
	  }
	}

	image3.SavePng("day-name-test-B.png");

	////////

	// Part C

	Image image4;
	image4.Resize(1024, 512);
	double S1, S2, X;
	X = double(128);
	S1 = double(0);
	S2 = double(225);
	
	for(int i = 0; i < (image4.Width()/2); i++){
	  for(int j = 0; j < image4.Height(); j++){
	    image4.Pixel(i,j) = S1;
	  }
	}

	for(int i = (image4.Width()/2); i < image4.Width(); i++){
	  for(int j = 0; j < image4.Height(); j++){
	    image4.Pixel(i,j) = S2;
	  }
	}

	for(int i = ((image4.Width()/4) -(64/2) + 1); i < ((image4.Width()/4) + (64/2) + 1); i++){
	  for(int j = ((image4.Height()/2) -(64/2) + 1); j < ((image4.Height()/2) + (64/2) + 1); j++){
	    image4.Pixel(i,j) = X;
	  }
	}

	
	for(int i = ((3*image4.Width()/4) -(64/2) + 1); i < ((3*image4.Width()/4) + (64/2) + 1); i++){
	  for(int j = ((image4.Height()/2) -(64/2) + 1); j < ((image4.Height()/2) + (64/2) + 1); j++){
	    image4.Pixel(i,j) = X;
	  }
	}
	
	image4.SavePng("day-name-test-C.png");

	///////

	// Part D

	Image image5;
	image5.Resize(512,512);
	double I, F;
	F = double(0);
	I = double(40);
	int width = image5.Width(), height = image5.Height();
	
	for(int i = 0; i < width; i++){
	  for(int j = 0; j < height; j++){
	    image5.Pixel(i,j) = I;
	  }
	}

	for(int i =((width/2) -(8/2) + 1); i < ((width/2) + (8/2) +1); i++){
	  for(int j = ((height/2) - (8/2) + 1); j < ((height/2) + (8/2) + 1); j++){
	    image5.Pixel(i,j) = F;
	  }
	}

	image5.SavePng("day-name-test-D.png");

	//image.SavePng ("day-name-test.png");

	return 0;
}
