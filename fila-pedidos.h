#include "structs.h"
#ifndef FilaPedidos_H
#define FilaPedidos_H

typedef struct Produto {
    int volume;
    int codigo;
    struct Produto *proximo;
} Produto;

typedef struct ListaProdutos {
    Produto *primeiro;
} ListaProdutos;

typedef struct ItemPedido {
    Produto *produto;
    int quantidade;
    struct ItemPedido *proximo;
} ItemPedido;

typedef struct Pedido {
    int codigo;
    char endereco[100];
    int status;
    ItemPedido *itens;
    struct Pedido *proximo;
} Pedido;

typedef struct FilaPedidos {
    Pedido *frente;
    Pedido *tras;
} FilaPedidos;

FilaPedidos *criar_fila_pedidos();
ItemPedido *criar_item_pedido(Produto *produto, int quantidade);
Pedido *criar_pedido(int codigo, char *endereco, int status);
void adicionar_item_pedido(Pedido *pedido, ItemPedido *item);
void enfileirar_pedido(FilaPedidos *fila, Pedido *pedido);
Pedido *desenfileirar_pedido(FilaPedidos *fila);
void liberar_pedido(FilaPedidos *fila, Pedido *pedido);

#endif