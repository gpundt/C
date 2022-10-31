/*
 * CSEC-201
 * Authors: CSEC-201 Instructors
 * Semester: 2221
 * Purpose: Demonstrates linked lists in C.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Structure Definitions
/*
 * Name: struct node
 * Purpose: Represents a node in a linked list.
 * 	A node contains an integer (data) and 
 * 	a pointer to the next node in the linked list.
 */
struct node{
    int data;
    struct node* next;
};

/*
 * Name: struct linkedlist
 * Purpose: Represents a linked list.
 * 	A linked list contains an integer (size = number of
 * 	nodes in the linked list) and a pointer to the first
 * 	node (struct node), which is called the "head".
 */
struct linkedlist{
    int size;
    struct node* head;
};

//Function Prototypes
struct linkedlist* initialize();
void add(struct linkedlist* list, int value);
void print_list(struct linkedlist* list);
void delete_all(struct linkedlist* list, int data);
void print_recursive(struct node* current);
void print_oldest_first(struct linkedlist* list);
int delete_at(struct linkedlist* list, int index);
int update_at(struct linkedlist* list, int index, int data);

/*
 * Name: main
 * Purpose: Tests functions above
 * Parameters: Command line options
 * Returns: int
 */
/*
int main(int argc, char* argv[])
{
    //Create a linked list
    struct linkedlist* mylist = initialize();
	
    //Add nodes to linked list
    for(int i = 0; i < 10; i++)
    {
        add(mylist, (i+1)*10);
    }
	
    //Add nodes to linked list
    add(mylist, 50);
    add(mylist, 50);

    //Print linked list
    print_list(mylist);
	
    //Print oldest node in linked list
    print_oldest_first(mylist);
    
    printf("updated at 2? %s\n", update_at(mylist, 2, 300) == 1? "true" : "false");
    print_list(mylist);

    delete_all(mylist, 50);
    printf("delete 50\n");
    print_list(mylist);

    printf("deleted at 0? %s\n", delete_at(mylist, 0) == 1? "true" : "false");
    print_list(mylist);
    printf("deleted at 5? %s\n", delete_at(mylist, 5) == 1? "true" : "false");
    print_list(mylist);
    printf("deleted at 7? %s\n", delete_at(mylist, 7) == 1? "true" : "false");

    print_list(mylist);
    print_oldest_first(mylist);
}
*/

//Function Definitions
/*
 * Name: initialize
 * Purpose: Allocates memory on the heap, and creates an empty
 * 	linked list (0 nodes).
 * Parameters: None
 * Returns: Pointer to a linked list structure (struct linkedlist)
 */
struct linkedlist* initialize()
{
    struct linkedlist* list = (struct linkedlist*)malloc(sizeof(struct linkedlist));
    list->size = 0;
    list->head = NULL;
    return list;
}

/*
 * Name: add
 * Purpose: Adds a node to the linked list at the head.
 * Parameters: pointer to linked list structure, value to add
 * Returns: None
 */
void add(struct linkedlist* list, int value)
{
    struct node* newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = value;
    newnode->next = list->head;
    list->head = newnode;
    list->size++;
}

/*
 * Name: print_list
 * Purpose: Prints the linked list.
 * Parameters: pointer to linked list structure (struct linkedlist)
 * Returns: None
 */
void print_list(struct linkedlist* list)
{
    if(list->head == NULL)
    {
        printf("Empty list\n");
        return;
    }
    struct node* current = list->head;
    while(current)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

/*
 * Name: delete_all
 * Purpose: Deletes node(s) with value specified
 * Parameters: pointer to linked list structure (struct linkedlist)
 *             and value of node(s) to delete
 * Returns: None
 */
void delete_all(struct linkedlist* list, int data)
{
    struct node* current = list->head;
    struct node* previous = NULL;

    while(current)
    {
        if(current->data == data)
        {
            if(previous == NULL)
            {
                list->head = list->head->next;
                previous = NULL;
                free(current);
                current = list->head;
            }
            else
            {
                previous->next = current->next;
                free(current);
                current = previous->next;
            }
            list->size -= 1;
        }
        else
        {
            previous = current;
            current = current->next;
        }
    }
}

/*
 * Name: print_recursive
 * Purpose: Prints nodes using recursion
 * Parameters: pointer to a node in a linked list
 * Returns: None
 */
void print_recursive(struct node* current)
{
    if(current == NULL)
    {
        return;
    }
    print_recursive(current->next);
    printf("%d ", current->data);
}

/*
 * Name: print_oldest_first
 * Purpose: Prints linked list in reverse order
 *          using recursion
 * Parameters: pointer to a linked list
 * Returns: None
 */
void print_oldest_first(struct linkedlist* list)
{
    print_recursive(list->head);
    printf("\n");
}

/*
 * Name: delete_at
 * Purpose: Deletes a node at a specified index
 * Parameters: pointer to a linked list,
 *             index of node to delete
 * Returns: int
 */
int delete_at(struct linkedlist* list, int index)
{
    struct node* current = list->head;
    struct node* previous = NULL;
	
    //Check for invalid index
    if (index < 0 || index >= list->size)
    {
        return 0;
    }
	
    int i = 0;
    while(current != NULL)
    {
        if(i == index){
            if(previous == NULL)
            {
                list->head = current->next; 
            }
            else
            {
                previous->next = current->next;
            }
			
            free(current);
            list->size -= 1;
            
            return 1;
        }
		
        previous = current;
        current = current->next;
        i += 1;
    }
	
    return 0;
}

/*
 * Name: update_at
 * Purpose: Updates a node at a specified index with data
 * Parameters: pointer to a linked list,
 *             index of node to update,
 *             new data value for node
 * Returns: int
 */
int update_at(struct linkedlist* list, int index, int data)
{
    //Check for invalid index
    if(index < 0 || index >= list->size){
        return 0;
    }
	
    int i = 0;
    struct node* current = list->head;
    while(current != NULL){
        if(i == index){
            current->data = data;
        }
        current = current->next;
        i += 1;
    }
    return 1;
}
