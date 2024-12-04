#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMANHOCAMP 5   // Define o tamanho do campo de batalha (5x5)
#define TAMANHONICK 50  // Define o tamanho máximo para o apelido do jogador

// Funcao para ler e armazenar o apelido do jogador
void ler_e_armazenar_nick(char nick[], int tamanho, int player) {
    while (1) {
        printf("Adicione seu apelido Player %d \n", player); // Pede ao jogador seu apelido
        fgets(nick, tamanho, stdin); // Lê o apelido digitado e armazena em "nick"

        int posicao_enter = strcspn(nick, "\n"); // Localiza a posição do "Enter" na string
        nick[posicao_enter] = '\0'; // Remove a quebra de linha do final da string
        fflush(stdin); // Limpa o buffer de entrada (para evitar problemas com o "Enter" anterior)

        if (strlen(nick) > 0) {
            break; // Sai do loop se um apelido foi inserido
        } else {
            printf("Voce deve adicionar um nick para o Player %d \n", player);
        }
    }
}

// Funcao para preencher o campo de batalha com barcos
void preenchercamp(int camp[][TAMANHOCAMP], char player[]) {
    for (int i = 1; i <= 4; i++) {  // Cada jogador posiciona 4 barcos
        int pont_barco = (rand() % 4) + 1;  // Atribui um valor aleatório de pontos (1 a 4) para cada barco
        int barco[2];  // Array para armazenar a posição do barco (coluna e linha)

        // Solicita ao jogador a coluna e a linha onde deseja posicionar o barco
        printf("%s, escolha a posicao da coluna para seu barco %d \n", player, i);
        scanf("%d", &barco[0]);
        barco[0]--;  // Ajusta para índice do array (de 0 a 4 em vez de 1 a 5)

        printf("%s, escolha a posicao da linha para seu barco %d \n", player, i);
        scanf("%d", &barco[1]);
        barco[1]--;

        printf("%s, a pontuacao que o barco %d vale eh \"%d\" \n", player, i, pont_barco);

        // Verifica se a posição escolhida está dentro dos limites do campo
        if (barco[0] >= 0 && barco[0] < TAMANHOCAMP && barco[1] >= 0 && barco[1] < TAMANHOCAMP) {
            // Verifica se a posição já está ocupada por outro barco
            if (camp[barco[0]][barco[1]] != 0) {
                printf("Esse espaco ja contem um barco \n");
                i--;  // Reposiciona o barco (tenta novamente)
            } else {
                camp[barco[0]][barco[1]] = pont_barco;  // Coloca o barco na posição escolhida
            }
        } else {
            printf("Valor de posicao invalido (deve ser de 1 a 5)\n");
            i--;  // Reposiciona o barco (tenta novamente)
        }
    }
}

// Funcao para imprimir o campo de batalha do jogador
void imprimir_camp(int camp[][TAMANHOCAMP], char player[]) {
    printf("Campo de %s:\n", player);
    for (int i = 0; i < TAMANHOCAMP; i++) {
        for (int j = 0; j < TAMANHOCAMP; j++) {
            printf("%d ", camp[i][j]);  // Imprime cada posição do campo
        }
        printf("\n");  // Nova linha para cada linha do campo
    }
}

// Funcao para imprimir o placar do jogo
void imprimir_placar(int camp1[][TAMANHOCAMP], int camp2[][TAMANHOCAMP], char player1[], char player2[]) {
    int barcos_restantes_player1 = 0, barcos_restantes_player2 = 0;
    int pontos_player1 = 0, pontos_player2 = 0;

    // Conta quantos barcos restam e soma os pontos para cada jogador
    for (int i = 0; i < TAMANHOCAMP; i++) {
        for (int j = 0; j < TAMANHOCAMP; j++) {
            if (camp1[i][j] > 0) {  // Se a posição tiver um barco
                barcos_restantes_player1++;
                pontos_player1 += camp1[i][j];  // Adiciona a pontuação do barco
            }
            if (camp2[i][j] > 0) {
                barcos_restantes_player2++;
                pontos_player2 += camp2[i][j];
            }
        }
    }

    // Mostra o placar atualizado
    printf("\nPlacar:\n");
    printf("%s - Barcos restantes: %d, Pontos: %d\n", player1, barcos_restantes_player1, pontos_player1);
    printf("%s - Barcos restantes: %d, Pontos: %d\n", player2, barcos_restantes_player2, pontos_player2);
}

