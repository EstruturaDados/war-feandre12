#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura que representa um território
struct Territorio {
    char nome[50];
    char corExercito[30];
    int numeroTropas;
};

// Função para cadastrar os territórios
void cadastrarTerritorios(struct Territorio *territorios, int total) {
    printf("=== Cadastro de Territórios ===\n\n");

    for (int i = 0; i < total; i++) {
        printf("Território %d:\n", i + 1);

        printf("Nome: ");
        fgets(territorios[i].nome, sizeof(territorios[i].nome), stdin);
        territorios[i].nome[strcspn(territorios[i].nome, "\n")] = '\0';

        printf("Cor do Exército: ");
        fgets(territorios[i].corExercito, sizeof(territorios[i].corExercito), stdin);
        territorios[i].corExercito[strcspn(territorios[i].corExercito, "\n")] = '\0';

        // Validação do número de tropas
        do {
            printf("Número de Tropas (mínimo 1): ");
            scanf("%d", &territorios[i].numeroTropas);
            if (territorios[i].numeroTropas < 1) {
                printf("Valor inválido! Digite novamente.\n");
            }
        } while (territorios[i].numeroTropas < 1);

        getchar(); // limpa o buffer
        printf("\n");
    }
}

// Função para exibir o estado atual do mapa
void exibirMapa(struct Territorio *territorios, int total) {
    printf("\n=== Estado Atual do Mapa ===\n");
    for (int i = 0; i < total; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do Exército: %s\n", territorios[i].corExercito);
        printf("Número de Tropas: %d\n", territorios[i].numeroTropas);
    }
    printf("\n");
}

// Função que simula uma batalha entre dois territórios
void simularBatalha(struct Territorio *territorios, int atacante, int defensor) {
    // Impede ataques se o atacante tiver 1 tropa ou menos
    if (territorios[atacante].numeroTropas <= 1) {
        printf("\nO território %s não tem tropas suficientes para atacar!\n\n",
               territorios[atacante].nome);
        return;
    }

    // Sorteia os dados (1 a 6)
    int dadoAtaque = rand() % 6 + 1;
    int dadoDefesa = rand() % 6 + 1;

    printf("\nDados de Batalha:\n");
    printf("%s (Atacante) tirou: %d\n", territorios[atacante].nome, dadoAtaque);
    printf("%s (Defensor) tirou: %d\n", territorios[defensor].nome, dadoDefesa);

    // Regras da batalha
    if (dadoAtaque >= dadoDefesa) {
        printf("\nO atacante venceu a rodada!\n");
        territorios[defensor].numeroTropas--;

        if (territorios[defensor].numeroTropas <= 0) {
            printf("%s foi conquistado por %s!\n",
                   territorios[defensor].nome,
                   territorios[atacante].nome);

            // Transfere a cor e reinicia as tropas
            strcpy(territorios[defensor].corExercito, territorios[atacante].corExercito);
            territorios[defensor].numeroTropas = 1;
            territorios[atacante].numeroTropas--;
        }
    } else {
        printf("\nO defensor resistiu ao ataque!\n");
        territorios[atacante].numeroTropas--;
    }

    printf("\n");
}

int main() {
    srand(time(NULL)); // Inicializa aleatoriedade

    int totalTerritorios = 5;

    // Alocação dinâmica
    struct Territorio *territorios = (struct Territorio *)calloc(totalTerritorios, sizeof(struct Territorio));
    if (territorios == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    cadastrarTerritorios(territorios, totalTerritorios);

    int opcao;
    do {
        exibirMapa(territorios, totalTerritorios);

        printf("=== Fase de Ataque ===\n");
        printf("Escolha o território atacante (1 a %d, 0 para sair): ", totalTerritorios);
        scanf("%d", &opcao);

        if (opcao == 0) break; // Sai do jogo

        int atacante = opcao - 1;

        printf("Escolha o território defensor (1 a %d): ", totalTerritorios);
        int defensor;
        scanf("%d", &defensor);
        getchar(); // limpa buffer
        defensor--;

        // Verifica se as escolhas são válidas
        if (atacante < 0 || atacante >= totalTerritorios ||
            defensor < 0 || defensor >= totalTerritorios ||
            atacante == defensor) {
            printf("\nEscolha inválida! Tente novamente.\n\n");
            continue;
        }

        // Executa a batalha
        simularBatalha(territorios, atacante, defensor);

        // Exibe o mapa atualizado
        exibirMapa(territorios, totalTerritorios);

    } while (opcao != 0);

    free(territorios);
    printf("\nJogo encerrado. Obrigado por jogar!\n");

    return 0;
}