#include <stdio.h>
#include <stdlib.h>

long int * soma_racional (int a, int b, int c, int d){
	long int ptr[2];
	*ptr = (a*d + c*b);
	*(ptr + 1) = b*d;
	return ptr;
}

long int * produto_racional (int a, int b, int c, int d){
	long int ptr[2];
	*ptr = a*c;
	*(ptr + 1) = b*d;
	return ptr;
}

long int * divisa_racional (int a, int b, int c, int d){
	long int ptr[2];
	*ptr = a*d;
	*(ptr + 1) = b*c;
	return ptr;
}

long int * rotina_euclides (int a, int b){
	int M, m, r, q;
	long int ptr[2];
	if (!a){
		ptr[0] = 0;
		ptr[1] = 1;
		return ptr;
	}
	if (a > b){
		M = a;
		m = b;
	}	
	else{
		M = b;
		m = a;
	}

	while (1){
		q = M / m;
	 	r = M % m;
		if (!r) break;
		M = m;
		m = r;
	}
	if (m < 0) m *= -1;
	a /= m;
	b /= m;
	ptr[0] = a;
	ptr[1] = b;
	return ptr;
}

main (){
	int n, z, N1[2], N2[2];
	long int *resposta, a, b;
	resposta = ( long int * ) calloc (2, sizeof(long int)); 
	char select;
	scanf ("%d", &n);
	for (z = 0; z < n; z++){
		scanf ("%d / %d %c %d / %d", N1, N1 + 1, &select, N2, N2 + 1);
		switch (select){
			printf ("%c", select);
			case ('+'): resposta = soma_racional (*N1, *(N1 + 1), *N2, *(N2 + 1));
			break;
			case ('-'): resposta = soma_racional (*N1, *(N1 + 1), -*N2, *(N2 + 1));
			break;
			case ('*'): resposta = produto_racional (*N1, *(N1 + 1), *N2, *(N2 + 1));
			break;
			case ('/'): resposta = divisa_racional (*N1, *(N1 + 1), *N2, *(N2 + 1));
			break;
		}
		a = *resposta;
		b = *(resposta + 1);
		printf ("%ld/%ld = ", a, b);
		resposta = rotina_euclides (a, b);
		printf ("%ld/%ld\n", *resposta, *(resposta + 1));
	}
}
