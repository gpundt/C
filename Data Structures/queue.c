#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//this will be the objects that make up our queue
//they hold information about their data and the next value in the queue
struct node {
	int data;
	struct node* next;
};

//queues hold their size, the node at the front, and the node at the back
struct queue {
	int size;
	struct node* front;
	struct node* back;
};

//this initializes the queue, allowing us to set its base values
struct  queue* initialize_queue() {
	
	struct queue* queue = (struct queue*)malloc(sizeof(struct queue));
	queue->size = 0;
	queue->front = NULL;
	queue->back = NULL;
	return queue;
}

//enqueue places a node at the back of the queue
void enqueue(struct queue* queue, int value) {
	printf("Enqueueing %d\n", value);
	struct node* newnode = (struct node*)malloc(sizeof(struct node));
	newnode->data = value;
	newnode->next = NULL;

	if (queue->front == NULL && queue->back == NULL) {
		queue->front = newnode;
		queue->back = newnode;
		queue->size++;
	}
	else{
		struct node* current = queue->back;
		current->next = newnode;
		queue->back = newnode;
		
		queue->size++;
	}
}

//dequeue removes the front node
void dequeue(struct queue* queue) {
	struct node* front_node = queue->front;
	printf("Dequeuing %d\n", front_node->data);
	if (front_node->next == NULL) {
		queue->front = NULL;
		queue->back = NULL;
		queue->size--;
	}
	else {
		queue->front = front_node->next;
		queue->size--;

	}
}

//this prints the entire queue from front to back
void print_queue(struct queue* queue) {
	if (queue->front == NULL) {
		printf("Queue is empty\n");
	}
	else {
		struct node* current = queue->front;
		while (current!= NULL) {
			printf("%d ", current->data);
			current = current->next;
		}
		printf("\n");
	}
}


int main(void) {
	struct queue* queue = initialize_queue();

	print_queue(queue);
	enqueue(queue, 10);
	print_queue(queue);
	enqueue(queue, 20);
	print_queue(queue);
	enqueue(queue, 30);
	print_queue(queue);
	dequeue(queue);
	print_queue(queue);
	enqueue(queue, 40);
	print_queue(queue);
	dequeue(queue);
	print_queue(queue);
	dequeue(queue);
	print_queue(queue);
	enqueue(queue, 50);
	print_queue(queue);
}
