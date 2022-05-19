// Example source using array
// Programmed by Han, Kyu-Phil
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>

#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define BYTE    unsigned char

#define SIZE 5
#define BLACK 0
#define WHITE 255
#define RATIO 0.3

BYTE* inImg;
int height, width;

void bmp_read() {
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
	height = hInfo.biHeight, width = hInfo.biWidth;

	fclose(bmp_fp);

	// raw 이미지를 저장할 변수 선언
	inImg = malloc(height * width);

	// raw 파일 읽기
	FILE* raw_fp;

	if ((raw_fp = fopen("Lena.raw", "rb")) == NULL) {
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
	int nx[3][3] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
	int ny[3][3] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
	int dx, dy;
	unsigned int* result = malloc(height * width * sizeof(int));
	BYTE* outImg = malloc(height * width);
	
	int max = 0, min = 0;

	/* Sobel operator 적용 */
	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			dx = dy = 0;
			for (int k = -1; k < 2; k++) {
				for (int l = -1; l < 2; l++) {
					dx += nx[1 + k][1 + l] * inImg[(i + k) * width + j + l];
					dy += ny[1 + k][1 + l] * inImg[(i + k) * width + j + l];
				}
			}
			result[i * width + j] = abs(dx) + abs(dy);
			if (max < result[i * width + j]) max = result[i * width + j];
			if (result[i * width + j] < min) min = result[i * width + j];
		}
	}

	// 정규화
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImg[i * width + j] = (BYTE)((float)((result[i * width + j]-min) * 255 / (max - min))+0.5);

		}
	}

	// thresholding
	int boundary = height * width * RATIO;
	int cum = 0; // 누적
	int t; // 문턱치
	int histogram[256] = {0, };

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			histogram[outImg[i * width + j]]++;

	for (int i = 255; i > -1; i--) {
		if (boundary < cum) break;
		t = i;
		cum += histogram[i];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (outImg[i * width + j] < t) outImg[i * width + j] = WHITE;
			else outImg[i * width + j] = BLACK;
		}
	}

	pgm_write(outImg, "1-1.pgm");
	free(result);
	free(outImg);

}

void nonlinear_gradient(int case_number) {
	/* nonlinear gradient 적용 */
	unsigned int* result = malloc(height * width * sizeof(int));
	int p_max = 0, p_min = 0;
	BYTE* outImg = malloc(height * width);

	int i_max = 0;
	int i_min = 255;

	for (int i = (int)(SIZE / 2); i < height - (int)(SIZE / 2); i++) {
		for (int j = (int)(SIZE / 2); j < width - (int)(SIZE / 2); j++) {
			i_max = 0;
			i_min = 255;
			for (int k = i - 2; k <= i + 2; k++) {
				for (int l = j - 2; l <= j + 2; l++) {
					if (i_max < inImg[k * width + l]) i_max = inImg[k * width + l];
					if (i_min > inImg[k * width + l]) i_min = inImg[k * width + l];
				}
			}
			if (case_number == 1) result[i * width + j] = i_max - inImg[i * width + j]; // 최대값 - 현재값
			else result[i * width + j] = inImg[i * width + j] - i_min; // 현재값 - 최대값
			if (result[i * width + j] < p_min) p_min = result[i * width + j];
			if (result[i * width + j] > p_max) p_max = result[i * width + j];
		}
	}

	// 정규화
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImg[i * width + j] = (BYTE)((float)((result[i * width + j] - p_min) * 255 / (p_max - p_min)) + 0.5);

		}
	}

	// thresholding
	int boundary = height * width * RATIO;
	int cum = 0; // 누적
	int t; // 문턱치
	int histogram[256] = { 0, };

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			histogram[outImg[i * width + j]]++;

	for (int i = 255; i > -1; i--) {
		if (boundary < cum) break;
		t = i;
		cum += histogram[i];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (outImg[i * width + j] < t) outImg[i * width + j] = WHITE;
			else outImg[i * width + j] = BLACK;
		}
	}

	if (case_number == 1)  pgm_write(outImg, "1-2-1.pgm");
	else pgm_write(outImg, "1-2-2.pgm");
	free(result);
	free(outImg);
}

