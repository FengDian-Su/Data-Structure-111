#include <stdio.h>
#include <stdlib.h>
typedef struct list *node;
struct list
{
	int data;
	node left;
	node right;
};
node root = NULL;
int ary[10], ix = 0, count = 0;
node findnode(int, node);
void record_path(node, int);
node newnode(int value)
{
	node temp = (node)malloc(sizeof(struct list));
	temp->data = value;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}
node insert(node ptr, int value)
{
	if (!ptr)
		ptr = newnode(value);
	else if (value <= ptr->data)
		ptr->left = insert(ptr->left, value);
	else if (value > ptr->data)
		ptr->right = insert(ptr->right, value);
	return ptr;
}
void preorder(node ptr)
{
	if (ptr)
	{
		printf("%d\n", ptr->data);
		preorder(ptr->left);
		preorder(ptr->right);
	}
}
void postorder(node ptr, int max)
{
	if (ptr)
	{
		postorder(ptr->left, max);
		postorder(ptr->right, max);
		if (!ptr->left && !ptr->right)
			record_path(ptr, max);
	}
}
void record_path(node ptr, int max)
{
	int i;
	ary[ix++] = ptr->data;
	count+=ptr->data;
	while (ptr != root)
	{
		if (count == max)
		{
			for (i = ix-1;i >= 0;i--)
				printf("%d ", ary[i]);
			printf("\n");
			break;
		}
		ptr = findnode(ptr->data, root);
		count+=ptr->data;
		ary[ix++] = ptr->data;
		if (ptr == root && count == max)
		{
			for (i = ix-1;i >= 0;i--)
				printf("%d ", ary[i]);
			printf("\n");
			break;
		}
	}
	count = 0;
	ix = 0;
}
void delt(node ptr)
{
	if (ptr)
	{
		delt(ptr->left);
		delt(ptr->right);
		free(ptr);
		ptr = NULL;
	}
}
node findnode(int value, node ptr)
{
	node pre = ptr;
	while(1)
	{
		if (pre->left && (pre->left->data == value)||pre->right&&(pre->right->data == value))
			return pre;
		else if (value > pre->data)
			pre = pre->right;
		else if (value < pre->data)
			pre = pre->left;
	}
}
int main()
{
	FILE *fptr;
	fptr = fopen("input2.txt", "r");
	int sum, i = 0, test = 0, j;
	char c;
	int input[20];
	while(test != -1)
	{
		fscanf(fptr, "%d", &sum);
		while (1)
		{
			fscanf(fptr, "%d", &input[i++]);
			test = fscanf(fptr, "%c", &c);
			if (c == '\n' || test == -1)
			{
				for (j = 0;j < i;j++)
				{
					root = insert(root, input[j]);
					input[j] = 0;
				}
				postorder(root, sum);
				delt(root);
				root = NULL;
				i = 0;
				break;
			}
		}
		printf("\n");
	}
	return 0;
} 
