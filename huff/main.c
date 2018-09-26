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
	10 de Setembro de 2018, Maceió - AL, Brasil/
*/

/////////////START OF C FILE///////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HuffmanHash.h"
#include "HuffmanHeap.h"
#include "HuffmanTree.h"
#include "types.h"
#include <math.h>


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

/*void comprimir(Huff_hash *ht)
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

        }
    }

}*/

int number_of_bits (Huff_hash *ht)
{
		int bits = 0;
	    int i;
	    for(i = 0; i < 256; i++)
	        {
	            if(ht->table[i]->freq != 0)
	            {
	            	  bits += (ht->table[i]->bits * ht->table[i]->freq);
	            }
	        }

	    //printf ("Bits: %d\n", bits);
	    return bits;
}

int number_of_bytes(double bits)
{
	return ceil(bits/8);
}


#define num_prime 257



void create_header(int trash_size, int tree_size, Huff_node *tree, FILE* out)
{
	printf("%d %d\n", trash_size, tree_size);
	unsigned char a, b; a = b = 0;
	a |= trash_size << 5; a |= tree_size >> 8;
	b |= tree_size;

	fprintf(out, "%c%c", a, b);
	print_pre_order_file(tree, out);
}

/*void read_header()
{

}*/

int tree_size(Huff_node* raiz)
{
	if(raiz == NULL) 
		return 0;
	else
	{
		return  1 + tree_size(raiz -> down_left) + tree_size(raiz -> down_right);
	}

}

void compress(/*Huff_node *tree*/)
{
	FILE *in = fopen("teste.txt", "r");
	FILE *out = fopen ("out.txt", "w");

	int i, size, flag = 1;
	unsigned char s, shift_bit = 0;
	int freq[256] = {0}; while (fscanf(in, "%c",&s) != EOF) freq[s]++;//CRIA ARRAY DE FREQUENCIAS
	fclose(in);
	Huff_heap *heap = create_heap();//CRIA A HEAP
	Huff_hash *ht = create_hash_table();//CRIA A HASH

	for(i = 0; i < 256; i++)
	{
		if(freq[i] != 0)
		{
			enqueue_heap(heap, i, freq[i], NULL, NULL);
		}
		ht->table[i]->freq = freq[i];
	}
	i = 0;
	heapsort(heap);
	//print_heap(heap, heap -> size);
	Huff_node *raiz;
	raiz = criar_arvore(heap/*, tree*/);
	dfs(raiz, ht, flag, shift_bit, 0);
	print_pre_order(raiz);
	printf("\n");
	//comprimir(ht);
	
	int bits = number_of_bits(ht);
	int bytes = number_of_bytes(bits);
	int trash = (bytes*8) - bits;
	printf("bits %d bytes %d trash %d\n", bits, bytes, trash);
	int size_of_tree = tree_size(raiz);
	printf("TS %d\n", size_of_tree);

	print_hash(ht);


	create_header(trash, size_of_tree, raiz, out);//CALCULAR LIXO//E TAMANHO DA ARVORE

	in = fopen("teste.txt", "r");

	int control = 0;
	int empty_bits = 8;

	unsigned char aux = 0, c;

	//COMPRESS
	while (fscanf(in, "%c", &s) != EOF)
	{
		control = ht -> table[s] -> bits;
		empty_bits = empty_bits - control;
		c = ht -> table[s] -> shift_bit;
		if(empty_bits <= 0)
		{
			aux |= c >> abs(empty_bits);
			fprintf(out, "%c", aux);
			empty_bits =  8 + empty_bits;
			aux = 0;
			aux |= c << empty_bits;
		}
		else aux |= c << empty_bits;
	}
	fprintf(out, "%c", aux);
	fclose(in);
	fclose(out);

	return;
}

int main ()
{

	int menu;
	printf("Digite '1' para compactar,\nOu digite '2' para descompactar.\n");
	scanf("%d", &menu);

	if(menu == 1) compress();
	//else if(menu == 2) return 0;// decompress();
	else printf("Opção Inválida! Execute novamente o programa.\n");

	return 0;
}
