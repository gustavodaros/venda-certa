#ifndef FILA_PACOTES_H
#define FILA_PACOTES_H

#include "fila-pedidos.h"
#include "pilha.h"

typedef struct Pacote Pacote;
typedef struct FilaPacotes FilaPacotes;

FilaPacotes *criar_fila_pacotes();
Pacote *empacotar(Pedido *pedido, PilhaPacote *pilha, int sequencia);
void enfileirar_pacotes(FilaPacotes *fila, Pacote *pacote);
Pacote *desenfileirar_pacotes(FilaPacotes *fila);        
int fila_pacotes_vazia(FilaPacotes *fila);
void imprimir_fila_pacotes(FilaPacotes *fila);
void liberar_pacote(Pacote *pacote);
void liberar_fila_pacotes(FilaPacotes *fila);

char *pacote_codigo(Pacote *pacote);
char *pacote_endereco(Pacote *pacote);
int pacote_quantidade_itens(Pacote *pacote);
int pacote_volume_total(Pacote *pacote);

#endif
