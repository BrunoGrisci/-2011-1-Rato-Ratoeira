#define VERSAO 1.1

/*ALTERACOES DA VERSAO 1.1:
- opcao de pular a introducao a partir do
  return da printanimation
- passei sleep de movimento para plot4chars
  (depois podemos acrescentar um int na
  estrutura rato para a   velocidade e usa-lo
  na plot4chars -> Sleep((*rat).velocidade)
- correcao de alguns trechos do codigo

- sugiro que a primeira opcao do menu seja o branco!!!
- aqui o seletor do menu continua com aquele
  comportamento de descer uma linha depois da
  ultima opcao (resolve tirando os prints \a   */

//06-18-2011
//Jorge Alberto Wagner Filho - E - 205975
//Bruno Iochins Grisci - E - 208151

#include <stdio.h> //printf
#include <conio2.h> //putchxy, gotoxy, kbhit
#include <windows.h> //sleep
#include <string.h> //gets, strlen, strcpy
#include <time.h> //?????

//CORES
#define PRETO 0
#define AZUL 1
#define VERDE 2
#define VERDEAGUA 3
#define VERMELHO 4
#define ROXO 5
#define AMARELO 6
#define BRANCO 7
#define CINZA 8
#define AZULCLARO 9
#define VERDECLARO 10
#define VERDEAGUACLARO 11
#define VERMELHOCLARO 12
#define LILAS 13
#define AMARELOCLARO 14
#define BRANCOBRILHANTE 15

typedef struct coordenada
{
    int xy[2];
} COORDENADA;

typedef struct rato {
    COORDENADA pos_inicial;
    int dir;
    char player[9];
    int tempoinicial;
    int cor;
} RATO;

typedef struct queijo
{
    int valor;
    int visivel;
    int consumido;
    int cor;
    COORDENADA posicao;
} TIPO_QUEIJO;

typedef struct ratoeira
{
    int visivel;
    int gasta;
    int cor;
    COORDENADA posicao;
} RATOEIRA;

void screen (); //monta tela
void introducao (); //mostra autores
void movimento (RATO *rat);
void teclado(RATO *rat); //move rato
void jogador (RATO *rat); //
void plot4chars(RATO *rat, char carac);
void cleanline(int line);
void printstring(int inicio, int linha, char texto[]);
int  printanimation(int inicio, int linha, char texto[]);

void menucor (RATO *rat);
void colorerato(int *cy, RATO *rat);
void limpatabuleiro();

int main (){

    RATO rato = {{33, 13}, 0,{} , 0, BRANCO};
    //time_t tinicio, tfim;
    //tinicio= time(NULL);
    //tfim= time(NULL);
    screen();
    introducao();
    jogador(&rato);
    menucor (&rato);
    limpatabuleiro();
    teclado(&rato);
    return 0;
}

void cleanline(int line) {
    int i, x;
    for (i=0, x=2; i<67; i++, x++) putchxy(x, line, 32);
}

void printstring(int inicio, int linha, char texto[]) {
    gotoxy(inicio, linha); printf ("%s", texto);
}

int printanimation(int inicio, int linha, char texto[]) {
    int i, x, y;
    for (x=inicio, y=linha, i=0; x<(inicio+strlen(texto)); x++, i++) {
        putchxy (x, linha, texto[i]);
        if(kbhit()) {
            getch(); //come caracter digitado
            return 0; //interrompe introducao
        }
        Sleep(120);
    }
    return 1; //segue introducao
}

void screen () {
    //maximo 70x24 (+10x24) //aqui: 68x24 (+12x24)
    //caractere de bloco usado foi o 178 e nao 219
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

    printstring(71, 3, "NIVEL 01");
    printstring(71, 8, "Jogador:");
    printstring(71, 13, " Score:");
    printstring(71, 19, "Queijos:");
}

