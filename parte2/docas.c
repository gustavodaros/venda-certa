#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "docas.h"
#include "fila-pacotes.h"

struct Caminhao{
    int capacidade;
    int usado;
};

struct Docas{
    Caminhao vetor[NUM_DOCAS];
};

int sortear_capacidade()
{
    int capacidade[3] = {CAMINHAO_PEQUENO, CAMINHAO_MEDIO, CAMINHAO_GRANDE};
    return capacidade[rand() % 3];
}

Docas *criar_docas()
{
    Docas *docas = (Docas*)malloc(sizeof(Docas));
    if(docas == NULL) return NULL;

    for(int i = 0; i < NUM_DOCAS; i++)
    {
        docas->vetor[i].capacidade = sortear_capacidade();
        docas->vetor[i].usado = 0;
    }
    return docas;
}

int doca_mais_cheia(Docas *docas)
{
    int j = 0;
    double percentual, p = 0;
    for(int i = 0; i < NUM_DOCAS; i++)
    {
        percentual = (double)docas->vetor[i].usado / docas->vetor[i].capacidade;
        if(percentual > p) 
        {
            p = percentual;
            j = i;
        }
    }
    return j;
}

void sair_caminhao(Docas *docas, int i)
{
    printf("Doca %d: caminhão saiu com %d/%d do seu espaço preenchido.\n",
    i + 1, docas->vetor[i].usado, docas->vetor[i].capacidade);

    docas->vetor[i].capacidade = sortear_capacidade();
    docas->vetor[i].usado = 0;
}

void carregar_pacote(Docas *docas, Pacote *pacote)
{
    if(docas == NULL || pacote == NULL) return;

    int volume = pacote_volume_total(pacote);
    for(int i = 0; i < NUM_DOCAS; i++)
    {
        if(docas->vetor[i].usado + volume <= docas->vetor[i].capacidade)
        {
            docas->vetor[i].usado += volume;
            if(docas->vetor[i].usado == docas->vetor[i].capacidade)
            {
                sair_caminhao(docas, i);
            }
            return;
        }
    }
    int j = doca_mais_cheia(docas);
    sair_caminhao(docas, j);
    carregar_pacote(docas, pacote);

    return;
}

void finalizar_expedicao(Docas *docas)
{
    if(docas == NULL) return;
    for(int i = 0; i < NUM_DOCAS; i++)
    {
        if(docas->vetor[i].usado > 0) sair_caminhao(docas, i);
    }
    printf("Todos os pacotes foram expedidos com sucesso\n");
    return;
}

void imprimir_docas(Docas *docas)
{
    if(docas == NULL) return;

    for(int i = 0; i < NUM_DOCAS; i++)
    {
        printf("Doca %d: %d/%d\n", i + 1, docas->vetor[i].usado, docas->vetor[i].capacidade);
    }
    return;
}

void liberar_docas(Docas *docas)
{
    free(docas);
}