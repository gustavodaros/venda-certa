#ifndef DOCAS_H
#define DOCAS_H

#include "fila-pacotes.h"

typedef struct Caminhao Caminhao;
typedef struct Docas Docas;

int sortear_capacidade();
Docas *criar_docas();
void carregar_pacote(Docas *docas, Pacote *pacote);
void finalizar_expedicao(Docas *docas);
void imprimir_docas(Docas *docas);
void liberar_docas(Docas *docas);

#endif