#include "PPMfile.h"
#pragma warning(disable:4996)


PPMimage::PPMimage()
{
	M = 0;
	N = 0;
	width = 0;
	height = 0;
	max = 0;
	pixels = 0;
}

int PPMimage::exist_PPMimage()
{
	if (pixels == 0)
		return 1;
	return 0;
}

PPMimage::PPMimage(PPMimage &img)
{
	M = img.M;
	N = img.N;
	height = img.height;
	width = img.width;
	max = img.max;

	pixels = (unsigned char**)calloc(img.height, sizeof(unsigned char*));

	for (int i = 0; i < img.height; i++)
		pixels[i] = (unsigned char*)calloc(img.width * 3, sizeof(unsigned char));

	for (int i = 0; i < img.height; i++)
		for (int j = 0; j < img.width * 3; j++)
			pixels[i][j] = img.pixels[i][j];
}

void deletePPM(PPMimage* img)
{
	if (img->pixels != 0)
	{
		for (int i = 0; i < img->height; i++)
			delete[] img->pixels[i];
		delete[] img->pixels;
	}
}

int Read_PPM(char* filename, PPMimage* img)
{
	deletePPM(img);
	FILE* fp;
	if (filename == NULL)
	{
		cout << "\n파일을 열 수 없습니다." << endl;
		return 0;
	}
	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		cout << "\n파일을 열 수 없습니다." << endl;
		return 0;
	}
	fscanf(fp, "%c%c\n", &img->M, &img->N);
	if (img->M != 'P' || img->N != '6') {
		cout << "\nPPM 파일이 아닙니다." << endl;
		return 0;
	}
	fscanf(fp, "%d %d\n", &img->width, &img->height);
	fscanf(fp, "%d\n", &img->max);

	if (img->max != 255)
	{
		cout << "\n최대 밝기가 255가 아닙니다." << endl;
		return 0;
	}
	img->pixels = (unsigned char**)calloc(img->height, sizeof(unsigned char*));

	for (int i = 0; i < img->height; i++)
		img->pixels[i] = (unsigned char*)calloc(img->width * 3, sizeof(unsigned char));
	
	for (int j =0; j<img->height; j++)
		for (int k = 0; k < img->width * 3; k++)
		{
			fread(&img->pixels[j][k], sizeof(unsigned char), 1, fp);
		}

	fclose(fp);

	cout << "\n파일을 열었습니다." << endl;
	return 1;
}

int Save_PPM(char* filename, PPMimage* img)
{
	FILE* fp = fopen(filename, "wb");

	if (fp == NULL) {
		cout<< "\n저장에 실패하였습니다." << endl;
		return 0;
	}
	fprintf(fp, "P6\n%d %d\n255\n", img->width, img->height);
	for (int i=0; i<img->height;i++)
		for (int j = 0; j < img->width * 3; j+=3)
		{
			fprintf(fp, "%c", img->pixels[i][j]);
			fprintf(fp, "%c", img->pixels[i][j+1]);
			fprintf(fp, "%c", img->pixels[i][j+2]);
		}
	cout << "\n파일을 저장합니다." << endl;
	fclose(fp);
	return 1;
}

void color_Invert(PPMimage* img)
{
	unsigned char temp;

	for (int i = 0; i < img->height ;i++)
		for (int j = 0; j < img->width * 3; j++)
		{
			temp = 255 - img->pixels[i][j];
			img->pixels[i][j] = temp;
		}
	
	cout << "\n색 반전을 적용합니다." << endl;
	return;
}

void Filp(PPMimage* img, char num)
{
	PPMimage tmp_img(*img);
	int k;
	switch (num)
	{
	case '1':
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width * 3; j+=3)
			{
				k = (img->width * 3) - j - 3;
				img->pixels[i][k] = tmp_img.pixels[i][j];
				img->pixels[i][k + 1] = tmp_img.pixels[i][j + 1];
				img->pixels[i][k + 2] = tmp_img.pixels[i][j + 2];
			}
		cout << "\n좌우 반전을 적용합니다." << endl;
		break;
	case '2':
		for (int i = 0; i < img->height; i++)
		{
			k = img->height - i - 1;
			for (int j = 0; j < img->width * 3; j ++)
			{
				img->pixels[k][j] = tmp_img.pixels[i][j];
			}
		}
		cout << "\n상하 반전을 적용합니다." << endl;
		break;
	case '3':
		break;
	default:
		ErrorPrint();
		break;
	}
	deletePPM(&tmp_img);
	return;
}

