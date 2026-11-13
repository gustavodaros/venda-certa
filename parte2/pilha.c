#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

struct NoPilha{
    char codigo[4];
    int volume;
    NoPilha *proximo;
};

struct PilhaPacote{
    NoPilha *topo;
    int volume_total;
    int quantidade;
};

PilhaPacote *criar_pilha_pacote()
{
    PilhaPacote *pilha = (PilhaPacote*)malloc(sizeof(PilhaPacote));
    if (pilha == NULL) return NULL;

    pilha->topo = NULL;
    pilha->volume_total = 0;
    pilha->quantidade = 0;
    return pilha;
}

int empilhar(PilhaPacote *pilha, int volume, char *codigo)
{
    if (pilha == NULL) return 0;

    NoPilha *novo = (NoPilha*)malloc(sizeof(NoPilha));
    if (novo == NULL) return 0;

    novo->volume = volume;
    snprintf(novo->codigo, sizeof(novo->codigo), "%s", codigo);
    novo->proximo = pilha->topo;

    pilha->topo = novo;
    pilha->volume_total += volume;
    pilha->quantidade++;
    return 1;
}

void desempilhar(PilhaPacote *pilha)
{
    if (pilha == NULL || pilha->topo == NULL) return;

    NoPilha *removido = pilha->topo;
    pilha->topo = removido->proximo;
    pilha->volume_total -= removido->volume;
    pilha->quantidade--;

    free(removido);
}

int pilha_vazia(PilhaPacote *pilha)
{
    return pilha == NULL || pilha->topo == NULL;
}

int pilha_volume_total(PilhaPacote *pilha)
{
    return pilha == NULL ? 0 : pilha->volume_total;
}

int pilha_quantidade(PilhaPacote *pilha)
{
    return pilha == NULL ? 0 : pilha->quantidade;
}

void liberar_pilha(PilhaPacote *pilha)
{
    if (pilha == NULL) return;

    while (pilha->topo != NULL) desempilhar(pilha);
    free(pilha);
}
