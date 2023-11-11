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
node root = NULL, new_root = NULL, seq[10];
node findnode(int , node);
void rotate(node, int);
void preorder(node);
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
		if (height(ptr_next->left) > height(ptr_next->right))
			return LL(ptr);                                            //LL
		else
			return LR(ptr);                                              //LR
	}
	else
	{
		ptr_next = ptr->right;
		if (height(ptr_next->right) > height(ptr_next->left))      //RR
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
	if (value < ptr->data)
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
void postorder(node ptr, int index)
{
	if (ptr)
	{
		postorder(ptr->left, index);
		postorder(ptr->right, index);
		if (isbalance(ptr) == 1)
			rotate(ptr, index);
	}
}
void delt(node ptr)
{
	if (ptr)
	{
		delt(ptr->left);
		delt(ptr->right);
		free(ptr);
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
node spilt(node pre_root)
{
	node next_root = pre_root->right;
	pre_root->right = NULL;
	return next_root;
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
void rotate(node ptr, int index)
{
	if (ptr == seq[index])
		seq[index] = skewmode(ptr);
	else
	{
		node pre = findnode(ptr->data, seq[index]); 
		node x = skewmode(ptr);
		if (pre->data < x->data)
			pre->right = x;
		else
			pre->left = x;
	}
}
int main()
{
	FILE *fptr;
	fptr = fopen("Input2.txt", "r");
	int out, i, j, index, k, ht, give_num, test, record, find;
	char c;
	int ary[20];
	for (out = 0;out < 3;out++)
	{
		i = 0;
		index = 0;
		fscanf(fptr, "%d %d", &ht, &give_num);
		while(1)
		{
			fscanf(fptr, "%d", &ary[i++]);
			test = fscanf(fptr, "%c", &c);
			if (c == '\n' || test < 0)
				break;
		}
		int read_num = i;
		for (i = 0;i < read_num;i++)
		{
			int record = index, num = 0;
			for (k = 0;k <= index;k++)
			{
				if (seq[k] && ary[i] < seq[k]->data)
				{
					num = k;
					break;
				}
			}
			if (num == 0)
				num = index;
			seq[index] = insert(seq[index], ary[i]);
			postorder(seq[index], index);
			if (height(seq[index]) > ht)
			{
				seq[index+1] = spilt(seq[index]);
				postorder(seq[index], index);
				record++;
			}
			index = record;
		}
		find = (ht == findnum(seq[ht]))?ht:findnum(seq[give_num-1]);
		printf("%d\n", find);
		for (i = 0; i <= index;i++)
		{
			delt(seq[i]);
			seq[i] = NULL;
		}	
		for(i = 0;i < read_num;i++)
			ary[i] = 0;
	} 
	return 0;
} 
