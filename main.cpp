#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_PRODUTOS 10
#define MAX_NOME 50

// Struct do produto (objeto)
struct Produto
{
    int codigo;
    char nome[MAX_NOME];
    int quantidade;
    float preco;
};

// Função para salvar o banco de dados em um arquivo
void salvarBanco(const struct Produto estoque[], int *numProdutos)
{
    FILE *arquivo = fopen("estoque.csv", "w"); 
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < *numProdutos; i++)
    {
        fprintf(arquivo, "%d %s %d %.2f\n", estoque[i].codigo, estoque[i].nome, estoque[i].quantidade, estoque[i].preco);
    }

    fclose(arquivo);
}

// Botão 1: Carregar/subir arquivo do Banco
void carregarBanco(struct Produto estoque[], int *numProdutos)
{
    FILE *arquivo = fopen("estoque.csv", "r"); 
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    *numProdutos = 0;
    while (*numProdutos < MAX_PRODUTOS && fscanf(arquivo, "%d %s %d %f", &estoque[*numProdutos].codigo, estoque[*numProdutos].nome, &estoque[*numProdutos].quantidade, &estoque[*numProdutos].preco) == 4)
    {
        (*numProdutos)++;
    }

    fclose(arquivo);
}

// Botão 2: Cadastrar novo produto
void cadastrarProduto(struct Produto estoque[], int *numProdutos)
{
    if (*numProdutos >= MAX_PRODUTOS)
    {
        printf("Limite de produtos atingido.\n");
        return;
    }

    printf("Digite o código do produto: ");
    scanf("%d", &estoque[*numProdutos].codigo);

    printf("Digite o nome do produto: ");
    scanf("%s", &estoque[*numProdutos].nome);

    printf("Digite a quantidade disponível: ");
    scanf("%d", &estoque[*numProdutos].quantidade);

    printf("Digite o preço de venda: ");
    scanf("%f", &estoque[*numProdutos].preco);

    (*numProdutos)++;
    system("cls");
}

// Botão 3: listar todos os produtos
void listarProdutos(const struct Produto estoque[], int *numProdutos)
{
    printf("Lista de Produtos:\n");
    for (int i = 0; i < *numProdutos; i++)
    {
        printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n", estoque[i].codigo, estoque[i].nome, estoque[i].quantidade, estoque[i].preco);
    }
}

// Botão 4: Excluir produto
void excluirProduto(struct Produto estoque[], int *numProdutos)
{
    int troca;

    printf("Digite o código do produto a ser excluído: ");
    scanf("%d", &troca);

    for (int i = 0; i < *numProdutos; i++)
    {
        if (estoque[i].codigo == troca)
        {
            for (int j = i; j < *numProdutos - 1; j++)
            {
                estoque[j] = estoque[j + 1];
            }

            (*numProdutos)--;
            printf("Produto excluído com sucesso.\n");
            return;
            system("cls");
        }
    }
    printf("Produto não encontrado.\n");
    system("cls");
}
// Botão 5: Alterar produto
void alterarProduto(struct Produto estoque[], int *numProdutos)
{
    int troca;

    printf("Digite o código do produto a ser alterado: ");
    scanf("%d", &troca);

    for (int i = 0; i < *numProdutos; i++)
    {
        if (estoque[i].codigo == troca)
        {
            printf("Digite o novo código do produto: ");
            scanf("%d", &estoque[i].codigo);

            printf("Digite o novo nome do produto: ");
            scanf("%s", &estoque[i].nome);

            printf("Digite a nova quantidade disponível: ");
            scanf("%d", &estoque[i].quantidade);

            printf("Digite o novo preço de venda: ");
            scanf("%f", &estoque[i].preco);

            printf("Produto alterado com sucesso.\n");
            system ("cls");
            return;
        }
    }

    printf("Produto não encontrado.\n");
}
int main()
{
    setlocale(LC_ALL, "");

    struct Produto estoque[MAX_PRODUTOS];
    int numProdutos = 0;
    int opcao;

    do
    {
        printf("\nMenu:\n");
        printf("1 - Carregar Banco de Dados\n");
        printf("2 - Cadastrar produto\n");
        printf("3 - Listar produtos\n");
        printf("4 - Excluir produto\n");
        printf("5 - Alterar produto\n");
        printf("0 - Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            carregarBanco(estoque, &numProdutos);
            system("cls");
            break;

        case 2:
            cadastrarProduto(estoque, &numProdutos);
            salvarBanco(estoque, &numProdutos);
            system("cls");
            break;

        case 3:
            listarProdutos(estoque, &numProdutos);
            break;

        case 4:
            excluirProduto(estoque, &numProdutos);
            break;

        case 5:
            alterarProduto(estoque, &numProdutos);
            break;

        case 0:
            printf("Saindo do programa.\n");
            break;

        default:
            printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
