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

void zeroOrder() {

	// bmp ���� �б�
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

	// ������ ũ�� ���� �б�
	int height = hInfo.biHeight, width = hInfo.biWidth;

	fclose(bmp_fp);

	// raw �̹����� ������ ���� ����
	BYTE* inImg = malloc(height * width);

	// raw ���� �б�
	FILE* raw_fp;

	if ((raw_fp = fopen("Lena.raw", "rb")) == NULL) {
		printf("No Image File");
		return;
	}
	fread(inImg, height * width, sizeof(char), raw_fp);

	fclose(raw_fp);

	/* 0�� ���� */
	BYTE* tmpImg = malloc(height * width * 4); // 1��Ÿ�� ó��
	BYTE* outImg = malloc(height * width * 16); // 2��Ÿ�� ó��

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			tmpImg[(2 * i) * 2 * width + j * 2] = inImg[i * width + j];
			tmpImg[(2 * i) * 2 * width + j * 2 + 1] = inImg[i * width + j];
			tmpImg[(2 * i + 1) * 2 * width + j * 2] = inImg[i * width + j];
			tmpImg[(2 * i + 1) * 2 * width + j * 2 + 1] = inImg[i * width + j];
		}
	}

	for (int i = 0; i < height * 2; i++) {
		for (int j = 0; j < width * 2; j++) {
			outImg[(2 * i) * 4 * width + j * 2] = tmpImg[i * width * 2 + j];
			outImg[(2 * i) * 4 * width + j * 2 + 1] = tmpImg[i * width * 2 + j];
			outImg[(2 * i + 1) * 4 * width + j * 2] = tmpImg[i * width * 2 + j];
			outImg[(2 * i + 1) * 4 * width + j * 2 + 1] = tmpImg[i * width * 2 + j];
		}
	}

	// pgm ���Ϸ� ��������
	FILE* out = fopen("Lena_zero_order.pgm", "wb");
	fprintf(out, "P5\n");//magic no.
	fprintf(out, "%d %d\n", width*4, height*4);
	fprintf(out, "255\n");//max. value
	fwrite(outImg, sizeof(char), height * width * 16, out);

	fclose(out);

	// �޸� ����
	free(inImg);
	free(tmpImg);
	free(outImg);
}

void firstOrder() {

	// bmp ���� �б�
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

	// ������ ũ�� ���� �б�
	int height = hInfo.biHeight, width = hInfo.biWidth;

	fclose(bmp_fp);

	// raw �̹����� ������ ���� ����
	BYTE* inImg = malloc(height * width);

	// raw ���� �б�
	FILE* raw_fp;

	if ((raw_fp = fopen("Lena.raw", "rb")) == NULL) {
		printf("No Image File");
		return;
	}
	fread(inImg, height * width, sizeof(char), raw_fp);

	fclose(raw_fp);

	/* 1�� ���� */
	BYTE* tmpImg = malloc(height * width * 4); // 1��Ÿ�� ó��
	BYTE* outImg = malloc(height * width * 16); // 2��Ÿ�� ó��

	int a, b, c, d;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
		
			a = inImg[i * width + j];
			if (i + 1 == height && j + 1 == width) {
				b = a;
				c = a;
				d = a;
			}
			else if (j + 1 == width) {
				b = a;
				c = inImg[(i + 1) * width + j];
				d = c;
			}
			else if (i + 1 == height) {
				b = inImg[i * width + j + 1];
				c = a;
				d = b;
			}
			else {
				b = inImg[i * width + j + 1];
				c = inImg[(i + 1) * width + j];
				d = inImg[(i + 1) * width + j + 1];
			}
			tmpImg[(2 * i) * 2 * width + j * 2] = a;
			tmpImg[(2 * i) * 2 * width + j * 2 + 1] = (a + b) / 2;
			tmpImg[(2 * i + 1) * 2 * width + j * 2] = (a + c) / 2;
			tmpImg[(2 * i + 1) * 2 * width + j * 2 + 1] = (a + b + c + d) / 4;
		}
	}

	for (int i = 0; i < height * 2; i++) {
		for (int j = 0; j < width * 2; j++) {
			a = tmpImg[i * width * 2 + j];
			if (i + 1 == height * 2 && j + 1 == width * 2) {
				b = a;
				c = a;
				d = a;
			}
			else if (j + 1 == width * 2) {
				b = a;
				c = tmpImg[(i + 1) * width * 2 + j];
				d = c;
			}
			else if (i + 1 == height * 2) {
				b = tmpImg[i * width * 2 + j + 1];
				c = a;
				d = b;
			}
			else {
				b = tmpImg[i * width * 2 + j + 1];
				c = tmpImg[(i + 1) * width * 2 + j];
				d = tmpImg[(i + 1) * width * 2 + j + 1];
			}

			outImg[(2 * i) * 4 * width + j * 2] = a;
			outImg[(2 * i) * 4 * width + j * 2 + 1] = (a + b) / 2;
			outImg[(2 * i + 1) * 4 * width + j * 2] = (a + c) / 2;
			outImg[(2 * i + 1) * 4 * width + j * 2 + 1] = (a + b + c + d) / 4;
		}
	}

	// pgm ���Ϸ� ��������
	FILE* out = fopen("Lena_frist_order.pgm", "wb");
	fprintf(out, "P5\n");//magic no.
	fprintf(out, "%d %d\n", width * 4, height * 4);
	fprintf(out, "255\n");//max. value
	fwrite(outImg, sizeof(char), height * width * 16, out);

	fclose(out);

	// �޸� ����
	free(inImg);
	free(tmpImg);
	free(outImg);

}

void main() {
	zeroOrder(); // 0�� ����
	firstOrder(); // 1�� ����
}

