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

#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HuffmanHash.h"
#include "HuffmanHeap.h"
#include "types.h"

#define num_prime 257

////////////////////HEADER/////////////////////

Huff_node *new_huff_node(void *item, int freq, Huff_node *down_left, Huff_node *down_right);
/* CRIA UM NO DE HUFFMAN, ADICIONA A ELE A FREQUENCIA, O ITEM E
 * DA ENDEREÇO AOS SEUS DOIS PONTEIROS, LEFT E RIGHT.
 */

int tree_size(Huff_node* raiz);
/* CALCULA O TAMANHO DA ARVORE */

Huff_node *create_tree(Huff_heap *heap);
/* CRIA A ARVORE DANDO DEQUEUE E ENQUEUE NA HEAP,
 * RETORNANDO O NO RAIZ.
 */

Huff_node* create_tree_from_preorder(FILE* in, int a[]);
/* CRIA A ARVORE A PARTIR DE SEU FORMATO EM PRE ORDEM,
 * OBEDECENDO O CONTRATO DO CARACTER DE ESCAPE.
*/

void create_encoding(Huff_node *raiz, struct huff_hash *ht, int flag, unsigned int shift_bit, int level);
/*ADICIONA NA HASH, OS VALORES QUE REPRESENTAM A NOVA CODIFICACAO
 * PARA ISSO NAVEGA-SE NA ARVORE ATE ENCONTRAR UMA FOLHA, DANDO SHIFT-BIT E,
 * SOMANDO UMA CASO NAVEGUEMOS PARA A DIREITA
 * */

void print_pre_order(Huff_node* raiz);
/* PRINTA A ARVORE EM PRE ORDEM OBEDECENDO O
 * ESTABELECIDO SOBRE O CARACTER DE ESCAPE
 */

void print_pre_order_file(Huff_node* raiz, FILE* out);
/* PRINTA A ARVORE EM PRE ORDEM EM UM ARQUIVO OBEDECENDO O
 * ESTABELECIDO SOBRE O CARACTER DE ESCAPE
 */

////////////////////END OF H FILE/////////////////

#endif /* HUFFMANTREE_H_ */
