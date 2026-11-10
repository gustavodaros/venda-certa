#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "fila-pacotes.h"

struct Pacote{
    char codigo[TAM_CODIGO_PACOTE];
    char endereco[TAM_ENDERECO];
    int quantidade_itens;
    int volume_total;
    Pacote *proximo;
};

struct FilaPacotes{
    Pacote *frente;
    Pacote *tras;
};

FilaPacotes *criar_fila_pacotes()
{
    FilaPacotes *fila = (FilaPacotes*)malloc(sizeof(FilaPacotes));
    if (fila == NULL) return NULL;

    fila->frente = NULL;
    fila->tras = NULL;
    return fila;
}

Pacote *empacotar(Pedido *pedido, PilhaPacote *pilha, int sequencia)
{
    if (pedido == NULL || pilha == NULL || pilha_vazia(pilha)) return NULL;

    Pacote *novo = (Pacote*)malloc(sizeof(Pacote));
    if (novo == NULL) return NULL;

    snprintf(novo->codigo, TAM_CODIGO_PACOTE, "PAC-%d-%d", pedido_codigo(pedido), sequencia);
    snprintf(novo->endereco, TAM_ENDERECO, "%s", pedido_endereco(pedido));
    novo->quantidade_itens = pilha_quantidade(pilha);
    novo->volume_total = pilha_volume_total(pilha);
    novo->proximo = NULL;
    return novo;
}

void enfileirar_pacotes(FilaPacotes *fila, Pacote *pacote)
{
    if (fila == NULL || pacote == NULL) return;

    pacote->proximo = NULL;
    if (fila->tras == NULL) fila->frente = pacote;
    else fila->tras->proximo = pacote;
    fila->tras = pacote;
}

Pacote *desenfileirar_pacotes(FilaPacotes *fila)
{
    if (fila == NULL || fila->frente == NULL) return NULL;

    Pacote *removido = fila->frente;
    fila->frente = removido->proximo;
    if (fila->frente == NULL) fila->tras = NULL;

    removido->proximo = NULL;
    return removido;
}

int fila_pacotes_vazia(FilaPacotes *fila)
{
    return fila == NULL || fila->frente == NULL;
}

void imprimir_fila_pacotes(FilaPacotes *fila)
{
    if (fila_pacotes_vazia(fila)){
        printf("Nenhum pacote pronto para expedição.\n");
        return;
    }

    for (Pacote *p = fila->frente; p != NULL; p = p->proximo){
        printf("%s | Endereço: %s | Itens: %d | Volume total: %d\n", p->codigo, p->endereco, p->quantidade_itens, p->volume_total);
    }
}

void liberar_pacote(Pacote *pacote){
    free(pacote);
}

void liberar_fila_pacotes(FilaPacotes *fila)
{
    if (fila == NULL) return;

    Pacote *pacote;
    while ((pacote = desenfileirar_pacotes(fila)) != NULL) liberar_pacote(pacote);

    free(fila);
}

char *pacote_codigo(Pacote *pacote){
    return pacote == NULL ? "" : pacote->codigo;
}

char *pacote_endereco(Pacote *pacote){
    return pacote == NULL ? "" : pacote->endereco;
}

int pacote_quantidade_itens(Pacote *pacote){
    return pacote == NULL ? 0 : pacote->quantidade_itens;
}

int pacote_volume_total(Pacote *pacote){
    return pacote == NULL ? 0 : pacote->volume_total;
}
