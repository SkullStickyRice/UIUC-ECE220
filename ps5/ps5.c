/* compute a function */

#include <stdio.h>
#include <math.h>

int main()
{
    /* write your code here */ 
	int i,n;
	float omega1,omega2,x,f;

	const float pi=3.1415926;
	
	printf("enter n:");
	scanf("%d", &n);

	printf("enter omega1,omega2:");
	scanf("%f %f", &omega1,  &omega2);
	i = n;

		for (i = 0; i <= n-1; i++)
		{
			x = i*pi/(n-1);
			f = sin(omega1 * x) + 0.5 * sin(omega2 * x);
			printf ("(x=%f,f(x)=%f)\n", x, f);
		}
    return 0;
}

