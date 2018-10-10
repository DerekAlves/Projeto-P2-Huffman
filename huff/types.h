#ifndef TYPES_H_
#define TYPES_H_

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

/////////////START OF H FILE///////////////////

////////////////////STRUCTS////////////////////

struct huff_node
{
	void *item;
	int freq;
	struct huff_node *down_left;
	struct huff_node *down_right;
};
typedef struct huff_node Huff_node;
/*HUFF NODE
 * DESCREVE UM NO DA ARVORE DE HUFFMAN
 */

struct heap
{
	int size;
	Huff_node *data[257];
};
typedef struct heap Huff_heap;
/*HEAP
 * DESCREVE UMA HEAP, COMPOSTA POR ELEMENTOS DA STRUCT HUFF NODE
 */

struct hash_data_set
{
	void *item;
	unsigned int shift_bit;
	int bits;
	int freq;
};
typedef struct hash_data_set Hash_data;
/*HASH DATA
 * SAO OS DADOS DA HASH ABAIXO
 */

struct huff_hash
{
	Hash_data *table[256];
};
typedef struct huff_hash Huff_hash;
/*HASH
 * COM OS DADOS DO TIPO HASH DATA, IREMOS ADICIONAR-LOS A UMA HASH, E TERMOS ACESSO EM O(1)!
 */

#endif /* TYPES_H_ */

///////////////END OF H FILE///////////////////