void RGB_matrix(PPMimage* img, unsigned char** &color, unsigned char** &color_t, char RGB)
{
	int n = 0;
	if (RGB == 'G') n = 1;
	if (RGB == 'B') n = 2;

	color = (unsigned char**)calloc(img->height, sizeof(unsigned char*));
	for (int i = 0; i < img->height; i++)
		color[i] = (unsigned char*)calloc(img->width, sizeof(unsigned char));

	color_t = (unsigned char**)calloc(img->height, sizeof(unsigned char*));
	for (int i = 0; i < img->height; i++)
		color_t[i] = (unsigned char*)calloc(img->width, sizeof(unsigned char));

	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++)
		{
			color_t[i][j] = img->pixels[i][3 * j + n];
		}
	return;
}

void RGB_Rotaion(PPMimage* img, unsigned char** &color, unsigned char** &color_t, double center_x, double center_y, double seta)
{
	int new_x, new_y;
	int a;
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++)
		{
			new_x = (i - center_y) * sin(seta) + (j - center_x) * cos(seta) + center_x;
			new_y = (i - center_y) * cos(seta) - (j - center_x) * sin(seta) + center_y;
			a = 0;
			if ((new_x >= 0 && new_x < img->width) && (new_y >= 0 && new_y < img->height))
				a = color_t[new_y][new_x];
			color[i][j] = a;
		}
}

void Rotion(PPMimage* img, double degree)
{
	double center_x = img->width / 2.0;
	double center_y = img->height / 2.0;
	int new_x, new_y;
	int a;
	unsigned char** R;
	unsigned char** R_t;
	unsigned char** G;
	unsigned char** G_t;
	unsigned char** B;
	unsigned char** B_t;
	double seta = degree / 180.0 * PI;

	//RGB 매트리스 만들기
	RGB_matrix(img, R, R_t, 'R');
	RGB_matrix(img, G, G_t, 'G');
	RGB_matrix(img, B, B_t, 'B');
	
	// RGB에 각각 Rotation 적용
	RGB_Rotaion(img, R, R_t, center_x, center_y, seta);
	RGB_Rotaion(img, G, G_t, center_x, center_y, seta);
	RGB_Rotaion(img, B, B_t, center_x, center_y, seta);

	// 기존 img->합치기
	for (int i = 0; i < img->height; i++)
		for (int j = 0; j < img->width; j++)
		{
			img->pixels[i][3 * j] = R[i][j];
			img->pixels[i][3 * j + 1] = G[i][j];
			img->pixels[i][3 * j + 2] = B[i][j];
		}
	cout << endl;
	cout << degree << "도 회전을 적용합니다." << endl;
	delete[] R;
	delete[] G;
	delete[] B;
	delete[] R_t;
	delete[] G_t;
	delete[] B_t;
	return;
}

void channel_RGB(PPMimage* img, char n)
{
	if (n == 0)
		return;
	else if (n == 1)
	{
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width * 3; j += 3)
			{
				img->pixels[i][j + 1] = 0;
				img->pixels[i][j + 2] = 0;
			}
		cout << "\n빨간색 추출을 적용합니다. " << endl;
	}
	else if (n == 2)
	{
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width * 3; j += 3)
			{
				img->pixels[i][j] = 0;
				img->pixels[i][j + 2] = 0;
			}
		cout << "\n초록색 추출을 적용합니다. " << endl;
	}
	else if (n == 3)
	{
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width * 3; j += 3)
			{
				img->pixels[i][j] = 0;
				img->pixels[i][j + 1] = 0;
			}
		cout << "\n파란색 추출을 적용합니다. " << endl;
	}
	else if (n == 4)
	{
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width * 3; j += 3)
			{
				img->pixels[i][j + 2] = 0;
			}
		cout << "\n빨간색 + 초록색 추출을 적용합니다. " << endl;
	}
	else if (n == 5)
	{
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width * 3; j += 3)
			{
				img->pixels[i][j] = 0;
			}
		cout << "\n초록색 + 파란색 추출을 적용합니다. " << endl;
	}
	else if (n == 6)
	{
		for (int i = 0; i < img->height; i++)
			for (int j = 0; j < img->width * 3; j += 3)
			{
				img->pixels[i][j + 1] = 0;
			}
		cout << "\n빨간색 + 파란색 추출을 적용합니다. " << endl;
	}
	else
	{
		return;
	}
	return;
}

void Grayscale(PPMimage* img)
{
	unsigned char Gray;

	for (int i=0; i<img->height;i++)
		for (int j = 0; j < img->width*3; j += 3)
		{
			Gray = (img->pixels[i][j] + img->pixels[i][j + 1] + img->pixels[i][j + 2])/3;
			img->pixels[i][j] = Gray;
			img->pixels[i][j + 1] = Gray;
			img->pixels[i][j + 2] = Gray;
		}
	cout << "\nGrayScale로 변환합니다." << endl;
	return;
}





