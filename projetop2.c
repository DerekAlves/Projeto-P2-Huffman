#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define num_prime 257

typedef struct node_next
{
	struct Node_next *next;
}Node_next;

typedef struct node_down
{
	struct Node_down *down;
}Node_down;

typedef struct element_queue
{
	void *item;
	void *freq;
	Node_next *next;
	Node_down *down_left;
	Node_down *down_right
}Element_queue;

typedef struct Queue
{
  Element_queue *front;
  Element_queue *back;
  int size;
}Queue;

Queue *createQueue(){
  Queue *queue = (Queue*)malloc(sizeof(Queue));
  queue->front = queue->back = NULL;
  queue->size = 0;
  return queue;
}

Element_queue *new_element_queue(void *item, void *freq)
{
	Element_queue *node_queue = (Element_queue*) malloc(sizeof(Element_queue));
	node_queue->item = item;
	node_queue->freq = freq;
	node_queue->next = NULL;
	node_queue->down_left = NULL;
	node_queue->down_right = NULL;
	return node_queue;
}

void enqueue(Queue *queue, void *item, void *freq)
{
  Element_queue *node_queue = new_element_queue(item, freq);
  if(queue->size == 0 || freq < queue->front->freq)
  {
  	node_queue->next = queue->front;
    queue->front = node_queue;
  } 
  else 
  {
  	Element_queue *current = queue->front;
  	Element_queue *aux = current->next;
  	while ((aux != NULL) && (aux->freq < freq))
	{
		current = current->next;
		aux = current->next;
	}
    node_queue->next = aux;
	current->next = node_queue;
  }
  queue->size++;
}

Element_queue *dequeue(Queue *queue){
  if(queue->size == 0){
    printf("Fila Vazia\n");
  }
  else
  {
  	Element_queue *node_queue = queue->front;
	queue->front = queue->front->next;
	node_queue->next = NULL;
	queue->size--;
	return node_queue;
  }
}

void print_queue(Queue *queue)
{
	if(queue == NULL || queue->size == 0) return;
	Element_queue *element = queue->front;
	while(element != NULL)
	{
		printf("%x ", element->item);
		printf("%d\n", element->freq);
		element = element->next;
	}
	puts("");
}

int main ()
{
	int freq[256] = {};
	unsigned char s;
	FILE *f = fopen("japao.png", "r");
	FILE *p = fopen ("out.txt","a");
	Queue *queue = createQueue();
	while (fscanf(f, "%c",&s) != EOF)
	{
		freq[s]++;
	}
	for(int i = 0; i < 256; i++) 
	{
		enqueue(queue, i, freq[i]);
	}
	//print_hash(ht);
	print_queue(queue);
	fclose(f);
	return 0;	
}