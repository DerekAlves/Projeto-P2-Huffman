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

#ifndef COMPRESS_DECOMPRESS_H_
#define COMPRESS_DECOMPRESS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "HuffmanHash.h"
#include "HuffmanHeap.h"
#include "HuffmanTree.h"
#include "types.h"


int number_of_bits (Huff_hash *ht);
/*CALCULA O NUMERO DE BITS, PARA CALCULAR O LIXO E O NUMERO DE BYTES. */

int number_of_bytes(double bits);
/*CALCULA O NUMERO DE BYTES*/

void create_header(int trash_size, int tree_size, Huff_node *tree, FILE* out);
/* CRIA O CABEÇALHO ESTABELECIDO EM SALA DE AULA
 * O PRIMEIRO BYTE REPRESENTA O LIXO E PARTE DO TAMANHO DA ARVORE,
 * ENQUANTO O SEGUNDO BYTE REPRESENTA O RESTANTE DO TAMANHO DA ARVORE.
 * LOGO APOS SEGUE-SE A ARVORE EM PREORDEM,
 * OBEDECENDO AS REGRAS PARA O CARACTER ESCAPE '\'!.
 */

int is_bit_i_set(unsigned char byte, int i);
/* VERIFICA SE O BIT I, ESTÁ SETADO. */

long long int FileSize(FILE *in);
/* RETORNA O TAMANHO DO ARQUIVO */

void compress();
/* TODO O ALGORITMO DE COMPRESSÃO DE HUFFMAN
 * UMA MIN-HEAP PARA RETIRAR OS CARACTERES ORDENADOS PELA MENOR FREQUENCIA
 * LOGO APOS, CRIAMOS A ARVORE, E USAMOS UMA HASH PARA GUARDAR A CODIFICACAO,
 * CRIA-SE O CABEÇALHO E EM SEGUIDA PARA CADA CARACTER DO ARQUIVO ORIGINAL,
 * JUNTAMOS AS CODIFICACOES EM UM BYTE POR VEZ, E PRINTAMOS NO ARQUIVO DE SAIDA.
 */

void decompress();
/* TODO O ALGORITMO DE DESCOMPRESSÃO DE HUFFMAN
 * PEGAMOS O LIXO E O TAMANHO DA ARVORE, EM SEGUIDA
 * CRIAMOS A ARVORE A PARTIR DE SUA PREORDEM.
 * ENTAO PEGAMOS CADA BYTE E VERIFICAMOS SE SEUS BITS ESTAO SETADOS,
 * SE SIM, NAVEGO NA ARVORE DE HUFFMAN PARA A DIREITA, SE NAO
 * NAVEGO NA ARVORE PARA A ESQUERDA.
 * ASSIM QUE CHEGAR EM UMA FOLHA PRINTO O CARACTER QUE ELA CONTEM NO ARQUIVO DE SAIDA.
 */



#endif /* COMPRESS_DECOMPRESS_H_ */
