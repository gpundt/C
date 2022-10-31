#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//These will be our nodes that hold values
struct node {
	int data;
	struct node* next;
};

//our stack holds data for its size, and a pointer to its top node
struct stack {
	int size;
	struct node* top;
	
};

//add function creates new node and adds it to the top
void push(struct stack* stack, int value)
{
	printf("Pushing %d\n", value);
	struct node* newnode = (struct node*)malloc(sizeof(struct node));
	newnode->data = value;
	newnode->next = stack->top;
	stack->top = newnode;
	stack->size++;
}

struct stack* initialize_stack()
{
	struct stack* stack = (struct syack*)malloc(sizeof(struct stack));
	stack->size = 0;
	stack->top = NULL;
	return stack;
}

void pop(struct stack* stack)
{
	struct node* removing = stack->top;
	printf("Popping %d\n", removing->data);
	stack->top = removing->next;
	stack->size--;
}

void print_stack(struct stack* stack) {
	if (stack->top == NULL) {
		printf("Stack is empty\n");
	
	}
	else {
		struct node* current = stack->top;
		while (current) {
			printf("%d ", current->data);
			current = current->next;
		}
		printf("\n");
	}
	
}

/*
int main(void) {
	struct stack* stack = initialize_stack();
	
	push(stack, 10);
	print_stack(stack);
	push(stack, 20);
	print_stack(stack);
	push(stack, 30);
	print_stack(stack);
	pop(stack);
	print_stack(stack);
	push(stack, 40);
	print_stack(stack);
	pop(stack);
	print_stack(stack);
	pop(stack);
	print_stack(stack);
	push(stack, 50);
	print_stack(stack);
}
*/

