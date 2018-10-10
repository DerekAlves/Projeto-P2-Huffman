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

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "HuffmanHash.h"
#include "HuffmanHeap.h"
#include "HuffmanTree.h"
#include "Compress_Decompress.h"
#include "types.h"


void presentation()
{
	printf("\n\n\n");
	printf("                                              ___   ____________ \n");
	printf("                                             /   | / ____/ ____/ \n"); 	
	printf("                                            / /| |/ /   / / \n");
	printf("                                           / ___ / /___/ /___ \n");
	printf("                                          /_/  |_\\____/\\____/ \n\n\n");
	printf("                                             Huffman's coding\n");
	printf("                             ------------- Press any key to start -------------\n\n\n");
	printf("                                               Developed by:\n");
	printf("  Aldemir Melo Rocha Filho | Darlysson Olímpio Nascimento | Derek Nielsen Araújo Alves | Walmer Almeida Cavalcante | Yuri Fernandes Souza Silva \n");
	getchar();
}

int main ()
{
	presentation();
	system("clear");
	int c;
	int menu;
	printf("Press '1' to compress, Or press '2' to decompress.\n");
	scanf("%d", &menu);

	if(menu == 1) compress();
	else if(menu == 2) decompress();
	else printf("Invalid option! Run the program again.\n");

	return 0;
}
