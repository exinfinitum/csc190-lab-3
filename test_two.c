#include "process.h"

int main(int argc, const char * argv[])
{
    if(argc != 3)
    {
        printf("Please enter only the first PID and maximum size of memory.\n");
        return 0;
    }
    else
    {
	// first tree
	struct process* first = make_process(1, 1);
	first->left = make_process(2, 2);
	first->right = make_process(3, 3);
	first->left->left = make_process(4, 4);
	first->left->right = make_process(5, 5);
	first->right->left = make_process(6, 6);

	// second tree
	struct process* second = make_process(7, 7);
	second->right = make_process(8, 8);
	second->right->left = make_process(9, 9);
	second->right->right = make_process(10, 10);
	second->right->left->right = make_process(11, 11);

	// Test 1: contains_pid
	printf("Testing contains_pid\n");
	printf("%d\n", contains_pid(first, 2)); // 1
	printf("%d\n", contains_pid(first, 6)); // 1
	printf("%d\n", contains_pid(first, 23)); // 0
	printf("%d\n", contains_pid(NULL, 2)); // 0
	printf("%d\n", contains_pid(second, 11)); // 1
	printf("%d\n", contains_pid(second, 223)); // 0

	// Test 2: total_mem
	printf("Testing total_mem\n");
	printf("%d\n", total_mem(NULL)); // 0
	printf("%d\n", total_mem(first)); // 21
	printf("%d\n", total_mem(second)); // 45

	// Test 3: can_add
	printf("Testing can_add\n");
	// unique PIDs
	printf("%d\n", can_add(second, make_process(7, 7), 1000) ); // 0
	printf("%d\n", can_add(second, make_process(11, 7), 1000) ); // 0
	printf("%d\n", can_add(second, make_process(12, 7), 1000) ); // 1
	// max memory
	printf("%d\n", can_add(second, make_process(12, 1), 0) ); // 0
	printf("%d\n", can_add(second, make_process(12, 1), 45) ); // 0
	printf("%d\n", can_add(second, make_process(12, 1), 46) ); // 1
	printf("%d\n", can_add(second, make_process(12, 1), 47) ); // 1
	// adding NULL
//	printf("%d\n", can_add(second, NULL, 46) ); // should abort --  can_add: Assertion `new_node' failed.


	// Test 4: insert with level order
	// To begin, we'll test this with 
	// two of our trees from part one.

	// insert level order to first tree:
	int max_mem = 56;
	insert_levelorder(&first, make_process(7, 6), max_mem);  
	print_levelorder(first); // Levelorder: 1 2 3 4 5 6 7
	print_inorder(first); // Inorder: 4 2 5 1 6 3 7

	insert_levelorder(&first, make_process(8, 6), max_mem);  
	print_levelorder(first); // Levelorder: 1 2 3 4 5 6 7 8
	print_inorder(first); // Inorder: 8 4 2 5 1 6 3 7

	insert_levelorder(&first, make_process(9, 6), max_mem);  
	print_levelorder(first); // Levelorder: 1 2 3 4 5 6 7 8 9
	print_inorder(first); // Inorder: 8 4 9 2 5 1 6 3 7

	insert_levelorder(&first, make_process(10, 6), max_mem);  
	print_levelorder(first); // Levelorder: 1 2 3 4 5 6 7 8 9 10
	print_inorder(first); // Inorder: 8 4 9 2 10 5 1 6 3 7

	// now practice adding to a non-complete tree:
//	insert_levelorder(&second, make_process(12, 12)); // should abort since it's not complete:  Assertion `is_complete(*root)' failed.
	
	// insert to NULL:
	struct process *third = NULL;
	insert_levelorder(&third, make_process(20, 5), max_mem);
	print_levelorder(third);
	print_inorder(third);

	// make a non-complete tree
	third->right = make_process(25, 23);
	print_levelorder(third);
	print_inorder(third);

	// and add to it to complete it:
	insert_levelorder(&third, make_process(24, 24), max_mem);
	print_levelorder(third);
	print_inorder(third);

	// and test the can_add assertion:
//	insert_levelorder(&third, make_process(24, 24), max_mem); // should abort: Assertion `can_add(*root, to_add, max_mem)' failed.
//	insert_levelorder(&third, make_process(284, 242222), max_mem); // should abort: Assertion `can_add(*root, to_add, max_mem)' failed.


	// Test 5: create_tree
	printf("Testing create_tree\n");
        int first_pid = atoi(argv[1]);
        int max_size = atoi(argv[2]);
	// this is set up for specific entries from the command-line
	assert(first_pid == 50);
	assert(max_size == 24);

	struct process *fourth = create_tree(first_pid, max_size, 1, 3);
	print_levelorder(fourth);
	print_inorder(fourth);
	/* Levelorder: 50 51 52 
	Inorder: 51 50 52 */

	fourth = create_tree(first_pid, max_size, 1, 24);
	print_levelorder(fourth);
	print_inorder(fourth);
	/*
	Levelorder: 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 
	Inorder: 65 57 66 53 67 58 68 51 69 59 70 54 71 60 72 50 73 61 55 62 52 63 56 64
	*/

//	fourth = create_tree(first_pid, max_size, 1, 25);
	// two: process.c:244: insert_levelorder: Assertion `can_add(*root, to_add, max_mem)' failed.



	// Test 6: is_sorted
	printf("Testing is_sorted\n");
	printf("%d\n", is_sorted(NULL)); // 1
	printf("%d\n", is_sorted(first)); // 1
	printf("%d\n", is_sorted(second)); // 1

	first->right->left = make_process(12, 5);
	printf("%d\n", is_sorted(first)); // 0

	struct process *sixth = make_process(20, 6);
	sixth->left = make_process(17, 6);
	printf("%d\n", is_sorted(sixth)); // 0



/*
	// Test 7: get_min
	printf("Testing get_min\n");
	print_process(get_min(NULL, 0)); // NULL: blank line
	printf("\n");
	print_process(get_min(fourth, 0)); // 50
	printf("\n");
	print_process(get_min(fourth, 50)); // 50
	printf("\n");
	print_process(get_min(fourth, 51)); // 51
	printf("\n");
	print_process(get_min(fourth, 72)); // 72
	printf("\n");
	print_process(get_min(fourth, 73)); // 73
	printf("\n");
	print_process(get_min(fourth, 74)); // NULL: blank line
	printf("\n");
//	get_min(first, 0); // should abort: get_min: Assertion `is_sorted(root)' failed.

	// Test 8: rebuild_tree
	printf("Testing rebuild_tree\n");

	// rebuild a tree that doesn't need it
	printf("%d\n", rebuild_tree(&fourth)); // 0
	printf("%d\n", rebuild_tree(NULL)); // 0

	// make a small tree to rebuild
	struct process *fifth = make_process(17, 3);
	fifth->right = make_process(20, 4);
	// when rebuilt, the 20 node should be on the left
	rebuild_tree(&fifth);
	print_levelorder(fifth); // 17 20
	print_inorder(fifth); // 20 17

	rebuild_tree(&sixth);
	print_levelorder(sixth); // 17 20
	print_inorder(sixth); // 20 17

	// and finally, rebuild second
	rebuild_tree(&second);
	print_levelorder(second); // 7 8 9 10 11
	print_inorder(second); // 10 8 11 7 9

	second->right->right = make_process(20, 3);
	print_levelorder(second); // 7 8 9 10 11 20
	print_inorder(second); // 10 8 11 7 9 20

	rebuild_tree(&second);
	print_levelorder(second); // 7 8 9 10 11 20
	print_inorder(second); // 10 8 11 7 20 9


	// Test 9: kill
	printf("Testing kill\n");

	// kill on NULL
	printf("%d\n", kill(NULL, 5)); // 0
	// kill a PID not in tree
	printf("%d\n", kill(&second, 5)); // 0 

	// kill a leaf
	kill(&first, 8);
	print_inorder(first); // 1 2 3 4 5 7 8 9 12
	print_preorder(first); // 1 2 4 9 12 5 3 7 8

	// kill another leaf (left)
	kill(&first, 9);
	print_inorder(first); // 1 2 3 4 5 7 8 12
	print_preorder(first); // 1 2 4 12 5 3 7 8

	// kill another leaf (right)
	kill(&first, 12);
	print_inorder(first); // 1 2 3 4 5 7 8
	print_preorder(first); // 1 2 4 9 5 3 7 8

	// kill root
	struct node *seventh = make_process(80, 1);
	kill(&seventh, 80);
	print_inorder(seventh); // is null

	// kill a different root
	kill(&first, 1);
	print_inorder(first); // 2 3 4 5 7 8
	print_preorder(first); // 2 3 5 7 4 8

	// kill a parent with a right child
	kill(&first, 3);
	print_inorder(first); // 2 4 5 7 8
	print_preorder(first); // 2 4 7 8 5

	// kill a parent with a left child and right child
	kill(&first, 4);
	print_inorder(first); // 2 5 7 8
	print_preorder(first); // 2 5 8 7

	// kill a parent with only left child
	kill(&first, 5);
	print_inorder(first); // 2 7 8
	print_preorder(first); // 2 7 8

	return 0;
*/
    }
}



