#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 100000
int avg_t=0,total_num=0;
typedef struct list *node;
struct list
{
	int data;
	node next;
};
node head=NULL,tail=NULL;
void enqueue(int value)
{
	node temp; 
	temp=(node)malloc(sizeof(struct list));
	temp->data=value;
	temp->next=NULL;
	if (head==NULL)
		head=temp;            
	else
		tail->next=temp;      
	tail=temp;               
}
int dequeue()
{
	node temp;
	int value;
	temp=head;
	if (head==NULL)
		tail=NULL;
	else
		head=head->next;
	value=temp->data;
	free(temp);
	return value;
}
int output(int cnt,float qnum,int qsize,int ary[][MAX],int total)  //cnt=5, qnum=3
{
	int label=(int)qnum-1,cnt_label=0;                    //label=2, 1, 0
	int ceiling=ceil(cnt/qnum);                           //ceiling=2
	int max,temp,i,j;
	for(i=1;i<=cnt-ceiling;i++)                           //for(i= 1,2,3) find the biggest element
	{
		max=0;
		for(j=1;j<cnt;j++)                                // ary[1~4] 
		{
			if(ary[0][j]>ary[0][max]&&ary[1][j]==0)
				max=j;
		}
		ary[1][max]=label;                                //mark max=1
		cnt_label++;                                      //add label until 
//		if(cnt_label==ceiling)  //cnt_label ?= 2
//		{
//			cnt_label--;
//			label--;
//		}
	}
//	printf("============\n");
//	for (i=0;i<cnt;i++)
//		printf("%3d    %d\n",ary[0][i],ary[1][i]);
//	printf("============\n\n");
//	printf("cnt_label=%d\n",cnt_label);
	for(j=0;j<=cnt_label;j++)
	{
		for (i=0;i<cnt;i++)
		{
			if (ary[1][i]==j)
			{
//				printf("%d == %d\n",ary[0][i],j);
				enqueue(ary[0][i]);
			}
				
		}
	}
//	printf("before: head=%d, tail=%d\n",head->data,tail->data);
	for (i=1;i<=qsize;i++)
	{
		if (head==NULL||tail==NULL)
			break;
		temp=dequeue();
		printf("%d\t\t",temp);
		total+=temp;
		printf("%d\n",total);
		avg_t+=total;
	}
	while (head!=NULL)
	{
		temp=dequeue();
		printf("%d\t\t",temp);
		total+=temp;
		printf("%d\n",total);
		avg_t+=total;
		total=temp;
	}
//	printf("after: tail=%d\n",tail->data);
	return total;
}
int main()
{
	FILE *fptr;
	fptr=fopen("input2.txt","r");
	float qnum;
	int qsize,cnt=0,i=0,ary[2][MAX],num,j=0,flag=0,record[MAX],total=0;
	char input[20],temp;
	fscanf(fptr,"%f %d ",&qnum,&qsize);
	printf("Current work    turn around time\n");
	while(fscanf(fptr,"%c",&temp)>0)
	{
		if (temp==' ')
		{
			input[i]='\0';
			int trans_num=atoi(input);
			ary[0][cnt]=trans_num;
			ary[1][cnt]=0;
			cnt++;
			i=0;
			total_num++;
			continue;
		}
		if (temp=='\n')
		{
			total+=output(cnt,qnum,qsize,ary,total);
			cnt=0;
			continue;
		}
		input[i++]=temp;
	}
	output(cnt,qnum,qsize,ary,total);
	printf("Avg turn around time: %.2f\n",(float)avg_t/total_num);
	fclose(fptr);
	return 0;
} 
