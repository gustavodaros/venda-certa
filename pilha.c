#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

PilhaPacote *criar_pilha_pacote()
{
    PilhaPacote *pilha = (PilhaPacote*)malloc(sizeof(PilhaPacote));
    if(pilha != NULL)
    {
        pilha->topo = NULL;
        pilha->volume_total = 0;
    }
    return pilha;
}

void desempilhar(PilhaPacote *pilha)
{
    if(pilha->topo == NULL) return;
    NoPilha *removido = pilha->topo;

    pilha->topo = removido->proximo;
    pilha->volume_total -= removido->volume;
    removido->proximo = NULL;

    free(removido);
}

int empilhar(PilhaPacote *pilha, int volume, int codigo)
{
    if(pilha->volume_total + volume > 10) return 0;

    NoPilha *novo = (NoPilha*)malloc(sizeof(NoPilha));
    if(novo == NULL) return;
    novo->volume = volume;
    novo->codigo = codigo;

    novo->proximo = pilha->topo;
    pilha->topo = novo;
    pilha->volume_total += volume;
    
    return 1;
}

