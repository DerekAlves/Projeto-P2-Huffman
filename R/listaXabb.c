#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/////////////////---------LISTA--------////////////////


typedef struct node_
{
	int value;
	struct Node *next; //ponteiro de um nó
	struct Node *previous; //ponteiro de um nó	
}Node;

typedef struct linkedlist_
{
	int size;
	Node *front;
	Node *back;
}LinkedList;

Node *new_node (int x)
{
	Node *node = (Node*) malloc(sizeof(Node));
	node->value = x;
	node->next = NULL;
	node->previous = NULL;
	return node; 
}

LinkedList *new_list ()
{
	LinkedList *list = (LinkedList*) malloc(sizeof(LinkedList));
	list->size = 0;
	list->front = NULL;
	list->back = NULL;
	return list;
}

int isEmpty(LinkedList *list)
{
	if(list == NULL) return 1;
	return(list->size == 0);
}

int search_list(Node *head, int item)
{
	int cont = 0;
	//printf("SSSS\n");
	while(head != NULL)
	{
		//printf("####\n");
		if(head->value == item)
		{	
			cont++;
			return cont;
		}
		cont++;
		head = head->next;
	}
}

void add_front(LinkedList *list, int value)
{
	Node *node = new_node(value);
	if(list->size == 0)
	{
		list->size = 1;
		list->front = list->back = node;
	}
	else
	{
		node->next = list->front;
		list->front->previous = node;
		list->front = node;
		list->size++;
	}
}

void add_back (LinkedList *list, int value)
{
	Node *node = new_node(value);
	if(list->size == 0)
	{
		list->size = 1;
		list->front = list->back = node;
	}
	else 
	{
		node->previous = list->back;
		list->back->next = node;
		list->back = node;
		list->size++;
	}
}

void print_crescente (LinkedList *list)
{
	if(list == NULL || list->size == 0) return;
	Node *node = list->front;
	while(node != NULL)
	{
		printf("%d\n", node->value);
		node = node->next;
	}
	puts("");
}

void print_decrescente (LinkedList *list)
{
	if(list == NULL || list->size == 0) return;
	Node *node = list->back;
	while(node != NULL)
	{
		printf("%d ", node->value);
		node = node->previous;
	}
	puts("");
}

void remove_elemento (LinkedList *list, int value)
{
	if(list == NULL || list->size == 0) return;
	Node *aux;
	Node *current;
	if(list->front->value == value)
	{
		aux = list->front;
		list->front = list->front->next;
		list->front->previous = NULL;
		list->size--;
		free(aux);
	}
	else if(list->back->value == value)
	{
		aux = list->back;
		list->back = list->back->previous;
		list->back->next = NULL;
		list->size--;
		free(aux);
	}
	else 
	{
		current = list->front;
		while(current != NULL)
		{
			if(current->value == value)
			{
				Node *nodeprevious = current->previous;
				Node *nodenext = current->next;
				nodeprevious->next = nodenext;
				nodenext->previous = nodeprevious;
				list->size--;
				free(current);
				return;
			}
			current = current->next;
		}
	}
}


/////////////////---------ARVORE--------////////////////

typedef struct binary_tree 
{
	int item;
	struct binary_tree *left;
	struct binary_tree *right;
}Binary_tree;

Binary_tree *create_binary(int item, Binary_tree *left, Binary_tree *right)
{
	Binary_tree *bt = (Binary_tree*) malloc(sizeof(Binary_tree));
	bt->item = item;
	bt->left = left;
	bt->right = right;
	return bt;
}

Binary_tree *add(Binary_tree *bt, int item)
{
	if (bt == NULL) 
	{
		bt = create_binary(item, NULL, NULL);
	} 
	else if (bt->item > item) 
	{
		bt->left = add(bt->left, item);
	} 
	else 
	{
		bt->right = add(bt->right, item);
	}
	return bt;
}

void search_tree(Binary_tree *bt, int item, int comparacoes[])
{
	if ((bt == NULL) || (bt->item == item)) 
	{
		comparacoes[0]++;
	} 
	else if (bt->item > item) 
	{
		comparacoes[0]++;
		return search_tree(bt->left, item, comparacoes);
	} 
	else 
	{
		comparacoes[0]++;
		return search_tree(bt->right, item, comparacoes);
	}
}

void print_pre_order(Binary_tree *bt)
{
	printf(" (");
	if (!(bt == NULL)) 
	{
		printf(" %d ", bt->item);
		print_pre_order(bt->left);
		print_pre_order(bt->right);
	}
	printf(") ");
}

int main()
{
	int elements[1000000];
	srand(time(NULL));
	int i, cont, sorteado, comparacoes_list, comparacoes_tree[2];
	printf("Digite a quantidade de elementos que irá compor a lista...\n");
	scanf("%d", &cont);
	LinkedList *list = new_list();
	Binary_tree *bt = NULL;
	for(i = 0; i < cont; i++)
	{
		elements[i] = rand() % 5000;
		add_back(list, elements[i]);  //   add list
		bt = add(bt, elements[i]);    //   add tree
	}
	/*
	for(i = 0; i < cont; i++)
	{
		add_back(list, elements[i]);  //   add list
		bt = add(bt, elements[i]);    //   add tree
	}*/
	printf("\n");
	
	printf("Printando lista:\n");
	print_crescente(list);
	
	printf("Printando arvore de busca bin:\n");
	print_pre_order(bt);
	
	printf("\n");
	printf("\n");
	//int numbers[cont], passos_lista[cont], passos_tree[cont];
	FILE *arquivo = fopen("Graficos.txt", "w");
	for(i = 0; i <cont; i++)
	{
		//i = rand() % cont;
		sorteado = elements[i];
		fprintf(arquivo, "%d\n", sorteado);
		//numbers[i] = sorteado;
		printf("numero sorteado: %d\n", sorteado);
		printf("\n");
		comparacoes_list = search_list(list->front, sorteado);
		fprintf(arquivo, "%d\n", comparacoes_list);
		//passos_lista[i] = comparacoes_list;
		printf("numero de comparacoes Lista: %d\n", comparacoes_list);
		printf("\n");
		search_tree(bt, sorteado, comparacoes_tree);
		fprintf(arquivo, "%d\n", comparacoes_tree[0]);
		//passos_tree[i] = comparacoes_tree[0];
		printf("numero de comparacoes Binary Tree: %d\n", comparacoes_tree[0]);
		comparacoes_list = 0;
		comparacoes_tree[0] = 0;
		printf("---------------------------------------------------------------\n");
	}
	return 0;
}