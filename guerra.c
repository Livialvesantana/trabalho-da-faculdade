#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Códigos ANSI para cores no terminal
#define RESET   "\033[0m"
#define VERMELHO "\033[1;31m"
#define VERDE    "\033[1;32m"
#define AMARELO  "\033[1;33m"
#define AZUL     "\033[1;34m"
#define CIANO    "\033[1;36m"


// Estrutura que representa um território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os territórios dinamicamente
void cadastrarTerritorios(Territorio *mapa, int n) {
    printf("=== Cadastro de Territórios ===\n");
    for (int i = 0; i < n; i++) {
        printf("\n--- Cadastro do %dº Território ---\n", i + 1);

        printf("Nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir os territórios cadastrados
void exibirTerritorios(Territorio *mapa, int n) {
    printf("\n======= LISTA DE TERRITÓRIOS =======\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor do Exército: %s\n", mapa[i].cor);
        printf("Quantidade de Tropas: %d\n", mapa[i].tropas);
    }
    printf("=====================================\n");
}

// Função de ataque entre dois territórios
void atacar(Territorio *atacante, Territorio *defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\n⚠️ Você não pode atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas <= 1) {
        printf("\n⚠️ O território atacante precisa ter mais de 1 tropa para atacar!\n");
        return;
    }

    // Rolagem de dados (1 a 6)
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n🎲 %s (atacante) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("🛡️ %s (defensor) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\n✅ O atacante venceu a batalha!\n");
        // Atualiza o território defensor
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas /= 2;
    } else {
        printf("\n❌ O defensor resistiu ao ataque!\n");
        atacante->tropas -= 1;
    }
}

// Função para liberar a memória alocada
void liberarMemoria(Territorio *mapa) {
    free(mapa);
    printf("\n🧹 Memória liberada com sucesso!\n");
}

int main() {
    srand(time(NULL)); // Garante aleatoriedade

    int n;
    printf("Digite o número total de territórios: ");
    scanf("%d", &n);

    // Alocação dinâmica de memória
    Territorio *mapa = (Territorio *)calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(mapa, n);
    exibirTerritorios(mapa, n);

    int atacante, defensor;
    char opcao;

    do {
        printf("\n=== SIMULAÇÃO DE ATAQUE ===\n");
        printf("Escolha o número do território atacante (1 a %d): ", n);
        scanf("%d", &atacante);
        printf("Escolha o número do território defensor (1 a %d): ", n);
        scanf("%d", &defensor);

        // Executa o ataque
        atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
        exibirTerritorios(mapa, n);

        printf("\nDeseja realizar outro ataque? (s/n): ");
        scanf(" %c", &opcao);
    } while (opcao == 's' || opcao == 'S');

    liberarMemoria(mapa);
    printf("\n🏁 Fim do programa!\n");

    return 0;
}
