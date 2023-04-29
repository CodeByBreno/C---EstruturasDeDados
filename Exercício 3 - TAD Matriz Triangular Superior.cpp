#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int ordem;
	int *elementos;
} TRIANSUP;

void criar_matriz (int, TRIANSUP *);
void inicializar_matriz (TRIANSUP *);
void imprimir_matriz (TRIANSUP *);
int consulta_elemento (int, int, TRIANSUP *);

main(){
	int a, b;
	TRIANSUP *m;
	printf ("Insert matrix order: ");
	scanf ("%d", &a);
	if (!a){
		printf ("Nice try");
		exit (42);
	}
	criar_matriz (a, m);
	inicializar_matriz (m);
	while(1){
		printf ("\nWhat you want to do next?: \n");
		printf ("Press 1 to: Show the entire matrix\n");
		printf ("Press 2 to: Show one specified element\n");
		printf ("Press 3 to: Close aplication\n");
		scanf ("%d", &a);
		switch (a){
			case (1) : 
				imprimir_matriz (m);
				printf ("\n\n");
				break;
			case (2) : 
				printf ("Please enter the element coordinates: ");
				scanf ("%d %d", &a, &b);
				printf ("In this position, the follow element was founded: %d\n\n", consulta_elemento(a, b, m));
				break;
			case (3): 
				exit (1);
			default : 
				printf ("Invalid number!");
				system ("cls");
		}
	}
}

void criar_matriz (int a, TRIANSUP *m){
	m->ordem = a;
	m->elementos = (int *) calloc((a+1)*a/2, sizeof(int));
	if (!m->elementos){
		printf ("ERROR: Memory cannot be provided\n");
	}
}

void inicializar_matriz (TRIANSUP *m){
	int i, j;
	printf ("ATTENTION: You're going to insert only the main diagonal elements\n");
	printf ("AND The elements are place COLUMNS BY COLUMNS, not LINE BY LINE\n");
	for (j = 0; j < m->ordem ; j++){
		for (i = 0; i <= j; i++){
			printf ("Insert the [%d][%d] element: ", i, j);
			scanf ("%d", &m->elementos[(j+1)*j/2 + i]);
		}
	}
}

void imprimir_matriz (TRIANSUP *m){
	int i, j, count = 0;
	for (i = 0; i < m->ordem; i++, count = 0){
		for (j = 0; j < m->ordem; j++){
			count += j;
			if (i > j) printf ("  0");
			else printf ("%3d", m->elementos[count + i]);
		}
		printf ("\n");
	}
}

int consulta_elemento (int a, int b, TRIANSUP *m){
	if (a > b) return (0);
	else return (m->elementos[(b+1)*b/2 + a]);
}
