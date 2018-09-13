#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define num_prime 257

typedef struct element
{
	void *item;
	void *freq;
	struct Node *next;
	struct Node *previous;
}Node;

typedef struct node_next
{
	struct Node_next *next;
}Node_next;

typedef struct hash_table
{
	Node *table[10000];
}Hash_Table;

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

Node *newNode(void *x)
{
    Node *node = (Node*) malloc(sizeof(Node));
    node->item = x;
    node->freq = 0;
    node->next = NULL;
    node->previous = NULL;
    return node;
}

Node_next *new_index()
{
	Node_next *node = (Node_next*) malloc(sizeof(Node_next));
	node->next = NULL;
	return node;
}

Hash_Table *create_hash_table()
{
	int i;
	Hash_Table *new_ht = (Hash_Table*) malloc(sizeof(Hash_Table));
	for(i = 0; i < 10000; i++)
	{
		new_ht->table[i] = new_index();
	}
	return new_ht;
}

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

Node *add_element(Node *inicio, void *item, void *freq)
{
	Node *node = newNode(item);
	if(inicio->next == NULL)														
	{
		node->item = item;
		node->freq = freq;
		node->next = NULL;
		node->previous = inicio;
		inicio->next = node;
		return inicio;
	}
}

void put(Hash_Table *ht, void *item, void *freq)
{
	int index;
	int item_aux = item;
	index = item_aux % num_prime;
	ht->table[index] = add_element(ht->table[index], item, freq);
}

void print_hash(Hash_Table *ht)
{
	int i;
	Node *aux;
	for(i = 0; i < num_prime; i++)
	{
		aux = ht->table[i];
		if(aux->next == NULL)
		{
			printf("%d -> VAZIO\n", i);
		}
		else
		{
			aux = aux->next;
			printf("%d -> ", i);
	    	while(aux != NULL)
	    	{
		        printf("%d -> ", aux->freq);
		        aux = aux->next;
	  	  	}
	  	  	printf("VAZIO\n");
	  	}
	}
    printf("\n");	
}

void print_queue(Queue *queue)
{
	if(queue == NULL || queue->size == 0) return;
	Element_queue *element = queue->front;
	while(element != NULL)
	{
		printf("%d ", element->item);
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
	Hash_Table *ht = create_hash_table();
	Queue *queue = createQueue();
	while (fscanf(f, "%c",&s) != EOF)
	{
		freq[s]++;
	}
	for(int i = 0; i < 256; i++) 
	{
		//printf("%d %c %d", i, i, freq[i]);
		//printf("\n");
		//put(ht, i, freq[i]);
		enqueue(queue, i, freq[i]);
	}
	//print_hash(ht);
	print_queue(queue);
	fclose(f);
	return 0;	
}