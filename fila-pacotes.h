#include "structs.h"
#ifndef FilaPacotes_H
#define FilaPacotes_H

typedef struct Pedido {
    int codigo;
    char endereco[100];
    int status;
    ItemPedido *itens;
    struct Pedido *proximo;
} Pedido;

typedef struct PilhaPacote {
    NoPilha *topo;
    int volume_total;
} PilhaPacote;

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

Pacote *desenfileirar_pacotes(FilaPacotes *fila);
void enfileirar_pacotes(FilaPacotes *fila, Pacote *pacote);
Pacote *empacotar(Pedido *pedido, PilhaPacote *pilha);
FilaPacotes *criar_fila_pacotes();

#endif