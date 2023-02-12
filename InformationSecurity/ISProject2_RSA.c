#include <stdio.h>

typedef unsigned long long int ULLI;

/*ULLI gcd(ULLI a, ULLI b)
{
	if (b == 0)
		return a;
	ULLI r = a % b;
	return gcd(b, r);
}*/

ULLI find_pq(ULLI n, ULLI* p, ULLI* q)
{
	for (ULLI i = 2; i < n; ++i)
	{
		if (n % i == 0)
		{
			*p = i;
			*q = n / (*p);
			return 1;
		}
	}
	return 0;
}

int isPrime(ULLI n)
{
	ULLI i;
	for (i = 2; i < n; ++i)
	{
		if (n%i == 0)
			return i;
	}
	return 1;
}

int main(void){
	ULLI e = 13;
	ULLI C = 1220703125;
	ULLI n = 9943237852845877651u;
	

	ULLI p, q;
	find_pq(n, &p, &q);
	//p = 2701212721;
	//q = 3681027331;
	printf("p: %llu\tq: %llu\n", p, q);
	
	return 0;
}