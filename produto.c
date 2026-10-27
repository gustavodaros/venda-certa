#include <stdio.h>
#include <stdlib.h>
#include "produto.h"

ListaProdutos *criar_lista_produtos()
{
    ListaProdutos *lista = (ListaProdutos*)malloc(sizeof(ListaProdutos));
    if (lista == NULL) return NULL;
    lista->primeiro = NULL;
    return lista;
}

void inserir_lista_produtos(ListaProdutos *lista, int volume, int codigo)
{
    Produto *novo = (Produto*)malloc(sizeof(Produto));
    if(novo == NULL) return;
    novo->volume = volume;
    novo->codigo = codigo;

    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
}

Produto *buscar_produto(ListaProdutos *lista, int codigo)
{
    Produto *atual = lista->primeiro;
    while(atual != NULL)
    {
        if(atual->codigo == codigo) return atual;

        atual = atual->proximo;
    }
    return NULL;
}