void introducao() {
    int i;
    printstring(23, 22, "<qualquer tecla para pular>");
    if(printanimation(6, 6, "Jorge Alberto Wagner Filho e"))
        if(printanimation(6, 7, "Bruno Iochins Grisci"))
            if(printanimation(6, 8, "apresentam..."))
                if(printanimation(44, 15, "Rato_Ratoeira"))
                    if(printanimation(44, 16, "versao ")) {
                        printf("%.1f", VERSAO);
                        for (i=0; i<500; i++) {
                            Sleep(1);
                            if (kbhit()) {
                                i=500; //pulo durante o sleep
                                getch();
                            }
                        }
                    }
    cleanline(6); cleanline(7); cleanline(8);
    cleanline(15); cleanline(16); cleanline(22);
    Sleep(333);
}

void plot4chars(RATO *rat, char carac) {
    textcolor((*rat).cor);
    putchxy ((*rat).pos_inicial.xy[0], (*rat).pos_inicial.xy[1], carac);
    putchxy ((*rat).pos_inicial.xy[0]+1, (*rat).pos_inicial.xy[1], carac);
    putchxy ((*rat).pos_inicial.xy[0], (*rat).pos_inicial.xy[1]+1, carac);
    putchxy ((*rat).pos_inicial.xy[0]+1, (*rat).pos_inicial.xy[1]+1, carac);
    if(carac!=32) Sleep(120); //se for o espaço não sleepa
}

void movimento (RATO *rat) {
	switch((*rat).dir) {
		case 0: while ((!kbhit())&&((*rat).pos_inicial.xy[1]!=2)) { //PARA CIMA
                    plot4chars(rat, 32);
                    (*rat).pos_inicial.xy[1]--; plot4chars(rat, 30);
                } break;
        case 1: while ((!kbhit())&&(((*rat).pos_inicial.xy[1]+1)!=23)) { //PARA BAIXO
                    plot4chars(rat, 32);
                    (*rat).pos_inicial.xy[1]++; plot4chars(rat, 31);
                } break;
        case 2: while ((!kbhit())&&((*rat).pos_inicial.xy[0]!=2)) { //ESQUERDA
                    plot4chars(rat, 32);
                    (*rat).pos_inicial.xy[0]--; plot4chars(rat, 17);
                } break;
        case 3: while ((!kbhit())&&(((*rat).pos_inicial.xy[0]+1)!=68)) { //DIREITA
                    plot4chars(rat, 32);
                    (*rat).pos_inicial.xy[0]++; plot4chars(rat, 16);
                } break;
        default: break;
    }
}

void teclado(RATO *rat) {
    int encerra = 1;

    plot4chars(rat, 004);
    do {
        kbhit();
        switch(getch()) {
        case 'w': case 'W':
        case 56:  case 72: (*rat).dir=0;
                           movimento(rat); break; //PARA CIMA
        case 's': case 'S':
        case 'x': case 'X':
        case 50:  case 80: (*rat).dir=1;
                           movimento(rat); break; //PARA BAIXO
        case 'a': case 'A':
        case 52:  case 75: (*rat).dir=2;
                           movimento(rat); break; //ESQUERDA
        case 'd': case 'D':
        case 54:  case 77: (*rat).dir=3;
                           movimento(rat); break; //DIREITA
        case 32: plot4chars(rat, 004); break;//space = pause //aqui irao outras coisas
        case 'Q': case 'q': encerra = 0;
                            textcolor (AMARELOCLARO);
                            gotoxy(2, 24); break;  //QUIT
        default: movimento(rat); break;
        }
    } while(encerra);
}

void jogador (RATO *rat) {
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
    strcpy((*rat).player, jogador); //copia nome para a estrutura
}

