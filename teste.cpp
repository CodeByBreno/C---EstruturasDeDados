#include <stdio.h>

main (){
	int test = 10, limit = 10, a = 2;
	while (--test){
		printf ("%d ", test);
	}
	printf ("\n");
	test = 10;
	do{
		printf ("%d ", test);
	} while (test--);
	test = 2;
	printf ("\n");
	
	while (test++ <= limit){
		printf ("%d ", test);
	}
}
