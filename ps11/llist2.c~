#include <stdio.h>
#include <stdlib.h>


typedef struct node_t
{
    int data;
    struct node_t *next;
} node;

//void reverse(node** head);
void insert(node** head, node *newNode,int N);
void removing(node **head,int N);

// Fucnction to append nodes to the Linked list.
void append(node **head,int data)
{   
		
    node *temp,*n;

    temp = (node *)malloc(sizeof(node));
    temp->data=data;
    temp->next=NULL;

    n = *head;

    if(*head==NULL)
    {   
        *head=temp;
    }
    else
    {  
        while(n->next !=NULL)
	{  
	    n=n->next;
	}
	
	n->next=temp;
    }
}


void printList(node *head)
{
    node *n = head;
 
    while(n != NULL)
    {
	printf("%d ",n->data);
	n = n->next;
    }
    printf("\n");
}


int main()
{
    node* head = NULL;

    append(&head,20);
    append(&head,10);
    append(&head,90);
    append(&head,100);
    append(&head,80);
    append(&head,0);
    append(&head,4);
    append(&head,60);
    append(&head,05);

    printf("Before:\n");
    printList(head);

    //call your function here
    //reverse(&head);

    node *newNode = (node *)malloc(sizeof(node));
    newNode->data = 9;
    newNode->next = NULL;

	insert(&head, newNode,3);
	//removing(&head,3);

    printf("After:\n");
    printList(head);

    //free linked list here
    node* remove;
    while(head!=NULL){
	remove=head->next;
	free(head);
	head=remove;
    }
    return 0;
}

/*void reverse(node** head)
{
    //add your code here
    node* temp=*head;
    node* check=temp->next;
    node* a;
    if((*head)->next==NULL){
	return;
    }
    reverse(&check);
    a=temp->next;
    a->next=temp;
    temp->next=NULL;
    *head=check;

}
*/

void insert(node **head, node *newNode, int N)
{
	node *temp=(node*)malloc(sizeof(node));
	temp = *head;
	//node *ptr=(node*)malloc(sizeof(node));

	int i;
	int count=0;
	if (temp == NULL)
	{
		(*head)=newNode;
		(*head)->next=newNode->next;
	}
	else{
		while(temp->next!=NULL)
		{
			count++;
			temp=temp->next;
		}
		count++;
		printf("count=%d\n",count);
		if(N>count)
		{
'			temp->next=newNode;
		}
		else 
		{
			for (i=0;i<N-1;i++)
			{
				temp=temp->next;
			}
		}
		//ptr = temp->next;
		newNode->next = temp->next;
		temp->next = newNode;
		//newNode->next = ptr;
	}
	
}


void removing(node **head,int N)
{
	node *temp = (node*)malloc(sizeof(node));
	temp = *head;
	node *ptr = (node*)malloc(sizeof(node));
	int i;
	int count=0;

	if (temp == NULL)
		{
			return NULL;
		}
	if (N == 0)
	{
		*head=(*head)->next;
	}
	while(temp!=NULL)
	{
		count++;
		temp=temp->next;
	}
	printf("count=%d\n",count);
	if (N>=count)
	{
		return NULL;
	}
	else
	{
		temp=*head;
		for (i=0;i<N-1;i++)
		{
			temp = temp->next;	
		}
		ptr = temp->next;
		temp->next = ptr->next;
	}
}
	
