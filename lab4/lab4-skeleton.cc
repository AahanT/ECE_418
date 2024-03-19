/*===
lab4-skeleton.cc

Abstract: Skeleton for Lab 4
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
	Image image;
	image.Resize (512, 512);

	/*===
	
	Insert Lab 4 code here

	===*/

	image.SavePng ("day-name-test.png");

	return 0;
}
