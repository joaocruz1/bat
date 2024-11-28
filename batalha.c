#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMANHOCAMP 5
#define TAMANHONICK 50

char ler_e_armazenar_nick(char nick[],int tamanho, int player){

    while(1){
    printf("Adicone seu apelido Player %d \n", player); 
    fgets(nick, tamanho, stdin); 

    int posicao_enter = strcspn(nick, "\n");
    nick[posicao_enter] = '\0';
    fflush(stdin);

    if (strlen(nick)>0 )
    {
        break;
    }else{
        printf("Voce deve adicionar um nick para o Player %d \n", player);
    }
    
    }
    
}

int preenchercamp(int camp[][TAMANHOCAMP],char player[]){

    for(int i= 1; i<5; i++){

        int pont_barco = (rand() % 4) + 1;
        int barco[2];

        printf("%s; Escolha a posicao da coluna para seu barco %d \n", player, i);
        scanf("%d", &barco[0]);
        barco[0]--;
        printf("%s; Escolha a posicao da linha para seu barco %d \n", player, i);
        scanf("%d", &barco[1]);
        barco[1]--;
        printf("%s; A pontuacao que o barco %d vale eh \"%d\" \n", player, i, pont_barco);
        
        if (barco[0] >= 0 && barco[0] < TAMANHOCAMP && barco[1] >= 0 && barco[1] < TAMANHOCAMP) {
            if (camp[barco[0] ][barco[1] ] != 0) {  
                printf("Esse espaco ja contem um barco \n");
                i--;
            } else {
                camp[barco[0]][barco[1]] = pont_barco;  
            }
        } else {
            printf("Valor de posicao invalido (deve ser de 1 a 5)\n");
            i--;
        }

    }


}

void imprimir_placar(int camp[][TAMANHOCAMP],char player[]){

}

int imprimir_camp(int camp[][TAMANHOCAMP], char player[]){

    printf("Campo de %s :\n", player);
    for(int i = 0; i < TAMANHOCAMP; i++){
        for(int j = 0; j < TAMANHOCAMP; j++){
            printf("%d ", camp[i][j]);
        }
        printf("\n");
    }
}

void jogar(int camp1[][TAMANHOCAMP], int camp2[][TAMANHOCAMP], char player1[], char player2[]) {
    int acertou_barco_player1 = 0;
    int acertou_barco_player2 = 0;
    char vitorioso[TAMANHONICK] = "";
    int jogadas = 0;

    while (strlen(vitorioso) == 0 && jogadas < 9) {

        // Turno do Player 1
        int pos_ataque[2];
        printf("%s, escolha a coluna para atacar: ", player1);
        scanf("%d", &pos_ataque[0]);
        printf("%s, escolha a linha para atacar: ", player1);
        scanf("%d", &pos_ataque[1]);

        // Validação das posições
        if (pos_ataque[0] >= 0 && pos_ataque[0] < TAMANHOCAMP && pos_ataque[1] >= 0 && pos_ataque[1] < TAMANHOCAMP) {
            
            if (camp2[pos_ataque[0]][pos_ataque[1]] != 0) {
                printf("Acertou!\n");
                acertou_barco_player1++;
                camp2[pos_ataque[0]][pos_ataque[1]] = 0; 
                
                if (acertou_barco_player1 == 4) {
                    strcpy(vitorioso, player1);
                    break;
                }
            } else {
                printf("Você errou!\n");
            }
            jogadas++;
        }

        // Turno do Player 2 (semelhante ao turno do Player 1)
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
                printf("Você errou!\n");
            }
            jogadas++;
        }
    }

    // Exibição do resultado final
    if (strlen(vitorioso) > 0) {
        printf("Parabéns, %s venceu o jogo!\n", vitorioso);
    } else {
        printf("Jogo empatado!\n");
    }
}



int main(){

    int camp1[TAMANHOCAMP][TAMANHOCAMP] = {0}; 
    int camp2[TAMANHOCAMP][TAMANHOCAMP] = {0};

    char player1[TAMANHONICK];
    ler_e_armazenar_nick(player1,TAMANHONICK, 1);
    printf("Apelido Player 1: %s \n", player1);
    
    char player2[TAMANHONICK];
    ler_e_armazenar_nick(player2,TAMANHONICK, 2);
    printf("Apelido Player 2: %s \n", player2);

    preenchercamp(camp1,player1);
    preenchercamp(camp2,player2);

    printf("Inciando o jogo !!!!!!!!!! \n");

    imprimir_camp(camp1,player1);
    imprimir_camp(camp2,player2);

    jogar(camp1,camp2,player1,player2);
    
}



