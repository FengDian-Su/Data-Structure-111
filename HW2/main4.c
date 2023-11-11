#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Knapsack Problem
int eat[500], count[150000], size[1000];
int knapsack(int friend_num, int max_cake, int waste)
{
	int i, j, record1, record2, answer, temp, max = 0;
	for (i = 0;i < 150000;i++)
		count[i] = 0;
    for (i = 0; i < friend_num; i++)
	{
		temp = eat[i];
		size[temp]++;
		for (j = max_cake+waste; j-eat[i] >= waste; j--)
		{
			record1 = count[j];
			record2 = count[j-eat[i]-waste]+eat[i];
			if (record2 > record1)
				count[j] = record2;
		}
		if (eat[i] > max)
			max = eat[i];
	}
//	printf("max = %d\n", max);
	answer = count[max_cake+waste];
    return answer;
}
int main()
{
	FILE *fptr, *fw;
	int number, friend_num, waste, max_cake, i, j, ans;
	double start, finish;
	start = clock();
	fptr = fopen("input4(10000).txt", "r");
	fw = fopen("main4(10000).txt", "w");
	fscanf(fptr, "%d", &number);
	for (i = 0;i < 10000;i++)
	{
		fscanf(fptr, "%d %d %d", &max_cake, &friend_num, &waste);
		for (j = 0;j < friend_num;j++)
			fscanf(fptr, "%d", &eat[j]);
		ans = knapsack(friend_num, max_cake, waste);
		fprintf(fw, "%d\n", ans);
//		printf("%d\n", knapsack(friend_num, max_cake, waste));
//		for (j = 0;j < 500;j++)
//			eat[j] = 0;
	}
	fclose(fptr);
	fclose(fw);
	finish = clock();
	printf("time = %.5f\n", (finish-start)/CLOCKS_PER_SEC);
	return 0;
}
