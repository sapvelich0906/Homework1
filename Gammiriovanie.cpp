// Gammiriovanie.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include<time.h>
#include <iostream>

using namespace std;



int per2_10(int a)
{
	int a1=0, k=1;
	while (a > 0)
	{
		a1 = a1 + k * (a % 2);
		a = int(a / 2);
		k *= 10;
	}
	return a1;
}

int per10_2(int a)
{
	int a1 = 0, k = 0;
	while (a > 0)
	{
		a1 = a1 + int((a % 10)*pow(2, k));
		k++;
		a = int(a / 10);
	}
	return a1;
}

int uni(int a, int b)
{
	return 256*a+b;
}

int del_1(int a)
{
	return int(a / 256);
}

int del_2(int a) 
{
	return (a % 256);
}

int gamm_8(int a, int b)
{
	int c = 0, k=1;
	a = per2_10(a);
	b = per2_10(b);
	for (int i = 0; i < 8; i++)
	{
		c += (((a % 10) + (b % 10)) % 2) * k;
		a = int(a / 10);
		b = int(b / 10);
		k *= 10;
	}
	return per10_2(c);
}

int gamm_16(int a, int b)
{
	return uni(gamm_8(del_1(a), del_1(b)), gamm_8(del_2(a), del_2(b)));
}

int sdvigp(int a)
{
	return (a >> 2) | ((a % 4)<<14); 
}

int sdvigl(int a)
{
	return ((a % 16384) << 2) | ((a-(a % 16384))>> 14);
}

int ascii_cod(unsigned char a)
{
	int c;
	c = a;
	return c;
}

unsigned char ascii_sym(int a)
{
	char c;
	c = a;
	return c;
}


int main()
{
	setlocale(LC_ALL, "rus");
	char text[255], sht[255], desht[255];
	int *p;
	int l,k;
	srand(time(NULL));
	cin.getline(text, 255);
	l = int(strlen(text) / 2) + (strlen(text) % 2);
	p = (int *)malloc(l * sizeof(int));
	
	for (int i = 0; i < l; i++)
	{
		p[i] = rand() % 65535;
		cout << p[i] << " ";
	}
	cout << endl;
	
	for (int i = 0; i < l; i++)
	{
		sht[2 * i] = ascii_sym(del_1(sdvigp(gamm_16(uni(ascii_cod(text[2 * i]), ascii_cod(text[2 * i + 1])), p[i]))));
		sht[2 * i + 1] = ascii_sym(del_2(sdvigp(gamm_16(uni(ascii_cod(text[2 * i]), ascii_cod(text[2 * i + 1])), p[i]))));
	}
	
	for (int i = 0; i < 2*l; i++)
	cout << sht[i];
	cout << endl;
	
	for (int i = 0; i < l; i++)
	{
		desht[2 * i] = ascii_sym(del_1(gamm_16(sdvigl(uni(ascii_cod(sht[2 * i]), ascii_cod(sht[2 * i + 1]))), p[i])));
		desht[2 * i + 1] = ascii_sym(del_2(gamm_16(sdvigl(uni(ascii_cod(sht[2 * i]), ascii_cod(sht[2 * i + 1]))), p[i])));
	}
	
	for (int i = 0;i < 2*l; i++)
		cout << desht[i];
	cout << endl;
    return 0;
}

