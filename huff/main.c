#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HuffmanHash.h"
#include "HuffmanHeap.h"
#include "HuffmanTree.h"
#include "types.h"

/*////////////INFO//////////////////////
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
	10 de Setembro de 2018, Maceió - AL, Brasil
*/

/////////////START OF C FILE///////////////////

void binary(Huff_hash *ht, int index, int bin[])
{
	if(ht->table[index]->freq != 0)
	{
		//printf("%c -> ", ht->table[j]->item);
		int num = ht->table[index]->shift_bit;
		int bits = 8;
		int i = bits - 1;
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
		//return bin;
		/*
		for(i = 0; i < bits; i++)
		{
			printf("%d", bin[i]);
		}
		printf("\n");*/
	}
}

void comprimir(Huff_hash *ht)
{
    int i, j = 0, limitante, bin[15] = {};
    unsigned char byte;
    for(i = 0; i < 256; i++)
    {
        if(ht->table[i]->freq != 0)
        {
            limitante = ht->table[i]->bits;
            byte = ht->table[i]->shift_bit;
            binary(ht, i, bin);
            while(j < (8 -  ht->table[i]->bits))
            {
                byte = byte<<1;
                int check = 8 - limitante;
                if(bin[check] == 1)
                {
                    byte = byte + 1;
                }
                j++;
                limitante--;
                if(limitante == 0)
                {
                    limitante = ht->table[i]->bits;
                }
            }
            j = 0;
            printf("%d\n", byte);
        }
    }
}



#define num_prime 257
int main ()
{
	int freq[256] = {};
	int i, size, flag = 1;
	unsigned char s, shift_bit = 0	;
	FILE *f = fopen("teste.txt", "r");
	FILE *p = fopen ("out.txt", "a");
	Huff_heap *heap = create_heap();
	while (fscanf(f, "%c",&s) != EOF)
	{
		freq[s]++;
	}
	Huff_hash *ht = create_hash_table();
	for(i = 0; i < 256; i++)
	{
		if(freq[i] != 0)
		{
			enqueue_heap(heap, i, freq[i], NULL, NULL);
		}
		ht->table[i]->freq = freq[i];
	}
	i = 0;
	size = heap->size;
	heapsort(heap);
	heap->size = size;
	//print_heap(heap, size);
	Huff_node *tree = create_tree();
	Huff_node *raiz;
	raiz = criar_arvore(heap, tree);

	dfs(raiz, ht, flag, shift_bit, 0);


	//printf("Agora printando hash normal\n");
	print_hash(ht);
	//printf("Agora printando hash em bin\n");
	comprimir(ht);
	//print_pre_order(raiz);
	printf("\n");
	fclose(f);
	return 0;
}
