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

#ifndef HUFFMANHEAP_H_
#define HUFFMANHEAP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HuffmanHash.h"
#include "HuffmanTree.h"
#include "types.h"


#define num_prime 257

////////////////////HEADER/////////////////////

void swap(int *x, int *y);
/*COMENTARIO AQUI
 *
 */

Huff_heap* create_heap();
/*COMENTARIO AQUI
 *
 */

int get_parent_index(Huff_heap *heap, int i);
/*COMENTARIO AQUI
 *
 */

int get_left_index(Huff_heap *heap, int i);
/*COMENTARIO AQUI
 *
 */

int get_right_index(Huff_heap *heap, int i);
/*COMENTARIO AQUI
 *
 */

int item_of(Huff_heap *heap, int i);
/*COMENTARIO AQUI
 *
 */

void min_heapify(Huff_heap *heap, int i);
/*COMENTARIO AQUI
 *
 */

void max_heapify(Huff_heap *heap, int i);
/*COMENTARIO AQUI
 *
 */
void enqueue_heap(Huff_heap *heap, void *item, void *freq, Huff_node *down_left, Huff_node *down_right);
/*COMENTARIO AQUI
 *
 */

Huff_node *dequeue_heap(Huff_heap *heap);
/*COMENTARIO AQUI
 *
 */

void heapsort(Huff_heap *heap);
/*COMENTARIO AQUI
 *
 */

void print_heap(Huff_heap *heap, int size);
/*COMENTARIO AQUI
 *
 */

////////////////////END OF H FILE/////////////////


#endif /* HUFFMANHEAP_H_ */
