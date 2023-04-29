#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int nl;
	int nc;
	int *elementos;
} DIAG;

void criar_matriz (int, int, DIAG *);
void inicializar_matriz (DIAG *);
void imprimir_matriz (DIAG *);
void ler_elemento (int, int, DIAG *);

void criar_matriz (int a, int b, DIAG *m){
	m->nl = a;
	m->nc = b;
	m->elementos = (int *) calloc (a, sizeof(int)); 
	if (!m->elementos){
		printf ("Naum foi possivel criar a matriz \n1");
		exit(1);
	}
}

void inicializar_matriz (DIAG *){
	int i;
	printf ("Atenção: Essa é uma matriz diagonal, portanto os elementos inseridos estarão somente na diagonal principal \n");
	for (i = 0; i < m->nl; i++){
		printf ("Insira o elemento %d da diagonal principal\n", i+1);
		scanf ("%d", m1->elementos + i);
	}
}

void imprimir_matriz (DIAG *m){
	int i, j;
	for (i = 0; i < m->nl; i++){
		for (j = 0; j < m->nc; j++){
			if (i == j) printf ("%d ", m->elementos[i]);
			else printf ("0 ");
		}
		printf ("\n");
	}
}

void ler_elemento (int a, int b, DIAG *m){
	if (a == b) printf ("%d", m->elementos[a]);
	else printf ("0");
}