// Funcao principal do jogo (turnos de ataque)
void jogar(int camp1[][TAMANHOCAMP], int camp2[][TAMANHOCAMP], char player1[], char player2[]) {
    int acertou_barco_player1 = 0;
    int acertou_barco_player2 = 0;
    char vitorioso[TAMANHONICK] = "";
    int jogadas = 0;

    // O jogo continua ate que alguem acerte 4 barcos ou chegue a 9 rodadas
    while (strlen(vitorioso) == 0 && jogadas < 9) {
        // Turno do Player 1
        int pos_ataque[2];
        printf("%s, escolha a coluna para atacar: ", player1);
        scanf("%d", &pos_ataque[0]);
        printf("%s, escolha a linha para atacar: ", player1);
        scanf("%d", &pos_ataque[1]);

        // Verifica se a posição do ataque é válida
        if (pos_ataque[0] >= 0 && pos_ataque[0] < TAMANHOCAMP && pos_ataque[1] >= 0 && pos_ataque[1] < TAMANHOCAMP) {
            if (camp2[pos_ataque[0]][pos_ataque[1]] != 0) {  // Se houver um barco na posição
                printf("Acertou!\n");
                acertou_barco_player1++;
                camp2[pos_ataque[0]][pos_ataque[1]] = 0;  // Remove o barco (considera destruído)
                if (acertou_barco_player1 == 4) {  // Se o Player 1 destruir 4 barcos, vence o jogo
                    strcpy(vitorioso, player1);
                    break;
                }
            } else {
                printf("Voce errou!\n");
            }
            jogadas++;
        }

        // Atualiza o placar apos o turno do Player 1
        imprimir_placar(camp1, camp2, player1, player2);

        // Turno do Player 2 (similar ao do Player 1)
        printf("%s, escolha a coluna para atacar: ", player2);
        scanf("%d", &pos_ataque[0]);
        printf("%s, escolha a linha para atacar: ", player2);
        scanf("%d", &pos_ataque[1]);

        if (pos_ataque[0] >= 0 && pos_ataque[0] < TAMANHOCAMP && pos_ataque[1] >= 0 && pos_ataque[1] < TAMANHOCAMP) {
            if (camp1[pos_ataque[0]][pos_ataque[1]] != 0) {
                printf("Acertou!\n");
                acertou_barco_player2++;
                camp1[pos_ataque[0]][pos_ataque[1]] = 0;
                if (acertou_barco_player2 == 4) {
                    strcpy(vitorioso, player2);
                    break;
                }
            } else {
                printf("Voce errou!\n");
            }
            jogadas++;
        }

        // Atualiza o placar apos o turno do Player 2
        imprimir_placar(camp1, camp2, player1, player2);
    }

    // Exibe o resultado final do jogo
    if (strlen(vitorioso) > 0) {
        printf("Parabens, %s venceu o jogo!\n", vitorioso);
    } else {
        printf("Jogo empatado!\n");
    }
}

int main() {
    int camp1[TAMANHOCAMP][TAMANHOCAMP] = {0};  // Inicializa o campo do Player 1 com zeros
    int camp2[TAMANHOCAMP][TAMANHOCAMP] = {0};  // Inicializa o campo do Player 2 com zeros
    char player1[TAMANHONICK];
    char player2[TAMANHONICK];

    ler_e_armazenar_nick(player1, TAMANHONICK, 1);  // Lê o apelido do Player 1
    ler_e_armazenar_nick(player2, TAMANHONICK, 2);  // Lê o apelido do Player 2

    preenchercamp(camp1, player1);  // Player 1 posiciona seus barcos
    preenchercamp(camp2, player2);  // Player 2 posiciona seus barcos

    jogar(camp1, camp2, player1, player2);  // Inicia o jogo

}
