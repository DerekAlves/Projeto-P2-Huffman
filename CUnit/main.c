
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "c_unit.h"

#define num_prime 257

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

Hash_data *new_index();
/* ALOCA ESPACO PARA UM NOVO INDICE DA HASH*/

Huff_hash *create_hash_table();
/* CRIA UMA NOVA HASH-TABLE*/

Hash_data *create_data(Hash_data *local, void *item, unsigned int shift_bit, int level);
/* CRIA O CONJUNTO DE DADOS DA HASH*/

void put_hash(Huff_hash *ht, void *item, unsigned int shift_bit, int level);
/* USA A CREATE_DATA PARA CRIAR O CONJUNTO DE DADOS, E OS INSERE NA HASH*/

void print_hash(Huff_hash *ht);
/* PRINTA A HASH */

Hash_data *new_index()
{
	Hash_data *node = (Hash_data*) malloc(sizeof(Hash_data));
	node->item = NULL;
	node->shift_bit = 0;
	node -> bits = 0;
	return node;
}

Huff_hash *create_hash_table()
{
	int i;
	Huff_hash *new_ht = (Huff_hash*) malloc(sizeof(Huff_hash));
	for(i = 0; i < 257; i++)
		new_ht->table[i] = new_index();
	return new_ht;
}

Hash_data *create_data(Hash_data *local, void *item, unsigned int shift_bit, int level)
{
	local -> item = item;
	local -> shift_bit = shift_bit;
	local -> bits = level;
	return local;
}

void put_hash(Huff_hash *ht, void *item, unsigned int shift_bit, int level)
{
	int index;
	int item_aux = *(int*)item;
	index = item_aux % num_prime;
	ht -> table[index] = create_data(ht -> table[index], item, shift_bit, level);
	//printf("%c, %d\n", item, shift_bit);
}

void print_hash(Huff_hash *ht)
{
	int i;
	for(i = 0; i < 257; i++)
	{
		if(ht->table[i]->freq != 0)
			printf("%c -> %d, (%d)\n", *(unsigned char*)ht->table[i]->item, ht->table[i]->shift_bit, ht->table[i]->bits);
	}
	printf("\n");
}

unsigned int search(Huff_hash *hashtable,void* item)
{
	int index;
	int item_aux = *(int*)item;
	index = item_aux % num_prime;

	while(hashtable->table[index] != NULL)
	{
		if((*(unsigned int*)hashtable->table[index]->item) == (*(unsigned int*)item))
		{
			return (*(unsigned int*)item);
		}
		index++;
	}
	return -100;
}

////////////////////END OF C FILE/////////////////


/*void Testdahash()
{
	Huff_hash *hash = create_hash_table();
	unsigned int i = 1;
	put_hash(hash, &i, 0, 0);
	i = 2;
	put_hash(hash, &i, 0, 0);
	i = 3;
	put_hash(hash, &i, 0, 0);
	i = 4;
	put_hash(hash, &i, 0, 0);
	i = 5;
	put_hash(hash, &i, 0, 0);

	i = 1;
	CU_ASSERT(1 == search(hash, &i));
	i = 2;
	CU_ASSERT(2 == search(hash, &i));
	i = 3;
	CU_ASSERT(3 == search(hash, &i));
	i = 4;
	CU_ASSERT(4 == search(hash, &i));
	i = 5;
	CU_ASSERT(5 == search(hash, &i));
}*/

void Testdahash()
{
	Huff_hash* hash = create_hash_table();

	unsigned int i;
	for(i = 0; i < 256; i++)
	{
		put_hash(hash, &i, 0, 0);
	}
	for(i = 0; i < 256; i++)
	{
		CU_ASSERT(i == search(hash, &i));
	}
}



int main(int argc, char const *argv[])
{
	CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Testdahash_test", 0, 0);

    CU_add_test(suite,"Testdahash_fun",Testdahash);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

	return 0;
}