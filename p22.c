#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define num_prime 257

/*
void binary(FILE *p, unsigned char hexa)
{
	int num = hexa;
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
		fprintf(p, "%d", bin[i]);
	}
	fprintf(p, "\n");
}
*/

typedef struct element
{
	void *item;
	void *freq;
	struct Node *next;
	struct Node *previous;
}Node;

typedef struct nodes_index
{
	Node *next;
}Node_index;

typedef struct hash_table
{
	Node *table[10000];
}Hash_Table;

Node *newNode(void *x){
    Node *node = (Node*) malloc(sizeof(Node));
    node->item = x;
    node->freq = 0;
    node->next = NULL;
    node->previous = NULL;
    return node;
}

Node_index *new_index()
{
	Node_index *node = (Node_index*) malloc(sizeof(Node_index));
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
	/*
	else if(inicio->next != NULL)
	{
		Node *current = inicio->next;
		while(current->next != NULL)
		{
			current = current->next;
		}
		current->next = node;
		node->item = item;
		node->freq = current->freq++;
		node->next = NULL;
		node->previous = current;
		return inicio;
	}*/
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

int main ()
{
	int freq[256] = {};
	unsigned char s;
	FILE *f = fopen("japao.png", "r");
	FILE *p = fopen ("out.txt","a");
	Hash_Table *ht = create_hash_table();
	while (fscanf(f, "%c",&s) != EOF)
	{
		freq[s]++;
	}
	for(int i = 0; i < 256; i++) 
	{
		printf("%d %c %d", i, i, freq[i]);
		printf("\n");
		put(ht, i, freq[i]);
	}
	print_hash(ht);
	fclose(f);
	return 0;	
}