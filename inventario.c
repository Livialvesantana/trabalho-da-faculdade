#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Códigos de cor ANSI (funcionam no VS Code)
#define RESET   "\033[0m"
#define VERDE   "\033[1;32m"
#define VERMELHO "\033[1;31m"
#define AMARELO "\033[1;33m"
#define AZUL    "\033[1;34m"
#define CIANO   "\033[1;36m"

// Estrutura que representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Função para inserir um novo item na mochila
void inserirItem(Item mochila[], int *tamanho) {
    if (*tamanho >= 10) {
        printf(VERMELHO "\n❌ A mochila está cheia! Não é possível adicionar mais itens.\n" RESET);
        return;
    }

    printf(AZUL "\n=== Adicionar Item à Mochila ===\n" RESET);

    printf("Nome do item: ");
    scanf(" %[^\n]", mochila[*tamanho].nome);

    printf("Tipo do item (arma, munição, cura, etc): ");
    scanf(" %[^\n]", mochila[*tamanho].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[*tamanho].quantidade);

    (*tamanho)++;
    printf(VERDE "\n✅ Item adicionado com sucesso!\n" RESET);
}

// Função para listar todos os itens
void listarItens(Item mochila[], int tamanho) {
    printf(CIANO "\n=== Itens da Mochila ===\n" RESET);

    if (tamanho == 0) {
        printf(AMARELO "⚠️ A mochila está vazia.\n" RESET);
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        printf("\n🎒 Item %d\n", i + 1);
        printf("📦 Nome: %s\n", mochila[i].nome);
        printf("🔹 Tipo: %s\n", mochila[i].tipo);
        printf("🔢 Quantidade: %d\n", mochila[i].quantidade);
    }
}

// Função para remover um item pelo nome
void removerItem(Item mochila[], int *tamanho) {
    if (*tamanho == 0) {
        printf(AMARELO "\n⚠️ Não há itens para remover.\n" RESET);
        return;
    }

    char nomeRemover[30];
    printf(AZUL "\n=== Remover Item ===\n" RESET);
    printf("Digite o nome do item que deseja remover: ");
    scanf(" %[^\n]", nomeRemover);

    int encontrado = 0;
    for (int i = 0; i < *tamanho; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            for (int j = i; j < *tamanho - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*tamanho)--;
            encontrado = 1;
            printf(VERDE "\n✅ Item removido com sucesso!\n" RESET);
            break;
        }
    }

    if (!encontrado) {
        printf(VERMELHO "\n❌ Item não encontrado na mochila.\n" RESET);
    }
}

// Função de busca sequencial por nome
void buscarItem(Item mochila[], int tamanho) {
    if (tamanho == 0) {
        printf(AMARELO "\n⚠️ A mochila está vazia.\n" RESET);
        return;
    }

    char nomeBusca[30];
    printf(AZUL "\n=== Buscar Item ===\n" RESET);
    printf("Digite o nome do item que deseja buscar: ");
    scanf(" %[^\n]", nomeBusca);

    int encontrado = 0;
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf(VERDE "\n✅ Item encontrado!\n" RESET);
            printf("\n📦 Nome: %s\n", mochila[i].nome);
            printf("🔹 Tipo: %s\n", mochila[i].tipo);
            printf("🔢 Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf(VERMELHO "\n❌ Item não encontrado na mochila.\n" RESET);
    }
}

// Função principal
int main() {
    Item mochila[10];  // Vetor de até 10 itens
    int tamanho = 0;
    int opcao;

    printf(AMARELO "🎮 Bem-vindo ao Sistema de Inventário – Mochila de Loot!\n" RESET);

    do {
        printf(CIANO "\n=== MENU PRINCIPAL ===\n" RESET);
        printf("1️⃣  Adicionar item\n");
        printf("2️⃣  Remover item\n");
        printf("3️⃣  Listar itens\n");
        printf("4️⃣  Buscar item\n");
        printf("0️⃣  Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem(mochila, &tamanho);
                listarItens(mochila, tamanho);
                break;
            case 2:
                removerItem(mochila, &tamanho);
                listarItens(mochila, tamanho);
                break;
            case 3:
                listarItens(mochila, tamanho);
                break;
            case 4:
                buscarItem(mochila, tamanho);
                break;
            case 0:
                printf(VERDE "\n👋 Saindo do sistema... Até logo!\n" RESET);
                break;
            default:
                printf(VERMELHO "\n❌ Opção inválida! Tente novamente.\n" RESET);
        }

    } while (opcao != 0);

    return 0;
}
