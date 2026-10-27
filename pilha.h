#include "structs.h"
#ifndef Pilha_H
#define Pilha_H

typedef struct NoPilha {
    int codigo;
    int volume;
    struct NoPilha *proximo;
} NoPilha;

typedef struct PilhaPacote {
    NoPilha *topo;
    int volume_total;
} PilhaPacote;

PilhaPacote *criar_pilha_pacote();
void desempilhar(PilhaPacote *pilha);
int empilhar(PilhaPacote *pilha, int volume, int codigo);

#endif