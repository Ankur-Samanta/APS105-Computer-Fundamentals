#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
//#include "contactList.h"

// IF IT'S EASIER, YOU NEED NOT BE OVERLY GENERAL/FLEXIBLE
// BUT CAN ASSUME THESE LIMITS
#define MAXCONTACTS 30 /* max # of contacts */
#define MAXPHONES 10 /* max # of phone numbers for each contact */
#define PHONE_NUMBER_MAX_LENGTH 12

//Note: structs below defined in a recursive manner
typedef struct phoneNumber {char *number; struct phoneNumber *nextContact;} PhoneNumber; 
typedef struct contact {char *name; struct phoneNumber *head; struct contact *nextContact;} Contact;
typedef struct phoneBook {struct contact *head;} PhoneBook;

//function that creates new contact
Contact *createNewContact(char* name) {
    Contact *newContact = (Contact*)malloc(sizeof(Contact));
    newContact->name = name;
    newContact->nextContact = NULL;
    newContact->head = NULL;
    return newContact;
}

//function that creates new phone number
PhoneNumber *createNewPhoneNumber(char* number) {
    PhoneNumber *newPhoneNumber = (PhoneNumber*)malloc(sizeof(PhoneNumber));
    newPhoneNumber->number = number;
    newPhoneNumber->nextContact = NULL;
    return newPhoneNumber;
}

//function that inserts contact into phonebook in alphabetical order
int insertNewContact(PhoneBook *phonebook, Contact *newContact) {
    //insert contact at front if phonebook is empty or if newContact's name is alphabetically before the head contact's name
    if (phonebook->head == NULL || strcmp(phonebook->head->name, newContact->name) > 0) { //strcmp compares the two strings; >0 means str1 is > str2
        newContact->nextContact = phonebook->head;
        phonebook->head = newContact;
        return 0;
    }

    //now, make the currentContact the head; then, loop and move on to the next element as long as current contact is not the tail, and the next entry is alphabeticaly before the current contact's name
    Contact *currentContact = phonebook->head;
    while (currentContact->nextContact != NULL && strcmp(currentContact->nextContact->name, newContact->name) < 0) {currentContact = currentContact->nextContact;}
    //insert newContact after currentContact
    newContact->nextContact = currentContact->nextContact;
    currentContact->nextContact = newContact;
    return 0;
}

//function that compares the phone numbers of two contacts
bool comparePhoneNumbers(Contact *firstContact, Contact *secondContact) {
    ///set currentContact number pointer to head, and then compare to currentContact
    PhoneNumber *currentContact = firstContact->head; 
    PhoneNumber *comparisonContact;

    //looping through until the end of the numbers for currentContact
    while(currentContact != NULL) {
        comparisonContact = secondContact->head; //set comparisonContact to head of contact 2
        //loop through numbers and compare
        while (comparisonContact != NULL) {
            //if comparisonContact and currentContact are same, return true
            if (strcmp(currentContact->number, comparisonContact->number) == 0) {return true;}
            comparisonContact = comparisonContact->nextContact;
        }
        currentContact = currentContact->nextContact;
    }
    return false;
}

//outputs the phone numbers for a given contact
void outputPhoneNumbers(Contact *contact) {
    printf("Phone(s):");
    //currentContact pointer made equal to head
    PhoneNumber *currentContact = contact->head;

    //iterates through and prints phone number list
    while (currentContact != NULL) {printf(" %s", currentContact->number); currentContact = currentContact->nextContact;}
    printf("\n"); return;
}

//lists all contacts in alphabetical order
void ListAllContacts(PhoneBook *phonebook) {
    //make current contact head, and then loop through phonebook while outputting name and numbers of contact, and then moves on to the next one
    Contact *currentContact = phonebook->head;
    while (currentContact != NULL) {
        printf("Name: %s\n", currentContact->name);
        outputPhoneNumbers(currentContact);
        currentContact = currentContact->nextContact;
    }
}

/*
 * convertInputToDataStructure
 * Takes the information in contactList.h and puts it into a data
 * structure of your choosing, however: 1 mark of the lab will be
 * for using structs with pointers in your solution.
 * You might also want to consider the outputs from the program
 * (see the menu printed in printMenu) since some structures will
 * make this easier than others.
 */
void convertInputToDataStructure(PhoneBook *phonebook) {
    phonebook->head = NULL; Contact *newContact; PhoneNumber *newPhoneNumber;
    //loop through contactList
    for (int iterator = 0; iterator < (sizeof(contactList) / sizeof(char*)); iterator++) {
        //if it's an alphabetical entry, then make it a new contact
        if (isalpha(*contactList[iterator])) {newContact = createNewContact(contactList[iterator]);}
        //if it's a numerical entry, then make it a new phone number and put it in the front of the linked list for newContact
        else if (isdigit(*contactList[iterator])) {
            newPhoneNumber = createNewPhoneNumber(contactList[iterator]);
            newPhoneNumber->nextContact = newContact->head;
            newContact->head = newPhoneNumber;
        }
        //if it's the last element, or the next element is alphabetical, then insert the new entry into the phonebook
        if ((iterator == sizeof(contactList) / sizeof(char*) - 1) || (isalpha(*contactList[iterator+1]))) {insertNewContact(phonebook, newContact);}
    }
    return;
}

