#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5

// Definição da estrutura da peça
typedef struct {
    char nome;
    int id;
} Peca;

// Definição da estrutura da fila
typedef struct {
    Peca pecas[TAMANHO_FILA];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Protótipos das funções
void inicializarFila(Fila *fila);
int filaVazia(Fila *fila);
int filaCheia(Fila *fila);
void enqueue(Fila *fila, Peca peca);
Peca dequeue(Fila *fila);
Peca gerarPeca(int id);
void exibirFila(Fila *fila);
void mostrarMenu();

int main() {
    Fila fila;
    int opcao = -1;
    int proximoId = TAMANHO_FILA; // Próximo ID para novas peças
    Peca pecaRemovida;
    
    // Inicializar gerador de números aleatórios
    srand(time(NULL));
    
    // Inicializar a fila com 5 peças
    inicializarFila(&fila);
    for (int i = 0; i < TAMANHO_FILA; i++) {
        enqueue(&fila, gerarPeca(i));
    }
    
    printf("=== TETRIS STACK - FILA DE PEÇAS FUTURAS ===\n\n");
    
    while (opcao != 0) {
        // Exibir estado atual da fila
        printf("Confira a seguir seu estado:\n\n");
        printf("Fila de peças\n");
        exibirFila(&fila);
        printf("\n");
        
        // Mostrar opções
        mostrarMenu();
        
        // Ler opção do usuário
        printf("\nDigite sua opção: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 0:
                printf("Saindo do jogo...\n");
                break;
                
            case 1: // Jogar peça (dequeue)
                if (!filaVazia(&fila)) {
                    pecaRemovida = dequeue(&fila);
                    printf("Peça jogada: [%c %d]\n", pecaRemovida.nome, pecaRemovida.id);
                    
                    // Se a fila não estiver cheia, adicionar uma nova peça automaticamente
                    if (!filaCheia(&fila)) {
                        enqueue(&fila, gerarPeca(proximoId));
                        proximoId++;
                    }
                } else {
                    printf("Erro: Fila vazia! Não há peças para jogar.\n");
                }
                break;
                
            case 2: // Inserir nova peça (enqueue)
                if (!filaCheia(&fila)) {
                    enqueue(&fila, gerarPeca(proximoId));
                    printf("Nova peça adicionada à fila!\n");
                    proximoId++;
                } else {
                    printf("Erro: Fila cheia! Não é possível adicionar mais peças.\n");
                }
                break;
                
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
        
        printf("\n");
        printf("----------------------------------------\n\n");
    }
    
    return 0;
}

// Inicializa a fila vazia
void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->tamanho = 0;
}

// Verifica se a fila está vazia
int filaVazia(Fila *fila) {
    return fila->tamanho == 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *fila) {
    return fila->tamanho == TAMANHO_FILA;
}

// Adiciona uma peça ao final da fila
void enqueue(Fila *fila, Peca peca) {
    if (!filaCheia(fila)) {
        fila->tras = (fila->tras + 1) % TAMANHO_FILA;
        fila->pecas[fila->tras] = peca;
        fila->tamanho++;
    }
}

// Remove e retorna a peça da frente da fila
Peca dequeue(Fila *fila) {
    Peca pecaVazia = {' ', -1}; // Peça vazia para retorno em caso de erro
    
    if (!filaVazia(fila)) {
        Peca pecaRemovida = fila->pecas[fila->frente];
        fila->frente = (fila->frente + 1) % TAMANHO_FILA;
        fila->tamanho--;
        return pecaRemovida;
    }
    
    return pecaVazia;
}

// Gera uma peça aleatória com o ID especificado
Peca gerarPeca(int id) {
    Peca novaPeca;
    novaPeca.id = id;
    
    // Tipos de peças disponíveis: I, O, T, L
    char tipos[] = {'I', 'O', 'T', 'L'};
    int indiceAleatorio = rand() % 4;
    novaPeca.nome = tipos[indiceAleatorio];
    
    return novaPeca;
}

// Exibe o estado atual da fila
void exibirFila(Fila *fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        return;
    }
    
    int indice = fila->frente;
    for (int i = 0; i < fila->tamanho; i++) {
        printf("[%c %d] ", fila->pecas[indice].nome, fila->pecas[indice].id);
        indice = (indice + 1) % TAMANHO_FILA;
    }
    printf("\n");
}

// Mostra o menu de opções
void mostrarMenu() {
    printf("Opções de ação:\n");
    printf("Código\tAção\n");
    printf("1\tJogar peça (dequeue)\n");
    printf("2\tInserir nova peça (enqueue)\n");
    printf("0\tSair\n");
}