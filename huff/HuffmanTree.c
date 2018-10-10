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
	node_queue->item = (unsigned char*) malloc(sizeof(unsigned char));
	*(unsigned char *)node_queue->item = *(unsigned char*)item;
	node_queue->freq = freq;
	node_queue->down_left = down_left;
	node_queue->down_right = down_right;
	return node_queue;
}

int tree_size(Huff_node* raiz)
{
	if(raiz == NULL) return 0;
	else return  1 + tree_size(raiz -> down_left) + tree_size(raiz -> down_right);
}

Huff_node *create_tree(Huff_heap *heap)
{
	//int size;
	while(heap->size > 0)
	{
		Huff_node *esq = dequeue_heap(heap);
		Huff_node *dir = dequeue_heap(heap);

		unsigned char asterisco = 42;
		if(heap->size == 0)
		{	
			return new_huff_node(&asterisco, (esq->freq + dir->freq), esq, dir);
		}
		if((*(unsigned char*)dir->item == '*' && *(unsigned char*)esq->item != '*') && (dir->freq == esq->freq))
		{
			enqueue_heap(heap, &asterisco,esq->freq + dir->freq, dir, esq);
		}
		else
		{
			enqueue_heap(heap, &asterisco,esq->freq + dir->freq, esq, dir);
		}
	}
}

Huff_node* create_tree_from_preorder(FILE* in, int a[])
{
	char c;
	short int flag = 1;
	fscanf(in, "%c", &c);
	if(c == 92)  //barra
	{
		a[0]++;
		fscanf(in, "%c", &c);
		flag = 0;   // faz pular o proximo if de percorrer a arvore, pois indica que tal * é um filho
	}
	Huff_node *tree_node;
	tree_node = new_huff_node(&c, 1, NULL, NULL);
	if (c == '*' && flag == 1)                                       //significa que ainda n é uma folha, nenhum caso especial, continua criando a arvore
	{
		tree_node -> down_left = create_tree_from_preorder(in, a);
		tree_node -> down_right = create_tree_from_preorder(in, a);
	}
	return tree_node;
}

void create_encoding(Huff_node *raiz, Huff_hash *ht, int flag, unsigned int shift_bit, int level) //forma as novas representacoes dos bytes
{
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
			create_encoding(raiz->down_left, ht, 0, shift_bit, level + 1);
			create_encoding(raiz->down_right, ht, 0, (shift_bit | 1), level + 1);
		}
		else
		{
			create_encoding(raiz->down_left, ht, 0, (shift_bit<<1), level + 1);
			create_encoding(raiz->down_right, ht, 0, ((shift_bit<<1) | 1), level + 1);
		}
	}
}

void print_pre_order(Huff_node* raiz)///IF PARA IMPRIMIR \ CASO NO SEJA FOLHA E O CARACTER SEJA * ou \  ////
{
	if(raiz != NULL)
	{
		if(raiz->freq != 0)
		{
			if(((*(unsigned char*)raiz->item == 92) || *(unsigned char*)raiz->item == 42) && (raiz->down_left == NULL && raiz->down_right == NULL)) printf("%c", 92);
			printf("%c", *(int*)raiz->item);
			print_pre_order(raiz->down_left);
			print_pre_order(raiz->down_right);
		}
	}
}

void print_pre_order_file(Huff_node* raiz, FILE* out)///IF PARA IMPRIMIR \ CASO NO SEJA FOLHA E O CARACTER SEJA (*) ou (\)  ////
{
	if(raiz != NULL)
	{
		if(raiz->freq != 0)
		{
			if(((*(unsigned char*)raiz->item == 92) || *(unsigned char*)raiz->item == 42) && (raiz->down_left == NULL && raiz->down_right == NULL)) fputc(92, out);
			fputc(*(int*)raiz->item, out);
			print_pre_order_file(raiz->down_left, out);
			print_pre_order_file(raiz->down_right, out);
		}
	}
}

////////////////////END OF C FILE/////////////////
