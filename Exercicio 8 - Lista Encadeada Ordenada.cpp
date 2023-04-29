#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char name[30]; 
	int age;
	char gender;
	float height;
} LDP;

typedef struct node{
	LDP data;
	struct node *next;	
} NODO;

typedef NODO * LED;

void create_list (LED*);
int tam (LED);
NODO * acess (LED, int);
void print_data (LED*, int);
void print_full_list (LED*);
void insert (LED*, char *, int, char, float);
void remove (LED*, int);

int alphabetic (char *, char *);
void strcpy (char *, char *);

main(){
	LED list;
	int x, idade, flag = 1;
	float altura;
	char nome[30], genero, lixo;
	create_list(&list);
 	while (flag == 1){
		setbuf (stdin, NULL);
		printf ("What you want to do?\n"
				"Press 1 to see the data on some position on the list\n"
				"Press 2 to see the full list\n"
				"Press 3 to insert some data package\n"
				"Press 4 to remove some data of the list\n"
				"Press anything else to quit\n\n");
		scanf ("%d", &x);
		switch (x){
			case 1:
				printf ("Insert the position: ");
				scanf ("%d", &x);
				print_data (&list, x);
				break;
			case 2: 
				print_full_list (&list);
				break;
			case 3:
				printf ("Insert the data of the person,\n"
						"Name: ");
				scanf ("%c", &lixo);
				gets (nome);
				printf ("Now insert the age: ");
				scanf ("%d", &idade);
				scanf ("%c", &lixo);
				printf ("Time for the gender: \n"
						"(M) for Male, (F) for Female and (I) for indentifield -> ");
				scanf ("%c", &genero);
				printf ("Alright, now just the the height: ");
				scanf ("%f", &altura);
				insert (&list, nome, idade, genero, altura);
				break;
			case 4:
				printf ("Insert the positon: ");
				scanf ("%d", &x);
				remove (&list, x);
				break;
			default:
				printf ("\nAre you sure you want to quit?\n"
						"(1) YES\n"
						"(2) NO\n");
				scanf ("%d", &x);
				if (x == 1) exit (1);
		}
		printf ("\nDo something else?\n"
				"(1) YES\n"
				"(2) NO\n");
		scanf ("%d", &flag);
		system ("cls");
	}
}

void create_list (LED *list){ *list = NULL; }

int tam (LED list){
	int count = 0;
	NODO * i;
	for (i = list; i != NULL ; i = i->next, count++);
	return (count);
}

int alphabetic (char *vet1, char *vet2){
	int i;
	for (i = 0; vet1[i] != '\0' && vet2[i] != '\0'; i++){
		if (vet1[i] < vet2[i]) return (1);
		if (vet1[i] > vet2[i]) return (2);
	}
};

void strcpy (char *vet1, char *vet2){
	int i;
	for (i = 0; vet1[i] != '\0'; i++){
		vet2[i] = vet1[i];
	}
	vet2[i] = '\0';
}

NODO * acess (LED list, int k){
	NODO *i;
	for (i = list; k-- - 1; i = i->next);
	return (i);
}

void print_data (LED *list, int k){
	NODO * aux;
	if (k < 1 || k > tam(*list)){
		if (*list == NULL){
			printf ("The list is empty\n");
			return; }
		printf ("Invalid position\n");
		return;
	}
	aux = acess (*list, k);
	printf ("Name: %s\n", aux->data.name);
	printf ("Age: %d   || ", aux->data.age);
	printf ("Gender: %c || ", aux->data.gender);
	printf ("Height: %.3f\n", aux->data.height);
}

void print_full_list (LED *list){
	NODO *i;
	if (*list == NULL){
		printf ("The list is empty\n");
		return;
	}
	printf ("The actual full list is bellow: \n\n");
	for (i = *list; i != NULL; i = i->next){
		printf ("Name: %s\n", i->data.name);
		printf ("Age: %d   || ", i->data.age);
		printf ("Gender: %c || ", i->data.gender);
		printf ("Height: %.3f\n\n", i->data.height);
	}	
}

void insert (LED *list, char * nome, int idade, char genero, float altura){
	NODO *i, *aux, *aux2;
	int flag;
	
	if (*list == NULL) flag = 1;
	else flag = alphabetic(nome, (*list)->data.name);

	if (flag == 1){
		aux = *list;
		*list = (NODO *) malloc(sizeof(NODO));
		if (!list){
			printf ("An erro had ocurred while alocating space, please try again...\n");
			return;
		}
		strcpy (nome, (*list)->data.name);
		(*list)->data.age = idade;
		(*list)->data.gender = genero;
		(*list)->data.height = altura;
		(*list)->next = aux;
	}

	else{
		for (i = *list; 1 == 1; i = i->next){
			if (i->next == NULL) break;
			if (alphabetic(nome, i->next->data.name) == 1) break;
		}
		aux = (NODO *) malloc (sizeof(NODO));
		strcpy (nome, aux->data.name);
		aux->data.age = idade;
		aux->data.gender = genero;
		aux->data.height = altura;
		
		aux2 = i->next;
		i->next = aux;
		aux->next = aux2;
	}
}

void remove (LED *list, int k){
	NODO *aux, *aux2;
	int i;
	
	if (k < 1 || k > tam(*list)){
		printf ("You're trying to remove something that doesn't exist!\n");
		return;
	}

	if (k == 1){
		aux = *list;
		*list = (*list)->next;
		free (aux);	
	}
	else{
		aux = acess (*list, k - 1);
		aux2 = aux->next;
		aux->next = (aux->next)->next;
		free (aux2);
	}
}
