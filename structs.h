#ifndef STRUCTS_H
#define STRUCTS_H

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

typedef struct NoPilha {
    int codigo;
    int volume;
    struct NoPilha *proximo;
} NoPilha;

typedef struct PilhaPacote {
    NoPilha *topo;
    int volume_total;
} PilhaPacote;

typedef struct FilaPedidos {
    Pedido *frente;
    Pedido *tras;
} FilaPedidos;

typedef struct Pacote {
    int codigo;
    char endereco[100];
    int volume_total;
    struct Pacote *proximo;
} Pacote;

typedef struct FilaPacotes {
    Pacote *frente;
    Pacote *tras;
} FilaPacotes;

#endif