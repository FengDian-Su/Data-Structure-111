#include <stdio.h>
#include <stdlib.h>
#define maxv 50
int ary[50][2], record[10][10], temp[20];
int flag = 0, idx = 0;
typedef struct list *node;
struct list
{
	int data;
	node next;
};
node graph[maxv], graph2[maxv];
int visit[maxv];
void newgraph(int num1, int num2)
{
	if (num1 == num2)
		return;
	
	node newnode, ptr;
	ptr = graph[num1];
	while (ptr->next)
		ptr = ptr->next;
	newnode = (node)malloc(sizeof(struct list));
	newnode->data = num2;
	newnode->next = NULL;
	ptr->next = newnode;
}
void newgraph2(int num1, int num2)
{
	if (num1 == num2)
		return;
	node newnode, ptr;
	ptr = graph2[num1];
	while (ptr->next)
		ptr = ptr->next;
	newnode = (node)malloc(sizeof(struct list));
	newnode->data = num2;
	newnode->next = NULL;
	ptr->next = newnode;
}
void dfs(int v, int x)
{
	node w;
	if (flag) return;
	if (!graph[v]->next)
	{
		record[x][idx++] = graph[v]->data;
		flag = 1;
		return;
	}
	visit[v] = 1;
	record[x][idx++] = graph[v]->data;
	for (w = graph[v];w;w = w->next)
		if (!visit[w->data])
			dfs(w->data, x);
}
void dfss(int v, int x)
{
	node w;
	if (flag) return;
	if (!graph2[v]->next)
	{
		record[x][idx++] = graph2[v]->data;
		flag = 1;
		return;
	}
	visit[v] = 1;
	record[x][idx++] = graph2[v]->data;
	for (w = graph2[v];w;w = w->next)
		if (!visit[w->data])
			dfss(w->data, x);
}
int add(int end)
{
	int i, j, count = 0, ix = 0;
	for (i = 0;i < maxv;i++)
		visit[i] = 0;
	for (i = 0;i < 2;i++)
		for (j = 0;record[i][j] != end;j++)
		{
			if (!visit[record[i][j]])
			{
				temp[ix++] = record[i][j];
				count += record[i][j];
				visit[record[i][j]] = 1;
			}
		}
	return count;
}
void modify(int k, int new_num)
{
	int i, j;
	for (i = 0;temp[i] != 0;i++)
		for (j = 0;j < k;j++)
		{
			if (ary[j][0] == temp[i])
				ary[j][0] = new_num;
			if (ary[j][1] == temp[i])
				ary[j][1] = new_num;
		}
	for (i = 0;i < k;i++)
		for (j = i+1;j < k;j++)
			if (ary[i][0] == ary[j][0] && ary[i][1] == ary[j][1])
				ary[j][0] = ary[j][1] = ary[i][0];
}
int main()
{
	FILE *fptr;
	fptr = fopen("input3.txt", "r");
	while (1)
	{
		int num, i, j, q, first_num, k = 0, num2, max = 0;
		char c;
		node m = NULL;
		for (i = 0;i < 50;i++)
			ary[0][i] = ary[1][i] = 0;
		if (fscanf(fptr, "%d", &num) == -1)
			break;
		for (i = 0;i < num;i++)
		{
			fscanf(fptr, "%d %c", &first_num, &c);
			while(1)
			{
				fscanf(fptr, "%d", &num2);
				ary[k][0] = num2;
				ary[k++][1] = first_num;
				fscanf(fptr, "%c", &c);
				if (c == ']')
					break;
			}
		}
		for (i = 0;i < k;i++)
		{
			if (ary[i][0] > max)
				max = ary[i][0];
			if (ary[i][1] > max)
				max = ary[i][1];
		}
		node temp, temp2;
		for (i = 0;i <= maxv;i++)
		{
			temp = (node)malloc(sizeof(struct list));
			temp->data = i;
			temp->next = NULL;
			graph[i] = temp;
		}
		for (i = 0;i < k;i++)
			newgraph(ary[i][0], ary[i][1]);
		int total_max = max;
		for (i = 1;i <= max;i++)
		{
			int x = -1;
			for (m = graph[i]->next;m;m = m->next)
			{
				dfs(i, ++x);
				flag = idx = 0;
				for (j = 0;j < maxv;j++)
					visit[j] = 0;
				if (graph[i]->next)
					visit[graph[i]->next->data] = 1;
				if (x == 1)
					for (q = 1;record[0][q] != 0;q++)
						if (record[0][q] == record[1][q])
						{
							int new_num = add(record[0][q]);
							if (new_num > max)
								total_max = new_num;
							modify(k, new_num);
							break;
						}
			}
			for (j = 0;j < maxv;j++)
				visit[j] = 0;
			for (j = 0;j < 2;j++)
				for (q = 0;q < 10;q++)
					record[j][q] = 0;
		}
		for (i = 0;i <= total_max;i++)
		{
			temp = (node)malloc(sizeof(struct list));
			temp->data = i;
			temp->next = NULL;
			graph2[i] = temp;
		}
		for (i = 0;i < k;i++)
			newgraph2(ary[i][0], ary[i][1]);
		int path = 0, rr = 0, x1, x = -1;
		for (i = 1;i <= total_max;i++)
		{
			for (m = graph2[i]->next;m;m = m->next)
			{
				dfss(i, ++x);
				flag = idx = rr = 0;
				for (j = 0;j < maxv;j++)
					visit[j] = 0;
				if (graph2[i]->next)
					visit[graph2[i]->next->data] = 1;
				for (q = 0;record[x][q] != 0;q++)
					rr += record[x][q];
				if (rr > path)
				{
					path = rr;
					x1 = x;
				}
			}
			for (j = 0;j < maxv;j++)
				visit[j] = 0;
		}
		for (q = 0;record[x1][q] != 0;q++)
			printf("%d ", record[x1][q]);
		for (j = 0;j < 10;j++)
			for (q = 0;q < 10;q++)
				record[j][q] = 0;
		for (i = 0;i <= max;i++)
			graph[i] = NULL;
		for (i = 0;i <= total_max;i++)
			graph2[i] = NULL;
		printf("\n");
	}
	fclose(fptr);
	return 0;
}
