#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMANHOCAMP 5
#define TAMANHONICK 50


int camp0(int camp1[][TAMANHOCAMP],int camp2[][TAMANHOCAMP]){
    for(int i = 0; i<5; i++){
        for(int j = 0; j<5; j++){
            camp1[i][j] = 0;
            camp2[i][j]= 0;
        }
    }
}

char ler_e_armazenar_nick(char nick[],int tamanho, int player){

    while(1){
    printf("Adicone seu apelido Player %d \n", player); 
    fgets(nick, tamanho, stdin); // fgets adiciona no final da string o ENTER (\n)

    int posicao_enter = strcspn(nick, "\n");
    nick[posicao_enter] = '\0';

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
        scanf("%d", &barco[0]-1);
        printf("%s; Escolha a posicao da linha para seu barco %d \n", player, i);
        scanf("%d", &barco[1]-1);
        printf("%s; A pontuacao que o barco %d vale eh \"%d\" \n", player, i, pont_barco);
        
        if(barco[0] < 6 && barco[1] <5 && barco[0]> 0 && barco[1]> 0 ){

            if(camp[barco[0]][barco[1]] != 0){
                printf("Esse espaco ja contem um barco \n");
                i--;

            }else{
                camp[barco[0]][barco[1]] = pont_barco;
            }
        }else{
            printf("Valor de posicao invalido(deve ser de 1 a 5)");
            i--;
            
        }
    }


}
int main(){

    int jogadas = 0;
    int vitorioso = 0;

    int camp1[TAMANHOCAMP][TAMANHOCAMP];
    int camp2[TAMANHOCAMP][TAMANHOCAMP];
    camp0(camp1,camp2);

    char player1[TAMANHONICK];
    ler_e_armazenar_nick(player1,TAMANHONICK, 1);
    printf("Apelido Player 1: %s \n", player1);
    
    char player2[TAMANHONICK];
    ler_e_armazenar_nick(player2,TAMANHONICK, 2);
    printf("Apelido Player 2: %s \n", player2);

    preenchercamp(camp1,player1);
    preenchercamp(camp2,player2);

    printf("Inciando o jogo !!!!!!!!!!");

    while(vitorioso == 0 || jogadas <8){
        
    }

    
}



