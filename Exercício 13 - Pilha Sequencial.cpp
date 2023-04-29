#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int top;
	char ** vet;
	int max;
	int length;
} PILE_SEQ;

void strcpy (char *, char *, int);

void create (PILE_SEQ *, int, int);
void print_full_pile (PILE_SEQ *);
void push (PILE_SEQ *, char *);
void pop (PILE_SEQ *);
void destroy (PILE_SEQ *);

main (){
	PILE_SEQ Pile;
	int x, choose;
	printf ("Insert the amount of names that can be put in the pile: ");
	scanf ("%d", &x);
	printf ("Insert the maximum size of each name: ");
	scanf ("%d", &choose);
	create (&Pile, x, choose);
	x = 1;
	char vet[Pile.length];
	while (1){
		print_full_pile (&Pile);
		printf ("\nWhat you want to do?\n"
				"Press 1 to insert a new name on the pile\n"
				"Press 2 to remove the top element of the pile\n"
				"Press anything else to quit\n");
		scanf ("%d", &choose);
		switch(choose){
			case 1:
				setbuf (stdin, NULL);
				printf ("Enter the name (respect the maximun size of %d) : ", Pile.length);
				gets (vet);
				push (&Pile, vet);
				break;
			case 2:
				pop (&Pile);
				break;
			default:
				printf ("\nAre you certain?\n"
						"(1) = YES\n"
						"(Other number) = NO\n");
				scanf ("%d", &choose);
				if (choose == 1) {
					destroy (&Pile);
					exit (42);
				}
		}
		printf ("\nDo something else?\n"	
				"(Any number) = YES\n"
				"(0) = NO\n");
		scanf ("%d", &choose);
		if (choose == 0){
			destroy (&Pile);
			exit (42);
		}

		system ("cls");
	}
}

void strcpy (char * vet1, char * vet2, int k){
	int i; 
	for (i = 0; i < k && vet2[i] != '\0'; i++) vet1[i] = vet2[i];
	vet1[i] = '\0';
}

void create (PILE_SEQ * Pile, int max, int length){
	int i;
	Pile->length = length;
	Pile->max = max;
	Pile->vet = (char **) malloc (sizeof(char*)*max);
	if (Pile->vet == NULL){
		printf ("An error had ocurred while alocating memory\n");
		exit (2);
	}

	for (i = 0; i < max; i++){
		Pile->vet[i] = (char *) malloc (sizeof(char)*length);
		if (Pile->vet == NULL){
			printf ("An error had ocurred while alocating memory\n");
			exit (1);
		}
	}
	Pile->top = 0;
}

void print_full_pile (PILE_SEQ * Pile){
	int i;
	if (Pile->top == 0) printf ("The pile is empty\n");
	else{
		printf ("The element on the top is: %s\n", Pile->vet[Pile->top - 1]);
		if (Pile->top != 1) {
			printf ("And the following names are above:\n");
			for (i = Pile->top - 2; i >= 0; i--)
				printf ("%s\n", Pile->vet[i]);
		}
		else
			printf ("And there's no other element on it\n");
	}
}

void push (PILE_SEQ * Pile, char * vet){
	if (Pile->top == Pile->max){
		printf ("The pile is full! You can't insert a new element\n");
		return;
	}
	strcpy (Pile->vet[Pile->top], vet, Pile->length);
	Pile->top++;
	printf ("Sucefully pushed!\n");
}

void pop (PILE_SEQ * Pile){
	Pile->top--;
	printf ("Sucefully popped!\n");
}

void destroy (PILE_SEQ * Pile){
	int i;
	for (i = 0; i < Pile->max; i++)
		free(Pile->vet[i]);
	free(Pile->vet);
}

