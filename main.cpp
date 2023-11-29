#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_PRODUTOS 100
#define MAX_NOME 50



// Definição da struct para o produto
struct Produto {
    int codigo;
    char nome[MAX_NOME];
    int quantidade;
    float preco;
};

// Função para carregar o banco de dados a partir de um arquivo
void carregarBanco(struct Produto estoque[], int *numProdutos) {
    FILE *arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    *numProdutos = 0;
    while (fscanf(arquivo, "%d %s %d %f", &estoque[*numProdutos].codigo, estoque[*numProdutos].nome,
           &estoque[*numProdutos].quantidade, &estoque[*numProdutos].preco) == 4) {
        (*numProdutos)++;
        if (*numProdutos >= MAX_PRODUTOS) {
            printf("Limite de produtos atingido.\n");
            break;
        }
    }

    fclose(arquivo);
}

// Função para salvar o banco de dados em um arquivo
void salvarBanco(const struct Produto estoque[], int numProdutos) {
    FILE *arquivo = fopen("estoque.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < numProdutos; i++) {
        fprintf(arquivo, "%d %s %d %.2f\n", estoque[i].codigo, estoque[i].nome,
                estoque[i].quantidade, estoque[i].preco);
    }

    fclose(arquivo);
}

// Função para cadastrar um novo produto
void cadastrarProduto(struct Produto estoque[], int *numProdutos) {
    if (*numProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    printf("Digite o código do produto: ");
    scanf("%d", &estoque[*numProdutos].codigo);

    printf("Digite o nome do produto: ");
    scanf("%s", estoque[*numProdutos].nome);

    printf("Digite a quantidade disponível: ");
    scanf("%d", &estoque[*numProdutos].quantidade);

    printf("Digite o preço de venda: ");
    scanf("%f", &estoque[*numProdutos].preco);

    (*numProdutos)++;
}

// Função para listar todos os produtos
void listarProdutos(const struct Produto estoque[], int numProdutos) {
    printf("Lista de Produtos:\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
               estoque[i].codigo, estoque[i].nome, estoque[i].quantidade, estoque[i].preco);
    }
}

int main() {
	setlocale (LC_ALL,"");
	
    struct Produto estoque[MAX_PRODUTOS];
    int numProdutos = 0;
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1 - Carregar Banco de Dados\n");
        printf("2 - Cadastrar produto\n");
        printf("3 - Listar produtos\n");
        printf("0 - Sair\n");

        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                carregarBanco(estoque, &numProdutos);
                break;

            case 2:
                cadastrarProduto(estoque, &numProdutos);
                salvarBanco(estoque, numProdutos);
                break;

            case 3:
                listarProdutos(estoque, numProdutos);
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