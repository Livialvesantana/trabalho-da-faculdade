#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura base de um item
typedef struct {
    char nome[50];
    int quantidade;
    float peso;
} Item;

// Função para exibir o inventário
void mostrarInventario(Item inventario[], int tamanho) {
    printf("\n=== INVENTÁRIO ===\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%d. %s | Quantidade: %d | Peso: %.2fkg\n",
               i + 1, inventario[i].nome, inventario[i].quantidade, inventario[i].peso);
    }
    printf("===================\n");
}

// Função para adicionar um novo item
int adicionarItem(Item inventario[], int tamanho) {
    if (tamanho >= 10) {
        printf("\nInventário cheio! Não é possível adicionar mais itens.\n");
        return tamanho;
    }

    printf("\nDigite o nome do item: ");
    scanf(" %[^\n]", inventario[tamanho].nome);
    printf("Digite a quantidade: ");
    scanf("%d", &inventario[tamanho].quantidade);
    printf("Digite o peso do item (em kg): ");
    scanf("%f", &inventario[tamanho].peso);

    printf("Item adicionado com sucesso!\n");
    return tamanho + 1;
}

// Função para remover um item
int removerItem(Item inventario[], int tamanho) {
    if (tamanho == 0) {
        printf("\nInventário vazio!\n");
        return 0;
    }

    int indice;
    printf("\nDigite o número do item a remover: ");
    scanf("%d", &indice);

    if (indice < 1 || indice > tamanho) {
        printf("Índice inválido!\n");
        return tamanho;
    }

    for (int i = indice - 1; i < tamanho - 1; i++) {
        inventario[i] = inventario[i + 1];
    }

    printf("Item removido com sucesso!\n");
    return tamanho - 1;
}

// Função para calcular o peso total
float calcularPesoTotal(Item inventario[], int tamanho) {
    float total = 0;
    for (int i = 0; i < tamanho; i++) {
        total += inventario[i].peso * inventario[i].quantidade;
    }
    return total;
}

// Função do Nível 1 – Gerenciar itens
void nivel1() {
    Item inventario[10];
    int tamanho = 0;
    int opcao;

    do {
        printf("\n=== NÍVEL 1: GERENCIAMENTO DE ITENS ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Mostrar inventário\n");
        printf("4. Avançar para o próximo nível\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: tamanho = adicionarItem(inventario, tamanho); break;
            case 2: tamanho = removerItem(inventario, tamanho); break;
            case 3: mostrarInventario(inventario, tamanho); break;
            case 4: printf("\nAvançando para o Nível 2...\n"); break;
            default: printf("\nOpção inválida!\n");
        }
    } while (opcao != 4);
}

// Função do Nível 2 – Calcular peso e verificar capacidade
void nivel2() {
    Item inventario[10];
    int tamanho = 0;
    float capacidadeMax = 30.0; // limite de peso da mochila
    int opcao;

    do {
        printf("\n=== NÍVEL 2: GERENCIAR CAPACIDADE ===\n");
        printf("1. Adicionar item\n");
        printf("2. Mostrar inventário\n");
        printf("3. Verificar peso total\n");
        printf("4. Avançar para o Nível 3\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                tamanho = adicionarItem(inventario, tamanho);
                if (calcularPesoTotal(inventario, tamanho) > capacidadeMax)
                    printf("⚠️ Cuidado! A mochila está muito pesada!\n");
                break;
            case 2:
                mostrarInventario(inventario, tamanho);
                break;
            case 3:
                printf("Peso total: %.2fkg / %.2fkg\n", calcularPesoTotal(inventario, tamanho), capacidadeMax);
                break;
            case 4:
                printf("\nAvançando para o Nível 3...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4);
}

// Função do Nível 3 – Combinar e otimizar itens
void nivel3() {
    Item inventario[10] = {
        {"Kit Médico", 2, 1.5},
        {"Munição", 5, 0.3},
        {"Água", 3, 1.0}
    };
    int tamanho = 3;
    int opcao;

    do {
        printf("\n=== NÍVEL 3: OTIMIZAÇÃO DO INVENTÁRIO ===\n");
        printf("1. Mostrar inventário\n");
        printf("2. Combinar itens iguais\n");
        printf("3. Ordenar por peso\n");
        printf("4. Finalizar jogo\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                mostrarInventario(inventario, tamanho);
                break;
            case 2: {
                // Combinar itens iguais
                for (int i = 0; i < tamanho; i++) {
                    for (int j = i + 1; j < tamanho; j++) {
                        if (strcmp(inventario[i].nome, inventario[j].nome) == 0) {
                            inventario[i].quantidade += inventario[j].quantidade;
                            for (int k = j; k < tamanho - 1; k++) {
                                inventario[k] = inventario[k + 1];
                            }
                            tamanho--;
                            j--;
                        }
                    }
                }
                printf("Itens combinados com sucesso!\n");
                break;
            }
            case 3: {
                // Ordenar por peso (Bubble Sort)
                for (int i = 0; i < tamanho - 1; i++) {
                    for (int j = 0; j < tamanho - i - 1; j++) {
                        if (inventario[j].peso > inventario[j + 1].peso) {
                            Item temp = inventario[j];
                            inventario[j] = inventario[j + 1];
                            inventario[j + 1] = temp;
                        }
                    }
                }
                printf("Inventário ordenado por peso!\n");
                break;
            }
            case 4:
                printf("\n🎉 Parabéns! Você concluiu os 3 níveis do jogo de inventário! 🎮\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 4);
}

// Função principal
int main() {
    printf("=============================================\n");
    printf("🪖 JOGO DO INVENTÁRIO - SIMULAÇÃO COMPLETA 🪖\n");
    printf("=============================================\n");

    nivel1();
    nivel2();
    nivel3();

    return 0;
}

