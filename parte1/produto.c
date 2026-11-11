#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "produto.h"

struct Produto{
    int volume;
    int codigo;
    Produto *proximo;
};

struct ListaProdutos{
    Produto *primeiro;
};

ListaProdutos *criar_lista_produtos()
{
    ListaProdutos *lista = (ListaProdutos*)malloc(sizeof(ListaProdutos));

    if (lista == NULL) return NULL;
    lista->primeiro = NULL;
    return lista;
}

Produto *buscar_produto(ListaProdutos *lista, int codigo)
{
    if (lista == NULL) return NULL;

    Produto *atual = lista->primeiro;
    while (atual != NULL)
    {
        if (atual->codigo == codigo) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

ResultadoProduto inserir_lista_produtos(ListaProdutos *lista, int volume, int codigo)
{
    if (lista == NULL) return PRODUTO_ERRO;

    if (volume < VOLUME_MIN_PRODUTO || volume > CAPACIDADE_CAIXA)
        return PRODUTO_VOLUME_INVALIDO;

    if (buscar_produto(lista, codigo) != NULL)
        return PRODUTO_CODIGO_DUPLICADO;

    Produto *novo = (Produto*)malloc(sizeof(Produto));
    if (novo == NULL) return PRODUTO_ERRO;

    novo->volume = volume;
    novo->codigo = codigo;
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;

    return PRODUTO_OK;
}

int lista_produtos_vazia(ListaProdutos *lista)
{
    return lista == NULL || lista->primeiro == NULL;
}

void imprimir_lista_produtos(ListaProdutos *lista)
{
    if (lista_produtos_vazia(lista)){
        printf("Nenhum produto cadastrado\n");
        return;
    }

    for (Produto *atual = lista->primeiro; atual != NULL; atual = atual->proximo)
    {
        printf("Produto %d | volume %d\n", atual->codigo, atual->volume);
    }
}

void liberar_lista_produtos(ListaProdutos *lista)
{
    if (lista == NULL) return;

    Produto *atual = lista->primeiro;
    while (atual != NULL)
    {
        Produto *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(lista);
}

int produto_codigo(Produto *produto){
    return produto == NULL ? 0 : produto->codigo;
}

int produto_volume(Produto *produto){
    return produto == NULL ? 0 : produto->volume;
}