void nonlinear_laplacian() {
	/* nonlinear laplacian 적용 */
	int* result = malloc(height * width * sizeof(int));
	int max = 0, min = 255;
	BYTE* outImg = malloc(height * width);

	for (int i = (int)(SIZE/2); i < height - (int)(SIZE / 2); i++) {
		for (int j = (int)(SIZE / 2); j < width - (int)(SIZE / 2); j++) {
			max = 0, min = 255;
			for (int k = i - 2; k <= i + 2; k++) {
				for (int l = j - 2; l <= j + 2; l++) {
					if (max < inImg[k * width + l]) max = inImg[k * width + l];
					if (min > inImg[k * width + l]) min = inImg[k * width + l];
				}
			}
			result[i * width + j] = max + min - (2 * inImg[i * width + j]);
		}
	}

	// zc_array 255으로 초기화
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImg[i * width + j] = WHITE;
		}
	}

	// 수평 zero-crossing 찾기
	for (int i = 0; i < height; i++) {
		for (int j = 1; j < width; j++) {
			if (result[i * width + j] == 0) outImg[i * width + j] = BLACK;
			else if (result[i * width + j] * result[i * width + j - 1] < 0) outImg[i * width + j] = BLACK;
		}
	}

	// 수직 zero-crossing 찾기
	for (int i = 1; i < height; i++) {
		for (int j = 0; j < width; j++) {
			// 부호 변화 있음
			if (result[i * width + j] == 0) outImg[i * width + j] = BLACK;
			else if (result[i * width + j] * result[(i - 1) * width + j] < 0) outImg[i * width + j] = BLACK;
		}
	}

	// 대각선 zero-crossing 찾기
	for (int i = 1; i < height; i++) {
		for (int j = 1; j < width; j++) {
			// 부호 변화 있음
			if (result[i * width + j] == 0) outImg[i * width + j] = BLACK;
			else if (result[(i-1) * width + (j-1)] * result[i * width + j] < 0) outImg[i * width + j] = BLACK;
		}
	}

	pgm_write(outImg, "1-3.pgm");

	int average = 0; // 국부 평균
	int deviation_sum = 0; // 편차의 제곱의 합
	int local_variance_sum = 0; // 국부 분산값들의 합
	int local_variance_average = 0; // 국부 분산값들의 평균
	int* local_variance = malloc(height * width * sizeof(int)); // 픽셀의 국부 분산값 배열

	// 국부분산의 평균을 문턱치로 사용하여 분산값이 작은 화소의 경계 제거
	for (int i = (int)(SIZE/2); i < height - (int)(SIZE / 2); i++) {
		for (int j = (int)(SIZE / 2); j < width - (int)(SIZE / 2); j++) {
			average = 0;
			for (int k = i - 2; k <= i + 2; k++) {
				for (int l = j - 2; l <= j + 2; l++) {
					average += inImg[k * width + l];
				}
			}
			// 평균 계산
			average = average / (SIZE * SIZE);
			deviation_sum = 0;
			for (int k = i - 2; k <= i + 2; k++) {
				for (int l = j - 2; l <= j + 2; l++) {
					// 편차의 제곱 누적
					deviation_sum += (average - inImg[k * width + l]) * (average - inImg[k * width + l]);
				}
			}

			// 국부분산값 계산
			local_variance[i * width + j] = (int)((double)deviation_sum / (SIZE * SIZE) + 0.5);
			local_variance_sum += local_variance[i * width + j];
		}
	}
	
	local_variance_average = local_variance_sum / (height * width);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (outImg[i * width + j] == 0) { // zero-crossing 일 때
				if (local_variance[i * width + j] < local_variance_average) {
					outImg[i * width + j] = WHITE;
				}
			}
			
		}
	}

	pgm_write(outImg, "1-4.pgm");

	free(local_variance);
	free(result);
	free(outImg);

}

double logB(double x, double base) {
	return log10(x) / log10(base);
}

void entropy_sketch_operator() {

	/* entropy_sketch_operator */

	double pixel_percentage[SIZE * SIZE] = { 0.0, }; // 각 픽셀의 확률 변수

	double* result = malloc(height * width * sizeof(double));
	BYTE* outImg = malloc(height * width);

	int window_sum = 0;
	double entropy = 0.0;
	int mindex = 0;

	double min = 255.0, max = -255.0;

	for (int i = (int)(SIZE / 2); i < height - (int)(SIZE / 2); i++) {
		for (int j = (int)(SIZE / 2); j < width - (int)(SIZE / 2); j++) {
			window_sum = 0;

			// window sum 구하기
			for (int k = i - 2; k <= i + 2; k++) {
				for (int l = j - 2; l <= j + 2; l++) {
					window_sum += inImg[k * width + l];
				}
			}


			for (int n = 0; n < SIZE * SIZE; n++) {
				pixel_percentage[n] = 0.0;
			}

			mindex = 0;
			for (int k = i - 2; k <= i + 2; k++) {
				for (int l = j - 2; l <= j + 2; l++) {
					pixel_percentage[mindex] = (double)((double)inImg[k * width + l] / window_sum);
					mindex++;
				}
			}

			// entropy 값 구해서 result에 저장
			mindex = 0;
			entropy = 0.0;
			for (int k = i - 2; k <= i + 2; k++) {
				for (int l = j - 2; l <= j + 2; l++) {
					entropy += logB(pixel_percentage[mindex], 2.0) * pixel_percentage[mindex];
					mindex++;
				}
			}
			result[i * width + j] = entropy;
			if (max < result[i * width + j]) max = result[i * width + j];
			if (result[i * width + j] < min) min = result[i * width + j];
		}
	}

	// 정규화
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImg[i * width + j] = (BYTE)((float)((result[i * width + j] - min) * 255 / (max - min)) + 0.5);
		}
	}

	// thresholding
	int boundary = height * width * RATIO;
	int cum = 0; // 누적
	int t; // 문턱치
	int histogram[256] = { 0, };

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			histogram[outImg[i * width + j]]++;

	for (int i = 255; i > -1; i--) {
		if (boundary < cum) break;
		t = i;
		cum += histogram[i];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (outImg[i * width + j] < t) outImg[i * width + j] = WHITE;
			else outImg[i * width + j] = BLACK;
		}
	}

	pgm_write(outImg, "1-5.pgm");
	free(result);
	free(outImg);
}

