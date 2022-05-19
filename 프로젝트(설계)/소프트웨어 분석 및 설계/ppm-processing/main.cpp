#include <iostream>
#include "PPMfile.h"
#include "Print.h"
#pragma warning(disable:4996)

void main()
{
	PPMimage img;
	char filename[200];
	char savename[200];
	char ch1, ch2, ch3;
	double degree;
	do
	{
		ch1 = Main_Menu();
		if (img.pixels==0)
			if ((ch1 == '2') || (ch1 == '3'))
			{
				ErrorPrint();
				continue;
			}
		switch (ch1)
		{
		case '1':
			cout << "\n파일 이름을 입력하세요 : ";
			cin.ignore();
			cin.getline(filename, sizeof(filename), '\n');
			Read_PPM(filename, &img);
			break;
		case '2':
			do
			{
				ch2=edit_Menu();
				switch (ch2)
				{
				case '1':
					color_Invert(&img);
					break;
				case '2':
					ch3 = Filp_Menu();
					Filp(&img, ch3);
					break;
				case '3':
					degree = Rotion_input();
					Rotion(&img, degree);
					break;
				case '4':
					ch3 = channel_Menu();
					channel_RGB(&img, ch3);
					break;
				case '5':
					Grayscale(&img);
					break;
				case '6':
					break;
				default:
					ErrorPrint();
					break;
				}
			} while (ch2 != '6');
			break;
		case '3':
			cout << "\n저장할 파일 이름을 입력하세요 : ";
			cin.ignore();
			cin.getline(savename, sizeof(savename), '\n');
			Save_PPM(savename, &img);
			break;
		case '4':
			cout << "\n프로그램을 종료합니다. " << endl;
			deletePPM(&img);
			break;
		default:
			ErrorPrint();
			break;
		}
		
	} while (ch1 != '4');

	return;
}