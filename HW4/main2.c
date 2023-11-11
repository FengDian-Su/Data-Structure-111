#include <stdio.h>
#include <stdlib.h>
int ary[20][20], record[20], visit[20];
int flag = 0;
int ishead(int row)
{
	if (ary[row][1] == -1)
		return 1;
	else
		return 0;
}
void recurse(int row, int col)
{
	if (visit[ary[row][0]] == 1)
		return;
	if (!ishead(ary[row][col+1]) && ary[row][1] != -1 && visit[ary[row][1]] == 0)
	{
		record[++flag] = row;
		return;
	}
	if (ary[row][col+1] == -1 || ary[row][col+1] == 0)
	{
		if (visit[ary[row][0]] == 0)
		{
			printf("%d ", ary[row][0]);
			visit[ary[row][0]] = 1;
		}
		return;
	}
	recurse(ary[row][col+1], 0);
	while (ary[row][col] != 0)
		recurse(row, ++col);
}
int main()
{
	FILE *fptr;
	fptr = fopen("input2.txt", "r");
	int num, first_num, i, j, k, m, max = -1;
	char c;
	while (1)
	{
		for (i = 0;i < 20; i++)
		{
			for (j = 0;j < 20;j++)
				ary[i][j] = 0;
			record[i] = visit[i] = flag = 0;
		}
		if (fscanf(fptr, "%d", &num) == -1)
			break;
		for (i = 0;i < num;i++)
		{
			k = 0;
			fscanf(fptr, "%d %c", &first_num, &c);
			ary[first_num][k++] = first_num;
			record[i] = first_num;
			while(1)
			{
				fscanf(fptr, "%d", &ary[first_num][k++]);
				fscanf(fptr, "%c", &c);
				if (c == ']')
					break;
			}
			ary[first_num][k] = 0;
			k = 0;
			while (ary[first_num][k] != 0)
			{
				if (ary[first_num][k] > max)
					max = ary[first_num][k];
				ary[ary[first_num][k]][0] = ary[first_num][k++];
			}	
		}
		for (i = 1;i <= max;i++)
		{
			k = 0;
			if (ary[i][0] == 0)
				continue;
			else if (ary[i][1] == 0)
				ary[i][1] = -1;
		}
		for (j = 1;j <= max;j++)
		{
			recurse(record[flag], 0);
			if (ary[j][1] != 0 && ary[j][1] != -1 && visit[ary[j][0]] == 0)
				recurse(j, 0);
		}
		printf("\n\n");
	}
	fclose(fptr);
	return 0;
}
