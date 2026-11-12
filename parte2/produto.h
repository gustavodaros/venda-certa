#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct Produto Produto;
typedef struct AbbProdutos AbbProdutos;

typedef enum{
    PRODUTO_OK = 0,
    PRODUTO_ERRO,
    PRODUTO_VOLUME_INVALIDO,
    PRODUTO_CODIGO_DUPLICADO
} ResultadoProduto;

AbbProdutos *criar_arvore_produtos();
ResultadoProduto inserir_arvore_produtos(AbbProdutos *lista, int volume, int codigo);
Produto *criar_produto(int codigo, int volume);
Produto *buscar_produto(AbbProdutos *lista, int codigo);
int arvore_produtos_vazia(AbbProdutos *lista);
void imprimir_em_ordem(Produto *raiz);
void imprimir_arvore_produtos(AbbProdutos *abb);
void liberar_pos_ordem(Produto* raiz);
void liberar_arvore_produtos(AbbProdutos *abb);

int produto_codigo(Produto *produto);
int produto_volume(Produto *produto);

#endif
