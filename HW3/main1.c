#include <stdio.h>
#include <stdlib.h>
int ary[4][20];
int flag = 0;
int output(int num, int i)
{
	int j, k;
	if (flag == 1)
		return;
	printf("%d ", num);
	for (j = 0;j < i;j++)
	{
		if (ary[0][j] == num && ary[1][j] != -1)
		{
			ary[2][j] = 1;
			num = output(ary[1][j], i);
		}
		else if (ary[1][j] == -1)
			for (k = 0;k < i;k++)
				if (ary[0][j] == ary[1][k] && ary[2][k] == 1)
				{
					flag = 1;
					if (ary[3][j] == 0)
					{
						printf("\n");
						ary[3][j] = 1;
					}
					return;
				}
	}
}
int main()
{
	FILE *fptr;
	fptr = fopen("input1.txt", "r");

	int cc;
	for (cc = 0;cc < 3; cc++)
	{
		char c1, c2, c3;
		int num1, num2, i = 0, j, k;
		fscanf(fptr, "%c", &c1);
		while(1)
		{
			fscanf(fptr, "%c%d%c%d%c", &c1, &num1, &c2, &num2, &c3);
			fscanf(fptr, "%c", &c1);
			if (c1 == ',')
			{
				ary[0][i] = num1;
				ary[1][i] = num2;
				i++;
			}
			else if (c1 == ']')
			{
				ary[0][i] = num1;
				ary[1][i] = num2;
				i++;
				fscanf(fptr, "%c", &c2);
				break;
			}
		}
		int num;
		for (j = 0;j < i;j++)
		{
			if (ary[0][j] == -1)
			{
				ary[2][j] = 1;
				output(ary[1][j], i);
				for (k = 0;k < i;k++)
					ary[2][k] = ary[3][k] = 0;
				flag = 0;
			}
		}
		printf("\n\n");
	}
	return 0;
}
