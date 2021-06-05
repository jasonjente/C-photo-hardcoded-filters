#include <iostream>
#include <fstream>
#include <string>
#include "ppm.h"

using namespace std;

float * imaging::ReadPPM(const char * filename, int * w, int * h)
{
	float *array_pointer = nullptr;	
	string format;	int width;	int height;	int depth;	int max_c = 255;	string line;
	ifstream file(filename, ios::in | ios::binary);
	
	int counter = 0;

	if (!file.is_open())
	{
		printf("Could not open " + *filename);
		printf("\n");
		return nullptr;
	}
	else
	{
		file >> format;

		if (format != "P6") {
			throw "Different Image Format";
		}
		else {

			counter++;
		}
		file >> width >> height >> depth;

		if (width > 0) {
			
			counter++;
		}
		else {
			throw "Invalid Width!";
		}
		if (height > 0) {
			
			counter++;
		}
		else {
			throw "Invalid Height!";
		}
		if (depth <= 255 && depth >= 0) {
			
			counter++;
		}
		else {
			throw "Unsupported color depth!";
		}
		if (counter != 4) {
			throw "SOMETHING MISSING FROM THE HEADER";

		}
		file.get();

		*w = width;
		*h = height;

		unsigned char buffer;
		
		float *pixels = new float[width*height * 3];

		array_pointer = pixels;		

		int pixel_counter = 0;

		while (pixel_counter < width*height * 3) {

			buffer = file.get();			

			pixels[pixel_counter] = (float)(buffer) / (255);

			pixel_counter++;

		}
		file.close();		

	}
	
	return array_pointer;
}

bool imaging::WritePPM(const float * data, int w, int h, const char * filename) {

	if (data == nullptr) {return false;}

	ofstream file(filename, ios::out | ios::binary);
	
	if (!file.is_open()) 
	{
		printf("Could not open " + *filename);
		printf("\n");
		return false;
	}
	else
	{		
		file << "P6" << " " << w << " " << h << " " << 255 << " ";		
		int pixel_counter = 0;
		
		for (int i = 0; i < w * h * 3; i++) {
			unsigned char buffer = 255-(data[i] * 255);
			file << buffer;
		}
		file.close();			
	}
	
	return true;
}