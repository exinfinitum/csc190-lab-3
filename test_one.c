#include "process.h"

int main()
{
	// Test 1. First create a tree to test make_process
	printf("Testing make process\n");

	struct process* first = make_process(1, 1);
	first->left = make_process(2, 2);
	first->right = make_process(3, 3);
	first->left->left = make_process(4, 4);
	first->left->right = make_process(5, 5);
	first->right->left = make_process(6, 6);
	// and print: 
	print_preorder(first); // Preorder: 1 2 4 5 3 6

	// test this only accepts valid pid and memory
//	first->left->left->left = make_process(-2, 5); // should abort
//	first->left->left->left = make_process(5, 0); // should abort
//	first->left->left->left = make_process(0, -6); // should abort

	// And another tree
	struct process* second = make_process(7, 7);
	second->right = make_process(8, 8);
	second->right->left = make_process(9, 9);
	second->right->right = make_process(10, 10);
	second->right->left->right = make_process(11, 11);
	print_preorder(second); // Preorder: 7 8 9 11 10 

	// And another
	struct process* third = make_process(12, 12);
	third->right = make_process(13, 13);
	third->right->left = make_process(14, 14);
	third->right->right = make_process(15, 15);
	third->right->left->right = make_process(16, 16);
	third->right->right->left = make_process(17, 17);
	print_preorder(third); // Preorder: 12 13 14 16 15 17

	// Test 2. Now test postorder
	printf("Testing postorder\n");
	print_postorder(NULL);
	print_postorder(first); 
	print_postorder(second);
	print_postorder(third);
	// should print:
		// Testing postorder
		// Postorder: 
		// Postorder: 4 5 2 6 3 1 
		// Postorder: 11 9 10 8 7 
		// Postorder: 16 14 17 15 13 12  
	
	// Test 3. Now test inorder
	printf("Testing inorder\n");
	print_inorder(NULL); 
	print_inorder(first); 
	print_inorder(second);
	print_inorder(third); 
	// should print:
		// Testing inorder
		// Inorder: 
		// Inorder: 4 2 5 1 6 3
		// Inorder: 7 11 9 8 10 
		// Inorder: 12 14 16 13 17 15 

	// Test 4. Level order
	printf("Testing levelorder\n");
	print_levelorder(NULL); 
	print_levelorder(first); 
	print_levelorder(second); 
	print_levelorder(third);
	// should print:
		// Testing levelorder
		// Levelorder: 
		// Levelorder: 1 2 3 4 5 6
		// Levelorder: 7 8 9 10 11
		// Levelorder: 12 13 14 15 16 17 

	// Test 5. Num nodes
	printf("Test num nodes\n");
	printf("%d\n", num_nodes(NULL)); // 0
	printf("%d\n", num_nodes(first)); // 6
	printf("%d\n", num_nodes(second)); // 5
	printf("%d\n", num_nodes(third)); // 6

	// Test 6. Is complete? 
	
	printf("Testing is_complete\n");
	printf("%d\n", is_complete(NULL)); // 1
	printf("%d\n", is_complete(first)); // 1
	printf("%d\n", is_complete(second)); // 0
	printf("%d\n", is_complete(third)); // 0
	first->right->right = make_process(7, 7);
	printf("%d\n", is_complete(first)); // 1
	struct process **terminate = &(first->right->left);
	remove_all(terminate);
	first->right->left = NULL;
	printf("%d\n", is_complete(first)); // 0

	// Test 7. Remove all 
	printf("Testing remove\n");
	remove_all(NULL);
	remove_all(&first);
	remove_all(&second);
	remove_all(&third); 
	print_inorder(first); 
	print_inorder(second);
	print_inorder(third);
	// should print:
		// Testing remove
		// Inorder: 
		// Inorder:  
		// Inorder: 

	return 1;

}
