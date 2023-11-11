#include <stdio.h>
#include <stdlib.h>
int ary[10][10];
void rotate(int n)
{
	int i, j, k = n-1, new[10][10];
	for (i = 0;i < n;i++)
	{
		for (j = 0;j < n;j++)
			new[i][j] = ary[i][j];
	}
	for (i = 0;i < n;i++)
	{
		for (j = 0;j < n;j++)
			new[j][k] = ary[i][j];
		k--;
	}
	for (i = 0;i < n;i++)
	{
		for (j = 0;j < n;j++)
			ary[i][j] = new[i][j];
	}
	for (i = 0;i < n;i++)
	{
		for (j = 0;j < n;j++)
		{
			if (ary[i][j] == 0)
			{
				ary[i][j] = ary[i][j+1];
				ary[i][j+1] = 0;
			}
		}
	}
}
void insert(int n)
{
	int i, j, k, max = ary[0][0];
	max = n*n+1;
	for (i = 0;i < n;i++)
	{
		if (ary[i][0] != 0)
			ary[i][n] = max++;
	}
	for (k = 0;k < 2;k++)
	{
		for (i = 0;i < n;i++)
		{
			for (j = 0;j < n;j++)
			{
				if (ary[i][j] == 0)
				{
					ary[i][j] = ary[i][j+1];
					ary[i][j+1] = 0;
				}
			}
		}
	}
}
void del_e(int num1, int num2, int n)
{
	int i, j;
	ary[num1][num2] = 0;
	for (i = num2;i < n; i++)
	{
		if (ary[num1][i] == 0)
		{
			ary[num1][i] = ary[num1][i+1];
			ary[num1][i+1] = 0;
		}
	}
}
void del_c(int col, int n)
{
	int i, j;
	for (i = 0;i < n;i++)
	{
		for (j =  col;j < n-1;j++)
			ary[i][j] = ary[i][j+1];
		ary[i][j] = 0;
	}
}
int main()
{
	FILE *fptr;
	fptr = fopen("Input1.txt","r");
	int i, j, n;
	while(!feof(fptr))
	{
		int temp = 1, flag = 0;
		char string[10], tt;
		fscanf(fptr, "%d ", &n);
		for (i = 0;i < n;i++)
		{
			for (j = 0;j < n;j++)
				ary[i][j] = temp++;
		}
		while(1)
		{
			fgets(string, 10, fptr);
			if (feof(fptr))
				flag = 1;
			if (string[0] >= 48 && string[0] <= 57)
			{
				n = (int)string[0]-48;
				break;
			}
			if (string[0] == 'R')
				rotate(n);
			else if (string[0] == 'I')
			{
				insert(n);
				n++;
			}
			else if (string[0] == 'D')
			{
				if (string[2] == '(')
				{
					int num1 = (int)string[4]-48, num2 = (int)string[6]-48;
					del_e(num1-1, num2-1, n);
				}
				else
				{
					int num = (int)string[2]-48;
					del_c(num-1, n);
				}
			}
			if (flag == 1)
				break;
		}
		for (i = 0;i < n;i++)
		{
			for (j = 0;j < n;j++)
			{
				if (ary[i][j] != 0)
					printf("%2d ", ary[i][j]);
			}
			printf("\n");
		}
		for (i = 0;i < 10;i++)
			for (j = 0;j < 10;j++)
				ary[i][j] = 0;
	}
	return 0;
} 
