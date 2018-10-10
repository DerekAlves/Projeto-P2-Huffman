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
#include <math.h>
#include "HuffmanHash.h"
#include "HuffmanHeap.h"
#include "HuffmanTree.h"
#include "Compress_Decompress.h"
#include "types.h"


void decompress();

int number_of_bits (Huff_hash *ht)
{
	int bits = 0;
	int i;
	for(i = 0; i < 256; i++)
	    if(ht->table[i]->freq != 0) 
	    	bits += (ht->table[i]->bits * ht->table[i]->freq);

	    return bits;
}

int number_of_bytes(double bits){ return ceil(bits/8); }


#define num_prime 257



void create_header(int trash_size, int tree_size, Huff_node *tree, FILE* out)
{
	//printf("TRASH SIZE: %d | TREE SIZE: %d\n.", trash_size, tree_size);
	unsigned char* bytes = (unsigned char*)malloc(3 * sizeof(unsigned char));
	bytes[0] = trash_size << 5 | tree_size >> 8;   //trash_size esta representado no inicio do byte, importante joga-lo para os 3 primeiros, destacar >>8 em tree_size para add ao primeiro byte do arquivo trechos que formam o size_tree
	bytes[1] = tree_size;                          //salva as 8 primeiras posicoes do tree_size

	fputc(bytes[0], out);
	fputc(bytes[1], out);
	print_pre_order_file(tree, out);  //printa arvore no arquivo
}


void compress()
{
	/*FILE *in = fopen("teste.txt", "r");
	FILE *out = fopen ("out.huff", "w");*/
	system("clear");
	FILE *in;
	FILE *out;

	char filename[100] = "";
	char outputname[100] = "";
	printf("\nInsert the name of the file to be compressed:\n");
	scanf("%s", filename);
	in = fopen(filename, "rb");
	if (in == NULL)
	{
		printf("\n%s\"File not Found!\n", filename);
		printf("\nRestarting the process...\n");
		compress();
		return;
	}
	printf("\nInsert the compressed file name:\n");
	scanf("%s", outputname);
	printf("\n");
	out = fopen(outputname, "wb");



	int i, size, flag = 1;
	unsigned char s;
	unsigned int shift_bit = 0;
	long long int freq[256] = {0}; 
	while (fscanf(in, "%c",&s) != EOF) 
		freq[s]++;    //CRIA ARRAY DE FREQUENCIAS
	fclose(in);
	Huff_heap *heap = create_heap();//CRIA A HEAP
	Huff_hash *ht = create_hash_table();//CRIA A HASH

	for(i = 0; i < 256; i++)
	{
		if(freq[i] != 0)
		{
			enqueue_heap(heap, &i, freq[i], NULL, NULL);
		}
		ht->table[i]->freq = freq[i];
	}
	i = 0;
	Huff_node *raiz;
	raiz = create_tree(heap);
	create_encoding(raiz, ht, flag, shift_bit, 0);

	int bits = number_of_bits(ht);
	int bytes = number_of_bytes(bits);
	int trash = (bytes*8) - bits; //proximo a bits, porem a diferenca me da o lixo
	
	int size_of_tree = tree_size(raiz);

	create_header(trash, size_of_tree, raiz, out);//CALCULAR LIXO//E TAMANHO DA ARVORE

	in = fopen(filename, "rb");

	int control = 0;
	int empty_bits = 8;

	unsigned int c;
	unsigned char aux = 0;

	//COMPRESS
	while (fscanf(in, "%c", &s) != EOF)
	{
		control = ht -> table[s] -> bits;  //caracter s me mostra a qual to me referindo na hash
		empty_bits = empty_bits - control;
		c = ht -> table[s] -> shift_bit;
		if(empty_bits <= 0)
		{
			aux |= (c >> abs(empty_bits));
			fputc(aux, out);
			empty_bits =  8 + empty_bits;
			aux = 0;
			while(empty_bits < 0)
			{
				aux |= (c >> abs(empty_bits));
				fputc(aux, out);
				empty_bits =  8 + empty_bits;
				aux = 0;
			}
			aux |= (c << empty_bits);
		}
		else aux |= (c << empty_bits);
	}
	if(trash != 0)fputc(aux, out);
	fclose(in);
	fclose(out);
	
	//Test
	system("clear");
	printf("Do you want to decompress the generated file? 1 - Yes | 2 - No\n");
	int option;
	scanf("%d", &option);
	if (option == 1) decompress();
	else
	{
		system("clear");
		printf("\nDone.\n\n");
		return;
	}
		
}

