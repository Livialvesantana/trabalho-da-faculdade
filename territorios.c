   #include <stdio.h>   // Biblioteca padrão de entrada e saída
   #include <string.h>  // Biblioteca para manipulação de strings

// Estrutura (struct) que representa um território
struct Territorio {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército associado ao território
    int tropas;      // Número de tropas que ocupam o território
};

int main() {
    struct Territorio territorios[5]; // Vetor que armazenará 5 territórios

    // Entrada dos dados
    printf("=== Cadastro de Territórios ===\n");
    for (int i = 0; i < 5; i++) {
        printf("\n--- Cadastro do %dº Território ---\n", i + 1);

        // Lê o nome do território
        printf("Digite o nome do território: ");
        scanf(" %[^\n]", territorios[i].nome); // Lê até o Enter

        // Lê a cor do exército
        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", territorios[i].cor);

        // Lê a quantidade de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados cadastrados
    printf("\n======= LISTA DE TERRITÓRIOS CADASTRADOS =======\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].cor);
        printf("Quantidade de Tropas: %d\n", territorios[i].tropas);
    }

    printf("\n===============================================\n");
    printf("Fim do programa. Dados cadastrados com sucesso!\n");

    return 0; // Indica que o programa terminou corretamente
}
