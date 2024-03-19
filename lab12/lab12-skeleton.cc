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
