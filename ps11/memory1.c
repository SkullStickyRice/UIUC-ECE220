#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
int main()
{
    char *p = (char*)malloc(sizeof(char)*11);
    // Assign some value to p
    strcpy(p,"hello");
 
    char *name = (char*)malloc(sizeof(char)*3);
    // Assign some value to name
    strcpy(name,"Bye");
 
    memcpy (p,name,sizeof(char)*3); // Problem begins here
    printf("%s\n",p);
    return 0;
}


