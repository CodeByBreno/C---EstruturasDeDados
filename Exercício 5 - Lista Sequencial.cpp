#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int N;
	int * val;
	int max;
} LISTA;

void create_list (LISTA *, int);
int null_test (LISTA *);
int size_list (LISTA *);
void insert_element (LISTA *, int, int);
int recover_element (LISTA *, int);
void remove_element (LISTA *, int);
int search_element (LISTA *, int);
void order_test (LISTA *);

void create_list (LISTA * I, int max_size){
	I->val = (int *) malloc (sizeof(int)*max_size);
	if (I->val == 0) {
		printf ("\nERROR: Memory cannot be provided\n");
		exit (1);
	}
	I->N = 0;		 
	I->max = max_size;
}

int null_test (LISTA *I){
	return (I->N == 0);
}

int size_list (LISTA *I){
	return (I->N);
}

void insert_element (LISTA *I, int k, int a){
	int i;
	if (k < 1 || k > I->N + 1){
		printf ("\nERROR: Locate out of edge\n");
		exit(2);
	}
	for (i = I->N - 1; i >= k - 1; i--)
		I->val[i + 1] = I->val[i];
	I->val[k-1] = a;
	I->N++;
}

int recover_element (LISTA * I, int k){
	if (k < 1 || k > I->N){
		printf ("\nERROR: Locate out of edge\n");
		exit(3);
	}
	return (I->val[k-1]);
}

void remove_element (LISTA *I, int k){
	int i;
	if (k < 1 || k > I->N){
		printf ("\nERROR: Locate out of edge\n");
		exit(4);
	}
	for (i = k - 1; i < I->N - 1; i++)
		I->val[i] = I->val[i + 1];
	I->N--;
}

int search_element (LISTA *I, int a){
	int i;
	for (i = 0; i < I->N; i++)
		if (I->val[i] == a) return (i+1);
	return (0);
}

void order_test (LISTA *I){
	int i, flag;
	if (!(I->N > 2)){
		printf ("\nHey, there's nothing here yet'\n");
		return;
	}

	//analysing the patter on the first two elements
	if (I->val[1] > I->val[0]) flag = 1;
	if (I->val[1] < I->val[0]) flag = 2;
	if (I->val[1] == I->val[0]) flag = 3;

	//seeing if the patter continues or not
	if (flag == 1){
		for (i = 2; i < I->N; i++)
			if (!(I->val[i] > I->val[i-1])){
				printf ("The list doesn't have a order\n'");
				break; }
		if (i == I->N - 1) printf ("The list is Crescent\n");
	}
	if (flag == 2){
		for (i = 2; i < I->N; i++)
			if (!(I->val[i] < I->val[i-1])){
				printf ("The list doesn't have a order\n'");
				break; }
		if (i == I->N - 1) printf ("The list is Decrescent\n");
	}
	if (flag == 3) {
		for (i = 2; i < I->N; i++)
			if (!(I->val[i] == I->val[i-1])){
				printf ("The list doesn't have a order\n'");
				break; } 
		if (i == I->N - 1) printf ("All elements on the list are Equal");
	}
}

main (){
	LISTA *I;
	int i, a, flag = 1, tester = 1, aux;
	printf ("Insert the maximum list size: ");
	scanf ("%d", &a);
	create_list (I, a);
	while (tester == 1){
		printf ("What you want to do next?\n"
				"Press 1 to: See the list size\n"
				"Press 2 to: Consult the element on some position\n" 
				"Press 3 to: See the enterely list\n"
				"Press 4 to: Insert one element on list\n" 
				"Press 5 to: Insert a group of elements\n"
				"Press 6 to: Remove the element on a certain spot from the list\n"
				"Press 7 to: Search for some element on the list\n"
				"Press 8 to: See if the list is ordered\n\n"	);
		scanf ("%d", &a);
		switch (a){
			case 1:
				printf ("This list contain %d elements\n", size_list(I));
				break;
			case 2:
				printf ("Insert the position: ");
				scanf ("%d", &a);
				printf ("The element %d was founded\n", recover_element(I, a));
				break;
			case 3:
				if (I->N == 0){
					printf ("\nThe list is Empty!\n");
					break;
				}
				printf ("The list is bellow:\n");
				for (i = 1; i <= I->N; i++) printf ("%d ", recover_element(I, i));
				printf ("\n\n");
				break;
			case 4: 
				printf ("Put the position and the element you want to insert: ");
				scanf ("%d%d", &i, &a);
				insert_element (I, i, a);
				break;
			case 6:
				printf ("Insert the spot where the element is: ");
				scanf ("%d", &a);
				remove_element (I, a);
				break;
			case 7:
				printf ("Insert the element you want to be searched\n");
				scanf ("%d", &a);
				flag = search_element(I,a);
				if (flag) printf ("In %d place the element was located\n", flag);
				else printf ("The element dont show up on list\n");
				break;
			case 8:
				order_test(I);
				break;
			case 5:
				printf ("Lets start with the position of the first element: ");
				scanf ("%d", &tester);
				if ((tester < 1 || tester > I->N) && tester != 1) {
					printf ("Invalid Position\n");
					break;
				}
				printf ("How munch elements you want to insert? ");
				scanf ("%d", &a);
				if (a < 0 || a > I->max){
					printf ("Invalid size\n");
					break;
				}
				printf ("Put all the elements you want to insert\n");
				for (i = tester; i < a + tester; i++){
					scanf ("%d", &flag);
					insert_element (I, i, flag);
				}
				if (scanf("%d", &aux)) 
					printf ("\nWARNING: You had inserted more elements than you informed\n"
									"Only the firts will be put on list\n");
				break;
			default:
				printf ("Nice try\n");
				break;
			}
		setbuf (stdin, NULL);
		printf ("\nDo something else?\n(1) = YES\n(2) = NO\n");
		scanf ("%d", &tester);
		system("cls");
	}
}
