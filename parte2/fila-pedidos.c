#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "fila-pedidos.h"

struct ItemPedido{
    Produto *produto;
    int quantidade;
    ItemPedido *proximo;
};

struct Pedido{
    int codigo;
    char endereco[TAM_ENDERECO];
    int status;
    ItemPedido *itens;
    ItemPedido *ultimo_item;
    Pedido *proximo;
    int prioridade;
};

struct FilaPedidos{
    Pedido *frente;
    Pedido *tras;
};

FilaPedidos *criar_fila_pedidos()
{
    FilaPedidos *fila = (FilaPedidos*)malloc(sizeof(FilaPedidos));
    if (fila == NULL) return NULL;

    fila->frente = NULL;
    fila->tras = NULL;
    return fila;
}

ItemPedido *criar_item_pedido(Produto *produto, int quantidade)
{
    if (produto == NULL || quantidade <= 0) return NULL;

    ItemPedido *novo = (ItemPedido*)malloc(sizeof(ItemPedido));
    if (novo == NULL) return NULL;

    novo->produto = produto;
    novo->quantidade = quantidade;
    novo->proximo = NULL;
    return novo;
}

Pedido *criar_pedido(int codigo, char *endereco, int status, int prioridade)
{
    if (endereco == NULL) return NULL;

    Pedido *novo = (Pedido*)malloc(sizeof(Pedido));
    if (novo == NULL) return NULL;

    novo->codigo = codigo;
    snprintf(novo->endereco, TAM_ENDERECO, "%s", endereco);
    novo->status = status;
    novo->itens = NULL;
    novo->ultimo_item = NULL;
    novo->proximo = NULL;
    novo->prioridade = prioridade;
    return novo;
}

int adicionar_item_pedido(Pedido *pedido, ItemPedido *item)
{
    if (pedido == NULL || item == NULL) return 0;

    item->proximo = NULL;
    if (pedido->itens == NULL) pedido->itens = item;
    else pedido->ultimo_item->proximo = item;
    pedido->ultimo_item = item;
    return 1;
}

void enfileirar_pedido(FilaPedidos *fila, Pedido *pedido)
{
     if (fila == NULL || pedido == NULL) return;

    pedido->proximo = NULL;
    if (fila->tras == NULL) fila->frente = pedido;
    else fila->tras->proximo = pedido;
    fila->tras = pedido;
}

Pedido *desenfileirar_pedido(FilaPedidos *fila)
{
    if (fila == NULL || fila->frente == NULL) return NULL;

    Pedido *removido = fila->frente;
    fila->frente = removido->proximo;
    if (fila->frente == NULL) fila->tras = NULL;

    removido->proximo = NULL;
    return removido;
}

int fila_pedidos_vazia(FilaPedidos *fila)
{
    return fila == NULL || fila->frente == NULL;
}

char *texto_status(int status)
{
    switch (status){
        case PEDIDO_AGUARDANDO_SEPARACAO: return "Aguardando separação";
        case PEDIDO_EMPACOTADO: return "Empacotado";
        default: return "Desconhecido";
    }
}

void imprimir_fila_pedidos(FilaPedidos *fila)
{
    if (fila_pedidos_vazia(fila)){
        printf("Nenhum pedido na fila.\n");
        return;
    }

    for (Pedido *p = fila->frente; p != NULL; p = p->proximo)
    {
        printf("Pedido %d | Endereço: %s | Status: %s\n", p->codigo, p->endereco, texto_status(p->status));

        for (ItemPedido *i = p->itens; i != NULL; i = i->proximo) 
        {
            printf("Produto %d (volume %d) x %d\n", produto_codigo(i->produto), produto_volume(i->produto), i->quantidade);
        }
    }
}

void liberar_pedido(Pedido *pedido)
{
    if (pedido == NULL) return;

    ItemPedido *atual = pedido->itens;
    while (atual != NULL)
    {
        ItemPedido *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(pedido);
}

void liberar_fila_pedidos(FilaPedidos *fila)
{
    if (fila == NULL) return;

    Pedido *pedido;
    while ((pedido = desenfileirar_pedido(fila)) != NULL)
        liberar_pedido(pedido);
    free(fila);
}

int pedido_codigo(Pedido *pedido){
    return pedido == NULL ? 0 : pedido->codigo;
}

char *pedido_endereco(Pedido *pedido){
    return pedido == NULL ? "" : pedido->endereco;
}

ItemPedido *pedido_primeiro_item(Pedido *pedido){
    return pedido == NULL ? NULL : pedido->itens;
}

ItemPedido *item_proximo(ItemPedido *item){
    return item == NULL ? NULL : item->proximo;
}

Produto *item_produto(ItemPedido *item){
    return item == NULL ? NULL : item->produto;
}

int item_quantidade(ItemPedido *item){
    return item == NULL ? 0 : item->quantidade;
}

int pedido_prioridade(Pedido *pedido){
    return pedido == NULL ? 0: pedido->prioridade;
}
