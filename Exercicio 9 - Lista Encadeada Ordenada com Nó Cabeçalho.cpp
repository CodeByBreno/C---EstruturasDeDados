#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	char text[21];
	struct node * next;
} NODO;

typedef struct{
	int inf;
	char title[31];
	NODO * next;
} NC;

typedef NC * LED;
LED * index;

void strcpy (char *, char *);
int alphabetic (char *, char *);
int size (char *);

LED * create_list (LED *, int, char *);
void show_list (LED *, int);
void insert (LED *, int, char *);
void remove (LED, int);
void change_name (LED, char *);
void group (LED *, int, int);
void destroy (LED);

int size_index = 1;

main (){
	LED * index;
	int aux = 1, chose, list_number = 1;
	char *txt, lixo;
	index = (LED *) malloc (sizeof(LED));
	if (index == NULL){
		printf ("Some weird error had happened, try again\n");
		exit(2);
	}
	txt = (char *) malloc (sizeof(char)*21);
	if (txt == NULL){
		printf ("Some weird error had happened, try again\n");
		exit(3);
	}
	while (aux == 1){
		printf ("What you want to do?\n"
				"Press 1 to Create a New List\n"
				"Press 2 to See one of those\n"
				"Press 3 to See all lists\n"
				"Press 4 to Insert a New element on some list\n"
				"Press 5 to Remove an element from some list\n"
				"Press 6 to Put all the element of one list in other\n"
				"Press 7 to Destroy some list\n"
				"Press Anything else to quit\n");
				scanf ("%d", &chose);
				switch (chose){
					case 1:
						scanf ("%c", &lixo);
						printf ("Hello! Insert the name of the new list: ");
						gets (txt);
						index = create_list (index, list_number, txt);
						printf ("test = %s", index[list_number-1]->title);
						if (index != NULL){
							printf ("The list %s has been sucessifully created!", txt);
							list_number++;
							break;
						}
						else{
							printf ("Some error ocourred while creating the list, pleade try again\n");
							break;
						}
					case 2: 
						printf ("Which list you want to see?\n");
						scanf ("%d", &chose);
						if (chose < 1 || chose > size_index){
							printf ("This list doesn't exist!\n");
							break;
						}
						show_list (index, chose);
						break;
					case 3:
						for (chose = 1; chose != size_index; chose++, printf ("\n\n")) 
							show_list(index, chose);
						break;	
					case 4: 
						printf ("In which list you want to insert elements?  ");
						scanf ("%d", &chose);					
						if (chose < 1 || chose > size_index){
							printf ("This list doesn't exist!\n");
							break;
						}
						printf ("Okay, now insert the text you want to put (max = 20 lines):\n");
						gets (txt);
						insert (index, chose, txt);
						break;
					case 5:
						printf ("Okay, from which list you want to remove?   ");
						scanf ("%d", &chose);
						if (chose < 1 || chose > size_index){
							printf ("This list doesn't exist!\n");
							break;
						}
						printf ("Nice, now enter the position of the element to be removed\n");
						scanf ("%d", &aux);
						remove (*(index + chose - 1), aux);
						break;
					case 6:
						printf ("Pay attention: You will put all the elements os one list in other,\n"
								"after that the first list will be destroyed. All elements are automatically\n"
								"put o alphabetic order\n");
						printf ("First, insert the number of the list you want to put elements on:   ");
						scanf ("%d", &chose);
						if (chose < 1 || chose > size_index){
							printf ("This list doesn't exist!\n");
							break;
						}
						printf ("Okay, now enter the list which the elements you want to put: ");
						scanf ("%d", &aux);
						if (aux < 1 || aux > size_index){
							printf ("This list doesn't exist!\n");
							break;
						}
						group (index, chose, aux);
						break;
					case 7:
						printf ("Insert the number of the list you want to destroy: ");
						scanf ("%d", &chose);
						if (chose < 1 || chose > size_index){
							printf ("This list doesn't exist!\n");
							break;
						}
						destroy (*(index + chose - 1));
						printf ("It's done! You monster!\n");
						break;
					default:
						exit (1);
				}
			aux = 1;
			printf ("\n\nDo something else?\n"
					"YES = Press 1\n"
					"NO = Press 2\n");
			scanf ("%d", &aux);
			system("cls");
	}
}

