#ifndef PILHA_H
#define PILHA_H

typedef struct PilhaPacote PilhaPacote;

PilhaPacote *criar_pilha_pacote(void);
int empilhar(PilhaPacote *pilha, int volume, int codigo); 
void desempilhar(PilhaPacote *pilha);                      
int pilha_vazia(PilhaPacote *pilha);
int pilha_volume_total(PilhaPacote *pilha);
int pilha_quantidade(PilhaPacote *pilha);
void liberar_pilha(PilhaPacote *pilha);

#endif
