#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	float inf;
	struct node * prev;
	struct node * next;
} NODO;

typedef struct{
	int size;
	NODO * next;
} NC;
typedef NC * LCDE;

void create_list (LCDE *);
void print_full_list (LCDE);
void insert (LCDE *, int, float);
void remove (LCDE *, int);
void destroy (LCDE *);

main (){
	LCDE list;
	int choose, aux = 1, flag = 1;
	float newie;
	while (aux == 1){
		if (flag == 2){
			printf ("The full list is bellow:\n");
			print_full_list (list);
		}
		else printf ("There's no list here. Try to create a new one\n");
		
		printf ("\nChoose an option or die (just kidding................ or not)\n"
				"Press 1 to Create a New List\n"
				"Press 2 to Insert an element on some position\n"
				"Press 3 to Remove an element on some position\n"
				"Press 4 to Destroy the current list\n"
				"Press anything else to close\n");
		scanf ("%d", &choose);
		switch (choose){
			case 1:		
				if (flag == 2){
					printf ("You will destroy the current list\n"
							"Continue?\n"
							"(1) YES\n"
							"(2) NO\n");
					scanf ("%d", &choose);
					if (choose != 1){
						printf ("Okay\n");
						break;
					}
					destroy (&list);
				}
				create_list (&list);
				flag = 2;
				break;
			case 2:
				if (flag == 1) printf ("You have to create a list first!\n");
				else{
					printf ("Insert the position of the new element: ");
					scanf ("%d", &choose);
					if (choose < 1 || choose > list->size + 1){
						printf ("Invalid position, the list has only %d elements", list->size);
						break;
					}
					printf ("Insert the new element: ");
					scanf ("%f", &newie);
					insert (&list, choose, newie);
					break;
				}
			case 3:
				if (flag == 1) printf ("You have to create a list first!\n");
				else{
					if (list->size == 0){
						printf ("The list is empty!\n");
						break;
					}
					printf ("Insert the position where you want to remove the element: ");
					scanf ("%d", &choose);
					if (choose < 1 || choose > list->size){
						printf ("You're trying to reach an inexistent spot\n");
						break;
					}
					remove (&list, choose);
					break;
				}
			case 4:
				printf ("Are you certain of this? \n"
						"(1) YES\n"
						"(2) NO\n");
				scanf ("%d", &choose);
				if (choose == 1){
					destroy (&list);
					printf ("It's done, you monster!\n");
				}
				else printf ("So don't do it, lol\n");
				flag = 1;
				break;
			default:
				printf ("Have a lovely day! \n");
				exit (1);
		}
		aux = 1;
		printf ("\nDo something else?\n"
				"(1) YES\n"
				"(2) NO\n");
		scanf ("%d", &choose);
		system("cls");
	}
	list = NULL;
	return 1;
}	

void create_list (LCDE * list){
	NODO *aux;

	(*list)->size = 0;
	aux = (NODO *) malloc (sizeof(NODO));
	if (aux == NULL){
		printf ("An error had ocurred while creating the list\n");
		exit(521);
	}
	(*list)->next = aux;
	aux->next = aux;
	aux->prev = aux;
	aux->inf = 0;
	printf ("Done!\n");
}

void print_full_list (LCDE LT){
	NODO *i;
	int k;
	k = LT->size;
	if (LT->size == 0) printf ("The list is empty\n");
	else{
		for (i = LT->next; k--; i = i->next)
			printf ("%.2f ", i->inf);
		printf ("\n");
	}
}

void insert (LCDE * list, int k, float data){
	NODO *i, *vex;
	int tam, aux;
	tam = (*list)->size;

	if (tam == 0){
		((*list)->next)->inf = data;
		(*list)->size++;
		return;
	}
	else{
		vex = (NODO *) malloc (sizeof(NODO));
		vex->inf = data;

		// Finding, in the most efficent way, the memory position where we want to insert new data
		if (vex == NULL){
			printf ("An error had ocourred while trying to alocate memory\n");
			return;
		}

		if (k == 1){
			i = ((*list)->next)->prev;
			(*list)->next = vex;
		}
		else{
			if (k > tam/2){
				if (k == tam + 1) i = (*list)->next;
				else{
					aux = tam - k + 1;
					for (i = (*list)->next; aux--; i = i->prev);
				}
			}
			else
				for (i = (*list)->next; k-- - 1; i = i->next);
		}

		(i->prev)->next = vex;
		vex->prev = i->prev;
		vex->next = i;		
		i->prev = vex;
		(*list)->size++;
		return;
	}
}

void remove (LCDE * list, int k){
	NODO *i, *aux;
	int tam, aux2;
	tam = (*list)->size;
	aux2 = tam - k + 1;

	if (k == 1){
		i = (*list)->next;
		(*list)->next = i->next;
	}
	else{
		if (k > tam/2)
			for (i = (*list)->next; aux2--; i = i->prev);	
		else
			for (i = (*list)->next; k-- - 1; i = i->next);
	}
	
	(i->prev)->next = i->next;
	(i->next)->prev = i->prev;
	(*list)->size--;
}

void destroy (LCDE * list){
	NODO *i, *aux;
	for (i = (*list)->next; (*list)->size--; i = aux){
		aux = i->next;
		free (i);
	}
}
