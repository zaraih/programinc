#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "KindredSpirits.h"

// HELPER FUNCTIONS

#define EMPTY_LIST_ERR INT_MIN
#define EMPTY_STACK_ERR INT_MIN
// Linked lists struct and functions
// for stacks taken from queues notes
// Credit: Dr. Szumlanski
typedef struct linkNode
{
	int data;
	struct linkNode *next;
} linkNode;

typedef struct LinkedList
{
	linkNode *head;
	linkNode *tail;
} LinkedList;

linkNode *create_linkNode(int data)
{
	linkNode *n = malloc(sizeof(linkNode));
	n->data = data;
	n->next = NULL;
	return n;
}

LinkedList *create_list(void)
{
	return calloc(1, sizeof(LinkedList));
}

linkNode *recursive_destroyer(linkNode *head)
{
	if (head == NULL)
		return NULL;

	recursive_destroyer(head->next);
	free(head);

	return NULL;
}

LinkedList *destroy_list(LinkedList *list)
{
	if (list == NULL)
		return NULL;

	recursive_destroyer(list->head);
	free(list);

	return NULL;
}

void tail_insert(LinkedList *list, int data)
{
	if (list == NULL)
		return;

	if (list->tail == NULL)
	{
		list->head = list->tail = create_linkNode(data);

		return;
	}

	list->tail->next = create_linkNode(data);
	list->tail = list->tail->next;
}

int head_delete(LinkedList *list)
{
	int retval;
	linkNode *temp;

	if (list == NULL || list->head == NULL)
		return EMPTY_LIST_ERR;

	retval = list->head->data;

	temp = list->head->next;

	free (list->head);

	list->head = temp;

	if (list->head == NULL)
		list->tail = NULL;

	return retval;
}

// stacks struct and functions

typedef struct Stack
{
	LinkedList *list;
	int size;
} Stack;

Stack *create_stack(void)
{
	Stack *s = malloc(sizeof(Stack));
	s->list = create_list();
	s->size = 0;
	return s;
}

int isEmpty(Stack *s)
{
	return (s == NULL || s->size == 0);
}

Stack *destroyStack(Stack *s)
{
	if (s == NULL)
		return NULL;

	// free list within the struct
	destroy_list(s->list);
	// free the struct itself
	free(s);

	return NULL;
}

void push (Stack *s, int data)
{
	if (s == NULL || s->list == NULL)
		return;

	tail_insert(s->list, data);
	s->size++;
}

int pop(Stack *s)
{
	if (isEmpty(s))
		return EMPTY_STACK_ERR;

	s->size--;
	return head_delete(s->list);
}

void preorder (node *root, Stack *s)
{
	if (root == NULL)
	 return;

	push (s, root->data);
	preorder(root->left, s);
	preorder(root->right, s);
}

void postorder (node *root, Stack *s)
{
	if (root == NULL)
	 return;

	postorder(root->left, s);
	postorder(root->right, s);
	push (s, root->data);
}
// This function is taken from the
// header file with a new function name
node *new_node(int data)
{
	node *n = malloc(sizeof(node));

	n->data = data;
	n->left = n->right = NULL;

	return n;
}

// Credit: Dr. Szumlanski
int isItself(node *a, node *b)
{
	if (a == NULL && b == NULL)
		return 1;

	if (a == NULL || b == NULL)
		return 0;

	if (a->data == b->data)
		return 1;

	return isReflection(a->left, b->left) || isReflection(a->right, b->right);
}
// REQUIRED FUNCTIONS

// A function to determine whether the trees
// rooted at a and b are reflections of one another
int isReflection(node *a, node *b)
{
	// if both a and b are null then then they are empty
	// trees which means they are reflection of eachother
	if (a == NULL && b == NULL)
	{
		return 1;
	}
	// make sure neither of the roots are NULL then
	// check if the data at the root is equal
	else if (a != NULL && b != NULL )
	{
		if (a->data == b->data)
		{
			// check that the opposite subtrees of the roots are equivalent
			// If opposite subtrees are equvalent then they are reflections
			if (isReflection(a->left, b->right) && isReflection(a->right, b->left))
				return 1;
		}
	}

	return 0;
}

// A function that creates a new tree, which
// is a reflection of the tree rooted at root
node *makeReflection(node *root)
{
	node *reflection;

	// empty tree is a reflection of itself
	if (root == NULL)
		return NULL;

	// if it's not empty then copy
	// root value to the reflective tree
	reflection = new_node(root->data);

	// aslong as there is a node to left of the root
	// copy the value to the right of the new tree
		reflection->right = makeReflection(root->left);

	// aslong as there is a node to right of the root
	// copy the value to the left of the new tree
		reflection->left = makeReflection(root->right);

	return reflection;
}

int kindredSpirits(node *a, node *b)
{
	Stack *s1, *s2;
	int temp1, temp2, equal1 = 0, equal2 = 0, check;

	if (a == NULL && b == NULL)
		return 1;
	// create two stacks to
	// store each tree
	s1 = create_stack();
	s2 = create_stack();

	// store preorder and
	// postorder into a stack
	preorder(a, s1);
	postorder(b, s2);

	// check if the size of both stacks are equal
	if (s1->size != s2->size)
	{
		s1 = destroyStack(s1);
		s2 = destroyStack(s2);
		return 0;
	}
	// if the root is only one node check whether
	// the data within the node is equal
	if ((s1->size == 1 && s2->size == 1) && a->data == b->data)
	{
		s1 = destroyStack(s1);
		s2 = destroyStack(s2);
		return 1;
	}
	else if ((s1->size == 1 && s2->size == 1) && a->data != b->data)
	{
		s1 = destroyStack(s1);
		s2 = destroyStack(s2);
		return 0;
	}

	// check if both trees are the same
	// than the preorder and postorder
	// cannot be the same
	check = isItself(a,b);
	if (check)
	{
		s1 = destroyStack(s1);
		s2 = destroyStack(s2);
		return 0;
	}
	// check that the preorder and
	// postorder are the equal
	while (!equal1)
	{
		temp1 = pop(s1);
		temp2 = pop(s2);
		if (temp1 == temp2)
			equal1 = 1;
		else
			equal1 = 0;
	}

	// the rest of the code below does the same value check but for the
	// case in which the preorder of b is equal to the postorder of a
	s1 = destroyStack(s1);
	s2 = destroyStack(s2);

	s1 = create_stack();
	s2 = create_stack();

	preorder(b, s1);
	postorder(a, s2);

	if (s1->size != s2->size)
	{
		s1 = destroyStack(s1);
		s2 = destroyStack(s2);
		return 0;
	}
	if ((s1->size == 1 && s2->size == 1) && a->data == b->data)
	{
		s1 = destroyStack(s1);
		s2 = destroyStack(s2);
		return 1;
	}
	else if ((s1->size == 1 && s2->size == 1) && a->data != b->data)
	{
		s1 = destroyStack(s1);
		s2 = destroyStack(s2);
		return 0;
	}
	while (!equal2)
	{
		temp1 = pop(s1);
		temp2 = pop(s2);
		if (temp1 == temp2)
			equal2 = 1;
		else
			equal2 = 0;
	}

	s1 = destroyStack(s1);
	s2 = destroyStack(s2);

	if (equal1 == 1 || equal2 == 1)
		return 1;

	return 0;
}

double difficultyRating(void)
{
	return 2.5;
}

double hoursSpent(void)
{
	return 8.0;
}
