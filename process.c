// process.c
// implements a binary tree, uses it for making a process tree
// YOU, DATE

#include "process.h"

// Implement your methods here

// Implement your methods here
struct process* make_process(int pid, int mem_used)
{
	assert((pid >= 0) && (mem_used > 0));
	//Create memory space for the process
	struct process* output = malloc(sizeof(struct process));
	//Initiate the variables
	output->pid = pid;
	output->mem_used = mem_used;
	output->left = NULL;
	output->right = NULL;
	return output;
}

void helper_print_postorder(struct process *root)
{
	if(root)	
	{
		//left, right, then root
		helper_print_postorder(root->left);
		helper_print_postorder(root->right);
		printf("%d ", root->pid);
	}
}


void print_postorder(struct process *root)
{
	printf("Postorder: ");
	helper_print_postorder(root);
	printf("\n");
}

void helper_print_inorder(struct process *root)
{
	if(root)
	{        	
		//left, root, right

        	helper_print_inorder(root->left);
		printf("%d ", root->pid);
        	helper_print_inorder(root->right);
   	}
}

void print_inorder(struct process *root)
{
	printf("Inorder: ");
	helper_print_inorder(root);
	printf("\n");
}




void lvlorder_recursive(struct queue **btqueue)
{
	if (*btqueue == NULL)
	{
		return;
	}
	struct process *node = dequeue(btqueue);
	if(node == NULL)
	{
		return;
	}
	printf("%d ", node->pid);
	if(node->left)
	{
		enqueue(node->left, btqueue);
	}
	if(node->right)
	{
		enqueue(node->right, btqueue);
	}
	lvlorder_recursive(btqueue);

}


void helper_print_levelorder(struct process *root)
{
	struct queue *pointme = NULL;
	struct queue **bt_queue = &pointme;
	enqueue(root, bt_queue);
	lvlorder_recursive(bt_queue);
}

void print_levelorder(struct process *root)
{
	printf("Level order: ");
	helper_print_levelorder(root);
	printf("\n");
}


int num_nodes(struct process *root)
{	
//If not a root (meaning empty tree), we return 0. Else we return 1, and add 1 for every
//node in the tree.
	if(!root)
	{
		return 0;
	}
	int number = 1;
	number += num_nodes(root->left);
	number += num_nodes(root->right);
	return number;
}

void complete_recursive(struct queue **btqueue, int lastnull, int* incomplete)
{
	//Traverse the tree lengthwise. If there is a non-null node following a null,
	//the tree is not complete.
	int null = 0;
	if (*btqueue == NULL)
	{
		return;
	}
	struct process *node = dequeue(btqueue);
	if(node == NULL)
	{
		null = 1;
	}
	if(node && lastnull)
	{
		*incomplete = 1;
	}
	if(node)
	{
		enqueue(node->left, btqueue);
		enqueue(node->right, btqueue);
	}
	complete_recursive(btqueue, null, incomplete);

}




int is_complete(struct process *root)
{
	//We do a level order traversal. Enqueue all nodes.
	//A complete node will have absolutely no non-null processes
	//following a null node.
	struct queue *pointme = NULL;
	struct queue **bt_queue = &pointme;
	enqueue(root, bt_queue);
	int notcomplete = 0;
	int *incomplete = &notcomplete;
	complete_recursive(bt_queue, 0, incomplete);
	if (notcomplete)
	{
	return 0;
	}
	else
	{
		return 1;
	}

	
}

void remove_all_rec(struct process *root)
{
	//Traverse postorder and free nodes.
	if(root)	
	{
		//left, right, then root
		remove_all_rec(root->left);
		remove_all_rec(root->right);
		free(root);
	}
}

void remove_all(struct process **root)
{
	//We free the children first, else we cannot access them anymore as the root's pointer is deleted
	//Similar to postorder, but instead of print we free.
	if(root)
	{
	struct process *target = *root;
	if(target)	
	{
		//left, right, then root
		remove_all_rec(target->left);
		remove_all_rec(target->right);
		free(target);
	}
	*root = NULL;
	}
}

int contains_pid(struct process *root, int target)
{	
//If not a root (meaning empty tree), we return 0. Else, check each node for the pid.
	if(!root)
	{
		return 0;
	}
	if(root->pid == target)
	{
		return 1;
	}
	//If either the right or left subtrees have the pid, our tree also has the pid (corollary).
	int cont_left = contains_pid(root->left, target);
	int cont_right = contains_pid(root->right, target);
	if(cont_left || cont_right)
	{
		return 1;
	}
	return 0;
}

