#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>

#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define BYTE    unsigned char

void filter2D() {

	// bmp ���� �б�
	FILE* bmp_fp;

	if ((bmp_fp = fopen("Snow.bmp", "rb")) == NULL) {
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

	if ((raw_fp = fopen("Snow.raw", "rb")) == NULL) {
		printf("No Image File");
		return;
	}
	fread(inImg, height * width, sizeof(char), raw_fp);

	fclose(raw_fp);

	/* 21��21 2���� ��� ����(����ġ�� ������) */
	BYTE* outImg = malloc(height * width); // ��� ����

	int tmp_s, w = 21;

	int tmp_width, tmp_height = 0;

	for (int i = 0; i< height; i++)
		for (int j = 0; j < width; j++) {
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
			outImg[i * width + j] = (int)((float)tmp_s / (w * w) + 0.5);
			
		}

	// pgm ���Ϸ� ��������
	FILE* out = fopen("Snow_filter2D.pgm", "wb");
	fprintf(out, "P5\n");//magic no.
	fprintf(out, "%d %d\n", width, height);
	fprintf(out, "255\n");//max. value
	fwrite(outImg, sizeof(char), height * width, out);
	fclose(out);

	// ���� �Ҵ� ����
	free(inImg);
	free(outImg);
}

void filter1D() {

	// bmp ���� �б�
	FILE* bmp_fp;

	if ((bmp_fp = fopen("Snow.bmp", "rb")) == NULL) {
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

	if ((raw_fp = fopen("Snow.raw", "rb")) == NULL) {
		printf("No Image File");
		return;
	}
	fread(inImg, height * width, sizeof(char), raw_fp);

	fclose(raw_fp);

	/* 1��21 1���� ��� ���͸� ��� ���������� ���� ���� */
	BYTE* tmpImg = malloc(height * width);
	BYTE* outImg = malloc(height * width); // ��� ����

	int tmp_s, w = 21;

	int tmp_width, tmp_height = 0;

	// horizontal average
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			tmp_s = 0;
			for (int l = j - w / 2; l <= j + w / 2; l++) {
					if (l < 0) tmp_width = j + (j - l);
					else if (l >= width) tmp_width = j - (l - j);
					else tmp_width = l;

					tmp_s += inImg[i * width + tmp_width];
				}
			tmpImg[i*width + j] = (int)((float) tmp_s / w + 0.5);
		}

	// vertical average
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			tmp_s = 0;
			for (int k = i - w / 2; k <= i + w / 2; k++) {
				if (k < 0) tmp_height = i + (i - k);
				else if (k >= height) tmp_height = i - (k - i);
				else tmp_height = k;

				tmp_s += tmpImg[tmp_height * width + j];
			}
			outImg[i * width + j] = (int)((float) tmp_s / w + 0.5);
		}


	// pgm ���Ϸ� ��������
	FILE* out = fopen("Snow_filter1D.pgm", "wb");
	fprintf(out, "P5\n");//magic no.
	fprintf(out, "%d %d\n", width, height);
	fprintf(out, "255\n");//max. value
	fwrite(outImg, sizeof(char), height * width, out);
	fclose(out);

	// ���� �Ҵ� ����
	free(inImg);
	free(outImg);
}

void filter2DWithIntegralImg() {
	// bmp ���� �б�
	FILE* bmp_fp;

	if ((bmp_fp = fopen("Snow.bmp", "rb")) == NULL) {
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

	if ((raw_fp = fopen("Snow.raw", "rb")) == NULL) {
		printf("No Image File");
		return;
	}
	fread(inImg, height * width, sizeof(char), raw_fp);

	fclose(raw_fp);

	/* ���� ���� ���� */
	unsigned int* integralImg = malloc(sizeof(unsigned int) * height * width); // ���� ����
	BYTE* outImg = malloc(height * width); // ��� ����

	/* ���� */
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			integralImg[i * width + j] = (unsigned int)inImg[i * width + j];
		}
	}

	// 1 - ���� ����
	for (int i = 0; i < height; i++) {
		for (int j = 1; j < width; j++) {
			integralImg[i * width + j] += integralImg[i * width + j - 1];
		}
	}

	//2. ���� ����
	for (int i = 0; i < width; i++) {
		for (int j = 1; j < height; j++) {
			integralImg[j * width + i] += integralImg[(j - 1) * width + i];
		}
	}

	// 3. ����ȭ
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImg[i * width + j]= (BYTE)((float)integralImg[i * width + j] / integralImg[height * width - 1] * 255 + 0.5);

		}
	}

	// pgm ���Ϸ� ��������
	FILE* out = fopen("Snow_intergral_img.pgm", "wb");
	fprintf(out, "P5\n");//magic no.
	fprintf(out, "%d %d\n", width, height);
	fprintf(out, "255\n");//max. value
	fwrite(outImg, sizeof(char), height * width, out);
	fclose(out);

	/* 21��21 2���� ��� ����(����ġ�� ������) */
	BYTE* outImg2 = malloc(height * width); // ��� ����

	int w = 21;

	int x1, x2, y1, y2 = 0;
	int tmp_s;

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++) {
			if (j - w / 2 < 0) x1 = 0;
			else x1 = j - w / 2;
			if (j + w / 2 >= width) x2 = width - 1;
			else x2 = j + w / 2;
			if (i - w / 2 < 0) y1 = 0;
			else y1 = i - w / 2;
			if (i + w / 2 >= height) y2 = height - 1;
			else y2 = i + w / 2;

			tmp_s = integralImg[y2 * width + x2] - integralImg[y1 * width + x2]
				- integralImg[y2 * width + x1] + integralImg[y1 * width + x1];
			outImg2[i * width + j] = (int)((float)tmp_s / (w * w) + 0.5);

		}

	// pgm ���Ϸ� ��������
	FILE* out2 = fopen("Snow_filter_interImg.pgm", "wb");
	fprintf(out2, "P5\n");//magic no.
	fprintf(out2, "%d %d\n", width, height);
	fprintf(out2, "255\n");//max. value
	fwrite(outImg2, sizeof(char), height * width, out);
	fclose(out2);

	// ���� �Ҵ� ����
	free(inImg);
	free(integralImg);
	free(outImg);
	free(outImg2);
}


void main() {
	double start, end;

	start = (double)clock() / CLOCKS_PER_SEC;
	filter2D();
	end = (((double)clock()) / CLOCKS_PER_SEC);
	printf("1�� ���� ���� �ð�(filter2D()) : %lf\n", end - start);

	start = (double)clock() / CLOCKS_PER_SEC;
	filter1D();
	end = (((double)clock()) / CLOCKS_PER_SEC);
	printf("2�� ���� ���� �ð�(filter1D()) : %lf\n", end - start);

	start = (double)clock() / CLOCKS_PER_SEC;
	filter2DWithIntegralImg();
	end = (((double)clock()) / CLOCKS_PER_SEC);
	printf("3-4�� ���� ���� �ð�(filter2DWithIntegralImg()) : %lf\n", end - start);
}