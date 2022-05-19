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

int mid(int arr[], int n) {
	int temp;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	return arr[n / 2];
}

void medianFilter() {

	// bmp 파일 읽기
	FILE* bmp_fp;

	if ((bmp_fp = fopen("Lena.bmp", "rb")) == NULL) {
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

	if ((raw_fp = fopen("Lena.raw", "rb")) == NULL) {
		printf("No Image File");
		return;
	}
	fread(inImg, height * width, sizeof(char), raw_fp);

	fclose(raw_fp);

	/* salt&pepper 잡음 생성 */
	BYTE* tmpImg = malloc(height * width);
	BYTE* outImg = malloc(height * width);

	int x, y, SorP;

	srand(time(NULL));

	for (int i = 0; i < height * width * 0.05; i++) {
		x = rand() % width; // generate x coordinate
		y = rand() % height; // generate y coordinate
		SorP = rand() % 2; // salt or pepper?
		if (SorP) inImg[y * width + x] = 255;//salt
		else inImg[y* width + x] = 0; // pepper
	}
	
	/* 1*5 median(중간값) 필터 적용(separable) */

	int w = 5;
	int tmpArr[5] = {0, 0, 0, 0, 0};
	int tmp_width, tmp_height = 0;
	int k;
	// horizontal average
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			k = 0;
			tmpArr[0] = 0;
			tmpArr[1] = 0;
			tmpArr[2] = 0;
			tmpArr[3] = 0;
			tmpArr[4] = 0;
			for (int l = j - w / 2; l <= j + w / 2; l++) {
				if (l < 0) tmp_width = j + (j - l);
				else if (l >= width) tmp_width = j - (l - j);
				else tmp_width = l;

				tmpArr[k] = inImg[i * width + tmp_width];
				k++;
			}
			tmpImg[i * width + j] = mid(tmpArr, w);
		}

	int l;
	// vertical average
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			l = 0;
			tmpArr[0] = 0;
			tmpArr[1] = 0;
			tmpArr[2] = 0;
			tmpArr[3] = 0;
			tmpArr[4] = 0;
			for (int k = i - w / 2; k <= i + w / 2; k++) {
				if (k < 0) tmp_height = i + (i - k);
				else if (k >= height) tmp_height = i - (k - i);
				else tmp_height = k;

				tmpArr[l] += tmpImg[tmp_height * width + j];
				l++;
			}
			outImg[i * width + j] = mid(tmpArr, w);
		}

	// pgm 파일로 내보내기
	
	FILE* out1 = fopen("Lena_noisy.pgm", "wb"); // 노이즈 영상
	fprintf(out1, "P5\n");//magic no.
	fprintf(out1, "%d %d\n", width, height);
	fprintf(out1, "255\n");//max. value
	fwrite(inImg, sizeof(char), height * width, out1);

	fclose(out1);

	FILE* out2 = fopen("Lena_medianFilter.pgm", "wb"); // 필터 적용 영상
	fprintf(out2, "P5\n");//magic no.
	fprintf(out2, "%d %d\n", width, height);
	fprintf(out2, "255\n");//max. value
	fwrite(outImg, sizeof(char), height * width, out2);
	fclose(out2);

	// 메모리 해제
	free(inImg);
	free(outImg);
}

void main() {
	medianFilter();
}