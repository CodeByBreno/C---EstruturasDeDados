#include <stdio.h>

main (){
	int p, f, i, n;
	while (1){
		p = 0;
		f = 0;
		i = 1;
		scanf ("%d", &n);
		if (!n) break;
		while (1){
			n--;
			p++;
			if (n < 0){ p += n; break; }
			n -= i;
			f += i++;
			if (n <= 0) {
				p += n;
				break; }
		}
		printf ("%d %d\n", f, p);
	}
}
