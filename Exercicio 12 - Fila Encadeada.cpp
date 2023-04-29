#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char name[20];
	struct node * next;
} NODO;

typedef struct{
	NODO * start;
	NODO * end;
	int size;
} Descritor;

typedef Descritor * FILA_ENC;

void strcpy (char *, char *);

void create_row (FILA_ENC *);
void print_full_row (FILA_ENC);
void insert (FILA_ENC, char *);
void remove (FILA_ENC);
void destroy (FILA_ENC *);

int main(){
	FILA_ENC row;
	int choose = 1;
	char name[20];
	create_row (&row);
	while (choose == 1){
		printf ("There's %d clients to be attended\n", row->size);
		print_full_row (row);

		printf ("\nWhat you want top do?\n"
				"Press 1 to insert a new name\n"
				"Press 2 to conclude the first client\n"
				"Press anything else to quit\n");
		scanf ("%d", &choose);
		scanf ("%c", &name[0]);
		switch (choose){
			case 1:
				printf ("Put the new name: ");
				scanf ("%[^\n]", name);
				insert (row, name);
				break;
			case 2:
				remove (row);
				break;
			default:
				printf ("\nAre you certain?\n"
						"(YES) = Press 1\n"
						"(NO) = Press any other number\n");
				scanf ("%d", &choose);
				if (choose == 1) exit(42);
		}
		choose = 1;
		printf ("\nDo something else?\n"
				"(YES) = Press 1\n"
				"(NO) = Press any other number\n");
		scanf ("%d", &choose);
		system ("cls");
	}
}

void strcpy (char * vet1, char * vet2){
	int i;
	for (i = 0; vet2[i] != '\0'; i++)
		vet1[i] = vet2[i];
	vet2[i] = '\0';
}
	
void create_row (FILA_ENC * row){
	*row = (Descritor *) malloc (sizeof(Descritor));
	if (row == NULL){
		printf ("There's been an error while alocating the memory, please try again\n");
		exit(1);
	}
	(*row)->end = (NODO *) malloc (sizeof(NODO));
	if ((*row)->end == NULL){
		printf ("There's been an error while alocating memory\n");
		return;
	}
	(*row)->end->next = NULL;
	(*row)->start = (*row)->end;
	(*row)->start->next = NULL;
	(*row)->size = 0;
}

void print_full_row (FILA_ENC row){
	NODO * i;
	int cont;

	if (row->size == 0) printf ("The row is empty\n");
	else{
		for (i = row->start, cont = 0; i != NULL ; i = i->next, cont++){
			if (cont == 0){
				printf ("\nName in attendance: %s\n\n", i->name);
				if (row->size > 1) printf ("The rest of the clients is:\n");
			}
			else printf ("%s\n", i->name);
		}
	}
}

void insert (FILA_ENC row, char * vet){
	NODO * aux;
	
	if (row->size == 0){
		strcpy (row->end->name, vet);
		row->size++;
	}
	else{
		(row->end)->next = (NODO *) malloc(sizeof(NODO));
		if ((row->end)->next == NULL){
			printf ("Some error had ocourred while trying to alocate memory\n");
			return;
		}	
		strcpy ((row->end)->next->name, vet);
		row->size++;
		row->end = row->end->next;
		row->end->next = NULL;
		printf ("Done!\n");
	}
}

void remove (FILA_ENC row){
	NODO * aux;

	if (row->size == NULL){
		printf ("There's no clients yet...\n");
		return;
	}
	
	aux = row->start;
	row->start = row->start->next;
	free (aux);	
	row->size--;
	printf ("Done!\n");
}

void destroy (FILA_ENC * row){
	NODO * i, * aux;
	for (i = (*row)->start; i != NULL; i = aux){
		aux = i->next;
		free (i);
	}
	free (*row);
}
