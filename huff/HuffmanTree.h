#ifndef HUFFMANTREE_H_
#define HUFFMANTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HuffmanHash.h"
#include "HuffmanHeap.h"
#include "types.h"


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

#define num_prime 257

////////////////////HEADER/////////////////////

Huff_node *new_huff_node(void *item, int freq, Huff_node *down_left, Huff_node *down_right);
/*COMENTARIO AQUI
 *
 */

Huff_node *create_tree();
/*COMENTARIO AQUI
 *
 */

Huff_node *criar_arvore(struct heap *heap, Huff_node *tree);
/*COMENTARIO AQUI
 *
 */

void dfs(Huff_node *raiz, struct huff_hash *ht, int flag, unsigned char shift_bit, int level);
/*COMENTARIO AQUI
 *
 */

void print_pre_order(Huff_node* raiz);
/*COMENTARIO AQUI
 *
 */

////////////////////END OF H FILE/////////////////


#endif /* HUFFMANTREE_H_ */