int is_bit_i_set(unsigned char byte, int i){ return (byte & (1 << i)); }

long long int FileSize(FILE *in)
{
	long long int bytes;
	if (in != NULL)
	{
		fseek(in, 0, SEEK_END);
		bytes = ftell(in);
	}
	return bytes;
}

void decompress()
{
	system("clear");
	FILE *in;
	FILE *out;

	char filename[100] = "";
	char outputname[100] = "";
	printf("\nInsert the file name to be decompressed:\n");
	scanf("%s", filename);
	in = fopen(filename, "rb");

	if (in == NULL)
	{
		printf("\n%s\"File not Found!\n", filename);

		printf("\nRestarting the process...\n");
		decompress();
		return;
	}

	printf("\nInsert the output file name:\n");
	scanf("%s", outputname);
	printf("\n");
	out = fopen(outputname, "wb");



	char s;
	long long int  bytes = FileSize(in);

	fclose(in);

	in = fopen(filename, "rb");

	unsigned char a, b, trash;
    fscanf(in, "%c%c", &a, &b);
    trash = a>>5;
    a = a<<3;  //retiro o lixo
    a = a>>3;  //deixa 0  no lugar do lixo
    short int tam_arv = a;
    tam_arv = tam_arv<<8;  //abro espaco para o b ser somado
    tam_arv |= b;

    bytes = bytes - (tam_arv + 2);  //os bytes da arvore mais os dois do comeco

	Huff_node* raiz;
	int barras[5] = {0};
	raiz = create_tree_from_preorder(in, barras);

	///////////////

	bytes -= barras[0]; //retiro as barras que so estavam ali como apoio

	int i, j;

	Huff_node* aux =  raiz;

	for(i = 1; i <= bytes; i++)                   //roda byte a byte
	{
		fscanf(in, "%c", &s);                     //continua leitura de onde parou
		for(j = 7; j >= 0; j--)                   //roda bit a bit
		{
			if(j == (trash - 1) && (i == bytes)) break;  //trash - 1, indica a posiçao do byte onde inicia-se o lixo, e se esta no ultimo byte
			if(is_bit_i_set(s, j)) raiz = raiz -> down_right;       //percorre a arvore para salvar os itens originais
			else raiz = raiz -> down_left;                          //percorre a arvore para salvar os itens originais

			if(raiz -> down_right == NULL && raiz -> down_left == NULL)
			{
				fputc(*(unsigned char*)raiz -> item, out);
				raiz = aux;
			}
		}
	}

	//Test
	system("clear");
	printf("Do you want to compare the decompressed file with the original file?\n");
	printf("1 - Yes | 2 - No\n");
	int option2;
	scanf("%d", &option2);
	if (option2 == 1)
	{
		char original[100] = "";
		printf("\nInsert the original file name:\n");
		scanf("%s", original);
		FILE *p = fopen(original, "r");
		if (p == NULL)
		{
			printf("\n%s\"File not Found!\n", original);
			return;
		}

		long long int bytes_in = FileSize(p);
		long long int bytes_out = FileSize(out);

		printf("Size of the output file: %lld\n", bytes_out);
		printf("Size of the original file: %lld", bytes_in);

		if (bytes_out != bytes_in) { printf("\nIt gave bad\n"); return; }
		else { printf("\nGave good\n"); return; }
	}
	else
	{
		system("clear");
		printf("\nDone.\n\n");
		return;
	}
		
	
}
