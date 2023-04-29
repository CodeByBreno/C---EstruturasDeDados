#include <stdio.h>
#include <stdlib.h>
#define length 21

typedef struct node{
	char vet[length];
	struct node * next;
} NODE;
typedef NODE * PILE_ENC;

void strcpy (char *, char *);
void create (PILE_ENC *);
void print_full_pile (PILE_ENC);
int is_empty (PILE_ENC);
void push (PILE_ENC *, char *);
char * top (PILE_ENC);
void pop (PILE_ENC *);
char * top_pop (PILE_ENC *);
void destroy (PILE_ENC*);

main (){
	PILE_ENC Pile;
	int choose;
	char vet[length];
	create(&Pile);
	while(1){
		print_full_pile (Pile);
		printf ("\nWhat you want to do?\n"
				"Press 1 to insert a new name on the pile\n"
				"Press 2 to remove the name on the pile top\n"
				"Press 3 to see the name on top of the pile\n"
				"Press 4 to remove and see the name on top of the pile\n"
				"Press anything else to quit\n");
		scanf ("%d", &choose);
		switch(choose){
			case 1:
				setbuf (stdin, NULL);
				printf ("Insert the new name: ");
				gets(vet);
				push (&Pile, vet);
				break;
			case 2:	
				pop (&Pile);
				break;
			case 3:
				printf ("\n%s\n", top(Pile));
				break;
			case 4:
				printf ("\n%s\n", top_pop(&Pile));
				break;
			default:
				printf ("Are you certain?"
						"Press 1 if YES\n"
						"Press anything else if NO\n");
				scanf ("%d", &choose);
				if (choose == 1){
					destroy (&Pile);
					exit (42);
				}
		}
		printf ("Do something else?\n"
				"Press anything else if YES\n"
				"Press 0 if NO\n");
		scanf ("%d", &choose);
		if (choose == 0){
			destroy (&Pile);
			exit (42);
		}
		system ("cls");
	}
}
void strcpy (char * vet1, char * vet2){
	int i;
	for (i = 0; i < length && vet2[i] != '\0'; i++) vet1[i] = vet2[i];
	vet1[i] = '\0';
}

void create (PILE_ENC * Pile){
	*Pile = (NODE *) malloc (sizeof(NODE));
	if (!*Pile){
		printf ("An error had ocourred while alcating memory\n");
		exit(1);
	}
	(*Pile)->next = NULL;
}

int is_empty (PILE_ENC Pile){
	return (Pile->next == NULL);
}

void print_full_pile (PILE_ENC Pile){
	NODE * i;
	if (is_empty(Pile)){
		printf ("The pile is empty\n");
		return;
	}
	printf ("TOP = %s\n", Pile->vet);
	for (i = Pile->next; i->next != NULL ; i = i->next) printf ("%s\n", i->vet);
}

void push (PILE_ENC * Pile, char * vet){
	NODE * aux;
	aux = (NODE *) malloc (sizeof(NODE));	
	if (aux == NULL){
		printf ("An error had ocourred while trying to alocate memory\n");
		return;
	}
	strcpy (aux->vet, vet);
	aux->next = *Pile;
	*Pile = aux;
	printf ("\nDone!\n");
}

char * top (PILE_ENC Pile){
	if (Pile->next == NULL){
		printf ("The pile is empty\n");
		return(NULL);
	}
	return (Pile->vet);
}

void pop (PILE_ENC * Pile){
	NODE * aux;
	aux = *Pile;
	*Pile = (*Pile)->next;
	free (aux);
	printf ("Done!\n");
}

char * top_pop (PILE_ENC * Pile){
	char * aux;
	if ((*Pile)->next == NULL){
		printf ("The pile is empty\n");
		return(NULL);
	}
	strcpy (aux, (*Pile)->vet);
	pop (Pile);
	return (aux);
}

void destroy (PILE_ENC * Pile){
	NODE * aux, *i = *Pile;;
	while (aux != NULL){
		aux = i->next;
		free (i);
		i = aux;
	}
}

