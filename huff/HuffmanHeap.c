/*////////////INFO////////////////////////////
 *
 * # Projeto-P2-Huffman
	Projeto para Estrutura de Dados (Huffman);
	Universidade Federal de Alagoas - Instituto de Computação;
	ECOM-008 - Estrutura de Dados.

	Derek Nielsen Araújo Alves	 - dnaa@ic.ufal.br;
	Darlysson Olímpio Nascimento - don@ic.ufal.br;
	Aldemir Melo Rocha Filho	 - amrf@ic.ufal.br;
	Yuri Fernandes Souza Silva	 - yfss@ic.ufal.br;
	Walmer Almeida Cavalcante	 - wac@ic.ufal.br.

	Inicio em:
	10 de Setembro de 2018, Maceió - AL, Brasil.
*/

/////////////START OF C FILE///////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HuffmanHash.h"
#include "HuffmanHeap.h"
#include "HuffmanTree.h"
#include "types.h"

#define num_prime 257


void swap(Huff_node **x, Huff_node **y)
{
   Huff_node *temp;
   temp = *x;
   *x = *y;
   *y = temp;
}

Huff_heap* create_heap()
{
	int i;
	Huff_heap *new_heap = (Huff_heap*) malloc(sizeof(Huff_heap));
	new_heap->size = 0;
	for(i = 1; i < 257; i++) 
		new_heap->data[i] = NULL;
	return new_heap;
}

int get_parent_index(Huff_heap *heap, int i) { return i/2; }

int get_left_index(Huff_heap *heap, int i) { return 2*i; }

int get_right_index(Huff_heap *heap, int i) { return 2*i + 1; }

Huff_node *item_of(Huff_heap *heap, int i) { return heap->data[i]; }

void min_heapify(Huff_heap *heap, int i) //o no de menor frequencia no topo da heap
{
	int smallest;
	int left_index = get_left_index(heap, i);	
	int right_index = get_right_index(heap, i);
	if (left_index <= heap->size && (heap->data[left_index]->freq < heap->data[i]->freq))
		smallest = left_index;	//recebe indice do menor: left (esta no lugar errado)
	else smallest = i; //meu menor ainda é o i;
	if (right_index <= heap->size && (heap->data[right_index]->freq < heap->data[smallest]->freq))
		smallest = right_index; //recebe o indice do menor: right (esta no lugar erradp)
	if (heap->data[i]->freq != heap->data[smallest]->freq) // se for menor que o meu topo, ja que sempre i = 1
	{
		swap(&(heap->data[i]), &(heap->data[smallest]));
		min_heapify(heap, smallest);
	}
}

void enqueue_heap(Huff_heap *heap, void *item, int freq, Huff_node *down_left, Huff_node *down_right)
{	
	if (heap->size >= 256) printf("Heap overflow");
	else
	{
		heap->data[++heap->size] = new_huff_node(item, freq, down_left, down_right); //incrementa pra add
		int key_index = heap->size;
		int parent_index = get_parent_index(heap, heap->size);   //indice pai de key_index
		while (parent_index >= 1 && heap->data[key_index]->freq < heap->data[parent_index]->freq)
		{
			swap(&heap->data[key_index], &heap->data[parent_index]); //troca nos com freq menores(topo)
			key_index = parent_index;   //checa ate o topo
			parent_index = get_parent_index(heap, key_index);
		}
	}
}

Huff_node *dequeue_heap(Huff_heap *heap)
{
	if (heap == NULL || heap->size == 0)
	{
		printf("Heap underflow");
		return NULL;
	}
	else
	{
		Huff_node *item = heap->data[1];
		heap->data[1] = heap->data[heap->size];
		heap->size--; //remocao logica
		min_heapify(heap,1);
		return item;
	}
}

void print_heap(Huff_heap *heap, int size)
{
	int i;
	for(i = 1; i <= size; i++)
	{
		printf("%c -> %d\n", *(unsigned char*)heap->data[i]->item, heap->data[i]->freq);
	}
	puts("");
}

////////////////////END OF C FILE/////////////////
