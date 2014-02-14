
#include "process.h"


//////////////////////////////////////////////////////////////////////////////////
///// Stack implementation
//////////////////////////////////////////////////////////////////////////////////

void push(struct process *to_push, struct stack **head)
{
	// Pushes a new process, to_push, onto the stack
	// PRE: head != NULL
	// POST: first element of stack contains to_push; *head = new_node
	assert(head);

	struct stack *new_node = malloc(sizeof(struct stack));
	new_node->proc = to_push;
	new_node->next = (*head);
	*head = new_node;
}

struct process *pop(struct stack **head)
{
	// Pops an element off the stack
	// PRE: *head != NULL
	// POST: head points to what was the second element of the stack
	assert(*head);

	struct stack *to_return = *head;
	*head = (*head)->next;
	struct process* ret = to_return->proc;
	free(to_return);
	return ret;
}

void print_stack(struct stack *head)
{
	while(head)
	{
		print_process(head->proc);
		head = head->next;
	}
}


//////////////////////////////////////////////////////////////////////////////////
///// Queue implementation
//////////////////////////////////////////////////////////////////////////////////

void enqueue(struct process *to_enqueue, struct queue **front)
{
	// enqueues to_enqueue at the end of the
	// queue fronted by front
	// PRE: none
	// POST: to_enqueue is at the end
	struct queue *new_node = malloc(sizeof(struct queue));
	new_node->proc = to_enqueue;
	new_node->next = NULL;

	if(!(*front))
	{
		// if front is NULL we're at the beginning.
		*front = new_node;
		return;
	}

	// otherwise, find the last node
	struct queue *curr = *front;
	while(curr->next)
	{
		curr = curr->next;
	}

	// then we are at the last node, and we insert here
	curr->next = new_node;
}

struct queue* peek(struct queue **front)
{
	// Peeks at the first element in the queue
	// PRE: none
	// POST: none

	return *front;
}

struct process* dequeue(struct queue **front)
{
	// takes the first element off the front
	// PRE: none
	// POST: front points to what was the second element of the stack
	if(*front == NULL)
		return NULL;

	struct queue *to_return = *front;
	(*front) = (*front)->next;
	struct process *ret = to_return->proc;
	free(to_return);
	return ret;
}

void print_queue(struct queue *head)
{
	printf("Queue: ");
	while(head)
	{
		print_process(head->proc);
		head = head->next;
	}
	printf("\n");
}


//////////////////////////////////////////////////////////////////////////////////
///// Helpers for processes
//////////////////////////////////////////////////////////////////////////////////

void print_process(struct process *root)
{
	// Prints a single process
	// PRE: none
	// POST: none
	if(root)
	{
		printf("%d ", root->pid);
	}
}

void helper_print_preorder(struct process *root)
{
	// Recursively prints a binary tree using preorder traversal
	// PRE: none
	// POST: none
	if(root)
	{
		print_process(root);
		helper_print_preorder(root->left);
		helper_print_preorder(root->right);
	}
}

void print_preorder(struct process *root)
{
	// Prints a binary tree using preorder traversal
	// PRE: none
	// POST: none
	printf("Preorder: ");
	helper_print_preorder(root);
	printf("\n");
}


