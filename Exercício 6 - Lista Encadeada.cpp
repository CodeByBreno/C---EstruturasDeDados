#include <stdio.h>
#include <stdlib.h>

typedef struct{
	float content;
	int next;
} NODO;

typedef struct{
	int Start;
	int Free;
	NODO * vet;
	int max;
} LEE;

int acess(int, LEE *);
void create_LEE (LEE *, int);
int test_empty (LEE *);
int size (LEE *);
void insert (float, int, LEE *);
float locate (int, LEE *);
void print_full_list (LEE *);
void remove (int, LEE *);
void search (float, LEE *);

main (){
	int i, aux, flag, aux2, tam;
	float value;
	char x;
	LEE * List;
	printf ("Insert the maximum list size: ");
	scanf ("%d", &aux);
	scanf ("%c", &x);
	printf ("\n");
	create_LEE (List, aux);
	while (1){
		printf ("The current list is: \n");
		print_full_list (List);
		printf ("\n\nWhat you want to do next?\n"
				"Press 1 to See te size of the list\n"
				"Press 2 to See if the list is Empty\n"
				"Press 3 to Insert an element on some position\n"
				"Press 4 to Insert a Serie of element on adjacent positions\n"
				"Press 5 to Remove an element on some position\n"
				"Press 6 to See if the element is on the list\n"
				"Press anything else to close the aplication\n");
		
		scanf ("%c", &x);
		printf ("\n");
		switch (x){
			case '1': 
				printf ("The list have %d elements\n", size(List));
				break;
			case '2':
				printf ("You know, u could just look at the top of the screen, but anyway...\n");
				if (test_empty) printf ("The list is Empty\n");
				else printf ("The list is not Empty\n");
				break;
			case '3': 
				printf ("Insert the position where you want to put the element: ");
				scanf ("%d", &aux);
				printf ("Insert the element: ");
				scanf ("%f", &value);
				insert (value, aux, List);
				break;
			case '4':
				printf ("Insert the position of the first element: ");
				scanf ("%d", &aux);
				tam = size(List);
				if ((!(aux == 1 && tam == 0) && aux > tam) || aux < 1){
					printf ("Spot out of reach\n");
					break;
				}
				printf ("Insert the amount of elements you want to insert: ");
				scanf ("%d", &aux2);
				if (aux2 > List->max - tam || aux2 < 1){
					printf ("Invalid amount!\n");
					break;
				}
				printf ("Insert the elements: ");
				for (i = 0; i < aux2 ; i++){
					scanf ("%f", &value);
					insert (value, aux + i, List);
				}
				break;
			case '5':
				printf ("Insert the position of the element to be removed: ");
				scanf ("%d", &aux);
				remove (aux, List);
				break;
			case '6':
				printf ("Well, you could look at the top of the screen but okay...\n");
				printf ("Which element you want to look for? ");
				scanf ("%f", &value);
				search (value, List);
				break;
			default:
				exit (42);
		}
		x = 'B';
		printf ("Press enter to continue: \n");
		scanf ("%c%c", &x, &x);
		setbuf (stdin, NULL); 
		system ("cls");
	}
}

int acess(int k, LEE *I){
	int i;
	for ( i = I->Start; k-- - 1; i = I->vet[i].next);
	return (i);
}

void create_LEE ( LEE * I , int max){
	int i;
	if (max == 0){
		printf ("Why do you want a blank list?!\n");
		exit(5);
	}
	I->Start = -1;
	I->Free = 0;
	I->max = max;
	I->vet = (NODO *) malloc (sizeof(NODO)*max);
	if (!I->vet){
		printf ("Memory alocation not allowed\n");
		return;
	}
	for (i = 0; i < max - 1; i++)
		I->vet[i].next = i + 1;
	I->vet[i].next = -1;
}

int test_empty (LEE *I)
	{ return (I->Start == -1); }

int size (LEE * I){
	int i, count;
	for (i = I->Start, count = 0; i != -1 ; i = I->vet[i].next, count++);
	return (count);
}

void insert (float Value, int k, LEE * I){
	int i, aux;
	if (k < 1 || k > size(I) + 1){
		printf ("\nSpot out of reach\n\n");
		return;
	}
	if (I->Free == -1){
		printf ("The list is full\n");
		return;
	}
	if (k == 1){
		I->vet[I->Free].content = Value;
		aux = I->vet[I->Free].next;
		I->vet[I->Free].next = I->Start;
		I->Start = I->Free;
		I->Free = aux;
	}
	else{
		I->vet[I->Free].content = Value;
		aux = I->vet[I->Free].next;
		i = acess (k - 1, I);
		I->vet[I->Free].next = I->vet[i].next;
		I->vet[i].next = I->Free;
		I->Free = aux;
	}
}

float locate (int k, LEE *I){
	int i;
	for (i = I->Start; k-- - 1; i = I->vet[i].next);
	return (I->vet[i].next);
}

void print_full_list (LEE *I){
	int i, count;
	if (I->Start == -1) printf("The List is Empty\n");
	for (i = I->Start, count = 1; i != -1 ; i = I->vet[i].next, count++){
		printf ("%3.2f ", I->vet[i].content);
		if (count == 10) printf ("\n");
	}
}

void remove (int k, LEE * I){
	int i, aux, count;
	int pre, pos, now;
	if (k < 1 || k > size(I)){
		printf ("Spot out of reach\n");
		return;
	}
	if (k == 1){
		aux = I->Start;
		I->Start = I->vet[I->Start].next;
		I->vet[aux].next = I->Free;
		I->Free = aux; 
	}
	else{
		/*position = k + 1;
		for (i = I->Start, count = 1; k-- ; i = I->vet[i].next, count++){
			if (count == position - 2) pre = i;
			if (count == position - 1) now = i;
		}*/
		k = acess(k - 1, I);
		aux = I->vet[k].next;
		I->vet[k].next = I->vet[I->vet[k].next].next;
		I->vet[aux].next = I->Free;
		I->Free = aux;
	}
}

void search (float value, LEE * I){
	int i, count;
	for (i = I->Start, count = 1; i != -1 ; i = I->vet[i].next, count++)
		if (I->vet[i].content == value){
			printf ("The element is the %dth on list\n", count);
			return;
		}
	printf ("The element is not on the list\n");
}
