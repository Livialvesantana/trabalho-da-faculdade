#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// ==================== ESTRUTURAS COMPARTILHADAS ====================

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Variáveis globais para medição
int comparacoes = 0;
int trocas = 0;

// ==================== FUNÇÕES UTILITÁRIAS ====================

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void toLowerString(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// ==================== NÍVEL NOVATO - SISTEMA BÁSICO ====================

#define MAX_COMPONENTES 10
Componente componentesNovato[MAX_COMPONENTES];
int totalComponentesNovato = 0;

void cadastrarComponenteNovato() {
    if (totalComponentesNovato >= MAX_COMPONENTES) {
        printf("Limite de componentes atingido! (%d/%d)\n", totalComponentesNovato, MAX_COMPONENTES);
        return;
    }
    
    printf("\n--- CADASTRAR COMPONENTE ---\n");
    
    printf("Nome: ");
    fgets(componentesNovato[totalComponentesNovato].nome, 30, stdin);
    componentesNovato[totalComponentesNovato].nome[strcspn(componentesNovato[totalComponentesNovato].nome, "\n")] = 0;
    
    printf("Tipo (controle/suporte/propulsao): ");
    fgets(componentesNovato[totalComponentesNovato].tipo, 20, stdin);
    componentesNovato[totalComponentesNovato].tipo[strcspn(componentesNovato[totalComponentesNovato].tipo, "\n")] = 0;
    
    printf("Prioridade (1-10): ");
    scanf("%d", &componentesNovato[totalComponentesNovato].prioridade);
    limparBuffer();
    
    if (componentesNovato[totalComponentesNovato].prioridade < 1) {
        componentesNovato[totalComponentesNovato].prioridade = 1;
    } else if (componentesNovato[totalComponentesNovato].prioridade > 10) {
        componentesNovato[totalComponentesNovato].prioridade = 10;
    }
    
    totalComponentesNovato++;
    printf("Componente cadastrado com sucesso!\n");
}

void bubbleSortBasico() {
    // Ordenação básica por prioridade (decrescente)
    for (int i = 0; i < totalComponentesNovato - 1; i++) {
        for (int j = 0; j < totalComponentesNovato - i - 1; j++) {
            if (componentesNovato[j].prioridade < componentesNovato[j + 1].prioridade) {
                Componente temp = componentesNovato[j];
                componentesNovato[j] = componentesNovato[j + 1];
                componentesNovato[j + 1] = temp;
            }
        }
    }
    printf("Componentes ordenados por prioridade (mais importante primeiro)!\n");
}

void listarComponentesNovato() {
    if (totalComponentesNovato == 0) {
        printf("\nNenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n--- COMPONENTES PARA MONTAGEM (%d/%d) ---\n", totalComponentesNovato, MAX_COMPONENTES);
    printf("%-25s %-15s %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("-------------------------------------------------------\n");
    
    for (int i = 0; i < totalComponentesNovato; i++) {
        printf("%-25s %-15s %-10d\n", 
               componentesNovato[i].nome, 
               componentesNovato[i].tipo, 
               componentesNovato[i].prioridade);
    }
}

void buscarComponenteSequencial() {
    if (totalComponentesNovato == 0) {
        printf("Nenhum componente para buscar!\n");
        return;
    }
    
    char nome[30];
    printf("Nome do componente a buscar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = 0;
    
    int encontrado = 0;
    for (int i = 0; i < totalComponentesNovato; i++) {
        if (strcmp(componentesNovato[i].nome, nome) == 0) {
            printf("\n✅ COMPONENTE ENCONTRADO!\n");
            printf("Nome: %s\n", componentesNovato[i].nome);
            printf("Tipo: %s\n", componentesNovato[i].tipo);
            printf("Prioridade: %d\n", componentesNovato[i].prioridade);
            encontrado = 1;
            break;
        }
    }
    
    if (!encontrado) {
        printf("❌ Componente '%s' não encontrado!\n", nome);
    }
}

void nivelNovato() {
    printf("\n=== 🎮 NIVEL NOVATO - MONTAGEM BÁSICA DA TORRE ===\n");
    printf("Sistema simples para organização de componentes\n\n");
    
    int opcao;
    
    do {
        printf("\n--- MENU MONTAGEM BÁSICA ---\n");
        printf("1. Cadastrar componente\n");
        printf("2. Ordenar por prioridade (Bubble Sort)\n");
        printf("3. Listar componentes\n");
        printf("4. Buscar componente (Sequencial)\n");
        printf("5. Voltar ao menu principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1: cadastrarComponenteNovato(); break;
            case 2: bubbleSortBasico(); break;
            case 3: listarComponentesNovato(); break;
            case 4: buscarComponenteSequencial(); break;
            case 5: printf("Retornando ao menu principal...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 5);
}

// ==================== NÍVEL AVENTUREIRO - ALGORITMOS DE ORDENAÇÃO ====================

#define MAX_AVENTUREIRO 20
Componente componentesAventureiro[MAX_AVENTUREIRO];
int totalAventureiro = 0;

// Bubble Sort por nome
void bubbleSortNome() {
    comparacoes = 0;
    trocas = 0;
    clock_t inicio = clock();
    
    for (int i = 0; i < totalAventureiro - 1; i++) {
        for (int j = 0; j < totalAventureiro - i - 1; j++) {
            comparacoes++;
            if (strcmp(componentesAventureiro[j].nome, componentesAventureiro[j + 1].nome) > 0) {
                Componente temp = componentesAventureiro[j];
                componentesAventureiro[j] = componentesAventureiro[j + 1];
                componentesAventureiro[j + 1] = temp;
                trocas++;
            }
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\n📊 BUBBLE SORT FINALIZADO!\n");
    printf("Comparações: %d\n", comparacoes);
    printf("Trocas: %d\n", trocas);
    printf("Tempo: %.6f segundos\n", tempo);
}

// Insertion Sort por tipo
void insertionSortTipo() {
    comparacoes = 0;
    trocas = 0;
    clock_t inicio = clock();
    
    for (int i = 1; i < totalAventureiro; i++) {
        Componente chave = componentesAventureiro[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes++;
            if (strcmp(componentesAventureiro[j].tipo, chave.tipo) > 0) {
                componentesAventureiro[j + 1] = componentesAventureiro[j];
                trocas++;
                j--;
            } else {
                break;
            }
        }
        componentesAventureiro[j + 1] = chave;
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\n📊 INSERTION SORT FINALIZADO!\n");
    printf("Comparações: %d\n", comparacoes);
    printf("Trocas: %d\n", trocas);
    printf("Tempo: %.6f segundos\n", tempo);
}

// Selection Sort por prioridade (decrescente)
void selectionSortPrioridade() {
    comparacoes = 0;
    trocas = 0;
    clock_t inicio = clock();
    
    for (int i = 0; i < totalAventureiro - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < totalAventureiro; j++) {
            comparacoes++;
            if (componentesAventureiro[j].prioridade > componentesAventureiro[max_idx].prioridade) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            Componente temp = componentesAventureiro[i];
            componentesAventureiro[i] = componentesAventureiro[max_idx];
            componentesAventureiro[max_idx] = temp;
            trocas++;
        }
    }
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\n📊 SELECTION SORT FINALIZADO!\n");
    printf("Comparações: %d\n", comparacoes);
    printf("Trocas: %d\n", trocas);
    printf("Tempo: %.6f segundos\n", tempo);
}

// Busca binária (requer ordenação por nome)
int buscaBinaria(char nome[]) {
    int esquerda = 0, direita = totalAventureiro - 1;
    comparacoes = 0;
    
    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        comparacoes++;
        
        int resultado = strcmp(componentesAventureiro[meio].nome, nome);
        
        if (resultado == 0) {
            return meio; // Encontrado
        } else if (resultado < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    return -1; // Não encontrado
}

void cadastrarComponenteAventureiro() {
    if (totalAventureiro >= MAX_AVENTUREIRO) {
        printf("Limite máximo de componentes atingido! (%d/%d)\n", totalAventureiro, MAX_AVENTUREIRO);
        return;
    }
    
    printf("\n--- CADASTRAR COMPONENTE AVANÇADO ---\n");
    
    printf("Nome: ");
    fgets(componentesAventureiro[totalAventureiro].nome, 30, stdin);
    componentesAventureiro[totalAventureiro].nome[strcspn(componentesAventureiro[totalAventureiro].nome, "\n")] = 0;
    
    printf("Tipo: ");
    fgets(componentesAventureiro[totalAventureiro].tipo, 20, stdin);
    componentesAventureiro[totalAventureiro].tipo[strcspn(componentesAventureiro[totalAventureiro].tipo, "\n")] = 0;
    
    printf("Prioridade (1-10): ");
    scanf("%d", &componentesAventureiro[totalAventureiro].prioridade);
    limparBuffer();
    
    if (componentesAventureiro[totalAventureiro].prioridade < 1) componentesAventureiro[totalAventureiro].prioridade = 1;
    if (componentesAventureiro[totalAventureiro].prioridade > 10) componentesAventureiro[totalAventureiro].prioridade = 10;
    
    totalAventureiro++;
    printf("✅ Componente cadastrado!\n");
}

void listarComponentesAventureiro() {
    if (totalAventureiro == 0) {
        printf("\nNenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n--- COMPONENTES PARA MONTAGEM (%d/%d) ---\n", totalAventureiro, MAX_AVENTUREIRO);
    printf("%-25s %-15s %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("-------------------------------------------------------\n");
    
    for (int i = 0; i < totalAventureiro; i++) {
        printf("%-25s %-15s %-10d\n", 
               componentesAventureiro[i].nome, 
               componentesAventureiro[i].tipo, 
               componentesAventureiro[i].prioridade);
    }
}

void nivelAventureiro() {
    printf("\n=== ⚡ NIVEL AVENTUREIRO - ALGORITMOS DE ORDENAÇÃO ===\n");
    printf("Comparação de desempenho entre diferentes algoritmos\n\n");
    
    int opcao;
    char nome[30];
    
    do {
        printf("\n--- MENU ALGORITMOS AVANÇADOS ---\n");
        printf("1. Cadastrar componente\n");
        printf("2. Ordenar por NOME (Bubble Sort)\n");
        printf("3. Ordenar por TIPO (Insertion Sort)\n");
        printf("4. Ordenar por PRIORIDADE (Selection Sort)\n");
        printf("5. Busca Binária (após ordenar por nome)\n");
        printf("6. Listar componentes\n");
        printf("7. Voltar ao menu principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1: cadastrarComponenteAventureiro(); break;
            case 2: bubbleSortNome(); break;
            case 3: insertionSortTipo(); break;
            case 4: selectionSortPrioridade(); break;
            case 5: 
                printf("Nome do componente-chave: ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                int posicao = buscaBinaria(nome);
                if (posicao != -1) {
                    printf("\n🎯 COMPONENTE-CHAVE ENCONTRADO!\n");
                    printf("Posição: %d\n", posicao);
                    printf("Comparações: %d\n", comparacoes);
                    printf("Nome: %s\n", componentesAventureiro[posicao].nome);
                    printf("Tipo: %s\n", componentesAventureiro[posicao].tipo);
                    printf("Prioridade: %d\n", componentesAventureiro[posicao].prioridade);
                } else {
                    printf("❌ Componente '%s' não encontrado!\n", nome);
                    printf("Comparações realizadas: %d\n", comparacoes);
                }
                break;
            case 6: listarComponentesAventureiro(); break;
            case 7: printf("Retornando ao menu principal...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 7);
}

// ==================== NÍVEL MESTRE - SISTEMA COMPLETO COM MÚLTIPLAS ESTRATÉGIAS ====================

#define MAX_MESTRE 30
Componente componentesMestre[MAX_MESTRE];
int totalMestre = 0;

// Quick Sort por nome
void quickSortNome(int esquerda, int direita) {
    if (esquerda < direita) {
        Componente pivo = componentesMestre[direita];
        int i = esquerda - 1;
        
        for (int j = esquerda; j < direita; j++) {
            comparacoes++;
            if (strcmp(componentesMestre[j].nome, pivo.nome) < 0) {
                i++;
                Componente temp = componentesMestre[i];
                componentesMestre[i] = componentesMestre[j];
                componentesMestre[j] = temp;
                trocas++;
            }
        }
        
        Componente temp = componentesMestre[i + 1];
        componentesMestre[i + 1] = componentesMestre[direita];
        componentesMestre[direita] = temp;
        trocas++;
        
        int pi = i + 1;
        quickSortNome(esquerda, pi - 1);
        quickSortNome(pi + 1, direita);
    }
}

// Merge Sort por prioridade
void merge(int esquerda, int meio, int direita) {
    int n1 = meio - esquerda + 1;
    int n2 = direita - meio;
    
    Componente L[n1], R[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = componentesMestre[esquerda + i];
    for (int j = 0; j < n2; j++)
        R[j] = componentesMestre[meio + 1 + j];
    
    int i = 0, j = 0, k = esquerda;
    
    while (i < n1 && j < n2) {
        comparacoes++;
        if (L[i].prioridade >= R[j].prioridade) {
            componentesMestre[k] = L[i];
            i++;
        } else {
            componentesMestre[k] = R[j];
            j++;
        }
        trocas++;
        k++;
    }
    
    while (i < n1) {
        componentesMestre[k] = L[i];
        i++;
        k++;
        trocas++;
    }
    
    while (j < n2) {
        componentesMestre[k] = R[j];
        j++;
        k++;
        trocas++;
    }
}

void mergeSortPrioridade(int esquerda, int direita) {
    if (esquerda < direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        mergeSortPrioridade(esquerda, meio);
        mergeSortPrioridade(meio + 1, direita);
        merge(esquerda, meio, direita);
    }
}

void executarQuickSort() {
    comparacoes = 0;
    trocas = 0;
    clock_t inicio = clock();
    
    quickSortNome(0, totalMestre - 1);
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\n🚀 QUICK SORT FINALIZADO!\n");
    printf("Comparações: %d\n", comparacoes);
    printf("Trocas: %d\n", trocas);
    printf("Tempo: %.6f segundos\n", tempo);
}

void executarMergeSort() {
    comparacoes = 0;
    trocas = 0;
    clock_t inicio = clock();
    
    mergeSortPrioridade(0, totalMestre - 1);
    
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("\n🚀 MERGE SORT FINALIZADO!\n");
    printf("Comparações: %d\n", comparacoes);
    printf("Trocas: %d\n", trocas);
    printf("Tempo: %.6f segundos\n", tempo);
}

void cadastrarComponenteMestre() {
    if (totalMestre >= MAX_MESTRE) {
        printf("Limite máximo de componentes atingido! (%d/%d)\n", totalMestre, MAX_MESTRE);
        return;
    }
    
    printf("\n--- CADASTRAR COMPONENTE MESTRE ---\n");
    
    printf("Nome: ");
    fgets(componentesMestre[totalMestre].nome, 30, stdin);
    componentesMestre[totalMestre].nome[strcspn(componentesMestre[totalMestre].nome, "\n")] = 0;
    
    printf("Tipo: ");
    fgets(componentesMestre[totalMestre].tipo, 20, stdin);
    componentesMestre[totalMestre].tipo[strcspn(componentesMestre[totalMestre].tipo, "\n")] = 0;
    
    printf("Prioridade (1-10): ");
    scanf("%d", &componentesMestre[totalMestre].prioridade);
    limparBuffer();
    
    if (componentesMestre[totalMestre].prioridade < 1) componentesMestre[totalMestre].prioridade = 1;
    if (componentesMestre[totalMestre].prioridade > 10) componentesMestre[totalMestre].prioridade = 10;
    
    totalMestre++;
    printf("✅ Componente mestre cadastrado!\n");
}

void listarComponentesMestre() {
    if (totalMestre == 0) {
        printf("\nNenhum componente cadastrado!\n");
        return;
    }
    
    printf("\n--- COMPONENTES MESTRE (%d/%d) ---\n", totalMestre, MAX_MESTRE);
    printf("%-25s %-15s %-10s\n", "NOME", "TIPO", "PRIORIDADE");
    printf("-------------------------------------------------------\n");
    
    for (int i = 0; i < totalMestre; i++) {
        printf("%-25s %-15s %-10d\n", 
               componentesMestre[i].nome, 
               componentesMestre[i].tipo, 
               componentesMestre[i].prioridade);
    }
}

void simularMontagemTorre() {
    if (totalMestre == 0) {
        printf("Nenhum componente para montar a torre!\n");
        return;
    }
    
    printf("\n🏗️  INICIANDO MONTAGEM DA TORRE DE FUGA...\n");
    printf("=== ETAPAS DE CONSTRUÇÃO ===\n");
    
    // Ordenar por prioridade para montagem
    mergeSortPrioridade(0, totalMestre - 1);
    
    for (int i = 0; i < totalMestre; i++) {
        printf("\nEtapa %d: %s\n", i + 1, componentesMestre[i].nome);
        printf("Tipo: %s | Prioridade: %d\n", componentesMestre[i].tipo, componentesMestre[i].prioridade);
        
        // Simular tempo de montagem
        printf("Montando");
        for (int j = 0; j < 3; j++) {
            printf(".");
            fflush(stdout);
            // Pequena pausa para efeito visual
            clock_t start = clock();
            while (clock() < start + 300000); // 0.3 segundos
        }
        printf(" ✅ CONCLUÍDO!\n");
    }
    
    printf("\n🎉 TORRE DE FUGA MONTADA COM SUCESSO!\n");
    printf("💨 Fuga iniciada! Você escapou da ilha!\n");
}

void nivelMestre() {
    printf("\n=== 🏆 NIVEL MESTRE - SISTEMA COMPLETO DE MONTAGEM ===\n");
    printf("Algoritmos avançados e simulação de montagem final\n\n");
    
    int opcao;
    char nome[30];
    
    do {
        printf("\n--- MENU MESTRE - MONTAGEM DA TORRE ---\n");
        printf("1. Cadastrar componente\n");
        printf("2. Ordenar por NOME (Quick Sort)\n");
        printf("3. Ordenar por PRIORIDADE (Merge Sort)\n");
        printf("4. Busca Binária Avançada\n");
        printf("5. Listar componentes\n");
        printf("6. SIMULAR MONTAGEM FINAL DA TORRE\n");
        printf("7. Voltar ao menu principal\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1: cadastrarComponenteMestre(); break;
            case 2: executarQuickSort(); break;
            case 3: executarMergeSort(); break;
            case 4: 
                printf("Nome do componente-chave: ");
                fgets(nome, 30, stdin);
                nome[strcspn(nome, "\n")] = 0;
                
                int posicao = buscaBinaria(nome);
                if (posicao != -1) {
                    printf("\n🎯 COMPONENTE-CRUCIAL ENCONTRADO!\n");
                    printf("Este componente destrava a torre!\n");
                    printf("Posição: %d | Comparações: %d\n", posicao, comparacoes);
                } else {
                    printf("❌ Componente essencial não encontrado!\n");
                }
                break;
            case 5: listarComponentesMestre(); break;
            case 6: simularMontagemTorre(); break;
            case 7: printf("Retornando ao menu principal...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while(opcao != 7);
}

// ==================== MENU PRINCIPAL ====================

int main() {
    srand(time(NULL));
    int opcao;
    
    printf("=== 🎮 SISTEMA DE MONTAGEM DA TORRE DE FUGA ===\n");
    printf("        Três Níveis de Complexidade\n");
    printf("           💥 FASE FINAL DO JOGO 💥\n");
    
    do {
        printf("\n╔══════════════════════════════════════════╗\n");
        printf("║           MENU PRINCIPAL                 ║\n");
        printf("╠══════════════════════════════════════════╣\n");
        printf("║  1. 🎮 NÍVEL NOVATO                      ║\n");
        printf("║     - Sistema Básico de Montagem         ║\n");
        printf("║                                          ║\n");
        printf("║  2. ⚡ NÍVEL AVENTUREIRO                  ║\n");
        printf("║     - Algoritmos de Ordenação            ║\n");
        printf("║                                          ║\n");
        printf("║  3. 🏆 NÍVEL MESTRE                      ║\n");
        printf("║     - Sistema Completo de Montagem       ║\n");
        printf("║                                          ║\n");
        printf("║  0. 🚪 SAIR                              ║\n");
        printf("╚══════════════════════════════════════════╝\n");
        printf("\nEscolha o nível: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1: nivelNovato(); break;
            case 2: nivelAventureiro(); break;
            case 3: nivelMestre(); break;
            case 0: printf("\n🎊 Obrigado por jogar! Até a próxima! 🎊\n"); break;
            default: printf("❌ Opção inválida!\n");
        }
    } while(opcao != 0);
    
    return 0;
}


