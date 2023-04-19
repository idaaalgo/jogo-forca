#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

char palavraSecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesDados = 0;

void abertura(){
    printf("*************************\n");
    printf("*     Jogo da Forca     *\n");
    printf("*************************\n\n");
}

void chuta(){

    char chute;
    scanf(" %c", &chute);

    chutes[chutesDados] = chute;
    chutesDados++;
}

int jaChutou(char letra){

    int achou = 0;

    for(int j=0; j<chutesDados; j++){
        if(chutes[j]==letra){
        achou = 1;
        break;
        }
    }
    return achou;
}

void desenhaForca(){

    int erros = chutesErrados();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(' : ' '),(erros>=1?'_':' '),(erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '),(erros>=2?'|':' '),(erros>=4?'/':' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n",(erros>=5?'/':' '),(erros>=6?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for(int i=0; i<strlen(palavraSecreta); i++){

        int achou = jaChutou(palavraSecreta[i]);
            
        if(achou)
            printf("%c ", palavraSecreta[i]);
        else
            printf("_ ");
    }

    printf("\n");
}

void adicionaPalavra(){
    char quer;
    printf("Você gostaria de adicionar uma nova palavra(frutas somente), no jogo?(S/N)");
    scanf(" %c", &quer);

    if(quer=='S'){

        char novaPalavra[TAMANHO_PALAVRA];
        printf("Digite a fruta para adicionar no banco de dados do jogo\nSem acentos e com letra maiúscula. Exemplo: MAMAO.\n");
        scanf("%s", novaPalavra);

        FILE* f;
        
        f=fopen("palavras.txt", "r+");
        if(f==0){
            printf("Desculpe, banco de dados fora do ar\n\n");
            exit(1);
        }

        int qtd;
        fscanf(f,"%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s",novaPalavra);

        fclose(f);
    }

}

void escolhePalavra(){
    FILE* f;

    f = fopen("palavras.txt", "r");
    if(f==0){
        printf("Desculpe, banco de dados fora do ar\n\n");
        exit(1);
    }

    int qtdDePalavras;
    fscanf(f, "%d", &qtdDePalavras);

    srand(time(0));

    int randomico = rand() % qtdDePalavras;

    for(int i=0;i<=randomico;i++){
        fscanf(f, "%s", palavraSecreta);
    }

    fclose(f);
}

int acertou(){

    for(int i=0;i<strlen(palavraSecreta);i++){
        if(!jaChutou(palavraSecreta[i])){
            return 0;
        }
    }
    return 1;
}
int chutesErrados(){

    int erros = 0;

    for(int i=0; i<chutesDados;i++){
    
        int existe = 0;

        for(int j = 0; j < strlen(palavraSecreta); j++){
            
            if(chutes[i]== palavraSecreta[j]){

            existe = 1;
            break;
            }
        }
        if(!existe)
            erros++;
    }
    return erros;
}

int enforcou(){
    
    return chutesErrados() >=6;
}

int main(){

    escolhePalavra();
    abertura();

    do{

        desenhaForca();

        chuta();

    } while(!acertou() && !enforcou());

    if(acertou()){
        printf("\nParabéns, você ganhou!\n");
        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    }else{
        printf("\nPuxa, você foi enforcado!\n");
        printf("A palavra secreta era **%s**\n\n", palavraSecreta);
        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }

    adicionaPalavra();

    return 0;
}