/*
 * printMenu - Prints out the user menu
 */
void printMenu() {
    printf("\n\nEnter a command by number\n");
    printf("1. List all contacts in alphabetical order\n");
    printf("2. Print phone(s) for a contact\n");
    printf("3. Find duplicate entries\n");
    printf("4. Delete contact\n");
    printf("5. Exit the program\n");
    printf("Your input: ");
}
//eliminate trailing \n
char* rtrim(char* str) {
    int i;
    for (i = strlen(str) - 1; i >= 0 && str[i] == '\n'; i--)
        str[i] = '\0';
    return str;
}

//function that prints a contact after user inputs a name
void PrintContact(PhoneBook *phonebook) {
    char name[100]; //string for name
    printf("Enter name: "); //user input
    fgets(name, 100, stdin);
    name[strlen(name) - 1] = '\0';

    //set a current contact and loop through the phonebook
    Contact *currentContact = phonebook->head;
    while (currentContact != NULL) {
        //if currentContact's name is same as the user inputted name, print name and output associated phone numbers
        if (strcmp(currentContact->name, name) == 0) {
            printf("Name: %s\n", currentContact->name);
            outputPhoneNumbers(currentContact);
            return;
        }
        currentContact = currentContact->nextContact; //next contact
    }
    printf("Contact not found\n"); //if no matches were found
    return;
}

/*
 * DeleteContact deletes a contact from the list
 * The user must enter the name of the contact to delete
 *
 */
void DeleteContact(PhoneBook *phonebook) {
    char name[100]; //string for name
    printf("Enter name: "); //user input
    fgets(name, 100, stdin);
    name[strlen(name) - 1] = '\0';

    //if phonebook is empty, print contact not found
    if (phonebook->head == NULL) {printf("Contact not found"); return;}
    //if the first contact matches with name, then delete first contact
    if (strcmp(phonebook->head->name, name) == 0) {
        Contact *placeHolder = phonebook->head->nextContact;
        free(phonebook->head);
        phonebook->head = placeHolder;
        return;
    }
    //set a current contact and then loop through the phonebook; if next contact's name is same as user input name, then delete the contact
    Contact *currentContact = phonebook->head;
    while (currentContact->nextContact != NULL) {
        if (strcmp(currentContact->nextContact->name, name) == 0) {
            Contact *temp = currentContact->nextContact;
            currentContact->nextContact = temp->nextContact;;
            free(temp);
            return;
        }
        currentContact = currentContact->nextContact;
    }
    //if after looping, no match was found, print message
    printf("Contact not found "); return;
}

/*
 * findDuplicates finds the names of contacts with
 * a phone number in common
 */
void FindDuplicates(PhoneBook *phonebook) {
    //set pointer for currentContact node to head, and then compare to currentContact
    Contact *currentContact = phonebook->head;
    Contact *comparisonContact;
    int comparisonCounter = 1; int numberOfDuplicates = 0;

    //looping through until the end of the phonebook for currentContact
    while(currentContact != NULL) {
        comparisonContact = phonebook->head;
        for (int iterator = 0; iterator < comparisonCounter; iterator++) {comparisonContact = comparisonContact->nextContact;}
        //loop through phonebook to compare entries
        while (comparisonContact != NULL) {
            //compare compare and currentContact if they have a shared number, then print statement and increase counter
            if (comparePhoneNumbers(comparisonContact, currentContact)) {
                printf("%s and %s have a phone number in common\n", currentContact->name, comparisonContact->name);
                numberOfDuplicates++;
            }
            comparisonContact = comparisonContact->nextContact; //move to next entry
        }
        //move to next currentContact and up the count on the comparisonCounter
        currentContact = currentContact->nextContact; comparisonCounter++;
    }
    if (numberOfDuplicates == 0) {printf("No duplicates found");}
}

int main() {
    PhoneBook phonebook;
    //first move data from contactList.h to a data structure
    convertInputToDataStructure(&phonebook);
    char notDone = 1;
    while (notDone) {
        printMenu();
        char userChoice[100];
        char* s = fgets(userChoice, sizeof(userChoice), stdin);
        if (!s){printf("Wrong input\n"); continue;}
        s = rtrim(s); /* eliminate trailing \n */
        //printf("selection = %s\n", s);
        int userSelection = atoi(s);

        switch (userSelection) {
            case 1: ListAllContacts(&phonebook); break;
            case 2: PrintContact(&phonebook); break;
            case 3: FindDuplicates(&phonebook); break;
            case 4: DeleteContact(&phonebook); break;
            case 5: notDone = 0; break;
            default: printf("Bad command...\n"); break;
        }
    }
    return 0;
}