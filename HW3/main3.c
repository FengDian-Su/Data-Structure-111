#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int ary[2][100], max = 0;
typedef struct list *node;
struct list
{
	int data;
	node child;
	node sibling;
	int ht;
};
node root = NULL, temp, tt, head, pre;
void findpre(node, int);
node newnode(int value)
{
	node temp = (node)malloc(sizeof(struct list));
	temp->data = value;
	temp->child = NULL;
	temp->sibling = NULL;
	return temp;
}
void findtemp(node ptr, int value)
{
	if (ptr)
	{
		if (ptr->data == value)
		{
			temp = ptr;
			return;
		}
		findtemp(ptr->child, value);
		findtemp(ptr->sibling, value);
	}
}
void findtt(node ptr, int value)
{
	if (ptr)
	{
		if (ptr->data == value)
		{
			tt = ptr;
			return;
		}
		findtt(ptr->child, value);
		findtt(ptr->sibling, value);
	}
}
void findhead(node ptr, int value)
{
	if (ptr)
	{
		if (ptr->data == value)
		{
			head = ptr;
			return;
		}
		findhead(ptr->child, value);
		findhead(ptr->sibling, value);
	}
}
void insert(node ptr, int value, int flag)
{
	node newptr = newnode(value);
	if (flag == 0)
		ptr->child = newptr;
	else if (flag == 1)
		ptr->sibling = newptr;
}
void preorder(node ptr)
{
	if (ptr)
	{
		ptr->ht = findht(ptr);
		if (ptr->ht > max)
			max = ptr->ht;
		preorder(ptr->child);
		preorder(ptr->sibling);
	}
}
void output(node ptr, int n)
{
	if (ptr)
	{
		if (ptr->ht == n)
			printf("%d ", ptr->data);
		output(ptr->child, n);
		output(ptr->sibling, n);
	}
}
void findpre(node ptr, int value)
{
	if (ptr)
	{
		if (ptr->child && ptr->child->data == value)
			pre = ptr;
		else if (ptr->sibling && ptr->sibling->data == value)
			pre = ptr;
		findpre(ptr->child, value);
		findpre(ptr->sibling, value);
	}
}
int findht(node ptr)
{
	int count_h = 1;
	pre = ptr;
	while (pre != root)
	{
		findpre(root, pre->data);
		if (pre->child == ptr)
			count_h++;
		ptr = pre;
	}
	return count_h;
}
void delt(node ptr)
{
	if (ptr)
	{
		delt(ptr->child);
		delt(ptr->sibling);
		free(ptr);
		ptr = NULL;
	}
}
int main()
{
	FILE *fptr;
	fptr = fopen("input3.txt", "r");
	int test = 0;
	while(test != -1)
	{
		char cc;
		int degree, height, c = 0, i, j, flag, dnum, k;
		max = 0;
		fscanf(fptr, "%d %d %d", &degree, &height, &dnum);
		test = fscanf(fptr, "%c", &cc);
		if (cc == '\n' || test == -1)
		{
			for (i = 0;i < height;i++)
				c+=(int)pow(degree, i);
			for (i = c;i > 0;)
			{
				int num = i/degree;
				for (j = 0;j < degree;j++)
				{
					ary[0][i] = i;
					ary[1][i--] = num;
				}
			}
			root = newnode(1);
			for (i = 2;i <= c;i++)
			{
				flag = 0;                        // insert as child
				findtemp(root, ary[1][i]);
				if (temp->child)
				{
					findtemp(root, ary[0][i]-1);
					flag = 1;                    // insert as sibling
				}
				insert(temp, ary[0][i], flag);
			}
			findtemp(root, dnum);     
			findtt(root, dnum);       
			findhead(root, dnum-1);   
			if (head == root)
			{
				tt = tt->child;
				tt->sibling = temp->sibling;
				head->child = tt;
			}
			else if (tt->child)
			{
				tt = tt->child;
				for (i = 0;i < degree/2;i++)
					tt = tt->sibling;   
				tt->sibling = temp->sibling;
				findtemp(root, dnum-1);
				temp->sibling = tt;
			}
			else
				head->sibling = temp->sibling;
			preorder(root);
			for (k = 1;k <= max;k++)
			{
				output(root, k);
				printf("\n");
			}
			printf("\n");
		}
		for (i = 0;i < 50;i++)
			ary[0][i] = ary[1][i] = 0;
		delt(root);
		root = NULL;
		if (test == -1)
			break;
	}
	fclose(fptr);
	return 0;
}
