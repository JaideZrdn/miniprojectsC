#include <stdio.h>
#include <string.h>
#include "forca.h"
#include <stdlib.h>
#include <time.h>

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura() {
    printf("*******************\n");
    printf("*  Jogo da Forca  *\n");
    printf("*******************\n\n");
}

void chuta() {
    char chute;
    scanf(" %c", &chute);

    chutes[(chutesdados)] = chute;
    (chutesdados)++;
}

int jachutou(char letra){
    int achou = 0;

    for(int j = 0; j < chutesdados; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;

        }
    }
    return achou;
}

void desenhaforca(){
    for (int i =0; i < strlen(palavrasecreta); i++){

        int achou = jachutou(palavrasecreta[i]);

        if(achou){
            printf(" %c", palavrasecreta[i]);
        }
        else {printf(" _");
        }
    }
}

void escolhepalavra(){
    FILE* f;
    f = fopen("/home/jaidezrdn/CLionProjects/forca/palavras.txt", "r");
    if (f == 0){
        printf("DESCULPE BANCO DE DADOS NAO DISPONÍVEL");
        exit(1);
    }

    int qttdpalavaras;
    fscanf(f, "%d", &qttdpalavaras);
    srand(time(0));
    int randomico = rand() % qttdpalavaras;

    for (int i = 0; i < randomico; i++){
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

int enforcou(){

    int erros = 0;
    for(int i =0; i<chutesdados; i++){
        int existe =0;
        for(int j =0; j<strlen(palavrasecreta); j++){
            if (chutes[i] == palavrasecreta[j]){
                existe = 1;
                break;
            }
        }
        if (!existe){
            erros++;
        }
    }
    return erros >= 5;
}

int acertou() {
    for(int i = 0; i < strlen(palavrasecreta); i++) {
        if(!jachutou(palavrasecreta[i])) {
            return 0;
        }
    }

    return 1;
}

void printfinal(){
    if(acertou()){
        printf("PARABÉNS VOCÊ ACERTOU A PALAVRA\n");
    }
    else{
        printf("PERDEU DOIDO\n");
    }
}

void adicionapalavra(){
    char quer;
    printf("Você quer adicionar uma nova palavra no seu bando de dados? (S/N): \n");
    scanf(" %c", &quer);

    if(quer == 'S'){

        char novapalavra[TAMANHO_PALAVRA];
        printf("Qual a nova palavra?: \n");
        scanf(" %s", novapalavra);

        FILE* f;

        f = fopen("/home/jaidezrdn/CLionProjects/forca/palavras.txt", "r+");

        int qtd;
        fscanf(f, "%d", &qtd);
         qtd++;
        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);
        fclose(f);
    }
}

int main() {

    escolhepalavra();
    abertura();

    do {

        desenhaforca();
        chuta();

    } while(!acertou() && !enforcou());

    printfinal();
    adicionapalavra();
}
