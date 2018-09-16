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

typedef struct heap {
	int size;
	Element_queue *data[257];
}heap;

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

heap* create_heap()
{
	heap *new_heap = (heap*) malloc(sizeof(heap));
	new_heap->size = 0;
	return new_heap;
}

void swap(int *x, int *y){ 
   int temp;
   temp=*x;
   *x=*y;
   *y=temp;
}

int get_parent_index(heap *heap, int i)
{
	return i/2;
}

int get_left_index(heap *heap, int i)
{
	return 2*i;
}

int get_right_index(heap *heap, int i)
{
	return 2*i + 1;
}

int item_of(heap *heap, int i)
{
	return heap->data[i];
}

void max_heapify(heap *heap, int i)
{
	int largest;
	int left_index = get_left_index(heap, i);
	int right_index = get_right_index(heap, i);
	if (left_index <= heap->size && heap->data[left_index]->freq > heap->data[i]->freq) 
	{
		largest = left_index;
	} 
	else 
	{
		largest = i;
	}
	if (right_index <= heap->size && heap->data[right_index]->freq > heap->data[largest]->freq) 
	{
		largest = right_index;
	}
	if (heap->data[i]->freq != heap->data[largest]->freq) 
	{
		swap(&heap->data[i], &heap->data[largest]);
		max_heapify(heap, largest);
	}
}

void enqueue(heap *heap, void *item, void *freq)
{
	if (heap->size >= 257) 
	{
		printf("Heap overflow");
	} 
	else 
	{
		heap->data[++heap->size] = new_element_queue(item, freq);
		int key_index = heap->size;
		int parent_index = get_parent_index(heap, heap->size);
		while (parent_index >= 1 && heap->data[key_index]->freq > heap->data[parent_index]->freq) 
		{
			swap(&heap->data[key_index], &heap->data[parent_index]);
			key_index = parent_index;
			parent_index = get_parent_index(heap, key_index);
		}
	}
}

int dequeue(heap *heap)
{
	if (heap == NULL || heap->size == 0) 
	{
		printf("Heap underflow");
		return -1;
	} 
	else 
	{
		int item = heap->data[1]->item;
		heap->data[1] = heap->data[heap->size];
		heap->size--;
		max_heapify(heap, 1);
		return item;
	}
}

void heapsort(heap *heap)
{
	int i;
	for (i = heap->size; i >= 2; i--) 
	{
		swap(&heap->data[1], &heap->data[i]);
		heap->size--;
		max_heapify(heap, 1);
	}
}

void print_heap(heap *heap)
{
	int i;
	for(i = 1; i <= heap->size; i++)
	{
		printf("%x -> %d\n", heap->data[i]->item, heap->data[i]->freq);
	}
	puts("");
}

int main ()
{
	int freq[256] = {};
	int i;
	unsigned char s;
	FILE *f = fopen("japao.png", "r");
	FILE *p = fopen ("out.txt","a");
	heap *heap = create_heap();
	while (fscanf(f, "%c",&s) != EOF)
	{
		freq[s]++;
	}
	for(i = 0; i < 256; i++) 
	{
		enqueue(heap, i, freq[i]);
	}
	heapsort(heap);
	heap->size = 256;
	//dequeue(heap);
	print_heap(heap);
	fclose(f);
	return 0;	
}