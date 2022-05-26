#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define BYTE    unsigned char

void bmpToPGM()
{
	FILE* infile;

	if ((infile = fopen("ImgBW.bmp", "rb")) == NULL) {
		printf("No Image File");
		return;
	}

	// BMP Header Information
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hInfo;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, infile);//14 bytes
	//if (hf.bfType != 0x4D42) exit(1);//"BM"
	printf("bfType : 0x%x\n", hf.bfType);
	printf("bfSize : %ldBytes\n", hf.bfSize);
	printf("bfReserved1 : %x\n", hf.bfReserved1);
	printf("bfReserved2 : %x\n", hf.bfReserved2);
	printf("bfOffBits : %ldBytes = 14 + 40 + %ld(Pallete size)\n\n", hf.bfOffBits, hf.bfOffBits - 54);

	_getch();

	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, infile);//40 bytes
//	if (hInfo.biBitCount != 8) { printf("Bad File Format!!"); return; }//BW
	printf("biSize : %ldBytes\n", hInfo.biSize);
	printf("Image Size : %ld x %ld -> %ld x %ld\n", hInfo.biWidth, hInfo.biHeight, WIDTHBYTES(hInfo.biBitCount * hInfo.biWidth), hInfo.biHeight);
	printf("biPlanes : %d\n", hInfo.biPlanes);
	printf("biBitCount : %d\n", hInfo.biBitCount);
	printf("biCompression : %ld\n", hInfo.biCompression);
	printf("biSizeImage : %ldBytes\n", hInfo.biSizeImage);
	printf("biXPelsPerMeter : %ld\n", hInfo.biXPelsPerMeter);
	printf("biYPelsPerMeter : %ld\n", hInfo.biYPelsPerMeter);
	printf("biClrUsed : %ld\n", hInfo.biClrUsed);
	printf("biClrImportant : %ld\n\n", hInfo.biClrImportant);

	_getch();

	// BMP Pallete
	RGBQUAD hRGB[256];
	printf("sizeofRGBQUAD : %d\n", sizeof(RGBQUAD));
	_getch();
	fread(hRGB, sizeof(RGBQUAD), 256, infile);//read color pallete
	for (int i = 0; i < (int)pow(2, hInfo.biBitCount); i++) {
		printf("[%3d] B:%3d G:%3d R:%3d Res:%3d\n", i, hRGB[i].rgbBlue, hRGB[i].rgbGreen, hRGB[i].rgbRed, hRGB[i].rgbReserved);
		//_getch();
	}


	// Memory
	//BYTE *lpImg = new BYTE[hInfo.biSizeImage];//for c++
	BYTE* lpImg = malloc(hInfo.biSizeImage);//for c
	fread(lpImg, sizeof(char), hInfo.biSizeImage, infile);
	fclose(infile);

	int rwsize = WIDTHBYTES(hInfo.biBitCount * hInfo.biWidth);

	int h = hInfo.biHeight, w = hInfo.biWidth;

	/* 헤더교체(bmp->pgm)/ 행 별로 삽입된 빈 data제거 후 저장 */
	BYTE* bwImg_rmEmpty = malloc(h * w);

	// Image making
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			
			bwImg_rmEmpty[i * w + j] = lpImg[i * rwsize + j];
		}

	// Image Write
	FILE* out1 = fopen("bwImg-rmEmpty.pgm", "wb");
	fprintf(out1, "P5\n");//magic no.
	fprintf(out1, "%d %d\n", w, h);
	fprintf(out1, "255\n");//max. value
	fwrite(bwImg_rmEmpty, sizeof(char), h * w, out1);
	fclose(out1);

	/* 최종 행 순서 정렬 후 저장 */
	BYTE* bwImg_sort = malloc(h * w);

	int new_y;

	for (int i = 0; i < h; i++) {
		new_y = h - i - 1 ;
		for (int j = 0; j < w; j++) {
			bwImg_sort[i * w + j] = bwImg_rmEmpty[new_y * w + j];
		}
	}

	// Image Write
	FILE* out2 = fopen("bwImg-sort.pgm", "wb");
	fprintf(out2, "P5\n");//magic no.
	fprintf(out2, "%d %d\n", w, h);
	fprintf(out2, "255\n");//max. value
	fwrite(bwImg_sort, sizeof(char), h * w, out2);
	fclose(out2);

	free(lpImg);
	free(bwImg_rmEmpty);
	free(bwImg_sort);
}