int total_mem(struct process *root)
{	
//If not a root (meaning empty tree), we return 0. Else we get our memory size, and then add the memory used
//by our child nodes. Return this number.
	if(!root)
	{
		return 0;
	}
	int number = root->mem_used;
	number += total_mem(root->left);
	number += total_mem(root->right);
	return number;
}

int can_add(struct process *root, struct process *new_node, int max_mem)
{
	assert(new_node);
	//If we don't have the PID, and root plus memory is less than max mem: we can add. Else, no.
	if((!(contains_pid(root, new_node->pid))) && ((total_mem(root) + new_node->mem_used) <= max_mem))
	{
		return 1;
	}
	return 0;
}

struct process** findempty_recursive(struct queue **btqueue)
{
	struct process **firstempty;
	//Traverse the tree lengthwise. If we find a node
	//whose children are null, return a pointer to the node's
	//left or right pointer respectively (whichever is null).
	if(*btqueue == NULL)
	{
		return NULL;
	}
	//Unqueue last node. Is its children empty? If so, return a pointer there.
	struct process *node = dequeue(btqueue);
	if(node->left == NULL)
	{
		firstempty = &node->left;
		return firstempty;
	}
	if(node->right == NULL)
	{
		firstempty = &node->right;
		return firstempty;
	}
	//Enqueue the next nodes.
	if(node->left)
	{
		enqueue(node->left, btqueue);
	}
	if(node->right)
	{
		enqueue(node->right, btqueue);
	}
	//Recurse!
	findempty_recursive(btqueue);

}

void insert_levelorder(struct process **root, struct process *to_add, int max_mem)
{
	//Use level order traversal to get to the last non-filled child slot. (Helper)
	assert(can_add(*root, to_add, max_mem));
	if(!(*root))
	{
		*root = to_add;
	}
	else
	{
		struct queue *pointme = NULL;
		struct queue **btqueue = &pointme;
		enqueue(*root, btqueue);
		struct process **target = findempty_recursive(btqueue);
		*target = to_add;
	}
	assert(is_complete(*root));
}

struct process **create_helper(int first_pid, int max_mem, int mem_per_proc, int num_nodes, struct process *root, int max_pid)
{
	//Recursively use insert_levelorder to keep inserting nodes into our tree in order.
	struct process **pointme = &root;
	if(first_pid < max_pid)
	{
		struct process *new_node = make_process(first_pid, mem_per_proc);
		insert_levelorder(pointme, new_node, max_mem);
		create_helper(first_pid + 1, max_mem, mem_per_proc, num_nodes, root, max_pid);
	}
	return pointme;
}

struct process *create_tree(int first_pid, int max_mem, int mem_per_proc, int num_nodes)
{
	//create a null pointer so gcc wouldn't go crazy about 'uninitialized @$%*@'
	struct process *pointme = NULL;
	//run the helper - it's separate since we only want that bit to recurse
	struct process **firstone = create_helper(first_pid, max_mem, mem_per_proc, num_nodes, pointme, first_pid + num_nodes);
	return *firstone;
}

void sorted_recursive(struct queue **btqueue, int lastvalue, int* not_sorted)
{
	//Traverse the tree lengthwise. If the last value is smaller than the current, we are sorted.
	//Else, we are not.
	int thisvalue;
	if (*btqueue == NULL)
	{
		return;
	}
	struct process *node = dequeue(btqueue);
	if(node == NULL)
	{
		return;
	}
	thisvalue = node->pid;
	if(thisvalue < lastvalue)
	{
		*not_sorted = 1;
	}
	if(node->left)
	{
		enqueue(node->left, btqueue);
	}
	if(node->right)
	{
		enqueue(node->right, btqueue);
	}
	sorted_recursive(btqueue, thisvalue, not_sorted);

}

int is_sorted(struct process *root)
{
	//Use a queue - verify that the next element in the queue is larger than our preceding (or null).
	struct queue *pointme = NULL;
	struct queue **bt_queue = &pointme;
	enqueue(root, bt_queue);
	int unsorted = 0;
	int *not_sorted = &unsorted;
	sorted_recursive(bt_queue, 0, not_sorted);
	if (unsorted)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
/*

struct process *get_min_rec(struct process *root, int smallest_val, int curr_smallest)
{
	if(!root)
	{
		return curr_smallest;
	}
	
	return number;
}


struct process *get_min(struct process *root, int smallest_val);
{
	//Examine all nodes. Record the lowest value, and the smallest value we have yet encountered. Return that one.
	if(!root)
	{
		return smallest_val;
	}
	int number = root->mem_used;
	number += total_mem(root->left);
	number += total_mem(root->right);
	return number;
}


int rebuild_tree(struct process **root);
{
	//Enqueue all nodes, and then nullify their left and right pointers while we insert them levelorder into a new tree.
	//A sorting algorithm would be nice here!
}
*/
