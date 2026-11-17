#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config.h"
#include "produto.h"

struct Produto{
    int volume;
    char codigo[4];
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

Produto *buscar_produto(AbbProdutos *abb, char *codigo)
{
    if (abb == NULL || codigo == NULL) return NULL;

    Produto *atual = abb->raiz;
    while (atual != NULL)
    {
        int cmp = strcmp(codigo, atual->codigo);
        if (cmp == 0) return atual;

        if (cmp < 0) atual = atual->esquerdo;
        else atual = atual->direito;
    }
    return NULL;
}

static Produto *criar_produto(char *codigo, int volume)
{
    Produto *novo = (Produto*)malloc(sizeof(Produto));
    if(novo == NULL) return NULL;

    snprintf(novo->codigo, sizeof(novo->codigo), "%s", codigo);
    novo->volume = volume;
    novo->esquerdo = novo->direito = novo->pai = NULL;

    return novo;
}

ResultadoProduto inserir_arvore_produtos(AbbProdutos *abb, int volume, char *codigo)
{
    if(abb == NULL) 
        return PRODUTO_ERRO;
    if(!codigo_valido(codigo)) 
        return PRODUTO_CODIGO_INVALIDO;
    if(volume < VOLUME_MIN_PRODUTO || volume > CAPACIDADE_CAIXA)
        return PRODUTO_VOLUME_INVALIDO;
    if(buscar_produto(abb, codigo) != NULL)
        return PRODUTO_CODIGO_DUPLICADO;

    Produto *novo = criar_produto(codigo, volume);
    if(novo == NULL) return PRODUTO_ERRO;

    Produto *pai = NULL;
    Produto *atual = abb->raiz;

    while(atual != NULL)
    {
        pai = atual;
        if(strcmp(novo->codigo, atual->codigo) < 0) atual = atual->esquerdo;
        else atual = atual->direito;
    }
    novo->pai = pai;

    if(abb->raiz == NULL) abb->raiz = novo;
    else if(strcmp(novo->codigo, pai->codigo) < 0) pai->esquerdo = novo;
    else pai->direito = novo;

    return PRODUTO_OK;
}

int codigo_valido(char *codigo)
{
    return codigo != NULL &&
           strlen(codigo) == 3 &&
           isalpha((unsigned char)codigo[0]) &&
           isdigit((unsigned char)codigo[1]) &&
           isdigit((unsigned char)codigo[2]);
}

int arvore_produtos_vazia(AbbProdutos *abb)
{
    return abb == NULL || abb->raiz == NULL;
}

static void imprimir_em_ordem(Produto *raiz)
{
    if (raiz == NULL) return;          

    imprimir_em_ordem(raiz->esquerdo);
    printf("Produto: %s | volume: %d\n", raiz->codigo, raiz->volume);
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

static void liberar_pos_ordem(Produto* raiz)
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

static Produto *minimo(Produto *produto)
{
    Produto *atual = produto;

    while (atual && atual->esquerdo != NULL) atual = atual->esquerdo;

    return atual;
}

static Produto *sucessor(Produto *atual)
{
    if (atual->direito != NULL) return minimo(atual->direito);

    Produto *ancestral = atual->pai;
    while (ancestral != NULL && atual == ancestral->direito)
    {
        atual = ancestral;
        ancestral = ancestral->pai;
    }
    return ancestral;
}

static void remover_folha(AbbProdutos *abb, Produto *produto)
{
    if(produto == NULL) return;

    if(produto->pai == NULL) abb->raiz = NULL;
    else if(produto->pai->esquerdo == produto) produto->pai->esquerdo = NULL;
    else if(produto->pai->direito == produto) produto->pai->direito = NULL;

    free(produto);
}

static void remover_produto_um_filho(AbbProdutos *abb, Produto *produto)
{
    if(produto == NULL) return;

    Produto *filho = (produto->esquerdo != NULL) ? produto->esquerdo : produto->direito;

    if(produto->pai == NULL) abb->raiz = filho;
    else if(produto->pai->direito == produto) produto->pai->direito = filho;
    else if(produto->pai->esquerdo == produto) produto->pai->esquerdo = filho; 
    filho->pai = produto->pai;

    free(produto);
}

static void remover_produto_dois_filhos(AbbProdutos *abb, Produto *produto)
{
    if(produto == NULL) return;

    Produto *suc = sucessor(produto);
    if(suc->pai != produto)
    {
        suc->pai->esquerdo = suc->direito;
        if(suc->direito != NULL) suc->direito->pai = suc->pai;

        suc->direito = produto->direito;
        suc->direito->pai = suc;
    }

    if(produto->pai == NULL) abb->raiz = suc;
    else if(produto->pai->esquerdo == produto) produto->pai->esquerdo = suc;
    else produto->pai->direito = suc;
    suc->pai = produto->pai;

    suc->esquerdo = produto->esquerdo;
    suc->esquerdo->pai = suc;

    free(produto);
}

void remover_produto(AbbProdutos *abb, Produto *produto)
{
    if(abb == NULL || produto == NULL) return;

    if(produto->esquerdo == NULL && produto->direito == NULL) remover_folha(abb, produto);
    else if(produto->esquerdo == NULL || produto->direito == NULL) remover_produto_um_filho(abb, produto);
    else remover_produto_dois_filhos(abb, produto);
}

char *produto_codigo(Produto *produto){
    return produto == NULL ? "" : produto->codigo;
}

int produto_volume(Produto *produto){
    return produto == NULL ? 0 : produto->volume;
}
