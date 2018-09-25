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

/////////////START OF H FILE///////////////////

#ifndef HUFFMANHASH_H_
#define HUFFMANHASH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HuffmanHeap.h"
#include "HuffmanTree.h"
#include "types.h"

#define num_prime 257

////////////////////HEADER/////////////////////

Hash_data *new_index();
/*COMENTARIO AQUI
 *
 */

Huff_hash *create_hash_table();
/*COMENTARIO AQUI
 *
 */

Hash_data *add_element(Hash_data *local, void *item, unsigned char shift_bit, int level);
/*COMETARIO AQUI
 *
 */

void put_hash(Huff_hash *ht, void *item, unsigned char shift_bit, int level);
/*COMENTARIO AQUI
 *
 */

void print_hash(Huff_hash *ht);
/*COMENTARIO AQUI
 *
 */


////////////////////END OF H FILE/////////////////


#endif /* HUFFMANHASH_H_ */
