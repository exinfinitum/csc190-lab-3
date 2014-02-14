one: process.h process_provided_parts.c process.c test_one.c
	gcc -Wall process.h process_provided_parts.c process.c test_one.c -o one -g
two: process.h process_provided_parts.c process.c test_two.c
	gcc -Wall process.h process_provided_parts.c process.c test_two.c -o two -g 
three: process.h process_provided_parts.c process.c test_two.c
	gcc -Wall process.h process_provided_parts.c process.c test_three.c -o two -g 
