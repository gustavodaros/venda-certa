#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "produto.h"

struct Produto{
    int volume;
    int codigo;
    Produto *esquerdo;
    Produto *direito;
    Produto *pai;
};

struct AbbProdutos{
    Produto *raiz;
};

AbbProdutos *criar_arvore_produtos()
{
    AbbProdutos *abb = (AbbProdutos*)malloc(sizeof(AbbProdutos));
    if (abb == NULL) return NULL;
    abb->raiz = NULL;
    return abb;
}

Produto *buscar_produto(AbbProdutos *abb, int codigo)
{
    if (abb == NULL) return NULL;

    Produto *atual = abb->raiz;
    while (atual != NULL && atual->codigo != codigo)
    {
        if (codigo < atual->codigo) atual = atual->esquerdo;
        else atual = atual->direito;
    }
    return atual;
}

Produto* criar_produto(int codigo, int volume)
{
    Produto* novo = (Produto*)malloc(sizeof(Produto));
    if(novo == NULL) return NULL;

    novo->codigo = codigo;
    novo->volume = volume;
    novo->esquerdo = novo->direito = novo->pai = NULL;

    return novo;
}

ResultadoProduto inserir_arvore_produtos(AbbProdutos *abb, int volume, int codigo)
{
    if(abb == NULL) return PRODUTO_ERRO;

    if(volume < VOLUME_MIN_PRODUTO || volume > CAPACIDADE_CAIXA) 
    return PRODUTO_VOLUME_INVALIDO;

    if(buscar_produto(abb, codigo) != NULL)
        return PRODUTO_CODIGO_DUPLICADO;

    Produto *novo = criar_produto(codigo, volume);
    if(novo == NULL) return PRODUTO_ERRO;

    Produto* pai = NULL;
    Produto* atual = abb->raiz;

    while(atual != NULL)
    {
        pai = atual;
        if (novo->codigo < atual->codigo) atual = atual->esquerdo;
        else atual = atual->direito;
    }

    novo->pai = pai;

    if(abb->raiz == NULL) abb->raiz = novo;
    else if(novo->codigo < pai->codigo) pai->esquerdo = novo;
    else pai->direito = novo;

    return PRODUTO_OK;
}

int arvore_produtos_vazia(AbbProdutos *abb)
{
    return abb == NULL || abb->raiz == NULL;
}

void imprimir_em_ordem(Produto *raiz)
{
    if (raiz == NULL) return;          

    imprimir_em_ordem(raiz->esquerdo);
    printf("Produto %d | volume %d\n", raiz->codigo, raiz->volume);
    imprimir_em_ordem(raiz->direito);
}

void imprimir_arvore_produtos(AbbProdutos *abb)
{
    if (abb == NULL || abb->raiz == NULL){
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    imprimir_em_ordem(abb->raiz);
}

void liberar_pos_ordem(Produto* raiz)
{
    if(raiz != NULL) 
    {
        liberar_pos_ordem(raiz->esquerdo);
        liberar_pos_ordem(raiz->direito);
        free(raiz);
    }
}

void liberar_arvore_produtos(AbbProdutos *abb)
{
    if(abb == NULL) return;

    liberar_pos_ordem(abb->raiz);
    free(abb);
}

int produto_codigo(Produto *produto){
    return produto == NULL ? 0 : produto->codigo;
}

int produto_volume(Produto *produto){
    return produto == NULL ? 0 : produto->volume;
}
