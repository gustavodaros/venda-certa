#include <stdio.h>
#include <stdlib.h>
#include "structs.h"

// Anotações:
// Separar as funções do menu.c de modo que a fila de pedidos seja utilizada
// Dá pra manter a pilha funcionando sem desempilhar
// Criar um arquivo .h para todos os arquivos .c auxiliares

void limpar_buffer() 
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpar_tela() 
{
    printf("\033[H\033[2J");
}

void pausar() 
{
    printf("\nPressione [Enter] para continuar\n");
    getchar();
    limpar_tela();
}

void cadastrar_produto(ListaProdutos *lista_produtos) 
{
    int codigo, volume;
    printf("Cadastre seu produto no sistema\n");
    printf("Insira o código do produto:\n");
    scanf("%d", &codigo);
    printf("Insira o volume do produto:\n");
    scanf("%d", &volume);
    
    inserir_lista_produtos(lista_produtos, volume, codigo);
}

void cadastrar_pedido(ListaProdutos *lista_produtos, FilaPedidos *fila_pedidos, FilaPacotes *fila_pacotes) 
{
    int codigo, quantidade, status=0;
    char endereco[100];
    printf("Cadastre seu pedido\n");
    printf("Insira o código do produto que deseja e a quantidade que deseja, respectivamente:\n");
    scanf("%d %d", &codigo, &quantidade);

    Produto *produto = buscar_produto(lista_produtos, codigo);

    printf("Digite o endereço de entrega:\n");
    fgets(endereco, 100, stdin);

    Pedido *pedido = criar_pedido(codigo, endereco, status);
    for(int i=0; i<quantidade;i++)
    {
        ItemPedido *item_pedido = criar_item_pedido(produto, 1);
        adicionar_item_pedido(pedido, item_pedido);
    }
    enfileirar_pedido(fila_pedidos, pedido);

    PilhaPacote *pilha = criar_pilha_pacote();
    ItemPedido *item = pedido->itens;
    while(item != NULL)
    {
        if(!empilhar(pilha, item->produto->volume, item->produto->codigo)) 
        {
            Pacote *pacote = empacotar(pedido, pilha);
            enfileirar_pacotes(fila_pacotes, pacote);
            PilhaPacote *nova_pilha = criar_pilha_pacote();
            pilha = nova_pilha;
        }
        else item = item->proximo;
    }

    if (pilha->topo != NULL)
    {
        Pacote *pacote = empacotar(pedido, pilha);
        enfileirar_pacotes(fila_pacotes, pacote);
    }
}

int main() 
{
    int op;
    ListaProdutos *lista_produtos = criar_lista_produtos();
    FilaPedidos *fila_pedidos = criar_fila_pedidos();
    FilaPacotes *fila_pacotes = criar_fila_pacotes();
    do {
        printf("=== VENDA CERTA ===\n\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Cadastrar Pedido\n");
        printf("0. Encerrar\n\n");

        printf("Informe sua opcao: ");
        scanf("%d", &op);
        limpar_buffer();

        switch (op) {
            case 1:
                cadastrar_produto(lista_produtos);
                pausar();
                break;

            case 2:
                cadastrar_pedido(lista_produtos, fila_pedidos, fila_pacotes);
                pausar();
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opcao invalida!\n");
                pausar();
                break;
        }

    } while (op != 0);

    return 0;
}