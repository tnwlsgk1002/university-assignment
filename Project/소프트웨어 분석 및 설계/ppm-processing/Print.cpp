#include "Print.h"
#include <iostream>

int Main_Menu()
{
	char n;
	cout << "\n==== Main_Menu ====" << endl;
	cout << "1. ���� ����" << endl;
	cout << "2. ����" << endl;
	cout << "3. ����" << endl;
	cout << "4. ���α׷� ����" << endl;
	cout << "\n��ȣ �Է� : " ;
	cin >> n;
	return n;
}

int edit_Menu()
{
	char n;
	cout << "\n==== edit_Menu ====" << endl;
	cout << "1. �� ����" << endl;
	cout << "2. �¿�/���� ����" << endl;
	cout << "3. ȸ��" << endl;
	cout << "4. ä�� ����" << endl;
	cout << "5. GrayScale ��ȯ" << endl;
	cout << "6. ���ư���" << endl;
	cout << "\n��ȣ �Է� : ";
	cin >> n;
	return n;
}

int Filp_Menu()
{
	char n;
	cout << "\n==== Filp_Menu ====" << endl;
	cout << "1. �¿� ����" << endl;
	cout << "2. ���� ����" << endl;
	cout << "3. ���ư���" << endl;
	cout << "\n��ȣ �Է� : ";
	cin >> n;
	return n;
}

double Rotion_input()
{
	double degree = 0;
	int tf = 0;
	while (tf == 0)
	{
		cout << "ȸ���� �Է�(-360~360) : ";
		cin >> degree;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(256, '\n');
			ErrorPrint();
		}
		else if (degree < -360 || degree > 360)
		{
			cout << "ȸ������ �ʹ� ũ�ų� �۽��ϴ�." << endl;
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
	cout << "1. ���� ����" << endl;
	cout << "2. ��Ƽ ����" << endl;
	cout << "3. ���ư���" << endl << "\n��ȣ �Է� : ";
	cin >> n1;
	if (n1 == 1)
	{
		cout << "\n==== Single Channel ====" << endl;
		cout << "1. ������ ����(R)" << endl;
		cout << "2. �ʷϻ� ����(G)" << endl;
		cout << "3. �Ķ��� ����(B)" << endl << "\n��ȣ �Է� : ";
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
		cout << "1. ������-�ʷϻ�(R-G) ����" << endl;
		cout << "2. �ʷϻ�-�Ķ���(G-B) ����" << endl;
		cout << "3. ������-�Ķ���(R-B) ����" << endl << "\n��ȣ �Է� : ";
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
	cout << "�߸��� ��ȣ �Է��Դϴ�." << endl;
}
