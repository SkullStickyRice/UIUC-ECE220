#include <stdio.h>

/* provide swap function prototype here */
void swap (int *px, int *py);

int main()
{
    /* complete main function to demonstrate the sue of swap */
int a;
int b;
a = 5;
b = 10; 
swap (&a,&b);
printf("%d \n %d \n", a, b); 
return 0;

}


void swap (int *px, int *py)
{
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
}

