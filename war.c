#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ==================================================
// CONSTANTES E ESTRUTURAS
// ==================================================

#define MAX_TERRITORIOS 5    // número máximo de territórios
#define MAX_NOME 30          // tamanho máximo para nomes e cores

// Estrutura que representa cada território no mapa
typedef struct {
    char nome[MAX_NOME];     // nome do território
    char cor[MAX_NOME];      // cor do exército que o ocupa
    int tropas;              // quantidade de tropas naquele território
} Territorio;

// ==================================================
// PROTÓTIPOS DAS FUNÇÕES
// ==================================================

void inicializarTerritorios(Territorio territorios[], const int tamanho);
void exibirMapa(const Territorio territorios[], const int tamanho);
void atacar(Territorio territorios[], const int tamanho);
void exibirMenu();
int escolherMissao();
int verificarMissao(int missao, const Territorio territorios[], const int tamanho);
void limparBuffer();

// ==================================================
// FUNÇÃO PRINCIPAL
// ==================================================

int main() {
    srand(time(NULL));   // inicializa o gerador de números aleatórios

    Territorio territorios[MAX_TERRITORIOS];  // vetor de territórios
    inicializarTerritorios(territorios, MAX_TERRITORIOS); // preenche os dados iniciais

    int missao = escolherMissao(); // define aleatoriamente qual será a missão do jogador
    int opcao;                     // armazena a escolha do menu

    // Exibe a missão escolhida
    printf("\nSua missão é: ");
    if (missao == 1) 
        printf("Destruir o exército Verde!\n");
    else 
        printf("Conquistar 3 territórios!\n");

    // Loop principal do menu
    do {
        exibirMenu();  // exibe as opções disponíveis
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer(); // limpa o buffer de entrada

        switch (opcao) {
            case 1:
                atacar(territorios, MAX_TERRITORIOS); // executa um ataque
                break;
            case 2:
                // verifica se a missão foi concluída
                if (verificarMissao(missao, territorios, MAX_TERRITORIOS)) {
                    printf("\nMissão Concluída! Você venceu!\n");
                    opcao = 0; // encerra o jogo
                } else {
                    printf("\nMissão ainda não concluída. Continue jogando.\n");
                }
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0); // repete até o jogador escolher sair

    return 0;
}

// ==================================================
// FUNÇÕES AUXILIARES
// ==================================================

// Inicializa os territórios com dados padrão e aleatórios
void inicializarTerritorios(Territorio territorios[], const int tamanho) {
    const char *nomes[] = {"Norte", "Sul", "Leste", "Oeste", "Centro"};    // nomes fixos
    const char *cores[] = {"Vermelho", "Azul", "Verde", "Amarelo", "Preto"}; // cores fixas

    // percorre o vetor de territórios
    for (int i = 0; i < tamanho; i++) {
        strcpy(territorios[i].nome, nomes[i]);   // copia o nome do território
        strcpy(territorios[i].cor, cores[i]);    // copia a cor do exército
        territorios[i].tropas = rand() % 10 + 1; // gera de 1 a 10 tropas
    }

    printf("\nTerritórios Inicializados!\n");
    exibirMapa(territorios, tamanho); // mostra o estado inicial do mapa
}

// Exibe todos os territórios e suas informações
void exibirMapa(const Territorio territorios[], const int tamanho) {
    printf("\n===== ESTADO DO MAPA =====\n");
    for (int i = 0; i < tamanho; i++) {
        printf("[%d] %-8s | Exército: %-8s | Tropas: %d\n",
               i, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
    printf("==========================\n");
}

// Exibe o menu principal do jogo
void exibirMenu() {
    printf("\n===== MENU PRINCIPAL =====\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missão\n");
    printf("0 - Sair\n");
    printf("==========================\n");
}

// Escolhe aleatoriamente qual missão será atribuída ao jogador
int escolherMissao() {
    return rand() % 2 + 1; // retorna 1 ou 2 de forma aleatória
}

// Função que executa um ataque entre dois territórios
void atacar(Territorio territorios[], const int tamanho) {
    int atacante, defensor;

    exibirMapa(territorios, tamanho); // mostra os territórios disponíveis
    printf("Escolha o território atacante (0-%d): ", tamanho - 1);
    scanf("%d", &atacante);
    printf("Escolha o território defensor (0-%d): ", tamanho - 1);
    scanf("%d", &defensor);
    limparBuffer(); // limpa o buffer de entrada

    // validações das escolhas
    if (atacante == defensor || atacante < 0 || defensor < 0 || atacante >= tamanho || defensor >= tamanho) {
        printf("\nAtaque inválido!\n");
        return;
    }

    // verifica se há tropas suficientes para atacar
    if (territorios[atacante].tropas <= 1) {
        printf("\nO território atacante precisa de mais de 1 tropa!\n");
        return;
    }

    // sorteia os resultados dos dados de ataque e defesa (1 a 6)
    int forcaAtaque = rand() % 6 + 1;
    int forcaDefesa = rand() % 6 + 1;

    printf("\nAtaque (%s) tirou %d | Defesa (%s) tirou %d\n",
           territorios[atacante].cor, forcaAtaque, territorios[defensor].cor, forcaDefesa);

    // compara resultados para definir o vencedor do confronto
    if (forcaAtaque > forcaDefesa) {
        territorios[defensor].tropas--; // defesa perde uma tropa
        printf("Ataque bem-sucedido! Tropas restantes em %s: %d\n",
               territorios[defensor].nome, territorios[defensor].tropas);
        // se o defensor ficar sem tropas, o território é conquistado
        if (territorios[defensor].tropas <= 0) {
            printf("Território %s conquistado!\n", territorios[defensor].nome);
            strcpy(territorios[defensor].cor, territorios[atacante].cor); // muda o dono do território
            territorios[defensor].tropas = 1; // deixa uma tropa mínima
        }
    } else {
        territorios[atacante].tropas--; // atacante perde uma tropa
        printf("Defesa resistente! Tropas restantes em %s: %d\n",
               territorios[atacante].nome, territorios[atacante].tropas);
    }
}

// Verifica se a missão do jogador foi concluída
int verificarMissao(int missao, const Territorio territorios[], const int tamanho) {
    if (missao == 1) {
        // Missão 1: destruir o exército Verde
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(territorios[i].cor, "Verde") == 0 && territorios[i].tropas > 0) {
                return 0; // ainda existe território com exército verde
            }
        }
        return 1; // todos os verdes foram eliminados
    } else {
        // Missão 2: conquistar 3 territórios da mesma cor
        int contagem = 0;
        const char *jogador = territorios[0].cor; // referência à primeira cor encontrada

        for (int i = 0; i < tamanho; i++) {
            if (strcmp(territorios[i].cor, jogador) == 0)
                contagem++;
        }

        return (contagem >= 3); // retorna verdadeiro se 3 ou mais são da mesma cor
    }
}

// Função para limpar o buffer de entrada (para evitar problemas com scanf)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}