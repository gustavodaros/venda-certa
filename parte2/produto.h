#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct Produto Produto;
typedef struct AbbProdutos AbbProdutos;

typedef enum{
    PRODUTO_OK = 0,
    PRODUTO_ERRO,
    PRODUTO_VOLUME_INVALIDO,
    PRODUTO_CODIGO_DUPLICADO,
    PRODUTO_CODIGO_INVALIDO
} ResultadoProduto;

AbbProdutos *criar_arvore_produtos();
ResultadoProduto inserir_arvore_produtos(AbbProdutos *lista, int volume, char *codigo);
Produto *buscar_produto(AbbProdutos *lista, char *codigo);
int codigo_valido(char *codigo);
int arvore_produtos_vazia(AbbProdutos *lista);
void imprimir_arvore_produtos(AbbProdutos *abb);
void liberar_arvore_produtos(AbbProdutos *abb);
void remover_produto(AbbProdutos *abb, Produto *produto);

char *produto_codigo(Produto *produto);
int produto_volume(Produto *produto);

#endif
