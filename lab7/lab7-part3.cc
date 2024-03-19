/*===
lab7-part3-skeleton.cc

Abstract: Skeleton for part three of lab seven (histogram equalization)
===*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
	// verify arguments' correctness
	if (argc != 3)
	{
		cerr << "Useage: " << argv[0] 
		     << " input.png output.png histogram.txt" << endl;
		return 1;
	}

	// load the input image
	Image image;
	image.LoadPng (argv[1]);

	// set up the histogram
	vector<int> histogram (256, 0);
	
	// calculate the image's histogram
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			/*===

			Insert Lab 7 Part 3 Code Here - fill in the histogram
			
			===*/
			int idx = int(image.Pixel(x,y));
			histogram[idx] += 1;
		}
	}
	
	// calculate the cumulative distribution function from the histogram
	vector<int> cDistFunction (256, 0);
	/*===

	Insert Lab 7 Part 3 Code Here - Compute the cumulative distribution 
	function
	
	===*/

	// apply the cumulative distribution function

	for (int i = 0; i < 256; i++){
		if(i==0){
			cDistFunction[0] = histogram[0];
		}
		else{
			cDistFunction[i] = cDistFunction[i-1] + histogram[i];
		}
	}

	/*===

	Insert Lab 7 Part 3 Code Here - Apply the cumulative distribution 
	function to equalize the image's histogram.  You can then use part two 
	to compute the equalized image's histogram.
	
	===*/

	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			int idx = int(image.Pixel(x,y));
			image.Pixel(x,y) = double((cDistFunction[idx] * 255)/(image.Width()*image.Height()));
		}
	}

	// save the image 
	image.SavePng (argv[2]);

	vector<int> newHistogram (256, 0);

	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			/*===

			Insert Lab 7 Part 3 Code Here - fill in the histogram
			
			===*/
			int idx = int(image.Pixel(x,y));
			newHistogram[idx] += 1;
		}
	}

	ofstream out ("hist-part3-Lena.txt");
	if (out.fail () )
	{
		cerr << "Failed to open file for histogram output" << endl;
		return 1;
	}
	out<<"Original Histogram:" << endl;
	for (int i = 0; i < histogram.size (); i++)
	{
		out << histogram[i] << endl;
		cout << histogram[i] << endl;
	}
	out<<"New Histogram:" << endl;
	for (int i = 0; i < newHistogram.size (); i++)
	{
		out << newHistogram[i] << endl;
		cout << newHistogram[i] << endl;
	}
	out.close ();
	return 0;
}
