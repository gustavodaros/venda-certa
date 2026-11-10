#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "config.h"
#include "produto.h"
#include "pilha.h"
#include "fila-pedidos.h"
#include "fila-pacotes.h"

int proximo_codigo_pedido = 1001;

void limpar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limpar_tela()
{
    printf("\033[H\033[2J");
}

int ler_linha(char *buffer, size_t tamanho)
{
    if (fgets(buffer, (int)tamanho, stdin) == NULL)
    {
        buffer[0] = '\0';
        return 0;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
    else limpar_buffer();

    return 1;
}

int ler_inteiro(char *mensagem, int *valor)
{
    char buffer[32];
    char *fim;

    printf("%s", mensagem);
    if (!ler_linha(buffer, sizeof(buffer)) || buffer[0] == '\0') return 0;

    long numero = strtol(buffer, &fim, 10);
    if (*fim != '\0' || numero < INT_MIN || numero > INT_MAX) return 0;

    *valor = (int)numero;
    return 1;
}

void pausar()
{
    char descarte[8];
    printf("\nPressione [Enter] para continuar\n");
    ler_linha(descarte, sizeof(descarte));
    limpar_tela();
}

void cadastrar_produto(ListaProdutos *lista_produtos)
{
    int codigo, volume;

    printf("Cadastre seu produto no sistema\n");

    if(!ler_inteiro("Insira o código do produto: ", &codigo))
    {
        printf("Código inválido\n");
        return;
    }
    if(!ler_inteiro("Insira o volume do produto (1 a 10): ", &volume))
    {
        printf("Volume inválido\n");
        return;
    }

    switch(inserir_lista_produtos(lista_produtos, volume, codigo))
    {
        case PRODUTO_OK:
            printf("Produto %d cadastrado com sucesso!\n", codigo);
            break;
        case PRODUTO_VOLUME_INVALIDO:
            printf("Volume inválido, o volume deve estar entre 1 e %d\n", CAPACIDADE_CAIXA);
            break;
        case PRODUTO_CODIGO_DUPLICADO:
            printf("Já existe um produto com o código %d\n", codigo);
            break;
        default:
            printf("Erro ao cadastrar o produto\n");
            break;
    }
}

int ler_item_pedido(ListaProdutos *lista_produtos, Pedido *pedido)
{
    int codigo, quantidade;

    if(!ler_inteiro("Código do produto: ", &codigo)){
        printf("Código inválido\n");
        return 0;
    }

    Produto *produto = buscar_produto(lista_produtos, codigo);
    if(produto == NULL){
        printf("Produto %d não encontrado no catálogo\n", codigo);
        return 0;
    }

    if(!ler_inteiro("Quantidade: ", &quantidade) || quantidade <= 0){
        printf("Quantidade inválida\n");
        return 0;
    }

    ItemPedido *item = criar_item_pedido(produto, quantidade);
    if(item == NULL)
    {
        printf("Erro ao criar o item do pedido.\n");
        return 0;
    }
    adicionar_item_pedido(pedido, item);
    return 1;
}

void cadastrar_pedido(ListaProdutos *lista_produtos, FilaPedidos *fila_pedidos)
{
    char endereco[TAM_ENDERECO];
    int itens_adicionados = 0;
    int adicionar_mais = 0;

    printf("Cadastre seu pedido\n");
    if(lista_produtos_vazia(lista_produtos)){
        printf("Nenhum produto cadastrado. Cadastre um produto antes de criar pedidos.\n");
        return;
    }

    printf("Digite o endereço de entrega:\n");
    ler_linha(endereco, sizeof(endereco));
    if(endereco[0] == '\0'){
        printf("O endereço de entrega não pode ser vazio\n");
        return;
    }

    Pedido *pedido = criar_pedido(proximo_codigo_pedido, endereco, PEDIDO_AGUARDANDO_SEPARACAO);
    if(pedido == NULL){
        printf("Erro ao criar o pedido\n");
        return;
    }

    do{
        if (ler_item_pedido(lista_produtos, pedido)) itens_adicionados++;

        adicionar_mais = 0;
        ler_inteiro("Adicionar outro item? (1 = sim, 0 = nao)", &adicionar_mais);

    }while(adicionar_mais == 1);

    if(itens_adicionados == 0){
        printf("Pedido sem itens, cadastro cancelado\n");
        liberar_pedido(pedido);
        return;
    }

    enfileirar_pedido(fila_pedidos, pedido);
    printf("Pedido %d cadastrado e colocado na fila de separação\n", proximo_codigo_pedido);
    proximo_codigo_pedido++;
}

int fechar_pacote(Pedido *pedido, PilhaPacote *pilha,int sequencia, FilaPacotes *fila_pacotes)
{
    Pacote *pacote = empacotar(pedido, pilha, sequencia);
    if (pacote == NULL) return 0;

    enfileirar_pacotes(fila_pacotes, pacote);
    return 1;
}

void empilhar_empacotar(FilaPedidos *fila_pedidos, FilaPacotes *fila_pacotes)
{
    if(fila_pedidos_vazia(fila_pedidos)){
        printf("Não há pedidos aguardando separação\n");
        return;
    }

    PilhaPacote *pilha = criar_pilha_pacote();
    if(pilha == NULL){
        printf("Erro ao iniciar o pacote\n");
        return;
    }

    Pedido *pedido = desenfileirar_pedido(fila_pedidos);
    int sequencia = 1;
    int ok = 1;

    for (ItemPedido *item = pedido_primeiro_item(pedido); ok && item != NULL; item = item_proximo(item))
    {
        int volume = produto_volume(item_produto(item));
        int codigo = produto_codigo(item_produto(item));

        for(int unidade = 0; ok && unidade < item_quantidade(item); unidade++)
        {
            if (!empilhar(pilha, volume, codigo))
            {
                ok = 0;
                break;
            }

            if (pilha_volume_total(pilha) > CAPACIDADE_CAIXA)
            {
                desempilhar(pilha);
                if (!fechar_pacote(pedido, pilha, sequencia, fila_pacotes))
                {
                    ok = 0;
                    break;
                }
                sequencia++;
                liberar_pilha(pilha);
                pilha = criar_pilha_pacote();

                if (pilha == NULL || !empilhar(pilha, volume, codigo)){
                    ok = 0;
                    break;
                }
            }
        }
    }

    if(ok && !pilha_vazia(pilha))
    {
        if(fechar_pacote(pedido, pilha, sequencia, fila_pacotes)) sequencia++;
        else ok = 0;
    }

    if(ok) printf("Pedido %d separado e empacotado em %d pacote(s)\n", pedido_codigo(pedido), sequencia - 1);
    else printf("Erro ao empacotar o pedido %d\n", pedido_codigo(pedido));

    liberar_pilha(pilha);
    liberar_pedido(pedido);
}

int main()
{
    int op = -1;
    ListaProdutos *lista_produtos = criar_lista_produtos();
    FilaPedidos *fila_pedidos = criar_fila_pedidos();
    FilaPacotes *fila_pacotes = criar_fila_pacotes();

    if (lista_produtos == NULL || fila_pedidos == NULL || fila_pacotes == NULL)
    {
        printf("Erro ao inicializar o sistema\n");
        liberar_fila_pacotes(fila_pacotes);
        liberar_fila_pedidos(fila_pedidos);
        liberar_lista_produtos(lista_produtos);
        return 1;
    }

    do{
        printf("=== VENDA CERTA ===\n\n");
        printf("1. Cadastrar produto\n");
        printf("2. Cadastrar pedido\n");
        printf("3. Separar e empacotar próximo pedido\n");
        printf("4. Listar produtos\n");
        printf("5. Listar pedidos na fila\n");
        printf("6. Listar pacotes prontos\n");
        printf("0. Encerrar\n\n");

        if (!ler_inteiro("Informe sua opcao: ", &op)) op = feof(stdin) ? 0 : -1;

        switch (op) {
            case 1:
                cadastrar_produto(lista_produtos);
                pausar();
                break;

            case 2:
                cadastrar_pedido(lista_produtos, fila_pedidos);
                pausar();
                break;

            case 3:
                empilhar_empacotar(fila_pedidos, fila_pacotes);
                pausar();
                break;

            case 4:
                imprimir_lista_produtos(lista_produtos);
                pausar();
                break;

            case 5:
                imprimir_fila_pedidos(fila_pedidos);
                pausar();
                break;

            case 6:
                imprimir_fila_pacotes(fila_pacotes);
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

    }while (op != 0);

    liberar_fila_pedidos(fila_pedidos);
    liberar_fila_pacotes(fila_pacotes);
    liberar_lista_produtos(lista_produtos);

    return 0;
}
