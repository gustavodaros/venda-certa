#include "structs.h"
#ifndef Produto_H
#define Produto_H

typedef struct Produto {
    int volume;
    int codigo;
    struct Produto *proximo;
} Produto;

typedef struct ListaProdutos {
    Produto *primeiro;
} ListaProdutos;

ListaProdutos *criar_lista_produtos();
void inserir_lista_produtos(ListaProdutos *lista, int volume, int codigo);
Produto *buscar_produto(ListaProdutos *lista, int codigo);

#endif