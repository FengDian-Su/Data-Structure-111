#include <stdio.h>
#include <stdlib.h>
int main()
{
	FILE *fptr;
	fptr = fopen("input1.txt", "r");
	int num1, num2, i, j, k, m, ary[20][20], record[20];
	char c;
	while (1)
	{
		for (i = 0;i < 20; i++)
		{
			for (j = 0;j < 20;j++)
				ary[i][j] = 0;
			record[i] = 0;
		}
		if (fscanf(fptr, "%d", &num1) == -1)
			break;
		fscanf(fptr, "%d", &num2);
		for (i = 0;i < num1;i++)
		{
			k = 0;
			fscanf(fptr, "%d %c", &ary[i][k++], &c);
			while(1)
			{
				fscanf(fptr, "%d", &ary[i][k++]);
				fscanf(fptr, "%c", &c);
				if (c == ']')
					break;
			}
			ary[i][k] = 0;
		}
		k = 0;
		while(ary[0][k++] != 0)
			for (i = 1;i < num1;i++)
				for (j = 1;ary[i][j] != 0;j++)
					if (ary[i][j] == ary[0][k])
						for (m = 1;ary[i][m] != 0;m++)
							if (ary[i][m] != ary[0][k])
								record[ary[i][m]]++;
		int count = 0;
		for (i = 0;i < 20;i++)
		{
			for (j = 1;ary[0][j] != 0;j++)
				if (i == ary[0][j])
					record[i] = 0;
			if (record[i] != 0)
				count++;
		}
		for (;count > 0;count--)
		{
			int max = record[0], idx;
			for (i = 0;i < 20;i++)
				if (record[i] > max)
				{
					max = record[i];
					idx = i;
				}
			printf("%d ", idx);
			record[idx] = 0;
		}
		printf("\n");
	}
	fclose(fptr);
	return 0;
} 
