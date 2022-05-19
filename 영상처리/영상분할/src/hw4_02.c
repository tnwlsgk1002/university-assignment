#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>

#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define BYTE    unsigned char

#define SIZE 5

BYTE* inImg;
BYTE* outImg;
int* lab;
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
			if (inImg[i * width + j] < thres) outImg[i * width + j] = 0;
			else outImg[i * width + j] = 255;
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

void otsu() {

	outImg = malloc(height * width);
	float p1 = 0.;
	float ptmp = 0.;
	float var[256];

	float mean1 = 0., mean2 = 0.;
	float mtmp = 0.;

	for (int t = 0; t < 256; t++) {
		p1 = ptmp + (float)histo[t] / (float)(height * width);
		if (p1 == 0.) mean1 = 0.;
		else mean1 = (ptmp * mtmp + (float)(t * histo[t] / (float)(height * width))) / p1;
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
}

void labeling() {
	// Top-down
	for (int i = 0; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			if (lab[i * width + j] != 0 && lab[i * width + j + 1] != 0 && lab[i * width + j] != lab[i * width + j + 1]) {
				if (lab[i * width + j] < lab[i * width + j + 1]) lab[i * width + j + 1] = lab[i * width + j];
				else lab[i * width + j + 1] = lab[i * width + j];
			}

			if (lab[i * width + j] != 0 && lab[(i + 1) * width + j + 1] != 0 && lab[i * width + j] != lab[(i + 1) * width + j + 1]) {
				if (lab[i * width + j] < lab[(i + 1) * width + j + 1]) lab[(i + 1) * width + j + 1] = lab[i * width + j];
				else  lab[(i + 1) * width + j + 1] = lab[i * width + j];
			}

			if (lab[i * width + j] != 0 && lab[(i + 1) * width + j] != 0 && lab[i * width + j] != lab[(i + 1) * width + j]) {
				if (lab[i * width + j] < lab[(i + 1) * width + j]) lab[(i + 1) * width + j] = lab[i * width + j];
				else  lab[(i + 1) * width + j] = lab[i * width + j];
			}

			if (lab[i * width + j] != 0 && lab[(i + 1) * width + j - 1] != 0 && lab[i * width + j] != lab[(i + 1) * width + j - 1]) {
				if (lab[i * width + j] < lab[(i + 1) * width + j - 1]) lab[(i + 1) * width + j - 1] = lab[i * width + j];
				else  lab[(i + 1) * width + j - 1] = lab[i * width + j];
			}


		}
	}

	// Bottom-up pass
	for (int i = height - 1; i > 0; i--) {
		for (int j = width - 2; j > 0; j--) {
			if (lab[i * width + j] != 0 && lab[i * width + j - 1] != 0 && lab[i * width + j] != lab[i * width + j - 1]) {
				if (lab[i * width + j] < lab[i * width + j - 1]) lab[i * width + j - 1] = lab[i * width + j];
				else  lab[i * width + j - 1] = lab[i * width + j];
			}
			if (lab[i * width + j] != 0 && lab[(i - 1) * width + j - 1] != 0 && lab[i * width + j] != lab[(i - 1) * width + j - 1]) {
				if (lab[i * width + j] < lab[(i - 1) * width + j - 1]) lab[(i - 1) * width + j - 1] = lab[i * width + j];
				else  lab[(i - 1) * width + j - 1] = lab[i * width + j];
			}
			if (lab[i * width + j] != 0 && lab[(i - 1) * width + j] != 0 && lab[i * width + j] != lab[(i - 1) * width + j]) {
				if (lab[i * width + j] < lab[(i - 1) * width + j - 1]) lab[(i - 1) * width + j] = lab[i * width + j];
				else  lab[(i - 1) * width + j] = lab[i * width + j];
			}
			if (lab[i * width + j] != 0 && lab[(i - 1) * width + j + 1] != 0 && lab[i * width + j] != lab[(i - 1) * width + j + 1]) {
				if (lab[i * width + j] < lab[(i - 1) * width + j + 1]) lab[(i - 1) * width + j + 1] = lab[i * width + j];
				else  lab[(i - 1) * width + j + 1] = lab[i * width + j];
			}
		}
	}
}

void efficient_2_pass_algorithm() {

	// 관심 값에 번호 할당
	lab = malloc(height * width * sizeof(int));

	int count = 1;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (outImg[i * width + j] == 255) {
				lab[i * width + j] = count;
				count++;
			}
			else {
				lab[i * width + j] = 0;
			}
		}
	}
	
	// labeling
	int i = 0;
	do {
		labeling();
		printf(">> operation : %d\n", i++);
	} while (check() == 1);

	// renumbering

	// 면적 구하기
	int* number = malloc(height * width * sizeof(int));
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			number[i * width + j] = 0;
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (lab[i * width + j] != 0) {
				number[lab[i * width + j]]++;
			}
		}
	}

	// 작은 영역 제거
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (outImg[i * width + j] != 0) {
				if (number[lab[i * width + j]] <= 100) {
					outImg[i * width + j] = 0;
				}
			}
		}
	}

	pgm_write(outImg, "2-1.pgm");
	
	free(number);
}

int check() {
	for (int i = 0; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			if (lab[i * width + j] != 0 && lab[i * width + j + 1] != 0 && lab[i * width + j] != lab[i * width + j + 1])
				return 0;
			if (lab[i * width + j] != 0 && lab[(i + 1) * width + j + 1] != 0 && lab[i * width + j] != lab[(i + 1) * width + j + 1])
				return 0;
			if (lab[i * width + j] != 0 && lab[(i + 1) * width + j] != 0 && lab[i * width + j] != lab[(i + 1) * width + j])
				return 0;
			if (lab[i * width + j] != 0 && lab[(i + 1) * width + j - 1] != 0 && lab[i * width + j] != lab[(i + 1) * width + j - 1])
				return 0;

		}
	}
	return 1;
}

void main()
{
	bmp_read();
	histogram();
	otsu();
	efficient_2_pass_algorithm();

	free(inImg);
	free(outImg);
	free(lab);
}
