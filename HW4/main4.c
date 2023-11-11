#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//Greedy Algorithm
int total_num, people, occupation;
int ary[1001][1001];
int main()
{
	FILE *fptr, *fw;
	int i, j, cc;
	double start, finish;
	start = clock();
    fptr = fopen("input4.txt", "r");
    fw = fopen("output4.txt", "w");
    fscanf(fptr, "%d", &total_num);
    for (cc = 0;cc < total_num;cc++)
	{
		int max_temp, ans = 0;
        fscanf(fptr, "%d %d", &people, &occupation);
        for(i = 0;i < people;i++)
            for(j = 0;j < occupation;j++)
                fscanf(fptr, "%d", &ary[i][j]);
        for(j = 0;j < occupation;j++)
		{
            max_temp = 0;
            for(i = 0;i < people;i++)
                max_temp = (ary[i][j] > max_temp)?ary[i][j]:max_temp;
            ans += max_temp;
        }
        fprintf(fw, "%d \n", ans);
    }
    fclose(fptr);
	fclose(fw);
	finish = clock();
	printf("time = %.5f\n", (finish-start)/CLOCKS_PER_SEC);
    return 0;
}