void DP() {
	/* DP 적용 */
	double* result = malloc(height * width * sizeof(double));

	BYTE* outImg = malloc(height * width);

	int i_max = 0, i_sum = 0;
	int p_max = 0, p_min = 255;

	for (int i = (int)(SIZE / 2); i < height - (int)(SIZE / 2); i++) {
		for (int j = (int)(SIZE / 2); j < width - (int)(SIZE / 2); j++) {
			i_max = 0, i_sum = 0;
			for (int k = i - 2; k <= i + 2; k++) {
				for (int l = j - 2; l <= j + 2; l++) {
					i_sum += inImg[k * width + l];
					if (i_max < inImg[k * width + l])
						i_max = inImg[k * width + l];
				}
			}
			result[i * width + j] = ((double)(i_max / (double)inImg[i * width + j])- (double)((double)inImg[i * width + j]/ i_sum));
			if (p_min > result[i * width + j])
				p_min = result[i * width + j];
			if (p_max < result[i * width + j])
				p_max = result[i * width + j];
		}
	}

	// 정규화
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImg[i * width + j] = (BYTE)((float)((result[i * width + j] - p_min) * 255 / (p_max - p_min)) + 0.5);

		}
	}

	// thresholding
	int boundary = height * width * RATIO;
	int cum = 0; // 누적
	int t; // 문턱치
	int histogram[256] = { 0, };

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			histogram[outImg[i * width + j]]++;

	for (int i = 255; i > -1; i--) {
		if (boundary < cum) break;
		t = i;
		cum += histogram[i];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (outImg[i * width + j] < t) outImg[i * width + j] = WHITE;
			else outImg[i * width + j] = BLACK;
		}
	}

	pgm_write(outImg, "1-6.pgm");
	free(result);
	free(outImg);
}

void DIP() {
	/* DIP 적용 */
	double* result = malloc(height * width * sizeof(double));

	BYTE* outImg = malloc(height * width);

	int i_max = 0, i_sum = 0;
	int p_max = 0, p_min = 255;

	for (int i = (int)(SIZE / 2); i < height - (int)(SIZE / 2); i++) {
		for (int j = (int)(SIZE / 2); j < width - (int)(SIZE / 2); j++) {
			i_max = 0, i_sum = 0;
			for (int k = i - 2; k <= i + 2; k++) {
				for (int l = j - 2; l <= j + 2; l++) {
					i_sum += inImg[k * width + l];
					if (i_max < inImg[k * width + l])
						i_max = inImg[k * width + l];
				}
			}
			result[i * width + j] = ((double)(i_sum / (double)inImg[i * width + j]) - (double)(i_sum / i_max));
			if (p_min > result[i * width + j])
				p_min = result[i * width + j];
			if (p_max < result[i * width + j])
				p_max = result[i * width + j];
		}
	}

	// 정규화
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			outImg[i * width + j] = (BYTE)((float)((result[i * width + j] - p_min) * 255 / (p_max - p_min)) + 0.5);

		}
	}

	// thresholding
	int boundary = height * width * RATIO;
	int cum = 0; // 누적
	int t; // 문턱치
	int histogram[256] = { 0, };

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			histogram[outImg[i * width + j]]++;

	for (int i = 255; i > -1; i--) {
		if (boundary < cum) break;
		t = i;
		cum += histogram[i];
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (outImg[i * width + j] < t) outImg[i * width + j] = WHITE;
			else outImg[i * width + j] = BLACK;
		}
	}

	pgm_write(outImg, "1-7.pgm");
	free(result);
	free(outImg);
}

void main()
{
	bmp_read();
	sobel_operator(); // 1-1번
	nonlinear_gradient(1); // 1-2-1번째 케이스 : 최대값 - 현재값
	nonlinear_gradient(2); // 1-2-2번째 케이스 : 현재값 - 최솟값
	nonlinear_laplacian(); // 1-3번, 4번
	entropy_sketch_operator(); // 1-5번
	DP(); // 1-5번
	DIP(); // 1-6번
	free(inImg);
}
