#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	int ordem;
	char *elementos;
} SIMEMA;

void criar_matriz (int, SIMEMA *);
void inicializar_matriz (SIMEMA *);
void imprimir_matriz (SIMEMA *);
char consulta_elemento (int, int, SIMEMA *);

main (){
	int a, b;
	SIMEMA *m;
	printf ("Insert the matrix order: ");
	scanf ("%d", &a);
	criar_matriz (a, m);
	inicializar_matriz (m);
	printf ("\n");
	while (1){
		printf ("Chose what you want to do next: \n"
				"Press 1 to show the matrix\n"
				"Press 2 to show one specified element on the matrix\n"
				"Press 3 to close aplication\n");
		scanf ("%d", &a);
		printf ("\n\n");
		switch (a){
			case 1 : 
				imprimir_matriz (m);
				break;
			case 2 : 
				printf ("Insert the element position: ");
				scanf ("%d %d", &a, &b);
				printf ("The element on [%d][%d] is: %c", a, b, consulta_elemento (a, b, m));
				break;
			case 3 :
				exit(3);
			default:
				printf ("Invalid enter\n");
				break;
		}
		printf ("\n\nWant to do something else? \n(YES) = Press 1\n(NO) = Press 2\n");
		scanf ("%d", &a);
		if (a == 0) exit (4);
		else system ("cls");
	}
}

void criar_matriz (int a, SIMEMA *m){
	m -> ordem = a;
	m -> elementos = (char *) malloc ((a+1)*a/2);
	if (!m)	{
		printf ("ERROR: Memory cannot be provided\n");	
		exit (1);
	}
}

void inicializar_matriz (SIMEMA *m){
	int i, j, num = 0, test;
	printf ("ATTENTION: You're inserting only half of the matrix elements \n"
					"Look closely to the position where youre inserting it\n");
	for (i = 0; i < m->ordem; i++)
		for (j = 0; j <= i; j++){
			printf ("Insert the [%d][%d] element: ", i, j);
			scanf ("%c", &test);
 			num = scanf ("%c", &m->elementos[(i+1)*i/2 + j]);
			if (num == 0 || m->elementos[(i+1)*i/2 + j] == '\n'){
				printf ("You tried to insert many character in one run or\n"
						"Some invalid character were placed, closing aplication...");
				exit (2);
				}
			}
}


void imprimir_matriz (SIMEMA *m){
	int i, j;
	for (i = 0; i < m -> ordem; i++, printf ("\n"))
		for (j = 0; j < m -> ordem; j++)
			printf ("%3.c ", consulta_elemento (i, j, m));
}

char consulta_elemento (int a, int b, SIMEMA *m){
	if (a > m->ordem - 1 || a < 0 || b > m->ordem - 1 || b < 0){
		printf ("Invalid position, closing aplication\n");
		exit(5);
	}
	if (b > a)
		return (m->elementos[(b+1)*b/2 + a]);
	else
		return (m->elementos[(a+1)*a/2 + b]);
}
