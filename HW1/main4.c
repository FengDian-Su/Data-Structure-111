#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_SIZE 1000
int maze[101][101];
int mark[101][101];
typedef struct
{
	short int vert;
	short int horiz;
}offset;
offset move[4]={{-1,0},{0,1},{1,0},{0,-1}};
typedef struct
{
	short int row;
	short int col;
	short int dir;
}element;
element stack[MAX_SIZE];
int top=-1;
void push(element item)
{
	if (top>=MAX_SIZE-1)
	{
		fprintf(stderr, "Stack is full\n");
		exit(1);
	}
	stack[++top]=item;
}
element pop()
{
	if (top==-1)
	{
		printf("Stack is empty");
		exit(1);
	}
	return stack[top--];
}
int path(int b_row,int b_col,int n,int *size)
{
	int i,j,row,col,next_row,next_col,dir,found=0,minus;
	int s_row=0,s_col=0,count=0,complete=0,label=-1,m_num=0;
	element position;
	top=0;
	if (count==0)
	{
		mark[0][0]=-1;
		stack[0].row=0;
		stack[0].col=0;
		stack[0].dir=0;
	}
	while(!complete)
	{
		while(top>-1 && !found)
		{
			position=pop();
			row=position.row;
			col=position.col;
			dir=position.dir;
			while(dir<4 && !found)
			{
				next_row=row+move[dir].vert;
				next_col=col+move[dir].horiz;
				minus=maze[next_row][next_col]-maze[row][col];
				if (next_row<0 || next_col<0 || next_row>=b_row || next_col>=b_col)
				{
					dir++;
					continue;
				}
				if (row==s_row && col==s_col && dir==3)
				{
					found=1;
					break;
				}
				if (abs(minus)<=n && !mark[next_row][next_col])
				{
					position.row=row;                           
					position.col=col;
					position.dir=++dir;
					push(position);
					mark[next_row][next_col]=label;
					row=next_row;
					col=next_col;                               
					dir=0;
					count++;
				}
				else	
					dir++;
			}
		}
		found=0;
		int flag=1;
		for(i=0;i<b_row;i++)
		{
			for (j=0;j<b_col;j++)
			{
				if (mark[i][j]>=0)
				{
					mark[i][j]=--label;
					stack[0].row=i;
					stack[0].col=j;
					stack[0].dir=0;
					flag=0;
					m_num++;
					break;
				}
			}
			if (!flag)
				break;
		}
		if (flag)
			break;
		else
			top=0;
	}
	int record=label;
	int m_array[20000]={};
	int add=0;
	while(record!=0)
	{
		for(i=0;i<b_row;i++)
		{
			for (j=0;j<b_col;j++)
			{
				if(mark[i][j]==record)    
					m_array[add]++;
			}
		}
		add++;
		record++;
	}
	int max_size=m_array[0];
	for (i=1;i<add;i++)
	{
		if (m_array[i]>max_size)
			max_size=m_array[i];
	}
	*size=max_size;
	return (m_num+1);
}
int main()
{
	FILE *fptr;
	fptr=fopen("input4.txt","r");
	int number,row,col,i,j,c,minus,input;
	fscanf(fptr, "%d", &number);
	for (c=1;c<=number;c++)
	{
		fscanf(fptr, "%d %d %d ", &row,&col,&minus);
		for (i=0;i<row;i++)
		{
			for (j=0;j<col;j++)
			{
				fscanf(fptr, "%d", &input);
				maze[i][j]=input;
				mark[i][j]=0;
			}
		}
		int size=0;
		int m_num=path(row,col,minus,&size);
		printf("第%d張圖，山的數量 = %d，最大山面積 = %d\n",c,m_num,size);
    }
	fclose(fptr);
	return 0;
}
