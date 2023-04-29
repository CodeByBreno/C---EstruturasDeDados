#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int N;
	int start;
	int end;
	int *val;
	int max;
} FILA_SEQ;

void create_row (int, FILA_SEQ *);
void print_full_row (FILA_SEQ);
void insert (int, FILA_SEQ *);
void remove (FILA_SEQ *);
void destroy (FILA_SEQ *);
void generate_row (FILA_SEQ *, int, int);

main (){
	int x, choose = 1;
	FILA_SEQ row;
	printf ("Insert the row size : ");
	scanf ("%d", &x);	
	create_row (x, &row);
	while (choose == 1){
		print_full_row (row);
		printf ("\nWhat you want to do?\n"
				"Press 1 to insert a new element\n"
				"Press 2 to remove the first element of the row\n"
				"Press 3 to generate a PA row\n"
				"Press anything else to close the aplication\n");
		scanf ("%d", &choose);
		switch(choose){
			case 1:
				printf ("Put the element you want to insert: ");
				scanf ("%d", &x);
				insert (x, &row);
				break;
			case 2:
				remove (&row);
				break;
			case 3:
				printf ("\nInsert the number of the count beggining\n"
						"and the one at the end. The row will be generated\n"
						"putting the first number in the last position and\n"
						"stablishing the subsequent numbers in decrescent/crescent\n"
						"order until the second is reached\n"
						"For example, if you insert '1' and '8', the roll will recive\n"
						"1 2 3 4 5 6 7 8, if there's enough space, sure\n");
				scanf ("%d %d", &x, &choose);
				generate_row (&row, x, choose);
				break;
			default:
				destroy (&row);
				exit(2);
		}
		choose = 1;
		printf ("\nDo something else?\n"
				"Press 1 to continue\n"
				"Press anything else to close\n");
		scanf ("%d", &choose);
		system ("cls");
	}	
}
	
void create_row (int max, FILA_SEQ * row){
	row->val = (int *) calloc(max, sizeof(int));
	if (row->val == 0){
		printf ("An error had ocourred while alocating memory\n");
		exit (1);
	}
	row->start = 0;
	row->end = -1;
	row->N = 0;
	row->max = max;
}

void print_full_row (FILA_SEQ row){
	int i;
	if (row.N == 0){
		printf ("The row is empty\n");
		return;
	}
	for (i = row.start; row.N--; i++){
		if (i == row.max)
			i = 0;
		printf ("%d ", row.val[i]);
	}
	printf ("\n");
}

void insert (int num, FILA_SEQ * row){
	int aux;

	if (row->N == row->max){
		printf ("The row is full\n");
		return;
	}

	// poderia ser feito de outra maneira
	aux = row->end + 1;
	if (aux == row->max) aux = 0;
	row->end = aux;

	row->val[aux] = num;
	row->N++;
}

void remove (FILA_SEQ * row){

	if (row->N == 0){
		printf ("The row is empty\n");
		return;
	}	
	
	row->val[row->start] = 0; // opcional
	if (row->start + 1 == row->max) row->start = 0;
	else row->start++;
	row->N--;	
	printf ("Sucefully removed!\n");
}

void destroy (FILA_SEQ * row){
	free (row->val);
}

void generate_row (FILA_SEQ * row, int m, int n){
	
	if (row->N == row->max){
		printf ("The limit has been reached\n");
		return;
	}

	row->end++;
	if (row->end == row->max) row->end = 0;
	row->val[row->end] = m;
	row->N++;

	if (m == n){
		printf ("Suceffully added!\n");
		return;
	}
	
	if (m > n) m--;
	if (m < n) m++;

	generate_row (row, m, n);
}

