#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila-pacotes.h"

FilaPacotes *criar_fila_pacotes()
{
    FilaPacotes *fila = (FilaPacotes*)malloc(sizeof(FilaPacotes));
    if(fila == NULL) return NULL;
    fila->frente = NULL;
    fila->tras = NULL;
    return fila;
}

Pacote *empacotar(Pedido *pedido, PilhaPacote *pilha)
{
    if (pedido == NULL || pilha == NULL || pilha->topo == NULL) return NULL;

    Pacote *novo = (Pacote*)malloc(sizeof(Pacote));
    if(novo == NULL) return;

    novo->codigo = pilha->topo->codigo;
    strcpy(novo->endereco, pedido->endereco);
    novo->volume_total = pilha->volume_total;
    novo->proximo = NULL;

    return novo;
}

void enfileirar_pacotes(FilaPacotes *fila, Pacote *pacote)
{
    if(fila == NULL || pacote == NULL) return;

    if(fila->frente == NULL) fila->frente = pacote;
    else fila->tras->proximo = pacote;

    fila->tras = pacote;
}

Pacote *desenfileirar_pacotes(FilaPacotes *fila)
{
    if(fila == NULL || fila->frente == NULL) return NULL;

    Pacote *removido = fila->frente;
    fila->frente = removido->proximo;
    if(fila->frente == NULL) fila->tras = NULL;

    removido->proximo = NULL;
    return removido;
}