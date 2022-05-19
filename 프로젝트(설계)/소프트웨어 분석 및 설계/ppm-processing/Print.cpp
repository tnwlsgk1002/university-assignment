#include "Print.h"
#include <iostream>

int Main_Menu()
{
	char n;
	cout << "\n==== Main_Menu ====" << endl;
	cout << "1. 파일 열기" << endl;
	cout << "2. 편집" << endl;
	cout << "3. 저장" << endl;
	cout << "4. 프로그램 종료" << endl;
	cout << "\n번호 입력 : " ;
	cin >> n;
	return n;
}

int edit_Menu()
{
	char n;
	cout << "\n==== edit_Menu ====" << endl;
	cout << "1. 색 반전" << endl;
	cout << "2. 좌우/상하 반전" << endl;
	cout << "3. 회전" << endl;
	cout << "4. 채널 추출" << endl;
	cout << "5. GrayScale 변환" << endl;
	cout << "6. 돌아가기" << endl;
	cout << "\n번호 입력 : ";
	cin >> n;
	return n;
}

int Filp_Menu()
{
	char n;
	cout << "\n==== Filp_Menu ====" << endl;
	cout << "1. 좌우 반전" << endl;
	cout << "2. 상하 반전" << endl;
	cout << "3. 돌아가기" << endl;
	cout << "\n번호 입력 : ";
	cin >> n;
	return n;
}

double Rotion_input()
{
	double degree = 0;
	int tf = 0;
	while (tf == 0)
	{
		cout << "회전각 입력(-360~360) : ";
		cin >> degree;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			ErrorPrint();
		}
		else if (degree < -360 || degree > 360)
		{
			cout << "회전각이 너무 크거나 작습니다." << endl;
		}
		else if (-360 <= degree && degree <= 360)
		{
			tf == 1;
			break;
		}
		else
		{
			ErrorPrint();
		}
		cin.clear();
	}
	return degree;
}

int channel_Menu()
{
	int n1, n2, n3 = 0;
	cout << "\n==== channel_Menu ====" << endl;
	cout << "1. 단일 추출" << endl;
	cout << "2. 멀티 추출" << endl;
	cout << "3. 돌아가기" << endl << "\n번호 입력 : ";
	cin >> n1;
	if (n1 == 1)
	{
		cout << "\n==== Single Channel ====" << endl;
		cout << "1. 빨간색 추출(R)" << endl;
		cout << "2. 초록색 추출(G)" << endl;
		cout << "3. 파란색 추출(B)" << endl << "\n번호 입력 : ";
		cin >> n2;
		if (n2 < 1 || 3 < n2)
		{
			ErrorPrint();
			return 0;
		}
		return n2;

	}
	else if (n1 == 2)
	{
		cout << "\n==== Multi Channel ====" << endl;
		cout << "1. 빨간색-초록색(R-G) 추출" << endl;
		cout << "2. 초록색-파란색(G-B) 추출" << endl;
		cout << "3. 빨간색-파란색(R-B) 추출" << endl << "\n번호 입력 : ";
		cin >> n3;
		if (n3 < 1 || 3 < n3)
		{
			ErrorPrint();
			return 0;
		}
		return n3+3;
	}
	else if (n1 == 3)
	{
		return 0;
	}
	ErrorPrint();
	return 0;
}

void ErrorPrint()
{
	cout << "잘못된 번호 입력입니다." << endl;
}
