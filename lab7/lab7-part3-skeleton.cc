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
		     << " input.png output.png" << endl;
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
		}
	}
	
	// calculate the cumulative distribution function from the histogram
	vector<int> cDistFunction (256, 0);
	/*===

	Insert Lab 7 Part 3 Code Here - Compute the cumulative distribution 
	function
	
	===*/

	// apply the cumulative distribution function
	/*===

	Insert Lab 7 Part 3 Code Here - Apply the cumulative distribution 
	function to equalize the image's histogram.  You can then use part two 
	to compute the equalized image's histogram.
	
	===*/

	// save the image 
	image.SavePng (argv[2]);

	return 0;
}
