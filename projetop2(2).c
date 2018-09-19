#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define num_prime 257

typedef struct element_queue
{
	void *item;
	int freq;
	struct Element_queue *down_left;
	struct Element_queue *down_right;
}Element_queue;

typedef struct heap 
{
	int size;
	Element_queue *data[257];
}heap;

typedef struct arvore
{
	Element_queue *raiz;
 }arvore;

typedef struct nodes_index
{
	void *item;
	int shift_bit;
}Node_index;

typedef struct hash_table
{
	Node_index *table[256];
}Hash_Table;

Element_queue *new_element_queue(void *item, int freq, Element_queue *down_left, Element_queue *down_right)
{
	Element_queue *node_queue = (Element_queue*) malloc(sizeof(Element_queue));
	node_queue->item = item;
	node_queue->freq = freq;
	node_queue->down_left = down_left;
	node_queue->down_right = down_right;
	return node_queue;
}

heap* create_heap()
{
	int i;
	heap *new_heap = (heap*) malloc(sizeof(heap));
	new_heap->size = 0;
	for(i = 1; i < 257; i++) 
		new_heap->data[i] = NULL;
	return new_heap;
}

arvore *create_tree()
{
	arvore *new_tree = (arvore*) malloc(sizeof(arvore));
	new_tree->raiz = new_element_queue(NULL, NULL, NULL, NULL);
	return new_tree;
}

Node_index *new_index()
{
	Node_index *node = (Node_index*) malloc(sizeof(Node_index));
	node->item = NULL;
	node->shift_bit = -1;
	return node;
}

Hash_Table *create_hash_table()
{
	int i;
	Hash_Table *new_ht = (Hash_Table*) malloc(sizeof(Hash_Table));
	for(i = 0; i < 257; i++)
	{
		new_ht->table[i] = new_index();
	}
	return new_ht;
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

void min_heapify(heap *heap, int i)
{
	int largest;
	int left_index = get_left_index(heap, i);
	int right_index = get_right_index(heap, i);
	if (left_index <= heap->size && heap->data[left_index]->freq < heap->data[i]->freq) 
	{
		largest = left_index;
	} 
	else 
	{
		largest = i;
	}
	if (right_index <= heap->size && heap->data[right_index]->freq < heap->data[largest]->freq) 
	{
		largest = right_index;
	}
	if (heap->data[i]->freq != heap->data[largest]->freq) 
	{
		swap(&heap->data[i], &heap->data[largest]);
		min_heapify(heap, largest);
	}
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

void enqueue(heap *heap, void *item, void *freq, Element_queue *down_left, Element_queue *down_right)
{
	if (heap->size >= 257) 
	{
		printf("Heap overflow");
	} 
	else 
	{
		heap->data[++heap->size] = new_element_queue(item, freq, down_left, down_right);
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

Element_queue *dequeue(heap *heap)
{
	if (heap == NULL || heap->size == 0) 
	{
		printf("Heap underflow");
	} 
	else 
	{
		Element_queue *item = heap->data[1];
		heap->data[1] = heap->data[heap->size];
		heap->size--;
		min_heapify(heap, 1);
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


Element_queue *criar_arvore(heap *heap, arvore *tree)
{
	int size;
	while(heap->size > 1)
	{
		Element_queue *esq = dequeue(heap);
		Element_queue *dir = dequeue(heap);

		enqueue(heap, 42, esq->freq + dir->freq, esq, dir);
		size = heap->size;
		heapsort(heap);
		heap->size = size;
	}
	return tree->raiz = dequeue(heap);
}

Node_index *add_element(Node_index *local, void *item, int shift_bit)
{
	local->item = item;
	local->shift_bit = shift_bit;
	return local;
}

void put(Hash_Table *ht, void *item, int shift_bit)
{
	int index;
	int item_aux = item;
	index = item_aux % num_prime;
	ht->table[index] = add_element(ht->table[index], item, shift_bit);
	//printf("%c, %d\n", item, shift_bit);
}

void dfs(Element_queue *raiz, Hash_Table *ht, int flag, int shift_bit)
{
	//printf("%c, %d\n", raiz->item, shift_bit);
	if(raiz->down_left == NULL && raiz->down_right == NULL)
	{
		void *item = raiz->item;
		put(ht, item, shift_bit);
		return;
	}
	else
	{	
		if(flag == 1)
		{
			dfs(raiz->down_left, ht, 0, shift_bit + 0);
			dfs(raiz->down_right, ht, 0, shift_bit + 1);
		}
		else
		{
			dfs(raiz->down_left, ht, 0, (shift_bit<<1));
			dfs(raiz->down_right, ht, 0, (shift_bit<<1) + 1);
		}
	}
}

/*
void print_heap(heap *heap, int size)
{
	int i;
	for(i = 1; i <= size; i++)
	{
		printf("%c -> %d\n", heap->data[i]->item, heap->data[i]->freq);
	}
	puts("");
}

void print_pre_order(Element_queue* raiz)///TESTES
{
	if(raiz != NULL)
	{
		if(raiz->freq != 0)
		{
			printf("%c", raiz->item);
			print_pre_order(raiz->down_left);
			print_pre_order(raiz->down_right);
		}
	}
}*/

void print_hash(Hash_Table *ht)
{
	int i =0;
	while(i < 257)
	{
		if(ht->table[i]->shift_bit != -1)
		{
			printf("%c -> %d\n", ht->table[i]->item, ht->table[i]->shift_bit);
		}
		i++;
	}
	printf("\n");
}

void binary(Hash_Table *ht)
{
	int i = 0;
	while(i < 257)
	{
		if(ht->table[i]->shift_bit != -1)
		{
			printf("%c -> ", ht->table[i]->item);
			int num = ht->table[i]->shift_bit;
			int bits = 8;
			int i = bits - 1;
			int bin[15] = {};
			while(num/2 > 0)
			{
				bin[i] = num % 2;
				num = num/2;
				i--;
			}
			if(num/2 == 0)
			{
				bin[i] = num;
			}
			for(i = 0; i < bits; i++)
			{
				printf("%d", bin[i]);
			}	
			printf("\n");
		}
		i++;
	}
}

int main ()
{
	int freq[256] = {};
	int i, size, shift_bit = 0, flag = 1;
	unsigned char s;
	FILE *f = fopen("teste.txt", "r");
	FILE *p = fopen ("out.txt", "a");
	heap *heap = create_heap();
	while (fscanf(f, "%c",&s) != EOF)
	{
		freq[s]++;
	}
	for(i = 0; i < 256; i++) 
	{
		if(freq[i] != 0)
		{
			enqueue(heap, i, freq[i], NULL, NULL);
		}
	}
	i = 0;
	size = heap->size;
	heapsort(heap);
	heap->size = size;
	//print_heap(heap, size);
	arvore *tree = create_tree();
	Element_queue *raiz;
	raiz = criar_arvore(heap, tree);

	Hash_Table *ht = create_hash_table();
	dfs(raiz, ht, flag, shift_bit);

	print_hash(ht);

	binary(ht);

	//print_pre_order(raiz);
	printf("\n");
	fclose(f);
	return 0;	
}
