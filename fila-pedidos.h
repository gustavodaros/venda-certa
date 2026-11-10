#ifndef FILA_PEDIDOS_H
#define FILA_PEDIDOS_H

#include "produto.h"

typedef struct ItemPedido ItemPedido;
typedef struct Pedido Pedido;
typedef struct FilaPedidos FilaPedidos;

typedef enum{
    PEDIDO_AGUARDANDO_SEPARACAO = 0,
    PEDIDO_EMPACOTADO = 1
}StatusPedido;

FilaPedidos *criar_fila_pedidos(void);
ItemPedido *criar_item_pedido(Produto *produto, int quantidade);
Pedido *criar_pedido(int codigo, const char *endereco, int status);
int adicionar_item_pedido(Pedido *pedido, ItemPedido *item);  
void enfileirar_pedido(FilaPedidos *fila, Pedido *pedido);
Pedido *desenfileirar_pedido(FilaPedidos *fila);             
int fila_pedidos_vazia(const FilaPedidos *fila);
void imprimir_fila_pedidos(const FilaPedidos *fila);
void liberar_pedido(Pedido *pedido);
void liberar_fila_pedidos(FilaPedidos *fila);

int pedido_codigo(const Pedido *pedido);
char *pedido_endereco(const Pedido *pedido);
ItemPedido *pedido_primeiro_item(const Pedido *pedido);
ItemPedido *item_proximo(const ItemPedido *item);
Produto *item_produto(const ItemPedido *item);
int item_quantidade(const ItemPedido *item);

#endif
