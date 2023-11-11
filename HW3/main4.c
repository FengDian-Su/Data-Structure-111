#include <stdio.h>
#include <stdlib.h>
typedef struct list *node;
struct list
{
    int data;
    node left;
    node right;
};
node root = NULL, tt, pre, leaf;
typedef struct tlist *tern;
struct tlist
{
    int data;
    tern left;
    tern middle;
    tern right;
};
tern troot = NULL, ttt, tpre, tleaf;
int max = 0, ary[2];
int queue[40], rear = -1, front = -1;
node newnode(int value)
{
	node tnode = (node)malloc(sizeof(struct list));
	tnode->data = value;
	tnode->left = NULL;
	tnode->right = NULL;
	return tnode;
}
tern tnewnode(int value)
{
	tern tnode = (tern)malloc(sizeof(struct tlist));
	tnode->data = value;
	tnode->left = NULL;
	tnode->middle = NULL;
	tnode->right = NULL;
	return tnode;
}
int findnum(node ptr)
{
	if (!ptr)
		return 0;
	else
		return 1+findnum(ptr->left)+findnum(ptr->right);
}
int tfindnum(tern ptr)
{
	if (!ptr)
		return 0;
	else
		return 1+tfindnum(ptr->left)+tfindnum(ptr->middle)+tfindnum(ptr->right);
}
void findpre(node ptr, int value)
{
	if (ptr)
	{
		if (ptr->left && ptr->left->data == value)
			pre = ptr;
		else if (ptr->right && ptr->right->data == value)
			pre = ptr;
		findpre(ptr->left, value);
		findpre(ptr->right, value);
	}
}
void tfindpre(tern tptr, int value)
{
	if (tptr)
	{
		if (tptr->left && tptr->left->data == value)
			tpre = tptr;
		else if (tptr->middle && tptr->middle->data == value)
			tpre = tptr;
		else if (tptr->right && tptr->right->data == value)
			tpre = tptr;
		tfindpre(tptr->left, value);
		tfindpre(tptr->middle, value);
		tfindpre(tptr->right, value);
	}
}
void findnode(node ptr, int value)
{
	if (ptr)
	{
		if (ptr->data == value)
		{
			tt = ptr;
			return;
		}
		findnode(ptr->left, value);
		findnode(ptr->right, value);
	}
}
void tfindnode(tern ptr, int value)
{
	if (ptr)
	{
		if (ptr->data == value)
		{
			ttt = ptr;
			return;
		}
		tfindnode(ptr->left, value);
		tfindnode(ptr->middle, value);
		tfindnode(ptr->right, value);
	}
}
int ismp(node ptr1, node ptr2)
{
	if (!ptr1 && !ptr2)
		return 1;
	if (!ptr1 || !ptr2)
		return 0;
	if (findnum(ptr1) == findnum(ptr2))
		return (ismp(ptr1->left, ptr2->left) && ismp(ptr1->right, ptr2->right))
		 	 || ismp(ptr1->left, ptr2->right) && ismp(ptr1->right, ptr2->left);
	else
		return 0;
}
int tismp(tern ptr1, tern ptr2)
{
	if (!ptr1 && !ptr2)
		return 1;
	if (!ptr1 || !ptr2)
		return 0;
	if (tfindnum(ptr1) == tfindnum(ptr2))
		return (tismp(ptr1->left, ptr2->left) && tismp(ptr1->middle, ptr2->middle) && tismp(ptr1->right, ptr2->right) || 
				tismp(ptr1->left, ptr2->right) && tismp(ptr1->middle, ptr2->left) && tismp(ptr1->right, ptr2->middle) ||
				tismp(ptr1->left, ptr2->middle) && tismp(ptr1->middle, ptr2->right) && tismp(ptr1->right, ptr2->left) ||
				tismp(ptr1->left, ptr2->left) && tismp(ptr1->middle, ptr2->right) && tismp(ptr1->right, ptr2->middle) ||
				tismp(ptr1->left, ptr2->right) && tismp(ptr1->middle, ptr2->middle) && tismp(ptr1->right, ptr2->left) ||
				tismp(ptr1->left, ptr2->middle) && tismp(ptr1->middle, ptr2->left) && tismp(ptr1->right, ptr2->right));
	else
		return 0;
}
void output(node ptr)
{
	if (ptr)
	{
		output(ptr->left);
		output(ptr->right);
		if (leaf && leaf->data != ptr->data)
		{
			if (ismp(leaf, ptr) && findnum(leaf) > max)
			{
				ary[0] = leaf->data;
				ary[1] = ptr->data;
				max = findnum(leaf);
			}
		}
	}
}
void toutput(tern ptr)
{
	if (ptr)
	{
		toutput(ptr->left);
		toutput(ptr->middle);
		toutput(ptr->right);
		if (tleaf && tleaf->data != ptr->data)
		{
			if (tismp(tleaf, ptr) && tfindnum(tleaf) > max)
			{
				ary[0] = tleaf->data;
				ary[1] = ptr->data;
				max = tfindnum(tleaf);
			}
		}
	}
}
void postorder(node ptr)
{
	if (ptr)
	{
		postorder(ptr->left);
		postorder(ptr->right);
		leaf = ptr;
		output(root);
	}
}
void tpostorder(tern ptr)
{
	if (ptr)
	{
		tpostorder(ptr->left);
		tpostorder(ptr->middle);
		tpostorder(ptr->right);
		tleaf = ptr;
		toutput(troot);
	}
}
void preorder(node ptr)
{
	if (ptr)
	{
		printf("%d ", ptr->data);
		preorder(ptr->left);
		preorder(ptr->right);
	}
}
void tpreorder(tern ptr)
{
	if (ptr)
	{
		printf("%d ", ptr->data);
		tpreorder(ptr->left);
		tpreorder(ptr->middle);
		tpreorder(ptr->right);
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
void tdelt(tern ptr)
{
	if (ptr)
	{
		tdelt(ptr->left);
		tdelt(ptr->middle);
		tdelt(ptr->right);
		free(ptr);
	}
}
int main()
{
	FILE *fptr;
	fptr = fopen("input4.txt", "r");
	int total, cc, k;
	fscanf(fptr, "%d ", &total);
	for (cc = 0;cc < total;cc++)
	{
		int bt, ht, treenum, input[50];
		fscanf(fptr, "%d %d %d", &bt, &ht, &treenum);
		for (k = 0;k < treenum;k++)
			fscanf(fptr, "%d", &input[k]);
		int m = input[0];
		for (k = 1;k < treenum;k++)
			if (input[k] > m)
				m = input[k];
		int i, j = treenum-1;
		if (bt == 2)
		{
			root = newnode(1);
			node ptr = root;
			for (i = 2;i <= m;i++)
			{
				queue[++rear] = i;
				if (!ptr->left)
					ptr->left = newnode(i);
				else if (!ptr->right)
					ptr->right = newnode(i);
				else
				{
					findnode(root, queue[++front]);
					ptr = tt;
					ptr->left = newnode(i);
				}
			}
			for (i = m;i >= 1;i--)
			{
				if (i != input[j])
				{
					findnode(root, i);
					findpre(root, tt->data);
					if (tt == pre->left)
						pre->left = NULL;
					else if (tt == pre->right)
						pre->right = NULL;
					continue;
				}
				j--;
			}
			postorder(root);
  			if (ary[0] < ary[1])
  				printf("%d %d\n", ary[0], ary[1]);
  			else if (ary[1] < ary[0])
  				printf("%d %d\n", ary[1], ary[0]);
  			delt(root);
  			root = tt = pre = leaf = NULL;
		}
		else if (bt == 3)
		{
			troot = tnewnode(1);
			tern ptr = troot;
			for (i = 2;i <= m;i++)
			{
				queue[++rear] = i;
				if (!ptr->left)
					ptr->left = tnewnode(i);
				else if (!ptr->middle)
					ptr->middle = tnewnode(i);
				else if (!ptr->right)
					ptr->right = tnewnode(i);
				else
				{
					tfindnode(troot, queue[++front]);
					ptr = ttt;
					ptr->left = tnewnode(i);
				}
			}
			for (i = m;i >= 1;i--)
			{
				if (i != input[j])
				{
					tfindnode(troot, i);
					tfindpre(troot, ttt->data);
					if (ttt == tpre->left)
						tpre->left = NULL;
					else if (ttt == tpre->middle)
						tpre->middle = NULL;
					else if (ttt == tpre->right)
						tpre->right = NULL;
					continue;
				}
				j--;
			}
			tpostorder(troot);
  			if (ary[0] < ary[1])
  				printf("%d %d\n", ary[0], ary[1]);
  			else if (ary[1] < ary[0])
  				printf("%d %d\n", ary[1], ary[0]);
  			tdelt(troot);
  			troot = ttt = tpre = tleaf = NULL;
		}
		for (k = 0;k < 50;k++)
			input[k] = queue[k] = 0;
		max = 0;
		front = rear = -1;
	}
    return 0;
}
