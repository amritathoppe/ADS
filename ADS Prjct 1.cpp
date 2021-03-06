
// Bruteforce Final.cpp : Defines the entry point for the console application.
/*Amrita Thoppe Kuppubabu
ADS Prjct 1
*/
#include "stdafx.h"
#include <iostream>
#include <string>
#include<stdlib.h>
#include<ctime>
using namespace std;
const int m = 250;
const int n = 400;
int arr[m + 1][n + 1];
int F[m + 1][n + 1];
int bcounter = 0;//Count Bruteforce Comparisonss
int d_counter = 0;//Count Dynamic Comparisons
void display(int array[m + 1][n + 1])
{
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			cout << array[i][j] << "\t";
		}
		cout << "\n";
	}
}
int b_min(int a, int b)
{
	bcounter++;
	if (a < b)
		return a;//a small
	else return b;//b shld be small (or) both equal
}
bool b_checkAllZeros(int i, int j, int k) //pass arr to chk
{
	bool chkng = false;
	for (int l = i; l < i + k; l++)
	{
		for (int m = j; m < j + k; m++)
		{
			bcounter ++;//Comparison Counted
			if (arr[l][m] != 0)
			{
				return false;
			}
			else chkng = true;
		}
	}

	return chkng;
}
void BruteForce()
{
	int i, j, corner_a = 0, corner_b = 0, max_side = 0, s = 0, k = 0;
	bool chk;
	for (i = 1; i <= m; i++)
		for (j = 1; j <= n; j++)
		{

			s = b_min(m - i + 1, n - j + 1);//get minimum of row & coln
			for (k = s; k >= 1; k--)
			{
				chk = b_checkAllZeros(i, j, k);
				//bcounter++; //Count the comparison below
				if (chk == 1)
				{
					if (k > max_side)
					{
						corner_a = i; corner_b = j; max_side = k;
						break;
					}
				}
			}
		}

	cout << "\n---------------- Brute Force Approach Details---------------- \n";
	cout << "\n Largest Square Sub Matrix of Zeros is of Max_side" << max_side << "\n Starting at " << "(" << corner_a << "," << corner_b << ")";
	cout << "\n Total Number of Comparisons: " << bcounter;


}
int d_min(int a, int b, int c)
{
	int min = a;
	//count here
	d_counter++;
	if (min > b)min = b;
	//count here
	d_counter++;
	if (min > c) min = c;
	return min;
}
void DynamicPrgmg()
{
	int i, j;
	for (i = 1, j = 1; j <= n; j++) //Flip for Top row
	{
		//count here
		d_counter++;
		if (arr[1][j] == 0)
		{
			F[1][j] = 1;
		}
		else F[1][j] = 0;
	}

	for (j = 1, i = 2; i <= m; i++) //Flip  for Left Column
	{	//count here
		d_counter++;
		if (arr[i][1] == 0)

			F[i][1] = 1;

		else F[i][1] = 0;

	}

	//Construct F matrix
	for (i = 2; i <= m; i++)
		for (j = 2; j <= n; j++)
		{	//count here
			d_counter++;
			if (arr[i][j] == 1)
			{
				F[i][j] = 0;
			}
			else
			{
				int dmin = d_min(F[i][j - 1], F[i - 1][j], F[i - 1][j - 1]);
				F[i][j] = dmin + 1;
			}

		}
	
	//display(F);
	
	//Find Max of F matrix
	int d_max = F[1][1], d_max_i = 1, d_max_j = 1;
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			d_counter++;
			if (d_max < F[i][j])
			{
				d_max = F[i][j];
				d_max_i = i;
				d_max_j = j;
	
			}
		}
	}
	//cout << "\nMax Result==> d_max,d_max_i,d_max_j\t " << d_max << "\t" << d_max_i << "\t" << d_max_j;
	//Find the Start point & Largest square sub matrix"
	cout << "\n\n---------------- Dynamic Programming  Details---------------";
	cout << "\nLargest Square Sub Matrix of Zeros is of Max_side " << d_max << "\n Starting at " << "(" << d_max_i - (d_max - 1) << "," << d_max_j - (d_max - 1) << ")";
	cout << "\nTotal Number of Comparisons: " << d_counter << "\n\n";
}
int main()
{

	int i, j;
	srand(time(0));
	//generate Random number as 0 or 1
	for (i = 1; i <= m; i++)
	{
		for (j = 1; j <= n; j++)
		{
			arr[i][j] = rand() % 2;
		}

	}
	
	//display(arr);
	BruteForce();
	DynamicPrgmg();
	system("pause");
	return 0;
}

