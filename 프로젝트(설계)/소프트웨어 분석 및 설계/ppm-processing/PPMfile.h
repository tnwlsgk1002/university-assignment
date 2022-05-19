#include <iostream>
#include <stdlib.h>
#include "Print.h"
#include <math.h>
#pragma warning(disable:4996)
using namespace std;
#define PI 3.14159265

typedef struct PPMimage{
	char M, N;
	int width;
	int height;
	int max;
	unsigned char** pixels;

public :
	PPMimage();
	PPMimage(PPMimage& img);
	int exist_PPMimage();

}PPMimage;

int Read_PPM(char* filename, PPMimage* img);

int Save_PPM(char* filename, PPMimage* img);

void deletePPM(PPMimage* img);

void color_Invert(PPMimage* img);

void Filp(PPMimage* img, char num);

void RGB_matrix(PPMimage* img, unsigned char**& color, unsigned char**& color_t, char RGB);

void RGB_Rotaion(PPMimage* img, unsigned char**& color, unsigned char**& color_t, double center_x, double center_y, double seta);

void Rotion(PPMimage* img, double degree);

void channel_RGB(PPMimage* img, char num);

void Grayscale(PPMimage* img);