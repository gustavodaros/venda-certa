#ifndef PRODUTO_H
#define PRODUTO_H

typedef struct Produto Produto;
typedef struct ListaProdutos ListaProdutos;

typedef enum{
    PRODUTO_OK = 0,
    PRODUTO_ERRO,
    PRODUTO_VOLUME_INVALIDO,
    PRODUTO_CODIGO_DUPLICADO
} ResultadoProduto;

ListaProdutos *criar_lista_produtos();
ResultadoProduto inserir_lista_produtos(ListaProdutos *lista, int volume, int codigo);
Produto *buscar_produto(ListaProdutos *lista, int codigo);
int lista_produtos_vazia(ListaProdutos *lista);
void imprimir_lista_produtos(ListaProdutos *lista);
void liberar_lista_produtos(ListaProdutos *lista);

int produto_codigo(Produto *produto);
int produto_volume(Produto *produto);

#endif
