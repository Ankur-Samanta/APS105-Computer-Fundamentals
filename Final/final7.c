#include <stdio.h>
#include <stdbool.h>
#include <string.h>
 
// here are the definitions of the node and of the linked list
typedef struct node {
    char  *APCode;
    int priority;
    struct node *next;
} Node;
 
typedef struct linkedList {
    Node *head;
} LinkedList;
 
// use these prototypes to generate your code. Please do NOT change them
struct apnode *createAirportNode( char *APC ) { //create an airport node with an input of character APC (airport code) derived from pointer
    Node *prioritizedNode = (Node *) malloc(sizeof(Node)); // dynamically allocate the node with the prioritized airport correspondances
	int priorityVal = 999; //default val is 999 for all other destinations
    switch (*APC) { //use switch to check for airport code priorities (3 special cases)
        case 'Y': priorityVal = 100; //APC starting with Y get priority val of 100
        case 'F': priorityVal = 200; //APC starting with F get priority val of 200
        case 'S': priorityVal = 300; //APC starting with S get priority val of 300
    }
	prioritizedNode -> priority = priorityVal; //the priority integer is assigned the priorityVal
	prioritizedNode -> APCode = APC; //the airport code is assigned to APCode
	prioritizedNode -> next = NULL; // initialize the next to null; basically saying we don't know where it points so now its a null (tail)
bool insertIntoPriorityList(LinkedList *priorityList, char *APC) { //This is adapted from Prof Anderson's course notes on insertion into ordered lists
    //if the list is empty, inserting at front or back is the same
    if (isEmpty(priorityList) == true) {return insertAtFront(priorityList, *APC);}
    //if the APC, value to insert, comes before the current head (APCode), just insert at the front
    if (*APC < priorityList -> head -> APCode) {return insertAtFront(priorityList, *APC);}
    Node *current = priorityList > head; // should be priorityList -> head; setting the current to the head
    //while the value to insert is larger than the next element in the list, just move to the next element in the list
    while (current -> next != NULL && *APC > current -> next -> APCode) {current = current -> next;}
    Node *newNode = createNode(*APC);
    if (newNode == NULL) {return false;} //could not allocate memory for a new node
    //current may be the last element in the list
    //current may also be the last element in priorityLIst that is less in value
    newNode -> next = current -> next; //link the rest of this list with this new node
    current -> next = newNode; //overwrite next with this new node
    return true;
}