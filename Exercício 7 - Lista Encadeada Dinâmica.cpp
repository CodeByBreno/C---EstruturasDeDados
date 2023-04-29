#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	char inf;
	nodo * next;
} NODO;
typedef NODO * LED;

void create_list (LED *);
NODO * acess (LED, int);
int size(LED);
void print_full_list (LED);
void insert (LED *, int, char);
void remove (LED *, int);
void destroy (LED *);

main (){
	LED * lista;
	int flag = 1, aux, num;
	char answer, lixo;
	create_list (lista);
	while (flag == 1){
		printf ("\n");
		print_full_list(*lista);	
		printf ("\n\nWhat you want to do? \n"
				"Press 1 to insert one element in some position\n"
				"Press 2 to insert a group of elements starting on a certain position\n"
				"Press 3 to remove some element\n"
				"Press anything else to exit\n");
		scanf ("%c%c", &answer, &lixo);
		switch (answer){
			case '1': 
				printf ("What character you want to insert? ");
				scanf ("%c%c", &answer, &lixo);
				printf ("In which position? ");
				scanf ("%d", &aux);
				insert (lista, aux, answer);
				break;
			case '2':
				printf ("Put the starting position : ");
				scanf ("%d", &aux);
				printf ("How munch elements you will set? ");
				scanf ("%d", &num);
				printf ("Insert the elements: ");
				while (num--){
					scanf ("%c", &answer);
					if (answer != '\n' && answer != ' '){ 
						insert (lista, aux++, answer);
					}
					else num++;
				}
				break;
			case '3':
				printf ("Insert the position where you want to eliminate the data: ");
				scanf ("%d", &aux);
				remove (lista, aux);
				break;
			default:
				break;
		}
		printf ("Do something else?\n"
				"(1) = YES\n"
				"(2) = NO\n");
		scanf ("%d", &flag);
		setbuf (stdin, NULL);
		system ("cls");
	}
	destroy(lista);
}

void create_list (LED * lista){ 
	*lista = NULL; 
}

NODO * acess (LED pl, int pos){
	for (pl = pl; pos-- - 1; pl = pl->next);
	return (pl);
}

int size(LED lista){
	int count;
	NODO * i;
	for (count = 0, i = lista; i != NULL ; i = i->next, count++);
	return count;
}

void print_full_list (LED pl){
	int count;
	if (pl == NULL) printf ("The list is empty");
	else for (pl = pl, count = 1; pl != NULL ; pl = pl->next, count++){
			printf ("%c ", pl->inf);
			if (count == 10){
				printf ("\n");
				count = 1;
			}
	}
}

void insert (LED * lista, int k, char data){
	NODO *aux, *node;
	if (data == '\n'){
		return;
	}
	if (k < 1 || k > size(*lista) + 1){
		printf ("Invalid location\n");
		return;
	}
	if (k == 1){
		aux = *lista;
		*lista = (NODO *) malloc (sizeof(NODO));
		if (*lista == NULL){
			printf ("Alocation problem\n");
			return;
		}
		(*lista)->inf = data;
		(*lista)->next = aux;
	}
	else{
		node = acess(*lista, k - 1);
		aux = node->next;
		node->next = (NODO *) malloc (sizeof(NODO));
		if (node->next == NULL){
			printf ("Alocation problem\n");
			return;
		}	
		(node->next)->inf = data;
		(node->next)->next = aux;	
	}
}

void remove (LED * lista, int k){
	NODO *aux, *node;
	if (k < 1 || k > size(*lista)){
		printf ("Invalid location\n");
		return;
	}
	if (k == 1){
		aux = (*lista)->next;
		free (*lista);
		*lista = aux;
	}
	else{
		node = acess (*lista, k - 1);
		aux = (node->next)->next;
		free (node->next);
		node->next = aux;
	}
}

void destroy (LED * pl){
	NODO *aux;
	for (*pl = *pl; *pl != NULL; *pl = aux){
		aux = (*pl)->next;
		free ((*pl)->next);
	}
}

