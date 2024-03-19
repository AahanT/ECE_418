/*===
lab10-part4-skeleton.cc

Abstract: Skeleton for part for of lab ten (predictive coding)
===*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"
using namespace std;

// calculate the log base 2 of a number using the convention log2(0)=0
double log2 (double x);

// snake raster scan function - updates x and y for a raster-snake scan
// of image, returning false only when the whole image has been traversed
bool SnakePixel (const Image& image, int& x, int& y);

// main routine
int main (int argc, char* argv[]) 
{
	// verify arguments' correctness
	if (argc != 3) 
	{
		cerr << "Useage: " << argv[0] 
		     << " input.png histogram.txt" << endl;
		return 1;
	}

	// load the input image
	Image image;
	image.LoadPng (argv[1]);
	int totalPixels = image.Width () * image.Height ();
	
	// create the normalized (sum of elements is one) histogram for prediction errors
	vector<double> predictionErrorHistogram (511, 0);
	double prevPix = image.Pixel(0,0);
	double temp = image.Pixel(0,0);

	// traverse the image in raster-snake order
	for (int x = 1, y = 0; SnakePixel (image, x, y); )
	{
		/*===
		
		Insert Lab 10 Part 4 Code Here
			-as in Part 2, you will need to initialize some variables before
			 the loop (the previous pixel's value, initialized to 
			 image.Pixel (0, 0), for example.
			-note that the loop starts at coordinates (1,0).  this is because
			 we need don't have any pixel to use to predict the one at (0,0)
		
		===*/

		temp = image.Pixel(x,y);
		image.Pixel(x,y) = prevPix;
		prevPix = temp;
		predictionErrorHistogram[image.Pixel(x,y) - temp + 255] += 1;

	}

	// calculate and print the entropy of the histogram
	double entropy = 0;
	for (int i = 0; i < predictionErrorHistogram.size (); i++) 
	{
		/*===

		Insert Lab 10 Part 4 Code Here
		
		===*/

		double newtemp = predictionErrorHistogram[i] / (512*512 - 1);
		entropy -= newtemp * log2(newtemp);
	}

	double total_bits = entropy * (512*512 - 1);
	double avg_bits = total_bits / (image.Height() * image.Width());

	cout << "Prediction Error Entropy is " << entropy << "." << endl;
	cout << "Total bits " << total_bits << endl;
	// print additional needed data
	
	// print the histogram to the specified file
	ofstream out (argv[2]);
	if (out.fail () ) 
	{
		cerr << "Failed to open file for histogram output" << endl;
		return 1;
	}
	for (int i = 0, pixels = 0; i < predictionErrorHistogram.size (); i++) 
	{
		out << predictionErrorHistogram[i] << endl;
	}
	out.close ();

	return 0;
}

// calculate the log base 2 of a number
double log2 (double x) 
{
	if (x == 0) return 0;
	return log (x) / (log (2.0) );
}

// snake raster scan function - updates x and y for a raster-snake scan
// of image, returning false only when the whole image has been traversed
bool SnakePixel (const Image& image, int& x, int& y) 
{
	if (y % 2 == 0) 
	{
		x++;
		if (x == image.Width () ) 
		{
			x--;
			y++;
		}
	}
	else 
	{
		x--;
		if (x == -1) 
		{
			x++;
			y++;
		}		
	}
	return (y < image.Height () );
}

