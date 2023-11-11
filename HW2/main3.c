#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct list *node;
struct list
{
	int data;
	node left;
	node right;
};
node root = NULL, new_root = NULL;
node findnode(int , node);
void rotate(node);
void preorder(node);
void output(node);
node LL(node pivot)
{
	node next = pivot->left;
	node temp = next->right;
	next->right = pivot;
	pivot->left = temp;
	return next;
}
node RR(node pivot)
{
	node next = pivot->right;
	node temp = next->left;
	next->left = pivot;
	pivot->right = temp;
	return next;
}
node LR(node pivot)
{
	node next = pivot->left;
	node temp = next->right;
	pivot->left = temp->right;
	next->right = temp->left;
	temp->left = next;
	temp->right = pivot;
	return temp;
}
node RL(node pivot)
{
	node next = pivot->right;
	node temp = next->left;
	pivot->right = temp->left;
	next->left = temp->right;
	temp->right = next;
	temp->left = pivot;
	return temp;
}
node skewmode(node ptr)
{
	node ptr_next;
	if (height(ptr->left) > height(ptr->right))
	{
		ptr_next = ptr->left;
		if (height(ptr_next->left) >= height(ptr_next->right))
			return LL(ptr);                                            //LL
		else
			return LR(ptr);                                              //LR
	}
	else
	{
		ptr_next = ptr->right;
		if (height(ptr_next->right) >= height(ptr_next->left))      //RR
			return RR(ptr);
		else
			return RL(ptr);                                              //RL
	}
}
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
int postorder(node ptr,int num)
{
	if (ptr)
	{
		num = postorder(ptr->left, num);
		num = postorder(ptr->right, num);
		while (isbalance(ptr) == 1)
		{
//			printf("%d is not balance\n", ptr->data);
			num++;
			rotate(ptr);
		}
	}
	return num;
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
int findnum(node ptr)
{
	if (!ptr)
		return 0;
	else
		return 1+findnum(ptr->left)+findnum(ptr->right);
}
node findnode(int value, node ptr)      // ptr = root
{
	node pre = ptr;
	while(1)
	{
		if (pre->left&&(pre->left->data == value)||pre->right&&(pre->right->data == value))
			return pre;
		else if (value > pre->data)
			pre = pre->right;
		else if (value < pre->data)
			pre = pre->left;
	}
}
node copytree(node ptr)
{
	node temp;
	if (ptr)
	{
		temp = (node)malloc(sizeof(struct list));
		temp->left = copytree(ptr->left);
		temp->right = copytree(ptr->right);
		temp->data = ptr->data;
		return temp;
	}
	return NULL;
}
int height(node ptr)
{
	int left_h, right_h;
	if (ptr)
	{
		left_h = height(ptr->left);
		right_h = height(ptr->right);
		if (left_h >right_h)
			return (left_h+1);
		else
			return (right_h+1);
	}
	else
		return 0;
}
int isbalance(node ptr)
{
	int bf, isb;
	if (ptr)
	{
		bf = height(ptr->left)-height(ptr->right);
		isb = (abs(bf) > 1)?1:0;
		return isb;
	}
	else
		return -1;
}
void rotate(node ptr)
{
	if (ptr == new_root)
		new_root = skewmode(ptr);
	else
	{
		node pre = findnode(ptr->data, new_root);
		if (pre->data == new_root->data)
				pre = new_root;
		node x = skewmode(ptr);                 //x = pivot_next
		if (pre->data < x->data)
			pre->right = x;
		else
			pre->left = x;
	}
}
int leaf_ary[10];
void find_path(node ptr)
{
	node tt;
	if (ptr)
	{
		if (ptr->left == NULL && ptr->right == NULL)
		{
			tt = findnode(ptr->data,new_root);
			output(ptr);
		}
		find_path(ptr->left);
		find_path(ptr->right);
	}
}
void output(node ptr)
{
	node temp;
	int i = 0, k;
	while(1)
	{
		leaf_ary[i] = ptr->data;
		temp = findnode(ptr->data,new_root);
		ptr = temp;
		i++;
		if (ptr == new_root)
		{
			leaf_ary[i] = ptr->data;
			if (i == height(new_root)-1)
			{
				for(k = i;k >= 0;k--)
					printf("%d ", leaf_ary[k]);
				printf("\n");
			}
			break;
		}
	}
}
int main()
{
	FILE *fptr;
	fptr = fopen("Input3.txt", "r");
	int i = 0, j, num = 0, cc, read, test;
	char c;
	int input[20];
	while(1)
	{
		fscanf(fptr, "%d", &input[i++]);
		if ((test = fscanf(fptr, "%c", &c)) < 0 || c == '\n')
		{
			cc = i;
			for (i = 0;i < cc;i++)
			{
				root = insert(root, input[i]);
				new_root = copytree(root);
				num = postorder(new_root, num);
				printf("%d %d\n", input[i], num);
				num = 0;
				if (i == cc-1)
					find_path(new_root);
				delt(new_root);
				new_root = NULL;
			}
			delt(root);
			root = NULL;
			i = 0;
			printf("\n");
		}
		if(test < 0)
			break;
	}
	return 0;
} 
