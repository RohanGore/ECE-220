#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	int data;
     	struct node_t *next;
} node;

void printList(node * Node) {
	int j = 1;
        printf("data = ");
	while( Node != NULL){
		printf(" %d", Node->data);
		Node = Node->next;
		j++;
	}
        printf("\n");
}

/*Implement this function for Lab 10*/
void reverse(node** head){
	node * previous = NULL;	// Make node to hold data in the previous node
	node * current = *head;	// Make node to hold data in the current node
	node * next = NULL;	// Make node to hold data in the next node

	while(current != NULL)	// Traverse the linked list
	{
		next = current->next;	// Make next point to the next node
		current->next = previous;	// Make the next node pointed to by current point to the previous node
		previous = current;	// Set previous to current
		current = next;		// Set current to the next node;
	}
	*head = previous;	// Set the head to the last node

}

/*Implement this function for Lab 10*/
void removeDuplicates(node* head){
	node * current = head;	// Make node to hold data in current node
	node * temp;	// Make temporary node
	
	while(current->next != NULL)	// Traverse the linked list
	{
		if(current->data == current->next->data)	// Check if duplicate
		{	
			temp = current->next;	// Make temp point to the next node
			current->next = current->next->next;	// Make pointer to next node point to next next node
			free(temp);	// Deallocate memory held by duplicate node
		}
		else
			current = current->next;	// Set current to the next node if no duplicate was found
	}
}

int main() {
    node * head = NULL;
    node * temp;
    int i = 0;
    int j = 0;
    //Create Sorted linked list with repeats
    for(i = 9; i > 0; i--) {
        if(i%3==0){
            for(j = 0; j < 3; j++){
                temp = head;
	        head = (node *) malloc(sizeof(node));
	        head->data = i;
	        head->next = temp;     
            }
        }else{
            temp = head;
            head = (node *) malloc(sizeof(node));
            head->data = i;
            head->next = temp;
        }
    }
    printf("Printing the original list:\n");
    printList(head);
    removeDuplicates(head);
    printf("Printing the removeDuplicates list:\n");
    printList(head);
    reverse(&head);
    printf("Printing the reverse list:\n");
    printList(head);
    //free list
    while(head!=NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}
