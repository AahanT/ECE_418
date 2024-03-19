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
	if (argc < 5) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png [top] [left]" << endl;
		return 1;
	}

	// read the top row and left column that will be used [remove this for part (c)]
	// int topLeftRow = atoi(argv[3]);
	// int topLeftColumn = atoi(argv[4]);

	int decimation = atoi(argv[6]);
	//int decimation = 2;
	int filterFlag = atoi(argv[5]);
	
	// load the input image
	ComplexFFTImage inputImage;
	inputImage.LoadPng (argv[1]);
	
	// initialize the output interpolated image / bilinear stored image
	ComplexFFTImage outputImage;
	//outputImage.Resize (outputImage.Width (), outputImage.Height ());
	outputImage.Resize(512,512);

	// small image
	ComplexFFTImage smallImage;
	smallImage.Resize(512/decimation,512/decimation);

	// difference image
	ComplexFFTImage differenceImage;
	differenceImage.Resize(512,512);

	int rowsize = 512/decimation;
	int colsize = 512/decimation;
	
	/*===

	Insert Lab 3 code here
	
	Note that in this lab if you want to take the FFT of a ComplexFFTImage called image, 
	you only have to call image.FourierTransform () or image.InverseFourierTransform ()
	
	===*/

	// We use filterFlag = 0 for Decimation without filter and
	// filterFlag = 1 for Decimation with filter

	// Doing decimation without the filter
	if(filterFlag == 0){
	  for(int i = 0; i < (512/decimation); i++){
	    for(int j = 0; j < (512/decimation); j++){
	      smallImage.Pixel(i,j) = inputImage.Pixel(decimation*i, decimation*j);
	      outputImage.Pixel(decimation*i,decimation*j) = smallImage.Pixel(i,j); // for bilinear interpolation
	    }
	  }

	  // bilinear interpolation
	  for(int i = 0; i < (512/decimation); i++){
	    for(int j = 0; j < (512/decimation)-1; j++){ //-1
	    Complex A = outputImage.Pixel(decimation*i, decimation*j);
	    Complex B = outputImage.Pixel(decimation*i, decimation*(j+1));
	    for(int k = 1; k < decimation; k++){
	      outputImage.Pixel((decimation*i), (decimation*j) + k) = ((double(1) - (double(k)/double(decimation)))*A) + ((double(k)/double(decimation))*B);
	    }
	    }
	  }
	  int temp = 512-decimation;
	  for(int i = 0; i < (512/decimation)-1; i++){ // -1
	    for(int j = 0; j < 512-decimation; j++){
	    Complex A = outputImage.Pixel(decimation*i, j);
	    Complex B = outputImage.Pixel(decimation*(i+1), j);
	    for(int k = 1; k < decimation; k++){
	      outputImage.Pixel((decimation*i) + k, j) = ((double(1) - (double(k)/double(decimation)))*A) + ((double(k)/double(decimation))*B);
	    }
	    }
	  }

	  //////

	  ///// difference image and mse

	  double mse = 0;
	  for(int i = 0; i <  512; i++){
	    for(int j = 0; j < 512; j++){
	      differenceImage.Pixel(i,j) = inputImage.Pixel(i,j)- outputImage.Pixel(i,j);
	      mse += (differenceImage.Pixel(i,j).real())*(differenceImage.Pixel(i,j).real());
	    }
	  }

	  mse /= double(512*512);
	  cout<<"MSE is :"<<mse;
	  //////

	  ///// scalling difference image
	  double M = 0, m = 0;
	  for(int i = 0; i < 512; i++){
	    for(int j = 0; j < 512; j++){
	      if((differenceImage.Pixel(i,j).real()) > M ){
		M = (differenceImage.Pixel(i,j).real());
	      }
	      if((differenceImage.Pixel(i,j).real()) < m){
		m = (differenceImage.Pixel(i,j).real());
	      }
	    }
	  }


	  for(int i = 0; i < 512; i++){
	    for(int j = 0; j < 512; j++){
	      if(abs(differenceImage.Pixel(i,j)) <= 0){
		differenceImage.Pixel(i,j) = double(128)*(differenceImage.Pixel(i,j) - m)/(-m);
	      }
	      else{
		differenceImage.Pixel(i,j) = (double(127)*(differenceImage.Pixel(i,j))/(M)) + double(128);
	      }
	    }
	  }

	  
	}

	else if(filterFlag == 1){

	  inputImage.FourierTransform();

	  int blockSize = 512/(decimation*2);

	  //top-left corner

	  for(int i = 0; i < blockSize; i++){
	    for(int j = 0; j < blockSize; j++){
	      smallImage.Pixel(i,j) = inputImage.Pixel(i,j);
	    }
	  }


	  //top-right corner
	  
	  for(int i = 0; i < blockSize; i++){
	    for(int j = 0; j < blockSize; j++){
	      smallImage.Pixel(i, j+blockSize) = inputImage.Pixel(i, 512 - blockSize + j);
	    }
	  }

	  //bottom-left corner

	  for(int i = 0; i < blockSize; i++){
	    for(int j = 0; j < blockSize; j++){
	      smallImage.Pixel(i + blockSize, j) = inputImage.Pixel(512 - blockSize + i, j);
	    }
	  }

	  //bottom-right corner

	  for(int i = 0; i < blockSize; i++){
	    for(int j = 0; j < blockSize; j++){
	      smallImage.Pixel(i + blockSize, j + blockSize) = inputImage.Pixel(512 - blockSize + i, 512 - blockSize + j);
	    }
	  }

	  smallImage.InverseFourierTransform();

	  for(int i = 0; i < (512/decimation); i++){
	    for(int j = 0; j < (512/decimation); j++){
	      smallImage.Pixel(i,j) = smallImage.Pixel(i,j) / double(decimation*decimation);
	      if(smallImage.Pixel(i,j).real() < 0){
		smallImage.Pixel(i,j) = double(0);
	      }
	      else if(smallImage.Pixel(i,j).real() > 255){
		smallImage.Pixel(i,j) = double(255);
	      }
	      outputImage.Pixel(decimation*i, decimation*j) = smallImage.Pixel(i,j);
	    }
	  }
	  
	  

	  // bilinear interpolation
	  for(int i = 0; i < (512/decimation); i++){
	    for(int j = 0; j < (512/decimation)-1; j++){ //-1
	    Complex A = outputImage.Pixel(decimation*i, decimation*j);
	    Complex B = outputImage.Pixel(decimation*i, decimation*(j+1));
	    for(int k = 1; k < decimation; k++){
	      outputImage.Pixel((decimation*i), (decimation*j) + k) = ((double(1) - (double(k)/double(decimation)))*A) + ((double(k)/double(decimation))*B);
	    }
	    }
	  }
	  int temp = 512-decimation;
	  for(int i = 0; i < (512/decimation)-1; i++){ // -1
	    for(int j = 0; j < 512-decimation; j++){
	    Complex A = outputImage.Pixel(decimation*i, j);
	    Complex B = outputImage.Pixel(decimation*(i+1), j);
	    for(int k = 1; k < decimation; k++){
	      outputImage.Pixel((decimation*i) + k, j) = ((double(1) - (double(k)/double(decimation)))*A) + ((double(k)/double(decimation))*B);
	    }
	    }
	  }

	  //////

	  ///// difference image and mse
	  inputImage.InverseFourierTransform();
	  double mse = 0;
	  for(int i = 0; i <  512; i++){
	    for(int j = 0; j < 512; j++){
	      differenceImage.Pixel(i,j) = inputImage.Pixel(i,j)- outputImage.Pixel(i,j);
	      // if(differenceImage.Pixel(i,j).real()<= 0){
	      // 	differenceImage.Pixel(i,j) = double(0);
	      // }
	      // else if(differenceImage.Pixel(i,j).real() >= 255){
	      // 	differenceImage.Pixel(i,j) = double(255);
	      // }
	      mse += (differenceImage.Pixel(i,j).real())*(differenceImage.Pixel(i,j).real());
	    }
	  }

	   mse /= double(512*512);
	   cout<<"MSE is :"<<mse;

	  
	   ///// scalling difference image
	  double M = 0, m = 0;
	  for(int i = 0; i < 512; i++){
	    for(int j = 0; j < 512; j++){
	      if((differenceImage.Pixel(i,j).real()) > M ){
		M = (differenceImage.Pixel(i,j).real());
	      }
	      if((differenceImage.Pixel(i,j).real()) < m){
		m = (differenceImage.Pixel(i,j).real());
	      }
	    }
	  }


	  for(int i = 0; i < 512; i++){
	    for(int j = 0; j < 512; j++){
	      if(abs(differenceImage.Pixel(i,j)) <= 0){
		differenceImage.Pixel(i,j) = double(128)*(differenceImage.Pixel(i,j) - m)/(-m);
	      }
	      else{
		differenceImage.Pixel(i,j) = (double(127)*(differenceImage.Pixel(i,j))/(M)) + double(128);
	      }
	    }
	  }
	  
	  
	  
	}

	

	  
	// save the image
	outputImage.SavePng (argv[3]);
	smallImage.SavePng(argv[2]);
	differenceImage.SavePng(argv[4]);

	return 0;
}
