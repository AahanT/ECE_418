/*===
lab12-skeleton.cc

Abstract: Skeleton code for lab 12
===*/

#include "image.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// main
int main (int argc, char* argv[]) {
	
	// check arguments' correctness
	if (argc != 8) {
		cout << "Usage : " << argv[0] 
		     << " current previous blocksize"
		     << " xblock yblock search_size output_ascii_file" 
		     << endl;
	  return 1;
	}

	// load the current frame
	Image current;
	current.LoadPng ( argv[1] );

	// load the previous frame
	Image previous;
	previous.LoadPng ( argv[2] );

	// parse command line arguments
	int blockSize = atoi(argv[3]);  // the size of the block we will be comparing
	int xStart = atoi(argv[4]);     // starting horizontal pixel for the block we will compare
	int yStart = atoi(argv[5]);     // starting vertical pixel for the block we will compare
	int searchSize = atoi(argv[6]); // number of pixels up and down our search will encompass
	
	// initialize the 2D array holding the MSE for each displacement to have size searchSize^2
	vector<vector<double> > displacementMSE (searchSize, vector<double> (searchSize, 0) );

	// fill in the displacementMSE table and print the displacement that minimizes MSE
	/*===
	
	Insert Lab 12 Code Here
	
	===*/

	double sum = 0;
	double mse;
	int range = 0;

	for (int r = 0; r < searchSize; r++){
		for (int c = 0; c < searchSize; c++){
			range = (searchSize - 1) /2;
			sum = 0;
			for (int i = 0; i < blockSize; i++){
				for (int j = 0; j < blockSize; j++){
					double prev_pix = previous.Pixel(xStart + (r-range) + i, yStart + (c-range) + j);
					double cur_pix = current.Pixel(xStart + i, yStart + j);
					sum += (prev_pix - cur_pix ) * (prev_pix - cur_pix);
				}
			}

			mse = sum * (double)1/(double)(blockSize * blockSize) ;
			cout<<"sum = " << sum<<"\t"<<"mse = "<<mse<<endl;
			displacementMSE[r][c] = mse;
		}
	}

	// storing the energy in a histogram
	Image dfd_img;
	dfd_img.Resize(blockSize,blockSize);
	ofstream outh ("histB");
	double sum_b = 0;
	for (int r = 0; r < blockSize; r++){
		for(int c = 0; c < blockSize; c++){
			dfd_img.Pixel(r,c) = abs(current.Pixel(xStart+r,yStart+c)- previous.Pixel(xStart+r-1,yStart+c+27));
			sum_b += current.Pixel(xStart+r,yStart+c)*current.Pixel(xStart+r,yStart+c);
			outh << dfd_img.Pixel(r,c) <<endl;
		}
	}

	cout<<"energy of block of current part B" <<sum_b<<endl;
	outh.close();
	dfd_img.SavePng("DFD_Img_partB.png");

	// save each displacement's MSE to a file
	ofstream out (argv[7]);
	if (out.fail () ) 
	{
		cout << "Failed to open " << argv[7] << " for writing." << endl;
		return 1;
	}	
	for (int x = 0; x < searchSize; x++)
	{
		int xOffset = x - (searchSize - 1)/2;
		for (int y = 0; y < searchSize; y++)
		{
			int yOffset = y - (searchSize - 1)/2;
			out << xOffset << " " << yOffset << " " << displacementMSE[x][y] << endl;
		}
	}
	out.close ();	
}
