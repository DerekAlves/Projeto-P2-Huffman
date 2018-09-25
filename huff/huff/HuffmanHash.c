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

/////////////START OF C FILE/////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HuffmanHash.h"
#include "HuffmanHeap.h"
#include "HuffmanTree.h"
#include "types.h"

#define num_prime 257

Hash_data *new_index()
{
	Hash_data *node = (Hash_data*) malloc(sizeof(Hash_data));
	node->item = NULL;
	node->shift_bit = NULL;
	node -> bits = 0;
	return node;
}

Huff_hash *create_hash_table()
{
	int i;
	Huff_hash *new_ht = (Huff_hash*) malloc(sizeof(Huff_hash));
	for(i = 0; i < 257; i++)
	{
		new_ht->table[i] = new_index();
	}
	return new_ht;
}

Hash_data *add_element(Hash_data *local, void *item, unsigned char shift_bit, int level)
{
	local->item = item;
	local->shift_bit = shift_bit;
	local -> bits = level;
	return local;
}

void put_hash(Huff_hash *ht, void *item, unsigned char shift_bit, int level)
{
	int index;
	int item_aux = item;
	index = item_aux % num_prime;
	ht->table[index] = add_element(ht->table[index], item, shift_bit, level);
	//printf("%c, %d\n", item, shift_bit);
}

void print_hash(Huff_hash *ht)
{
	int i = 0;
	while(i < 257)
	{
		if(ht->table[i]->freq != 0)
		{
			printf("%c -> %d\n", ht->table[i]->item, ht->table[i]->shift_bit);
		}
		i++;
	}
	printf("\n");
}

////////////////////END OF C FILE/////////////////
