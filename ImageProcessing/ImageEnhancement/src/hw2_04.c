#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define BYTE    unsigned char

void unsharpMasking() {

	// bmp 파일 읽기
	FILE* bmp_fp;

	if ((bmp_fp = fopen("Pentagon.bmp", "rb")) == NULL) {
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
	int height = hInfo.biHeight, width = hInfo.biWidth;

	fclose(bmp_fp);

	// raw 이미지를 저장할 변수 선언
	BYTE* inImg = malloc(height * width);

	// raw 파일 읽기
	FILE* raw_fp;

	if ((raw_fp = fopen("Pentagon.raw", "rb")) == NULL) {
		printf("No Image File");
		return;
	}
	fread(inImg, height * width, sizeof(char), raw_fp);

	fclose(raw_fp);

	BYTE* blurImg = malloc(height * width);
	BYTE* subImg = malloc(height * width);
	BYTE* outImg = malloc(height * width);

	/* unsharp masking */

	/* 1. LPF */
	int tmp_s, w = 5;
	int tmp_width, tmp_height = 0;
	
	for (int i = 1; i < height - 1; i++)
		for (int j = 1; j < width - 1; j++) {
			tmp_s = 0;
			for (int k = i - w / 2; k <= i + w / 2; k++)
				for (int l = j - w / 2; l <= j + w / 2; l++) {
					if (k < 0) tmp_height = i + (i - k);
					else if (k >= height) tmp_height = i - (k - i);
					else tmp_height = k;

					if (l < 0) tmp_width = j + (j - l);
					else if (l >= width) tmp_width = j - (l - j);
					else tmp_width = l;

					tmp_s += inImg[tmp_height * width + tmp_width];
				}
			blurImg[i * width + j] = (int)((float)tmp_s / (w * w) + 0.5);

		}
	
	/* 2. Subtrac */
	int tmp = 0;
	float alpha = 0.3;
	for (int i = 1; i < height - 1; i++)
		for (int j = 1; j < width - 1; j++) {
			tmp = (int)(inImg[i * width + j] +
				alpha * (inImg[i * width + j] - blurImg[i * width + j])+ 0.5);
			if (tmp > 255) outImg[i * width + j] = 255;
			else if (tmp < 0) outImg[i * width + j] = 0;
			else outImg[i * width + j] = tmp;

		}

	// pgm 파일로 내보내기
	FILE* out = fopen("Pentagon_um.pgm", "wb"); // 노이즈 영상
	fprintf(out, "P5\n");//magic no.
	fprintf(out, "%d %d\n", width, height);
	fprintf(out, "255\n");//max. value
	fwrite(outImg, sizeof(char), height * width, out);

	fclose(out);

	// 메모리 해제
	free(inImg);
	free(blurImg);
	free(outImg);
}

void main() {
	unsharpMasking();
}