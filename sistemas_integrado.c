#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==================== NIVEL NOVATO ====================
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

void detectiveQuest() {
    printf("\n=== DETECTIVE QUEST ===\n");
    
    Sala* hall = criarSala("Hall de Entrada");
    Sala* salaEstar = criarSala("Sala de Estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* biblioteca = criarSala("Biblioteca");
    
    hall->esquerda = salaEstar;
    hall->direita = cozinha;
    salaEstar->esquerda = biblioteca;
    
    Sala* atual = hall;
    char escolha;
    
    do {
        printf("\nVoce esta na: %s\n", atual->nome);
        printf("Caminhos: ");
        if (atual->esquerda) printf("[E]squerda ");
        if (atual->direita) printf("[D]ireita ");
        printf("[S]air\nEscolha: ");
        scanf(" %c", &escolha);
        
        if (escolha == 'e' && atual->esquerda) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita) {
            atual = atual->direita;
        } else if (escolha == 's') {
            break;
        } else {
            printf("Movimento invalido!\n");
        }
    } while (1);
    
    free(hall); free(salaEstar); free(cozinha); free(biblioteca);
}

// ==================== NIVEL AVENTUREIRO ====================
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

void sistemaAtaque() {
    printf("\n=== SISTEMA DE ATAQUE ===\n");
    
    int num;
    printf("Quantos territorios? ");
    scanf("%d", &num);
    
    Territorio* territorios = (Territorio*)malloc(num * sizeof(Territorio));
    
    for (int i = 0; i < num; i++) {
        printf("Territorio %d - Nome: ", i);
        scanf("%s", territorios[i].nome);
        printf("Cor: ");
        scanf("%s", territorios[i].cor);
        printf("Tropas: ");
        scanf("%d", &territorios[i].tropas);
    }
    
    int opcao;
    do {
        printf("\n1. Listar 2. Atacar 3. Sair: ");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            for (int i = 0; i < num; i++) {
                printf("%d: %s (%s) - %d tropas\n", i, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
            }
        } else if (opcao == 2) {
            int atk, def;
            printf("Atacante: "); scanf("%d", &atk);
            printf("Defensor: "); scanf("%d", &def);
            
            if (atk >= 0 && atk < num && def >= 0 && def < num && atk != def) {
                int dadoA = rand() % 6 + 1;
                int dadoD = rand() % 6 + 1;
                printf("Dados: A=%d D=%d\n", dadoA, dadoD);
                
                if (dadoA > dadoD) {
                    printf("%s venceu!\n", territorios[atk].nome);
                    strcpy(territorios[def].cor, territorios[atk].cor);
                } else {
                    printf("%s defendeu!\n", territorios[def].nome);
                }
            }
        }
    } while (opcao != 3);
    
    free(territorios);
}

// ==================== NIVEL MESTRE ====================
typedef struct {
    char tipo;
    int id;
} Peca;

Peca fila[5];
int frente = 0, tras = -1, tamanho = 0;

void tetrisStack() {
    printf("\n=== TETRIS STACK ===\n");
    
    // Inicializar fila com pecas
    for (int i = 0; i < 5; i++) {
        tras = (tras + 1) % 5;
        fila[tras].id = i;
        fila[tras].tipo = "IOTL"[rand() % 4];
        tamanho++;
    }
    
    int opcao, nextId = 5;
    
    do {
        printf("\nFila: ");
        for (int i = 0, idx = frente; i < tamanho; i++, idx = (idx + 1) % 5) {
            printf("[%c%d] ", fila[idx].tipo, fila[idx].id);
        }
        
        printf("\n1.Jogar 2.Adicionar 3.Sair: ");
        scanf("%d", &opcao);
        
        if (opcao == 1 && tamanho > 0) {
            printf("Jogou: [%c%d]\n", fila[frente].tipo, fila[frente].id);
            frente = (frente + 1) % 5;
            tamanho--;
        } else if (opcao == 2 && tamanho < 5) {
            tras = (tras + 1) % 5;
            fila[tras].id = nextId++;
            fila[tras].tipo = "IOTL"[rand() % 4];
            tamanho++;
            printf("Nova peca adicionada!\n");
        }
    } while (opcao != 3);
}

// ==================== MENU PRINCIPAL ====================
int main() {
    srand(time(NULL));
    int opcao;
    
    printf("SISTEMA INTEGRADO - 3 NIVELS\n");
    
    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("1. Detective Quest (Novato)\n");
        printf("2. Sistema de Ataque (Aventureiro)\n");
        printf("3. Tetris Stack (Mestre)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: detectiveQuest(); break;
            case 2: sistemaAtaque(); break;
            case 3: tetrisStack(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    
    return 0;
}