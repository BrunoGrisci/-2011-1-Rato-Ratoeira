// MALDITOS
// PONTEIROS

#define VERSAO 0.8
//06-03-2011
//Jorge Alberto Wagner Filho - E - 205975
//Bruno Iochins Grisci - E - 208151

#include <stdio.h> //printf
#include <conio2.h> //putchxy, gotoxy
#include <windows.h> //sleep
#include <string.h> //gets
#include <time.h> //?????

typedef struct coordenada
{
    int xy[2];
} COORDENADA;

typedef struct rato {
    COORDENADA pos_incial;
    int dir_inicial;
    char player[9];
    int tempoinicial;
} RATO;

typedef struct queijo
{
    int valor;
    int visivel;
    int consumido;
    COORDENADA posicao;
} TIPO_QUEIJO;

typedef struct ratoeira
{
    int visivel;
    int gasta;
    COORDENADA posicao;
} RATOEIRA;

void screen (); //monta tela
void introducao (); //mostra autores
void movimento (int direcao, int *x, int *y);
void teclado (); //move rato
void jogador (); //
void plot4chars(int *x, int *y, char carac);
void cleanline(int line);
void printstring(int inicio, int linha, char texto[]);
void printanimation(int inicio, int linha, char texto[]);

int main (){
    screen();
    //introducao();
    //RATO rato
    //jogador();
    teclado();
    return 0;
}

void cleanline(int line) {
    int i, x, y;
    for (i=0, x=2; i<67; i++, x++) putchxy(x, line, 32);
}

void printstring(int inicio, int linha, char texto[]) {
    gotoxy(inicio, linha); printf ("%s", texto);
}

void printanimation(int inicio, int linha, char texto[]) {
    int i, x, y;
    for (x=inicio, y=linha, i=0; x<(inicio+strlen(texto)); x++, i++) {
        putchxy (x, linha, texto[i]);
        Sleep(120);
    }
}


void screen () {
    int i, j;
    for (i=0; i<80; i++) printf ("%c", 178);
    for (i=0; i<22; i++) {
        printf("%c", 178);
        for (j=0; j<67; j++) printf (" ");
        printf("%c", 178);
        for (j=0; j<10; j++) printf (" ");
        printf("%c", 178);
    }
    for (i=0; i<80; i++) printf ("%c", 178);
    //maximo 70x24. aqui: 68x24 + 12x24
    //caractere de bloco usado foi o 178 e nao 219

    //////////////////IMPRIME SIDEBAR
    printstring(71, 3, "NIVEL 01");
    printstring(71, 8, "Jogador:");
    printstring(71, 13, " Score:");
    printstring(71, 19, "Queijos:");
}

void introducao() { //futuramente abrir somente com novo jogo
    int cancela = 0;
    printanimation(6, 7, "Jorge Alberto Wagner Filho e");
    printanimation(6, 8, "Bruno Iochins Grisci");
    printanimation(6, 9, "apresentam...");
    printanimation(44, 15, "Rato_Ratoeira");
    printanimation(44, 16, "versao "); printf("%.1f", VERSAO);
    Sleep(4000);
    cleanline(7);
    cleanline(8);
    cleanline(9);
    cleanline(15);
    cleanline(16);
    Sleep(666);
}

void plot4chars(int *x, int *y, char carac) {
    putchxy (*x, *y, carac);
    putchxy (*x+1, *y, carac);
    putchxy (*x, *y+1, carac);
    putchxy (*x+1, *y+1, carac);
}

void movimento (int direcao, int *x, int *y) {
	switch(direcao) {
		case 0: while ((!kbhit())&&(*y!=2)) { //PARA CIMA
                    plot4chars(x, y, 32);
                    *y--; plot4chars(x, y, 30);
                    Sleep(120);
                } break;
        case 1: while ((!kbhit())&&((*y+1)!=23)) { //PARA BAIXO
                    plot4chars(x, y, 32);
                    *y++; plot4chars(x, y, 31);
                    Sleep(120);
                } break;
        case 2: while ((!kbhit())&&(*x!=2)) { //ESQUERDA
                    plot4chars(x, y, 32);
                    *x--; plot4chars(x, y, 17);
                    Sleep(120);
                } break;
        case 3: while ((!kbhit())&&((*x+1)!=68)) { //DIREITA
                    plot4chars(x, y, 32);
                    *x++; plot4chars(x, y, 16);
                    Sleep(120);
                } break;
        default: break;
    }
}

void teclado() {
    int encerra = 1, x=33, y=13;
    int direcao;
    plot4chars(&x, &y, 004);
    do {
        kbhit();
        switch(getch()) {
        case 'w': case 'W':
        case 56:  case 72: direcao=0;
                           movimento(direcao, &x, &y); break; //PARA CIMA
        case 's': case 'S':
        case 'x': case 'X':
        case 50:  case 80: direcao=1;
                           movimento(direcao, &x, &y); break; //PARA BAIXO
        case 'a': case 'A':
        case 52:  case 75: direcao=2;
                           movimento(direcao, &x, &y); break; //ESQUERDA
        case 'd': case 'D':
        case 54:  case 77: direcao=3;
                           movimento(direcao, &x, &y); break; //DIREITA
        case 32: break; //space = pause //aqui irao outras coisas
        case 'Q': case 'q': encerra = 0;
                            gotoxy(2, 25);  break;  //QUIT
        default: movimento(direcao, &x, &y); break;
        }
    } while(encerra);
}

void jogador () {
    int x, y, i; char jogador[9];//8 + \0
    do {
        printstring(30, 13, "Qual o seu nome?");
        printstring(29, 14, "<max 8 caracteres>");
        cleanline(15);
        gotoxy(32, 15); gets(jogador);
    } while (strlen(jogador)>8);
    cleanline(13); cleanline(14); cleanline(15);
    switch (strlen(jogador)) { //centraliza nome
        case 1: printstring(74, 9, jogador); break;
        case 2: printstring(74, 9, jogador); break;
        case 3: printstring(73, 9, jogador); break;
        case 4: printstring(73, 9, jogador); break;
        case 5: printstring(72, 9, jogador); break;
        case 6: printstring(72, 9, jogador); break;
        case 7: printstring(71, 9, jogador); break;
        case 8: printstring(71, 9, jogador); break;
    }
}
