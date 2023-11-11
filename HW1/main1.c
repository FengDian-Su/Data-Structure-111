#include <stdio.h>
#include <stdlib.h>
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
int main()
{
	FILE *fptr;
	fptr=fopen("input1.txt","r");
	int input,cnt=0,i,total=0,avg_t=0;
	while(!feof(fptr))
	{
		fscanf(fptr, "%d ", &input);
		enqueue(input);
		cnt++;
	}
	printf("Current work\tturn around time\n");
	for (i=0;i<cnt;i++)
	{
		int temp=dequeue();
		printf("%d\t\t", temp);
		total+=temp;
		avg_t+=total;
		printf("%d\n", total);
	}
	printf("Avg turn around time: %.2f", (float)avg_t/cnt);
	fclose(fptr);
	return 0;
}
