#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 200000
int maze[20][20];
int cnt_path=0;
typedef struct
{
	short int vert;
	short int horiz;
}offset;
offset move[8]={{-1,0},{-1,1},{0,1},{1,1},
			    {1,0},{1,-1},{0,-1},{-1,-1}};
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
int path(int s_row,int s_col,int e_row,int e_col)
{
	int i,row,col,next_row,next_col,dir,found=0;
	element position,trash;
	if (cnt_path==0)
	{
		top=0;
		stack[top].row=s_row;
		stack[top].col=s_col;
		stack[top].dir=0;
	}
	else 
	{
		trash=pop();
		stack[top].dir++;
	}
	while(top>-1 && !found)
	{
		position=pop();
		row=position.row;
		col=position.col;
		dir=position.dir;
		while(dir<8 && !found)
		{
			next_row=row+move[dir].vert;
			next_col=col+move[dir].horiz;
			if (next_row==e_row && next_col==e_col)
			{
				found=1;
				element end,last;
				last.row=row; last.col=col; last.dir=dir;
				end.row=next_row; end.col=next_col;
				push(last);
				push(end);
			}
			else if (maze[next_row][next_col]>maze[row][col])
			{
				position.row=row;                           
				position.col=col;
				position.dir=++dir;
				push(position);
				row=next_row;
				col=next_col;                               
				dir=0;
			}
			else	dir++;
		}
	}
	if (found)
		return top;
	else 
		return 0;	
}
int main()
{
	FILE *fptr;
	fptr=fopen("input3.txt","r");
	int number,row,col,i,j,c,s_row,s_col,e_row,e_col;
	fscanf(fptr, "%d", &number);
	for (c=1;c<=number;c++)
	{
		fscanf(fptr, "%d %d ", &row,&col);
		char input[20];
		for (i=0;i<row;i++)
		{
			for (j=0;j<col;j++)
			{
				fscanf(fptr, "%s", input);
				if (!strcmp("s",input))
				{
					s_row=i;
					s_col=j;
					maze[s_row][s_col]=0;
				}
				else if (!strcmp("e",input))
				{
					e_row=i;
					e_col=j;
					maze[e_row][e_col]=0;
				}
				else
				{
					int trans_num=atoi(input);
					maze[i][j]=trans_num;
				}
			}
		}
//		for (i=0;i<row;i++)
//		{
//			for (j=0;j<col;j++)
//				printf("%d ",maze[i][j]);
//			printf("\n");
//		}
//		printf("%d %d\n%d %d\n",s_row,s_col,e_row,e_col);
		while(1)
		{
			if (!path(s_row,s_col,e_row,e_col))
				break;
			cnt_path++;
		}
		printf("第%d張圖的可走路線共:%d種\n",c,cnt_path);
		cnt_path=0;
    }
	fclose(fptr);
	return 0;
}