void bmpToPPM() {
	FILE* infile;

	if ((infile = fopen("ImgColor.bmp", "rb")) == NULL) {
		printf("No Image File");
		return;
	}

	// BMP Header Information
	BITMAPFILEHEADER hf;
	BITMAPINFOHEADER hInfo;
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, infile);//14 bytes
	if (hf.bfType != 0x4D42) exit(1);//"BM"
	printf("\n\nbfType : 0x%x\n", hf.bfType);
	printf("bfSize : %ldBytes\n", hf.bfSize);
	printf("bfReserved1 : %x\n", hf.bfReserved1);
	printf("bfReserved2 : %x\n", hf.bfReserved2);
	printf("bfOffBits : %ldBytes = 14 + 40 + %ld(Pallete size)\n\n", hf.bfOffBits, hf.bfOffBits - 54);

	_getch();

	fread(&hInfo, sizeof(BITMAPINFOHEADER), 1, infile);//40 bytes
	if (hInfo.biBitCount != 24) { printf("Bad File Format!!"); return; }//24-bit
	printf("biSize : %ldBytes\n", hInfo.biSize);
	printf("Image Size : %ld x %ld -> %ld x %ld\n", hInfo.biWidth, hInfo.biHeight, WIDTHBYTES(hInfo.biBitCount * hInfo.biWidth), hInfo.biHeight);
	printf("biPlanes : %d\n", hInfo.biPlanes);
	printf("biBitCount : %d\n", hInfo.biBitCount);
	printf("biCompression : %ld\n", hInfo.biCompression);
	printf("biSizeImage : %ldBytes\n", hInfo.biSizeImage);
	printf("biXPelsPerMeter : %ld\n", hInfo.biXPelsPerMeter);
	printf("biYPelsPerMeter : %ld\n", hInfo.biYPelsPerMeter);
	printf("biClrUsed : %ld\n", hInfo.biClrUsed);
	printf("biClrImportant : %ld\n\n", hInfo.biClrImportant);

	_getch();

	// BMP Pallete, There's no pallete in the true color.
	//RGBQUAD hRGB[256];
	//fread(hRGB, sizeof(RGBQUAD), 256, infile);//read color pallete

	// Memory
	BYTE* lpImg = malloc(hInfo.biSizeImage);//for c
	fread(lpImg, sizeof(char), hInfo.biSizeImage, infile);
	fclose(infile);

	int rwsize = WIDTHBYTES(hInfo.biBitCount * hInfo.biWidth);
	int h = hInfo.biHeight, w = hInfo.biWidth;

	/* 헤더교체(bmp->ppm)/행 별로 삽입된 빈 data제거 후 저장 */
	BYTE* colorImg_rmEmpty = malloc(h * w * 3);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++)
			for (int k = 0; k < 3; k++)
				colorImg_rmEmpty[i * w * 3 + j * 3 + k] = lpImg[i * rwsize + j * 3 + k];
	}

	FILE* out1 = fopen("colorImg-rmEmpty.ppm", "wb");
	fprintf(out1, "P6\n");//magic no.
	fprintf(out1, "%d %d\n", w, h);
	fprintf(out1, "255\n");//max. value
	fwrite(colorImg_rmEmpty, sizeof(char), h * w * 3, out1);
	fclose(out1);

	/* RGB로 색채널을 변경 후 저장 */
	BYTE* colorImg_RGB = malloc(h * w * 3);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++)
			for (int k = 0; k < 3; k++) {
				if (k == 0) // R
					colorImg_RGB[i * w * 3 + j * 3 + k] = colorImg_rmEmpty[i * w * 3 + j * 3 + 2];
				else if (k == 1) // G
					colorImg_RGB[i * w * 3 + j * 3 + k] = colorImg_rmEmpty[i * w * 3 + j * 3 + 1];
				else if (k == 2) // B
					colorImg_RGB[i * w * 3 + j * 3 + k] = colorImg_rmEmpty[i * w * 3 + j * 3 + 0];
			}
	}

	FILE* out2 = fopen("colorImg-RGB.ppm", "wb");
	fprintf(out2, "P6\n");//magic no.
	fprintf(out2, "%d %d\n", w, h);
	fprintf(out2, "255\n");//max. value
	fwrite(colorImg_RGB, sizeof(char), h * w * 3, out2);
	fclose(out2);

	/* 최종 행 순서 정렬 후 저장 */
	BYTE* colorImg_sort = malloc(h * w * 3);
	int new_y = 0;
	for (int i = 0; i < h; i++) {
		new_y = h - i - 1;
		for (int j = 0; j < w; j++)
			for (int k = 0; k < 3; k++)
				colorImg_sort[i * w * 3 + j * 3 + k] = colorImg_RGB[new_y * w * 3 + j * 3 + k];
	}

	FILE* out3 = fopen("colorImg-sort.ppm", "wb");
	fprintf(out3, "P6\n");//magic no.
	fprintf(out3, "%d %d\n", w, h);
	fprintf(out3, "255\n");//max. value
	fwrite(colorImg_sort, sizeof(char), h * w * 3, out3);
	fclose(out3);

	free(lpImg);
	free(colorImg_rmEmpty);
	free(colorImg_RGB);
	free(colorImg_sort);
}

void main() {
	bmpToPGM();
	bmpToPPM();
}