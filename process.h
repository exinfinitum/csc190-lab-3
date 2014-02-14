#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

struct process{
	int pid; // must be unique	
	int mem_used; // memory_used must not exceed MAX_MEM
	struct process *left;
	struct process *right;
};

struct stack{
	struct process *proc;
	struct stack *next; // singly linked list	
};

struct queue{
	struct process *proc;
	struct queue *next; // singly-linked
};

// Provided to students: stack
struct process *pop(struct stack **head);
void push(struct process *to_push, struct stack **head);
void print_stack(struct stack *head);

// Provided to students: queue
void enqueue(struct process *to_enqueue, struct queue **front);
struct process* dequeue(struct queue **front);
void print_queue(struct queue *head);
struct queue* peek(struct queue **front);

// Provided tostudents: process 
void print_process(struct process *root);
void print_preorder(struct process *root);

// Part one methods
struct process* make_process(int pid, int mem_used);
void print_postorder(struct process *root);
void print_inorder(struct process *root);
void print_levelorder(struct process *root);
int num_nodes(struct process *root);
int is_complete(struct process *root);
void remove_all(struct process **root);

// Part two methods
int contains_pid(struct process *root, int value);
int total_mem(struct process *root);
int can_add(struct process *root, struct process *new_node, int max_mem);
void insert_levelorder(struct process **root, struct process *to_add, int max_mem);
struct process *create_tree(int first_pid, int max_mem, int mem_per_proc, int num_nodes);
int is_sorted(struct process *root);
struct process *get_min(struct process *root, int smallest_val);
int rebuild_tree(struct process **root);
int kill(struct process **root, int pid);

/*
// Part three methods
int can_add_alternate(struct process *root, struct process *new_node, int max_mem);
void spawn(struct node *root, int max_mem);
int is_leaf(struct process *root, struct process *current);
int time_to_crash(struct process *root, int max_mem);
void killall(struct node **root);
*/
