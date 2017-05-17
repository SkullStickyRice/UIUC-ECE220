/* 
   Write a program in C which prints all the prime numbers from 1 to n.
   At the beginning of the program, print a message that says 
   “Enter the value of n:  ”, so that the user can pick the length. 
   You have to implement and use a function int is_prime(int n) for this 
   program. The function must return 1 if n is a prime, or 0 otherwise 
*/

#include <stdio.h>
#include <math.h>

/* declare is_prime function here, before main() */
int is_prime(int n);

int main()
{  /* use is_prime in your main function */
	int n,i,x;
	printf("Enter the value of n:");
	scanf("%d", &n);
	printf("Printing primes less than or equal to %d:\n", n);
 	printf("2");

	for (x=3; x<=n; x++)
	{
		i = is_prime(x);
		if (i==1)
			printf (", %d",x);
	}
	printf(".\n");

    return 0;
}


/* provide implementation of is_prime here, below main() */
int is_prime(int n)
{

	int i;
	int a;
	for (i=2; i<n; i++)
	{	a = n%i;	
		if (a == 0)
			return 0;
	}
			return 1;
	
}
