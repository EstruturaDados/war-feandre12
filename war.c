#include <stdio.h>
#include <string.h>

// Define a quantidade fixa de territórios no vetor
#define TOTAL_TERRITORIOS 5

// Estrutura que representa um território no mapa
struct Territorio {
    char nome[50];         // Nome do território
    char corExercito[30];  // Cor do exército dominante
    int numeroTropas;      // Número de tropas nesse território
};

int main() {
    // Declara um vetor estático com 5 elementos do tipo Territorio
    struct Territorio territorios[TOTAL_TERRITORIOS];

    printf("=== Cadastro de Territórios ===\n\n");

    // Loop para cadastrar os 5 territórios
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("Território %d:\n", i + 1);

        // Lê o nome do território usando fgets (aceita espaços)
        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0'; // remove o '\n' do final

        // Lê a cor do exército
        printf("Cor do Exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0'; // remove o '\n'

        // Lê o número de tropas
        printf("Número de Tropas: ");
        scanf("%d", &territorios[i].numeroTropas);

        getchar(); // consome o '\n' deixado pelo scanf no buffer

        printf("\n"); // linha em branco para separar cada território
    }

    // Exibição do estado atual do mapa
    printf("\n=== Estado Atual do Mapa ===\n");

    // Loop para exibir todos os territórios cadastrados
    for (int i = 0; i < TOTAL_TERRITORIOS; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numeroTropas);
    }

    return 0;
}