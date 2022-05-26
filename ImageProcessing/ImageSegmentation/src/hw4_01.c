#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>

#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define BYTE    unsigned char

#define SIZE 5

BYTE* inImg;
int histo[256] = { 0, };
float global_mean = 0;
int height, width;

void bmp_read() {
	// bmp 파일 읽기
	FILE* bmp_fp;

	if ((bmp_fp = fopen("hand.bmp", "rb")) == NULL) {
		printf("No Image File");
		return;
	}

	// BMP Header Information
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hInfo;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, bmp_fp);//14 bytes

	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, bmp_fp);//40 bytes
	//printf(hInfo.biBitCount);

	// 영상의 크기 정보 읽기
	height = hInfo.biHeight, width = hInfo.biWidth;

	fclose(bmp_fp);

	// raw 이미지를 저장할 변수 선언
	inImg = malloc(height * width);

	// raw 파일 읽기
	FILE* raw_fp;

	if ((raw_fp = fopen("hand.raw", "rb")) == NULL) {
		printf("No Image File");
		return;
	}
	fread(inImg, height * width, sizeof(char), raw_fp);

	fclose(raw_fp);
}

void pgm_write(BYTE* bwImg, char* fname) {
	FILE* out = fopen(fname, "wb");
	fprintf(out, "P5\n");//magic no.
	fprintf(out, "%d %d\n", width, height);
	fprintf(out, "255\n");//max. value
	fwrite(bwImg, sizeof(char), height * width, out);
	fclose(out);
}

void thresholding(BYTE* outImg, int thres) {
	printf("\n>> Threshold : %d\n", thres);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (inImg[i * width + j] < thres) outImg[i*width + j] = 0;
			else outImg[i*width + j] = 255;
		}
	}
}

void histogram() {
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			histo[inImg[i * width + j]]++;
		}

	float sum = 0;
	for (int i = 0; i < 256; i++)
		sum += (float)(i * histo[i]);
	global_mean = sum / (float)(height * width);
}

void interative_threshold_selection() {

	BYTE* outImg = malloc(height * width);

	int thres = 128;
	int thres_tmp = 0;
	float lmean = 0., rmean = 0.;
	int lsum = 0, rsum = 0;
	int lnum = 0, rnum = 0;
	int idx = 1;
	while (thres_tmp != thres) {
		lmean = 0., rmean = 0.;
		lsum = 0, rsum = 0;
		lnum = 0, rnum = 0;
		for (int i = 0; i <= thres; i++) {
			lsum += i * histo[i];
			lnum += histo[i];
		}
		lmean = (float)lsum /(float)lnum;

		for (int i = thres + 1; i < 256; i++) {
			rsum += i * histo[i];
			rnum += histo[i];
		}
		rmean = (float) rsum / (float)rnum;
		thres_tmp = thres;
		thres = (int)((lmean + rmean) / 2.);

		printf(">> iteration : %d\n", idx);
		idx++;
	}

	thresholding(outImg, thres);

	pgm_write(outImg, "1-1.pgm");
	free(outImg);
}

void otsu() {

	BYTE* outImg = malloc(height * width);
	float p1 = 0.;
	float ptmp = 0.;
	float var[256];

	float mean1 = 0., mean2 = 0.;
	float mtmp = 0.;

	for (int t = 0; t < 256; t++) {
		p1 = ptmp + (float)histo[t] / (float)(height * width);
		if (p1 == 0.) mean1 = 0.;
		else mean1 = (ptmp * mtmp + (float)(t * histo[t]/ (float)(height * width))) / p1;
		if (p1 == 1.) mean2 = 0.;
		else mean2 = (global_mean - p1 * mean1) / (1. - p1);
		var[t] = p1 * (1. - p1) * (mean1 - mean2) * (mean1 - mean2);
		ptmp = p1;
		mtmp = mean1;
	}

	float max = 0.;
	int thres = 0;
	for (int t = 0; t < 256; t++) {
		if (max < var[t]) {
			max = var[t];
			thres = t;
		}
	}

	thresholding(outImg, thres);
	pgm_write(outImg, "1-2.pgm");
	free(outImg);
}

void kapur() {
	BYTE* outImg = malloc(height * width);

	int a = 0;
	float h1 = 0., h2 = 0.;
	float p1 = 0., p2 = 0.;
	int sum1 = 0, sum2 = 0;
	float max = 0.;
	int thres = 0;
	float entropy[256];

	for (int t = 0; t < 256; t++) {
		sum1 = sum2 = 0;
		h1 = h2 = 0.;
		for (int i = 0; i <= t; i++) {
			sum1 += histo[i];
		}
		for (int i = 0; i <= t; i++) {
			p1 = (float)histo[i] / (float)sum1;
			if (p1 == 0.);
			else h1 += p1 * log2(1. / p1);
		}

		sum2 = width * height - sum1;

		for (int i = t + 1; i < 256; i++) {
			p2 = (float)histo[i] / (float)sum2;
			if (p2 == 0.);
			else h2 += p2 * log2(1. / p2);
		}
		entropy[t] = h1 + h2;
	}

	for (int t = 0; t < 256; t++) {
		if (max < entropy[t]) {
			max = entropy[t];
			thres = t;
		}
	}
	thresholding(outImg, thres);
	pgm_write(outImg, "1-3.pgm");
	free(outImg);
}

void main()
{
	bmp_read();
	histogram();
	printf("< 1-1. interative threshold_selection >\n");
	interative_threshold_selection();
	printf("\n< 1-2. otsu >\n");
	otsu();
	printf("\n< 1-3. Kapur >\n");
	kapur();

	free(inImg);
}
