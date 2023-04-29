#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int nl;
	int nc;
	int *elementos;
} MATRIZ;

void criar_matriz (int, int, MATRIZ *);
void inicializar_matriz (MATRIZ *);
void somar_matriz (MATRIZ *, MATRIZ *, MATRIZ *);
void subtrair_matriz (MATRIZ *, MATRIZ *, MATRIZ *);
void multiplicar_matriz (MATRIZ *, MATRIZ *, MATRIZ *);

void criar_matriz (int a, int b, MATRIZ *m){
	m->nl = a;
	m->nc = b;
	*m.elementos = (int *) calloc (a*b, sizeof(int));
	if (!m->elementos){
		printf ("Naum foi possivel alocar o espaço :( \n");
		exit (1);
	}
}

void inicializar_matriz (int a, int b, MATRIZ *m){
	int i, j;
	printf ("Hora de inserir os elementos!\n");
	for (i = 0; i < a; i++){
		for (j = 0; j < b; j++){
			printf ("Insira o elemento [%d][%d]", i, j);
			scanf ("%d", matriz[i*b + j]);
		}
	}
}

void somar_matriz (MATRIZ *m1, MATRIZ *m2, MATRIZ *m3){
	int i, j;
	if (m1->nl == m2->nl && m1->nc == m2->nc){	
		criar_matriz(m1->nl, m1->nc, m3);
		for (i = 0; i < m1->nl; i++){
			for (j = 0; j < m1->nc ; j++){
				m3->elementos[i*m3->nc + j] = m1->elementos[i*m1->nc + j] + m2->elementos[i*m2->nc + j];
			}
		}
	}
	else printf ("A soma naum eh possivel\n");
}

void subtrair_matriz (MATRIZ *m1, MATRIZ *m2, MATRIZ *m3){
	int i, j;
	if (m1->nl == m2->nl && m1->nc == m2->nc){
		criar_matriz(m1->nl, m1->nc, m3);
		for (i = 0; i < m1->nl; i++){
			for (j = 0; j < m1->nc ; j++){
				m3->elementos[i*m3->nc + j] = m1->elementos[i*m1->nc + j] - m2->elementos[i*m2->nc + j];
			}
		}
	}
	else printf ("A soma naum eh possivel\n");
}

void multiplica_matriz (MATRIZ *m1, MATRIZ *m2, MATRIZ *M3){
	int i, j, z;
	if (m1->nc == m2->nl){	
		criar_matriz(m1->nl, m2->nc, m3);
		for (i = 0; i < m1->nl; i++)
			for (j = 0; j < m2->nc; j++){
				m3->elementos[i*m3->nc + j] = 0;
				for ( z = 0; z < m1->nc ; z++)
					m3->elementos[i*m3->nc + j] += m1->elementos[i*m1->nc + z]*m2->elementos[z*m2->nc + j];
		}
	}
	else printf ("O produto naum eh possivel\n");
}
