#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Do not modify anything. Write your code under the two if statements indicated below.
int main(int argc, char **argv)
{
	double omega1, omega2, omegac, T, dt;
	int N, method;
	FILE *in;

	// Open the file and scan the input variables.
	if (argv[1] == NULL) {
		printf("You need an input file.\n");
		return -1;
	}
	in = fopen(argv[1], "r");
	if (in == NULL)
		return -1;
	fscanf(in, "%lf", &omega1);
	fscanf(in, "%lf", &omega2);
	fscanf(in, "%lf", &omegac);
	fscanf(in, "%d", &method);

	T = 3 * 2 * M_PI / omega1; 		// Total time
	N = 20 * T / (2 * M_PI / omega2); 	// Total number of time steps
	dt = T / N;				// Time step ("delta t")

	// Method number 1 corresponds to the finite difference method.
	if (method == 1) 
		{
		int a;
		double Voutnext;
		double Voutcurrent;
		double Voutprevious;
		double i,j;

		Voutnext = 0;	/* initialize Voutnext*/
		Voutcurrent = 0; /* initialize Voutcerrent*/
		Voutprevious = 0; /* initialize Voutprevious*/

		i = 1 / (sqrt(2)* dt * omegac); /*do the calculation, will use in the formula*/
		j = 1/(pow(dt,2) * pow(omegac,2)); /*do the calculation, will use in the formula*/
		for (a=0;a<=N;a++) /*a<=N, print alll Voutcurrent*/	
		{	
		printf("%lf\n", Voutcurrent);
		Voutnext = (1 / (i + j)) * ((2*j -1) * Voutcurrent + (i - j) * Voutprevious + sin(omega1 * a * dt) + 0.5 * sin(omega2 * a * dt)); /* calculates the formula */
		Voutprevious = Voutcurrent; /* new Vout value*/
		Voutcurrent = Voutnext; /* new Vout value*/
		}	

		// Write your code here!
		
	}

	// Method number 2 corresponds to the Runge-Kutta method (only for challenge).
	else if (method == 2) {
		// Write your code here for the challenge problem.
		int a;
		double Vout1next;
		double Vout1current;
		double Vout2next;
		double Vout2current;
		double k1,k2,k3,k4;
		double m1,m2,m3,m4;

		Vout1next = 0;	/* initialize Vout1next*/
		Vout1current = 0; /* initialize Vout1cerrent*/
		Vout2next = 0; /* initialize Vout2net*/
		Vout2current = 0;/* initialize Vout2current*/

		for (a=0;a <=N; a++) /* a <= N, print all the vout1current */
		{ 
			printf("%lf\n", Vout1current);
			k1 = Vout2current; /* formula of k1*/
			k2 = Vout2current + (k1 * dt)/2; /* formula of k2*/
			k3 = Vout2current + (k2 * dt)/2; /* formula of k3*/
			k4 = Vout2current + k3 * dt; /* formula of k4*/
			m1 = pow(omegac,2) * (sin(omega1 * a * dt)+ 0.5*sin(omega2 *a *dt))-pow(omegac,2)* Vout1current - omegac * sqrt(2)* Vout2current; /* formula of m1*/
			m2 = m1*(1 + dt /2); /* formula of m2*/
			m3 = m1 + (m2 * dt)/2; /* formula of km3*/
			m4 = m1 + m3 * dt; /* formula of m4*/
			Vout1next = Vout1current + (dt /6) * (k1 + 2 * k2 + 2 * k3 + k4); /* Runge-Kutta method*/
			Vout2next = Vout2current + (dt /6)* (m1 + 2 * m2 + 2 * m3 + m4); /* Runge-Kutta method*/
			Vout1current = Vout1next; /* new value for vout1current*/
			Vout2current = Vout2next; /* new value for vout2current*/
		}
	}

	else {
		// Print error message.
		printf("Incorrect method number.\n");
		return -1;
	}

	fclose(in);
	return 0;
}
