#include "cos_camera_daheng.h"
#include <iostream>
#include <stdio.h>
#include <vector>
//#include <stdio.h>

#define IMG_FILE_NAME "out.ppm"

using namespace std;

int main()
{
	vector<uint8_t> img;
	CameraDaheng cam;
	if(!cam.ConfigureCamera(1))
	{
		cout << "Configure error.\n";
		return 1;
	}

	if(!cam.Start())
	{
		cout << "Start error.\n";
		return 2;
	}
	img.resize(cam.GetImgSize());
	if(!cam.GetFrame(&img[0]))
	{
		cout << "Frame error.\n";
		return 3;
	}

	// Save
	FILE *f = fopen(IMG_FILE_NAME,"wb");
	fprintf(f, "P5\n" "%u %u 255\n", cam.GetWidth(), cam.GetHeight());
	fwrite(&img[0], 1, cam.GetImgSize(), f);
	fclose(f);
	cout << "<Image was saved in " << IMG_FILE_NAME << " file>\n";

	cam.Stop();
	cam.Close();


	return 0;
}