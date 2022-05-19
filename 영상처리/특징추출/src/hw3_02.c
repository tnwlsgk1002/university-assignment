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

int height, width;

unsigned int* ix2;
unsigned int* iy2;
unsigned int* ixy;

unsigned int* gx2;
unsigned int* gy2;
unsigned int* gxy;

float* r;

void bmp_read() {
	// bmp 파일 읽기
	FILE* bmp_fp;

	if ((bmp_fp = fopen("Ctest.bmp", "rb")) == NULL) {
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

	if ((raw_fp = fopen("Ctest.raw", "rb")) == NULL) {
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

void sobel_operator() {

	int nx[3][3] = { -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	int ny[3][3] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
	int dx, dy;

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			dx = dy = 0;
			for (int k = -1; k < 2; k++) {
				for (int l = -1; l < 2; l++) {
					dx += nx[1 + k][1 + l] * inImg[(i + k) * width + j + l];
					dy += ny[1 + k][1 + l] * inImg[(i + k) * width + j + l];
				}
			}
			ix2[i * width + j] = dx * dx;
			iy2[i * width + j] = dy * dy;
			ixy[i * width + j] = abs(dx) + abs(dy);
		}
	}
}

void blurring() {
	int tmp_x, tmp_y, tmp_xy;

	int tmp_width, tmp_height = 0;

	for (int i = (int)(SIZE/2); i < height - (int)(SIZE / 2); i++)
		for (int j = (int)(SIZE / 2); j < width - (int)(SIZE / 2); j++) {
			tmp_x = tmp_y = tmp_xy = 0;
			for (int k = i - (int)(SIZE / 2); k <= i + (int)(SIZE / 2); k++) {
				for (int l = j - (int)(SIZE / 2); l <= j + (int)(SIZE / 2); l++) {
					tmp_x += ix2[i * width + k];
					tmp_y += iy2[i * width + k];
					tmp_xy += ixy[i * width + k];
				}
				gx2[i * width + j] = (int)((float)tmp_x / SIZE * SIZE + 0.5);
				gy2[i * width + j] = (int)((float)tmp_y / SIZE * SIZE + 0.5);
				gxy[i * width + j] = (int)((float)tmp_xy / SIZE * SIZE + 0.5);
			}
		}
}

void harris_corner_response_function() {
	double lambda = 0.05;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			r[i * width + j] = ((ix2[i * width + j] * iy2[i * width + j])
				- ixy[i * width + j]
				- (lambda * (ix2[i * width + j] * iy2[i * width + j]) * (ix2[i * width + j] * iy2[i * width + j])));
		}
	}
}

void thresholding() {
	int t = 0.01;
	for (int i = 2; i < height - 2; i++) {
		for (int j = 2; j < width - 2; j++) {
			if (t < r[i * width + j])
				outImg[i * width + j] = 255;
			else 
				outImg[i * width + j] = 0;
		}
	}
}

void main()
{
	bmp_read();
	
	/* harris_corner_detector */
	outImg = malloc(height * width);

	ix2 = malloc(height * width * sizeof(int));
	iy2 = malloc(height * width * sizeof(int));
	ixy = malloc(height * width * sizeof(int));

	gx2 = malloc(height * width * sizeof(int));
	gy2 = malloc(height * width * sizeof(int));
	gxy = malloc(height * width * sizeof(int));

	r = malloc(height * width * sizeof(float));

	sobel_operator(); // 1) Sobel operator 적용하여 세 가지 영상 계산
	blurring(); // 2) 1)의 각 영상에 5*5 균일 가중치 평균 계산(블러링)
	harris_corner_response_function(); // 2)에 대해서 Harris Corner Response Function 영상 계산
	thresholding(); // 4) R[x][y] > 0.01보다 큰 경우, 모서리로 판단하여 출력함

	pgm_write(outImg, "2-1.pgm");

	free(inImg);

	free(ix2);
	free(iy2);
	free(ixy);

	free(gx2);
	free(gy2);
	free(gxy);

	free(r);
	free(outImg);
}
