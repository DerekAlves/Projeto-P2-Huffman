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

Huff_node *new_huff_node(void *item, int freq, Huff_node *down_left, Huff_node *down_right)
{
	Huff_node *node_queue = (Huff_node*) malloc(sizeof(Huff_node));
	node_queue->item = item;
	node_queue->freq = freq;
	node_queue->down_left = down_left;
	node_queue->down_right = down_right;
	return node_queue;
}

Huff_node *create_tree()
{
	Huff_node *new_tree = (Huff_node*) malloc(sizeof(Huff_node));
	new_tree = new_huff_node(NULL, NULL, NULL, NULL);
	return new_tree;
}

Huff_node *criar_arvore(struct heap *heap/*, Huff_node *tree*/)
{
	int size;
	while(heap->size > 1)
	{
		Huff_node *esq = dequeue_heap(heap);
		Huff_node *dir = dequeue_heap(heap);

		enqueue_heap(heap, 42, esq->freq + dir->freq, esq, dir);
		size = heap->size;
		heapsort(heap);
		heap->size = size;
	}
	return dequeue_heap(heap);
}

Huff_node* create_tree_from_preorder(FILE* in)
{
	char c;
	short int flag = 1;
	fscanf(in, "%c", &c);
	printf("CHAR %c\n", c);
	if(c == 92)
	{
		fscanf(in, "%c", &c);
		flag = 0;
	}
	Huff_node *tree_node;
	tree_node = new_huff_node(c, 1, NULL, NULL);
	if (c == '*' && flag)
	{
		//tree_node = new_huff_node(c, 1, create_tree_from_preorder(in), create_tree_from_preorder(in));
		tree_node -> down_left = create_tree_from_preorder(in);
		tree_node -> down_right = create_tree_from_preorder(in);
	}
	return tree_node;
}

void dfs(Huff_node *raiz, struct huff_hash *ht, int flag, unsigned char shift_bit, int level)
{
	//printf("%c, %d\n", raiz->item, shift_bit);
	if(raiz->down_left == NULL && raiz->down_right == NULL)
	{
		void *item = raiz->item;
		put_hash(ht, item, shift_bit, level);
		return;
	}
	else
	{
		if(flag == 1)
		{
			dfs(raiz->down_left, ht, 0, shift_bit + 0, level + 1);
			dfs(raiz->down_right, ht, 0, shift_bit + 1, level + 1);
		}
		else
		{
			dfs(raiz->down_left, ht, 0, (shift_bit<<1), level + 1);
			dfs(raiz->down_right, ht, 0, (shift_bit<<1) + 1, level + 1);
		}
	}
}

void print_pre_order(Huff_node* raiz)///IF PARA IMPRIMIR \ CASO NO SEJA FOLHA E O CARACTER SEJA * ou \  ////
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
}

void print_pre_order_file(Huff_node* raiz, FILE* out)///IF PARA IMPRIMIR \ CASO NO SEJA FOLHA E O CARACTER SEJA * ou \  ////
{
	if(raiz != NULL)
	{
		if(raiz->freq != 0)
		{
			fprintf(out, "%c", raiz->item);
			print_pre_order_file(raiz->down_left, out);
			print_pre_order_file(raiz->down_right, out);
		}
	}
}

////////////////////END OF C FILE/////////////////
