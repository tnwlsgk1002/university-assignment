#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define BYTE    unsigned char

void histogramSpecification() {

	// bmp ���� �б�
	FILE* bmp_fp;

	if ((bmp_fp = fopen("publicSquare.bmp", "rb")) == NULL) {
		printf("No Image File");
		return;
	}

	// BMP Header Information
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hInfo;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, bmp_fp);//14 bytes

	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, bmp_fp);//40 bytes
	//printf(hInfo.biBitCount);

	// ������ ũ�� ���� �б�
	int height = hInfo.biHeight, width = hInfo.biWidth;

	fclose(bmp_fp);

	// raw �̹����� ������ ���� ����
	BYTE* inImg = malloc(height * width);

	// raw ���� �б�
	FILE* raw_fp;

	if ((raw_fp = fopen("publicSquare.raw", "rb")) == NULL) {
		printf("No Image File");
		return;
	}
	fread(inImg, height * width, sizeof(char), raw_fp);

	fclose(raw_fp);

	/* ������׷� ��ȭ */
	BYTE* outImg = malloc(height * width); // ��� ����

	int hist[256];
	float pdf[256];
	float d_pdf[256];

	// �Է� ���� histogram �����
	for (int i = 0; i < 256; i++)
		hist[i] = 0;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			hist[inImg[i * width + j]]++;

	for (int i = 0; i < 256; i++)
		pdf[i] = ((float)hist[i] / (height * width));

	for (int i = 1; i < 256; i++)
		pdf[i] += pdf[i - 1];

	// d_pdf �����
	for (int i = 0; i < 256; i++) {
		d_pdf[i] = (float)i * 2 / (255 * 255);
	}

	for (int i = 1; i < 256; i++)
		d_pdf[i] += d_pdf[i - 1];

	// min(Wn - W >= 0)
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) { 
			if (pdf[i] <= d_pdf[j]) {
				pdf[i] = j;
				break;
			}
		}
	}

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			outImg[i* width +j] = (BYTE)pdf[inImg[i * width + j]];
		}

	// pgm ���Ϸ� ��������
	FILE* out = fopen("public_square_hs.pgm", "wb");
	fprintf(out, "P5\n");//magic no.
	fprintf(out, "%d %d\n", width, height);
	fprintf(out, "255\n");//max. value
	fwrite(outImg, sizeof(char), height * width, out);
	fclose(out);

	// �޸� ����
	free(inImg);
	free(outImg);
}

void main() {
	histogramSpecification();
}