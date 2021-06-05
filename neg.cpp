#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Color.h"
#include "Image.h"
#include "ppm.lib"

using namespace std;

int main(int argc, char* argv[])
{
	char * filename = "Image06.ppm";

	int *w,  *h;

	int width = 0, height = 2;

	w = &width; h = &height;	

	imaging::Color *color_array = new imaging::Color[*w*(*h)];

	imaging::Image image(*w, *h);	

	bool load_flag = image.load(filename, ".ppm");
	
	if (load_flag) { color_array = image.getRawDataPtr(); cout << "Loading Successful!!" << endl; }
	else {cout << "Failed to load the file!!" << endl;}	

	imaging::Image img = image;
	
	imaging::Color white(1, 1, 1);

	for (int i = 0; i < (*w); i++) {

		for (int j = 0; j < (*h); j++) {

			imaging::Color pix = image.getPixel(i, j);	
			pix = white - pix;
			img.setPixel(i, j, pix);

		}
	}
	bool save_flag = img.save("katitis.ppm", ".ppm");

	if (save_flag) { cout << "Saving successful!!" << endl; }

	cout << "To platos einai: " << image.getWidth()<< endl << "To upsos einai: " << image.getHeight() << endl; 

	system("pause");

	return 0;
}