int size (char *vet1){
	int i;
	for (i = 0; vet1[i] != '\0'; i++);
	return i;
}

void strcpy (char *vet1, char *vet2){
	int i;
	for (i = 0; vet2[i] != '\0'; i++) vet1[i] = vet2[i];
	vet1[i] = '\0';
}

int alphabetic (char * vet1, char * vet2){
	int i, a, b;
	for (i = 0; vet1 != '\0' && vet2 != '\0'; i++){
		if (vet1[i] < vet2[i]) return 1;
		if (vet1[i] > vet2[i]) return 2;
	}
	a = size(vet1);
	b = size(vet2);
	if (a < b) return 1;
	if (b > a) return 2;
	return 1;
}

LED * create_list (LED * index, int c, char * vet){
	index = (LED *) realloc (index, sizeof(LED)*(c+1));
	if (index == NULL){
		printf ("Some error happened while creating a new list\n");
		return NULL;
		}
	index[c-1]->inf = 0;
	index[c-1]->next = (NODO *) malloc (sizeof(NODO));
	if (index[c-1]->next == NULL){
		printf ("Some error happened while creating a new list\n");
		return NULL;
	}
	strcpy (index[c-1]->title, vet);
	index[c-1]->next->next = NULL;
	index[c] = NULL;
	size_index++;
	return index;
}

void show_list (LED * index, int p){
	NODO * i;
	printf ("%d", index[p-1]->inf);
	if (index[p-1]->inf == 0) printf ("The list is empty\n");
	else{
		printf ("LISTA %d -- %s :\n\n", p, index[p-1]->title);
		for (i = index[p-1]->next; i != NULL; i = i->next) puts (i->text);
	}
}

void insert (LED * index, int p, char * txt){
	NODO * i, *aux;
	int b, flag = 2;

	b = alphabetic (txt, index[p-1]->next->text);

	/* Now i'm going to find the memory position of the node before
	the position where i want to insert the new node, that's will be in " i " */
	if (b == 1){
		aux = (NODO *) malloc (sizeof(NODO));
		if (!aux){
			printf ("An error had ocorred while alocating the memory\n");
			return;
		}
		aux->next = index[p-1]->next;
		index[p-1]->next = aux;
	}
	else {
		for (i = index[p-1]->next; i->next != NULL ; i = i->next) 
			if (alphabetic (txt, i->next->text) == 1) break; 
		aux = (NODO *) malloc (sizeof(NODO));
		if (!aux){
			printf ("An error had ocorred while alocating the memory\n");
			return;
		}
		aux->next = i->next;
		strcpy (aux->text, txt);
		i->next = aux;
	}
	index[p-1]->inf++;
}

void remove (LED list, int k){
	NODO *i, *aux;

	if (k < 1 || k > list->inf){
		printf ("This position is empty or invalid...\n");
		return;
	}
	
	if (k == 1){
		aux = list->next;
		list->next = list->next->next;
		free (aux);
	}
	else{
		for (i = list->next; k-- - 2; i = i->next);
		aux = i->next;
		i->next = i->next->next;
		free (aux);
	}

	list->inf--;
}

void change_name (LED list, char *txt){
	strcpy (list->title, txt);
}

void group (LED * index, int k, int p){
	NODO * i, *aux;
	int j;

	if (k < 0 || k > size_index - 1 || p < 0 || p > size_index - 1){
		printf ("There's no list here or you put and invalid position...\n");
		return;
	}

	for (i = index[p-1]->next; i != NULL; i = i->next) insert (index, k, i->text);
	destroy (*(index + k - 1));

	for (j = k - 1; index[j+1] != NULL; j++){
		index[j] = index[j+1];
	}
	index[j] = NULL;
}

void destroy (LED list){
	NODO * i, *aux;
	for (i = list->next; i != NULL; i = aux){
		aux = i->next;
		free (i);
	}
	free (list);
}




