#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    //imprime cabecalho do jogo
    printf("\n\n");
    printf("          P  /_\\  P                              \n");
    printf("         /_\\_|_|_/_\\                            \n");
    printf("     n_n | ||. .|| | n_n          Bem vindo ao    \n");
    printf("     |_|_|nnnn nnnn|_|_|      Jogo de Adivinhação!\n");
    printf("    |" "  |  |_|  |"  " |                         \n");
    printf("    |_____| ' _ ' |_____|                         \n");
    printf("          \\__|_|__/                              \n");
    printf("\n\n");

    int nivel;
    printf("Qual o nível de dificuldade?\n");
    printf("(1) Fácil (2) Médio (3) Difícil\n\n");
    printf("Escolha: ");
    scanf("%d", &nivel);

    int numerodetentativas;

    switch (nivel) {
        case 1: numerodetentativas = 20;
            break;
        case 2: numerodetentativas = 15;
            break;
        default: numerodetentativas = 6;
            break;
    }

    long segundos = time(0); //numero de segundos desde (01/01/1970)
    srand(segundos); //define a seed do meu número randomico como sendo esses segundos

    int numerogrande = rand(); // gera o numero randomico

    int numerosecreto = numerogrande % 100; //limita ele até 100
    int chute;
    int tentativas = 1;
    double pontos = 1000;

    int acertou = 0;

    for(int i = 1; i <= numerodetentativas; i++) {

        printf("Tentativa %d\n", tentativas);
        printf("Qual é o seu chute? ");

        scanf("%d", &chute); //le o input do teclado e armazena a tentavia na variável chute usando o &
        printf("Seu chute foi %d\n", chute);

        if(chute < 0) { //impede a entrada de numeros negativos
            printf("Você não pode chutar números negativos!\n");
            continue;
        }

        acertou = chute == numerosecreto;
        int maior = chute > numerosecreto;

        if(acertou){ //condição de vitoria
            break;
        }

        else if(maior) {//se o numero for maior que o numero secreto...
            printf("Seu chute foi maior que o número secreto\n");
        }

        else { //se for menor...
            printf("Seu chute foi menor que o número secreto\n");
        }

        tentativas++;

        double pontosperdidos = abs(chute - numerosecreto) / (double)2;//muda o tipo do 2 de int pra double usando casting
        pontos = pontos - pontosperdidos;

    }

    printf("Fim de jogo!\n");

    if(acertou) {//se ganhou
        printf("Você ganhou!\n");
        printf("Você acertou em %d tentativas!\n", tentativas);
        printf("Total de pontos: %.1f\n", pontos);
    } else {//se perdeu
        printf("Você perdeu! Tente de novo!\n");
    }
}