void menucor (RATO *rat) {
    #define LIMITESUP 21
    #define LIMITEINF 5
    char seletor = '>';
    int fim=1, cx=28, cy=LIMITEINF, cont=0;
    printstring(26, 3, "- Selecione a cor do rato -");
    putchxy(cx, cy, seletor);
    textcolor (CINZA);
    gotoxy(cx+2, cy); printf ("PRETO");
    textcolor (AZUL);
    gotoxy(cx+2, cy+1); printf ("AZUL");
    textcolor (VERDE);
    gotoxy(cx+2, cy+2); printf ("VERDE");
    textcolor (VERDEAGUA);
    gotoxy(cx+2, cy+3); printf ("VERDE-AGUA");
    textcolor (VERMELHO);
    gotoxy(cx+2, cy+4); printf ("VERMELHO");
    textcolor (ROXO);
    gotoxy(cx+2, cy+5); printf ("ROXO");
    textcolor (AMARELO);
    gotoxy(cx+2, cy+6); printf ("AMARELO");
    textcolor (BRANCO);
    gotoxy(cx+2, cy+7); printf ("BRANCO");
    textcolor (CINZA);
    gotoxy(cx+2, cy+8); printf ("CINZA");
    textcolor (AZULCLARO);
    gotoxy(cx+2, cy+9); printf ("AZUL CLARO");
    textcolor (VERDECLARO);
    gotoxy(cx+2, cy+10); printf ("VERDE CLARO");
    textcolor (VERDEAGUACLARO);
    gotoxy(cx+2, cy+11); printf ("VERDE-AGUA CLARO");
    textcolor (VERMELHOCLARO);
    gotoxy(cx+2, cy+12); printf ("VERMELHO CLARO");
    textcolor (LILAS);
    gotoxy(cx+2, cy+13); printf ("LILAS");
    textcolor (AMARELOCLARO);
    gotoxy(cx+2, cy+14); printf ("AMARELO CLARO");
    textcolor (BRANCOBRILHANTE);
    gotoxy(cx+2, cy+15); printf ("BRANCO BRILHANTE");
    textcolor (BRANCO);
    gotoxy(cx+2, cy+16); printf ("COR ORIGINAL");

    do{
        kbhit();
        switch (getch())
        {
            case 's':
            case 'S':
            case 'x':
            case 'X':
            case 50:
            case 80: putchxy(cx, cy, ' ');
                     cy++;
                     putchxy(cx, cy, seletor); printf ("\a");
                     if (cy > (LIMITESUP))
                     {
                        putchxy(cx, cy, ' ');
                        cy=LIMITEINF;
                     };
                     putchxy(cx, cy, seletor);
                     break;

          case 'w':
          case 'W':
          case 56:
          case 72: putchxy(cx, cy, ' ');
                   cy--;
                   putchxy(cx, cy, seletor); printf ("\a");
                   if (cy < (LIMITEINF))
                   {
                        putchxy(cx, cy, ' ');
                        cy=LIMITESUP;
                   };
                   putchxy(cx, cy, seletor);
                   break;
        case 13: colorerato(&cy, rat);
                  fim=0;
                  break;
        }

    } while (fim);
}

void colorerato(int *cy, RATO *rat) {
    #define LIMITEINF 5

    switch (*cy)
    {
        case LIMITEINF: (*rat).cor = PRETO; break;
        case (LIMITEINF+1): (*rat).cor = AZUL; break;
        case (LIMITEINF+2): (*rat).cor = VERDE; break;
        case (LIMITEINF+3): (*rat).cor = VERDEAGUA; break;
        case (LIMITEINF+4): (*rat).cor = VERMELHO; break;
        case (LIMITEINF+5): (*rat).cor = ROXO; break;
        case (LIMITEINF+6): (*rat).cor = AMARELO; break;
        case (LIMITEINF+7): (*rat).cor = BRANCO; break;
        case (LIMITEINF+8): (*rat).cor = CINZA; break;
        case (LIMITEINF+9): (*rat).cor = AZULCLARO; break;
        case (LIMITEINF+10): (*rat).cor = VERDECLARO; break;
        case (LIMITEINF+11): (*rat).cor = VERDEAGUACLARO; break;
        case (LIMITEINF+12): (*rat).cor = VERMELHOCLARO; break;
        case (LIMITEINF+13): (*rat).cor = LILAS; break;
        case (LIMITEINF+14): (*rat).cor = AMARELOCLARO; break;
        case (LIMITEINF+15): (*rat).cor = BRANCOBRILHANTE; break;
        case (LIMITEINF+16): (*rat).cor = BRANCO; break;
    }
}

void limpatabuleiro() {

    int li;
    for (li=2; li<23; li++)
        cleanline(li);
}
