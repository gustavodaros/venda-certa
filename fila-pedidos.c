#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila-pedidos.h"

FilaPedidos *criar_fila_pedidos()
{
    FilaPedidos *fila = (FilaPedidos*)malloc(sizeof(FilaPedidos));
    if(fila == NULL) return NULL;
    fila->frente = NULL;
    fila->tras = NULL;
    return fila;
}

ItemPedido *criar_item_pedido(Produto *produto, int quantidade)
{
    if (produto == NULL) return NULL;

    ItemPedido *novo = (ItemPedido*)malloc(sizeof(ItemPedido));

    if (novo == NULL) return NULL;

    novo->produto = produto;
    novo->quantidade = quantidade;
    novo->proximo = NULL;

    return novo;
}

Pedido *criar_pedido(int codigo, char *endereco, int status)
{
    Pedido *novo = (Pedido*)malloc(sizeof(Pedido));
    if(novo == NULL) return NULL;

    novo->codigo = codigo;
    strcpy(novo->endereco, endereco);
    novo->status = status;
    novo->proximo = NULL;
    novo->itens = NULL;

    return novo;
}

void adicionar_item_pedido(Pedido *pedido, ItemPedido *item)
{
    if(pedido == NULL || item == NULL) return NULL;

    item->proximo = pedido->itens;
    pedido->itens = item;
}

void enfileirar_pedido(FilaPedidos *fila, Pedido *pedido)
{
    if(pedido == NULL) return;
    pedido->proximo = NULL;

    if (fila->tras == NULL) fila->frente = pedido;
    else fila->tras->proximo = pedido;

    fila->tras = pedido;
}

Pedido *desenfileirar_pedido(FilaPedidos *fila)
{
    if(fila == NULL || fila->frente == NULL) return;

    Pedido *removido = fila->frente;
    fila->frente = removido->proximo;
    if(fila->frente == NULL) fila->tras = NULL;

    removido->proximo = NULL;

    return removido;
}