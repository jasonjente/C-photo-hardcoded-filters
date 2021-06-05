#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <cstddef>
#include "ppm.h"
#include "Image.h"
#include "Color.h"

using namespace std;

imaging::Image::Image()
	: width(0), height(0), buffer(nullptr)
{
}
imaging::Image::Image(unsigned int width, unsigned int height)
	: buffer(nullptr)
{

	this->width = width;
	this->height = height;
}
imaging::Image::Image(unsigned int width, unsigned int height, const Color * data_ptr) {
	this->width = width;
	this->height = height;
	*buffer = *data_ptr;
}
imaging::Image::Image(const Image &src) {
	width = src.getWidth();
	height = src.getHeight();
	buffer = src.buffer;
}
imaging::Image::~Image() {
	
}
imaging::Color* imaging::Image::getRawDataPtr() {

	return buffer;

}
void imaging::Image::setPixel(unsigned int x, unsigned int y, Color & value) {

	buffer[width*x + y] = value;

}
imaging::Color imaging::Image::getPixel(unsigned int x, unsigned int y) const {

	if (x < 0 || y<0 || x>width || y>height) {

		return Color(0, 0, 0);

	}
	else {

		return buffer[width*x + y];

	}
}
void imaging::Image::setData(const Color * & data_ptr) {

	*buffer = *data_ptr;

}
bool imaging::Image::load(const string & filename, const string & format) {

	unsigned int *w = &width;
	unsigned int *h = &height;
	


	if (filename.find(format) != string::npos) {

		float * array_ptr = ReadPPM(filename.c_str(), (int*)w, (int*)h);

		if (array_ptr == nullptr) {
			return false;
		}

		imaging::Color *color_array =new imaging::Color[*w**h * 3];  // Allocate n Pixels and save ptr in color_array.	
		buffer = new Color[(*w) *(*h)*3];
		unsigned int j = 0;
		for (int i = 0; i < (int)((*w) *(*h)); i++) {			
				buffer[i] = imaging::Color(array_ptr[j], array_ptr[j+1], array_ptr[j + 2]);
				j = j + 3;
		}		

	}
	else {return false;}	
}
bool imaging::Image::save(const string & filename, const string & format) {
	
	if (filename.find(format) != string::npos) {

		Color *pixel_array = getRawDataPtr();

		float *transition_pixels = new float[width*height*3];

		unsigned int pixel_iter = 0;
		
		for (unsigned int i = 0; i < width*height; i++) {

			transition_pixels[pixel_iter] = pixel_array[i][0];
			transition_pixels[pixel_iter+1] = pixel_array[i][1];
			transition_pixels[pixel_iter+2] = pixel_array[i][2];
			pixel_iter = pixel_iter + 3;

		}
		return WritePPM(transition_pixels, width, height, filename.c_str());
	}
	else { return false; }	
}