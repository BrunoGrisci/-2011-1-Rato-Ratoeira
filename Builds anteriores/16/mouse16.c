#define VERSAO 1.6

//Mudou muita coisa para escrever tudo aqui.

//Adicionei alteracoes, manti funcoes de velocidade como deletar1 e 2.

/*ALTERACOES DA VERSA0 1.4:
- Correcao da funcao limpatabuleiro (n�o limpava a �ltima linha);
- Criacao da estrutura GAME (guarda as informa��es necess�rias para salvar/abrir jogo);
- Atualiza��o das estruturas TIPO_QUEIJO e RATOEIRAS (os campos "consumido" e "gasta" n�o eram necess�rios);
- Mudan�as nos arquivos .txt (para facilitar, todos os queijos possuem apenas um caractere);
- Agora a funcao nivel funciona corretamente;

- Ainda � necess�rio corrigir a funcao ordenaqueijos (trechos comentados s�o apenas testes), com ela pronta ser� relativamente simples terminar o jogo;
- Pensei em adicionarmos as ratoeiras manualmente nos queijos, da� seria s� mandar imprimir elas quando seu queijo respectivo fosse consumido;
- Quando as coordenadas de um dos caracteres do rato se igualar a do queijo[i] (queijo atual), queijo[i].visivel = 0, e queijo[i+1].visivel = 1, pontuacao += queijo[i].valor e QUEIJOS++;*/


/*ALTERACOES DA VERSAO 1.3:
- Corre��o das fun��es relacionadas � cor do rato;
- Melhoramento de alguns trechos do c�digo;
- Melhor utiliza��o das fun��es limpatabuleiro e printcolor;
- Aproveitamento da �ltima linha para avisos ao usu�rio;
- Fun��es crianivel1, crianivel2 e crianivel3 para criacao dos arquivos txt.;
- Agora a estrutura TIPO_QUEIJOS recebe um arranjo com as suas ratoeiras;*/

//06-27-2011
//Jorge Alberto Wagner Filho - E - 205975
//Bruno Iochins Grisci - E - 208151

//BIBLIOTECAS
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
//VELOCIDADES
#define BAIXA 120
#define MEDIA 90
#define ALTA 60

//
#define LIMQ1 10
#define LIMQ2 15
#define LIMQ3 16

//ESTRUTURAS
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
    int speed;
} RATO;

typedef struct ratoeira
{
    char simbolo;
    int visivel;
    int cor;
    COORDENADA posicao;
} RATOEIRA;

typedef struct queijo
{
    int valor;
    int visivel;
    int cor;
    COORDENADA posicao;
} TIPO_QUEIJO;

typedef struct game
{
    RATO rato;
    TIPO_QUEIJO queijosA[LIMQ1];
    TIPO_QUEIJO queijosB[LIMQ2];
    TIPO_QUEIJO queijosC[LIMQ3];
    float pontuacao;
    int nroqueijos;
} GAME;

//PROTOTIPOS
void screen (); //monta tela
void introducao (); //mostra autores

//void movimento (RATO *rat);
void movimento (RATO *rat, TIPO_QUEIJO *queijos, int i, int *encerra);

//void teclado(RATO *rat); //move rato
void teclado(RATO *rat, TIPO_QUEIJO *queijos, int i);

void jogador (RATO *rat); //
void plot4chars(RATO *rat, char carac);
void cleanline(int line);
void printstring(int inicio, int linha, char texto[]);
int  printanimation(int inicio, int linha, char texto[]);
void menucor (RATO *rat);
void colorerato(int *cy, RATO *rat);
void limpatabuleiro();
int  menu (int limiteinf, int limitesup, int *cx, int *cy);
void printcolor(int inicio, int linha, int color, char texto[]);

void nivel(RATO *rat, TIPO_QUEIJO *queijos, int n, char nivel[9], char narq[11]);
void crianivel1();
void crianivel2();
void crianivel3();
void msghumor ();

void colorequeijos (TIPO_QUEIJO *queijos, int n, int cor);
void imprimequeijos (TIPO_QUEIJO *queijos, RATO *rat, GAME *game, int n);

void deletar1 (RATO *rat);
void deletar2 (int *cy, RATO *rat);

int testaposratoqueijo (RATO *rat, TIPO_QUEIJO *queijos, int i);

void printint (int x, int y, int cor, int i);
void printfloat (int x, int y, int cor, float f);

void cutscene1 ();
void cutscene2 ();
void cutscene3 ();

//FUNCOES
int main (){

    GAME game;

    RATO rato = {{33, 13}, 0,{} , 0, BRANCO, BAIXA};

    TIPO_QUEIJO queijos1[LIMQ1];
    TIPO_QUEIJO queijos2[LIMQ2];
    TIPO_QUEIJO queijos3[LIMQ3];

    game.pontuacao=0;
    game.nroqueijos=0;

    colorequeijos (queijos1,LIMQ1,AMARELOCLARO);
    colorequeijos (queijos2,LIMQ2,AMARELOCLARO);
    colorequeijos (queijos3,LIMQ3,AMARELOCLARO);

    //time_t tinicio, tfim;
    //tinicio= time(NULL);
    //tfim= time(NULL);
    screen();
    introducao();
    jogador(&rato);
    menucor (&rato);

    deletar1(&rato);

    cutscene1();
    nivel(&rato,queijos1,LIMQ1,"NIVEL 01","nivel1.txt");
    imprimequeijos (queijos1,&rato,&game,LIMQ1);
    cutscene2();
    nivel(&rato,queijos2,LIMQ2,"NIVEL 02","nivel2.txt");
    imprimequeijos (queijos2,&rato,&game,LIMQ2);
    cutscene3();
    nivel(&rato,queijos3,LIMQ3,"NIVEL 03", "nivel3.txt");
    imprimequeijos (queijos3,&rato,&game,LIMQ3);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void cleanline(int line) {
    int i, x;
    for (i=0, x=2; i<67; i++, x++) putchxy(x, line, 32);
}

void printstring(int inicio, int linha, char texto[]) {
    gotoxy(inicio, linha); printf ("%s", texto);
}

int printanimation(int inicio, int linha, char texto[]) {
    int i=0, x=inicio, y=linha, cancelou=0;
    while((x<(inicio+strlen(texto)))&&(!cancelou)) {
        putchxy (x, linha, texto[i]);
        Sleep(120);
        if(kbhit()) {
            getch(); //come caracter digitado
            cancelou=1; //interrompe introducao
        }
        i++; x++;
    }
    if(cancelou) return 0;
    else return 1;
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

    printstring(71, 3, "Krikkit!");
    printstring(71, 8, "Jogador:");
    printstring(71, 13, " Score:");
    printstring(71, 19, "Queijos:");
}

void introducao() {
    int i, encerrou=0;
    printcolor(2,25,BRANCO, "Pressione qualquer tecla para pular");
    textcolor(BRANCO);
    encerrou = (printanimation(6, 6, "Jorge Alberto Wagner Filho e"));
    if(encerrou) encerrou = (printanimation(6, 7, "Bruno Iochins Grisci"));
    if(encerrou) encerrou = (printanimation(6, 8, "apresentam..."));
    if(encerrou) encerrou = (printanimation(44, 15, "Rato_Ratoeira"));
    if(encerrou) encerrou = (printanimation(44, 16, "versao "));
    if(encerrou) {
        printf("%.1f", VERSAO);
        for (i=0; i<500; i++) {
            Sleep(1);
            if (kbhit()) {
                i=500; //pulo durante o sleep
                getch();
            }
        }
    }
    limpatabuleiro();
    cleanline(25);
    Sleep(333);
}

void plot4chars(RATO *rat, char carac) {
    textcolor((*rat).cor);
    putchxy ((*rat).pos_inicial.xy[0], (*rat).pos_inicial.xy[1], carac);
    putchxy ((*rat).pos_inicial.xy[0]+1, (*rat).pos_inicial.xy[1], carac);
    putchxy ((*rat).pos_inicial.xy[0], (*rat).pos_inicial.xy[1]+1, carac);
    putchxy ((*rat).pos_inicial.xy[0]+1, (*rat).pos_inicial.xy[1]+1, carac);
   if(carac!=32) Sleep((*rat).speed); //se for o espa�o n�o "sleepa"
}

void movimento (RATO *rat, TIPO_QUEIJO *queijos, int i, int *encerra) {
	switch((*rat).dir) {
		case 0: while (((!kbhit())&&((*rat).pos_inicial.xy[1]!=2))) { //PARA CIMA
                    plot4chars(rat, 32);
                    (*rat).pos_inicial.xy[1]--; plot4chars(rat, 30);
                    if (!testaposratoqueijo(rat,queijos,i))
                        *encerra=0;
                } break;
        case 1: while (((!kbhit())&&(((*rat).pos_inicial.xy[1]+1)!=23))) { //PARA BAIXO

                    plot4chars(rat, 32);
                    (*rat).pos_inicial.xy[1]++; plot4chars(rat, 31);
                    if (!testaposratoqueijo(rat,queijos,i))
                        *encerra=0;
                } break;
        case 2: while (((!kbhit())&&((*rat).pos_inicial.xy[0]!=2))) { //ESQUERDA
                    plot4chars(rat, 32);
                    (*rat).pos_inicial.xy[0]--; plot4chars(rat, 17);
                    if (!testaposratoqueijo(rat,queijos,i))
                        *encerra=0;
                } break;
        case 3: while (((!kbhit())&&(((*rat).pos_inicial.xy[0]+1)!=68))) { //DIREITA
                    plot4chars(rat, 32);
                    (*rat).pos_inicial.xy[0]++; plot4chars(rat, 16);

                    if (!testaposratoqueijo(rat,queijos,i))
                        *encerra=0;
                } break;
        default: break;
    }
}

void teclado(RATO *rat, TIPO_QUEIJO *queijos, int i) {
    int encerra = 1;

    plot4chars(rat, 004);
    do {

        //if (!testaposratoqueijo(rat,queijos,i))
        //    encerra=0;
        //else {

        kbhit();
        switch(getch()) {
        case 'w': case 'W':
        case 56:  case 72: (*rat).dir=0;
                           movimento(rat, queijos, i, &encerra); break; //PARA CIMA
        case 's': case 'S':
        case 'x': case 'X':
        case 50:  case 80: (*rat).dir=1;
                           movimento(rat, queijos, i, &encerra); break; //PARA BAIXO
        case 'a': case 'A':
        case 52:  case 75: (*rat).dir=2;
                           movimento(rat, queijos, i, &encerra); break; //ESQUERDA
        case 'd': case 'D':
        case 54:  case 77: (*rat).dir=3;
                           movimento(rat, queijos, i, &encerra); break; //DIREITA
        case 32: plot4chars(rat, 004); break;//space = pause //aqui irao outras coisas
        /*case 'Q': case 'q': encerra = 0;
                            textcolor (AMARELOCLARO);
                            gotoxy(2, 24); break;  //QUIT*/
        default: movimento(rat, queijos, i, &encerra); break;
        }

        //if ((((*rat).pos_inicial.xy[0] == queijos[i].posicao.xy[0]) && ((*rat).pos_inicial.xy[1] == queijos[i].posicao.xy[1])) ||
            //((((*rat).pos_inicial.xy[0]+1) == queijos[i].posicao.xy[0]) && (((*rat).pos_inicial.xy[1]) == queijos[i].posicao.xy[1])) ||
            //(((*rat).pos_inicial.xy[0] == queijos[i].posicao.xy[0]) && (((*rat).pos_inicial.xy[1]+1) == queijos[i].posicao.xy[0])) ||
            //((((*rat).pos_inicial.xy[0]+1) == queijos[i].posicao.xy[0]) && (((*rat).pos_inicial.xy[1]+1) == queijos[i].posicao.xy[0])))
                //encerra=0;
        //}
    } while(encerra);
}

void jogador (RATO *rat) {
    int x, y, i; char jogador[9];//8 + \0
    do {
        printstring(30, 13, "Qual o seu nome?");
        cleanline(14);
        gotoxy(32, 14); gets(jogador);
        if (strlen(jogador)>8){
            cleanline(25);
            printcolor(2,25,AMARELOCLARO, "Nome com maximo de 8 caracteres");}
        if (strlen(jogador)==0){
            cleanline(25);
            printcolor(2,25,AMARELOCLARO, "Nao seja timido, por favor compartilhe seu nome conosco.");}
        textcolor(BRANCO);
    } while (strlen(jogador)>8 || strlen(jogador)==0);
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
    cleanline(25);
    limpatabuleiro();
    printstring(25,13, "Seja bem-vindo(a),");
    printstring(44,13,jogador);
    Sleep(1000);
    limpatabuleiro();
}

void printcolor(int inicio, int linha, int color, char texto[]) {
    textcolor (color);
    gotoxy(inicio, linha); printf ("%s", texto);
}

void menucor (RATO *rat) {
    int linha, cx=28, cy=5; //LIMITEINF = 5
    char seletor = '>';
    printstring(26, 3, "- Selecione a cor do rato -");
    putchxy(cx, cy, seletor);
    printcolor(cx+2, cy, BRANCO, "COR ORIGINAL");
    printcolor(cx+2, cy+1, CINZA, "PRETO");
    printcolor(cx+2, cy+2, AZUL, "AZUL");
    printcolor(cx+2, cy+3, VERDE, "VERDE");
    printcolor(cx+2, cy+4, VERDEAGUA, "VERDE-AGUA");
    printcolor(cx+2, cy+5, VERMELHO, "VERMELHO");
    printcolor(cx+2, cy+6, ROXO, "ROXO");
    printcolor(cx+2, cy+7, AMARELO, "AMARELO");
    printcolor(cx+2, cy+8, BRANCO, "BRANCO");
    printcolor(cx+2, cy+9, CINZA, "CINZA");
    printcolor(cx+2, cy+10, AZULCLARO, "AZUL CLARO");
    printcolor(cx+2, cy+11, VERDECLARO, "VERDE CLARO");
    printcolor(cx+2, cy+12, VERDEAGUACLARO, "VERDE-AGUA CLARO");
    printcolor(cx+2, cy+13, VERMELHOCLARO, "VERMELHO CLARO");
    printcolor(cx+2, cy+14, LILAS, "LILAS");
    printcolor(cx+2, cy+15, AMARELOCLARO, "AMARELO CLARO");
    printcolor(cx+2, cy+16, BRANCOBRILHANTE, "BRANCO BRILHANTE");
    linha = menu(5, 21, &cx, &cy); //LIMITEINF=5, LIMITESUP=21
    colorerato(&linha, rat);
}

int menu (int limiteinf, int limitesup, int *cx, int *cy) {
	char seletor = '>';
	int fim=1;
    do {
        kbhit();
        switch (getch())
        {
            case 's': case 'S':
            case 'x': case 'X':
            case 50:
            case 80: putchxy(*cx, *cy, ' ');
                     (*cy)++;
                     putchxy(*cx, *cy, seletor);
                     if ((*cy) > (limitesup))
                     {
                        putchxy(*cx, *cy, ' ');
                        (*cy)=limiteinf;
                     };
                     putchxy(*cx, *cy, seletor);
                     break;

        	case 'w': case 'W':
        	case 56:
        	case 72: putchxy(*cx, *cy, ' ');
                     (*cy)--;
                     putchxy(*cx, *cy, seletor);
                     if ((*cy) < (limiteinf))
                     {
                          putchxy(*cx, *cy, ' ');
                          (*cy)=limitesup;
                     };
                     putchxy(*cx, *cy, seletor);
                     break;
        	case 13: fim=0; break;
        }
	} while (fim);
	return *cy;
}

void colorerato(int *cy, RATO *rat) {
    int limiteinf = 5;

    switch (*cy)
    {
        case 5: (*rat).cor = BRANCO; break;
        case 6: (*rat).cor = PRETO; break;
        case 7: (*rat).cor = AZUL; break;
        case 8: (*rat).cor = VERDE; break;
        case 9: (*rat).cor = VERDEAGUA; break;
        case 10: (*rat).cor = VERMELHO; break;
        case 11: (*rat).cor = ROXO; break;
        case 12: (*rat).cor = AMARELO; break;
        case 13: (*rat).cor = BRANCO; break;
        case 14: (*rat).cor = CINZA; break;
        case 15: (*rat).cor = AZULCLARO; break;
        case 16: (*rat).cor = VERDECLARO; break;
        case 17: (*rat).cor = VERDEAGUACLARO; break;
        case 18: (*rat).cor = VERMELHOCLARO; break;
        case 19: (*rat).cor = LILAS; break;
        case 20: (*rat).cor = AMARELOCLARO; break;
        case 21: (*rat).cor = BRANCOBRILHANTE; break;
    }
    limpatabuleiro();
}

void limpatabuleiro() {

    int li;
    for (li=2; li<24; li++)
        cleanline(li);
}

void nivel(RATO *rat, TIPO_QUEIJO *queijos, int n, char nivel[9], char narq[11]) {

    int teste=1;
    int seguranca=0;
    int i, y, k, z=0, x;
    char fase[1452];
    char valor[2] = {};

    (*rat).pos_inicial.xy[0]=33;
    (*rat).pos_inicial.xy[1]=13;

    FILE *arq;
    printcolor (71, 3, BRANCO, nivel);

    do{
        arq = fopen(narq, "r");
        if (!arq)
        {
            seguranca++;
            fclose(arq);
            msghumor();
            if (n==LIMQ1)
                crianivel1();
                else
                if (n==LIMQ2)
                    crianivel2();
                    else
                    crianivel3();
        }
        else
        {
            for (i=0, y=2; i<22; i++, y++)
            {
                fgets(fase, sizeof(fase), arq);
                for (k=0, x=2; k<66; k++, x++)
                {
                    if ((fase[k]!= ' ') && (fase[k]!= '\n'))
                    {
                        valor[0] = fase[k];
                        valor[1] = '\0';
                        queijos[z].posicao.xy[0] = x;
                        queijos[z].posicao.xy[1] = y;
                        queijos[z].valor = atoi(valor);
                        z++;
                    }
                }
            }

        //ordenaqueijos (queijos, n);

        fclose(arq);
        teste=0;
        }
        if (seguranca >= 2)
        {
            printcolor(2,25,AMARELOCLARO, "Erro na criacao do arquivo :(");
            teste=0;
        }
    }while(teste);
}

void crianivel1()
{
    FILE *arq1;
    arq1 = fopen("nivel1.txt", "w");
    if (!arq1)
    {
        printcolor(2,25,AMARELOCLARO, "Erro na criacao do arquivo");
        fclose(arq1);
    }
    else
    {
        fprintf(arq1, "3                                   1                            3\n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n            1                                                     \n                                                                  \n                                                                  \n                                                                  \n               5                  4                               \n                                                                  \n                                                                  \n                                                                  \n                                                   2              \n                                                                  \n                                                                  \n                                                                  \n                                           1                      \n                                                                  \n1                                                                2\n");
        fclose(arq1);
    }
}

void crianivel2()
{
    FILE *arq2;
    arq2 = fopen("nivel2.txt", "w");
    if (!arq2)
    {
        printcolor(2,25,AMARELOCLARO, "Erro na criacao do arquivo");
        fclose(arq2);
    }
    else
    {
        fprintf(arq2, "3                                   1                             \n       8                                                         2\n                                                        3         \n                                                                  \n                  2                                               \n                                                             2    \n                                                                  \n                                                                  \n                                                           3      \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                   1                           1                  \n                                                                  \n               2                                                  \n                                                                  \n                                                                  \n                                     3                            \n                                                     4            \n                                                                  \n2                                                             9   \n");
        fclose(arq2);
    }
}

void crianivel3()
{
    FILE *arq3;
    arq3 = fopen("nivel3.txt", "w");
    if (!arq3)
    {
        printcolor(2,25,AMARELOCLARO, "Erro na criacao do arquivo");
        fclose(arq3);
    }
    else
    {
        fprintf(arq3, "                                                                  \n  1                          2 2                               8  \n                                                                  \n                                                                  \n               2                                        1         \n                                                                  \n                                                                  \n                                                                  \n                                               1       3          \n                                                                  \n             7                  2                                 \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                                                 1     1          \n                                                                  \n           3                                                      \n                                                                  \n                                                                  \n  1                              4                             1  \n                                                                  \n");
        fclose(arq3);
    }
}


void msghumor ()
{
        printcolor(2,25,AMARELOCLARO, "Nivel nao encontrado :(");
        Sleep(1000);
        cleanline(25);
        printcolor(2,25,AMARELOCLARO, "Criando nivel...");
        Sleep(1000);
        cleanline(25);
        printcolor(2,25,AMARELOCLARO, "Coalhando o leite");
        Sleep(1000);
        cleanline(25);
        printcolor(2,25,AMARELOCLARO, "Armando ratoeiras");
        Sleep(1000);
        cleanline(25);
        printcolor(2,25,AMARELOCLARO, "Ralando parmesao");
        Sleep(1000);
        cleanline(25);
        printcolor(2,25,AMARELOCLARO, "Capturando ratos");
        Sleep(1000);
        cleanline(25);
}

void colorequeijos (TIPO_QUEIJO *queijos, int n, int cor)
{
    int i;
    for (i=0;i<n;i++)
        queijos[i].cor = cor;
}

void imprimequeijos (TIPO_QUEIJO *queijos, RATO *rat, GAME *game, int n)
{
    int i=0;

    queijos[i].visivel = 1;
    gotoxy (queijos[i].posicao.xy[0], queijos[i].posicao.xy[1]);
    textcolor (queijos[i].cor);
    printf ("%d", queijos[i].valor);

    do
    {
        if (queijos[i].visivel == 1) {

                teclado(rat, queijos, i);
                (*game).pontuacao += queijos[i].valor;
                printfloat(73,14,BRANCOBRILHANTE,(*game).pontuacao);
                i++;
                queijos[i-1].visivel = 0;
                queijos[i].visivel = 1;
                gotoxy (queijos[i].posicao.xy[0], queijos[i].posicao.xy[1]);
                textcolor (queijos[i].cor);
                printf ("%d", queijos[i].valor);
                (*game).nroqueijos++;
                printint(74,21,BRANCO,(*game).nroqueijos);
        }
    } while (i<n);
    limpatabuleiro();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deletar1 (RATO *rat) {
    int linha, cx=28, cy=13; //LIMITEINF = 10
    char seletor = '>';
    printcolor(15, 11, BRANCO, "Escolha a velocidade do nosso amiguinho");
    putchxy(cx, cy, seletor);
    printcolor(cx+2, cy, BRANCO, "BAIXA");
    printcolor(cx+2, cy+1, BRANCO, "MEDIA");
    printcolor(cx+2, cy+2, BRANCO, "ALTA");
    linha = menu(13, 15, &cx, &cy); //LIMITEINF=10, LIMITESUP=12
    deletar2(&linha, rat);
}

void deletar2 (int *cy, RATO *rat) {
    int limiteinf = 10;

    switch (*cy)
    {
        case 13: (*rat).speed = BAIXA; break;
        case 14: (*rat).speed = MEDIA; break;
        case 15: (*rat).speed = ALTA; break;
    }
    limpatabuleiro();
}

int testaposratoqueijo (RATO *rat, TIPO_QUEIJO *queijos, int i)
{
    if ((((*rat).pos_inicial.xy[0] == queijos[i].posicao.xy[0]) && ((*rat).pos_inicial.xy[1] == queijos[i].posicao.xy[1])) ||
        ((((*rat).pos_inicial.xy[0]+1) == queijos[i].posicao.xy[0]) && (((*rat).pos_inicial.xy[1]) == queijos[i].posicao.xy[1])) ||
        (((*rat).pos_inicial.xy[0] == queijos[i].posicao.xy[0]) && (((*rat).pos_inicial.xy[1]+1) == queijos[i].posicao.xy[1])) ||
        ((((*rat).pos_inicial.xy[0]+1) == queijos[i].posicao.xy[0]) && (((*rat).pos_inicial.xy[1]+1) == queijos[i].posicao.xy[1]))
        )
        return 0;
    else
        return 5;
}

void printint (int x, int y, int cor, int i)
    {
        textcolor(cor);
        gotoxy(x,y);
        printf("  ");
        gotoxy(x,y);
        printf("%d",i);
    }

void printfloat (int x, int y, int cor, float f)
    {
        textcolor(cor);
        gotoxy(x,y);
        printf("  ");
        gotoxy(x,y);
        printf("%.2f",f);
    }

void cutscene1 ()
{
    int i, encerrou=0;
    printcolor(2,25,BRANCO, "Pressione qualquer tecla para pular");
    textcolor(BRANCO);
    encerrou = (printanimation(6, 6, "Rato"));
    if(encerrou) encerrou = (printanimation(6, 8, "Reino:       Animalia"));
    if(encerrou) encerrou = (printanimation(6, 9, "Filo:        Chordata"));
    if(encerrou) encerrou = (printanimation(6, 10, "Classe:      Mammalia"));
    if(encerrou) encerrou = (printanimation(6, 11, "Ordem:       Rodentia"));
    if(encerrou) encerrou = (printanimation(6, 12, "Familia:     Muridae"));
    if(encerrou) encerrou = (printanimation(6, 13, "Genero:      Rattus"));
    if(encerrou) encerrou = (printanimation(6, 14, "Especie:     Rattus exulans"));
    if(encerrou) {
        for (i=0; i<500; i++) {
            Sleep(1);
            if (kbhit()) {
                i=500; //pulo durante o sleep
                getch();
            }
        }
    }
    limpatabuleiro();
    cleanline(25);
    Sleep(333);
}

void cutscene2()
{
    int i, encerrou=0;
    printcolor(2,25,BRANCO, "Pressione qualquer tecla para pular");
    textcolor(BRANCO);
    encerrou = (printanimation(6, 6, "Rato"));
    if(encerrou) encerrou = (printanimation(6, 8, "     Os ratos sao os unicos mamiferos terrestres que podem"));
    if(encerrou) encerrou = (printanimation(6, 9, "nadar por ate 3 dias sem por a cabe�a fora da superficie"));
    if(encerrou) encerrou = (printanimation(6, 10, "para respirar."));
    if(encerrou) encerrou = (printanimation(6, 11, "     A denticao dos murideos e capaz de serrar ou corroer"));
    if(encerrou) encerrou = (printanimation(6, 12, "madeira, aluminio, plastico e ate aco."));
    if(encerrou) encerrou = (printanimation(6, 13,"     A resistencia dos seus dentes e comparada com os"));
    if(encerrou) encerrou = (printanimation(6, 14, "da Onca-pintada, que e o unico carnivoro terrestre cujos dentes"));
    if(encerrou) encerrou = (printanimation(6, 15, "podem perfurar o casco de uma tartaruga."));
    if(encerrou) encerrou = (printanimation(6, 16, "    Os ratos comem diariamente o equivalente a 50% do seu"));
    if(encerrou) encerrou = (printanimation(6, 17, "peso, podendo variar entre 30% e 65%."));
    if(encerrou) {
        for (i=0; i<500; i++) {
            Sleep(1);
            if (kbhit()) {
                i=500; //pulo durante o sleep
                getch();
            }
        }
    }
    limpatabuleiro();
    cleanline(25);
    Sleep(333);
}

void cutscene3()
{
    int i, encerrou=0;
    printcolor(2,25,BRANCO, "Pressione qualquer tecla para pular");
    textcolor(BRANCO);
    encerrou = (printanimation(6, 6, "Rato"));
    if(encerrou) encerrou = (printanimation(6, 8, "     Juntamente com os seres humanos os ratos sao um dos"));
    if(encerrou) encerrou = (printanimation(6, 9, "animais mais adaptaveis do mundo, em relacao a condicoes"));
    if(encerrou) encerrou = (printanimation(6, 10, "geologicas e climaticas."));
    if(encerrou) encerrou = (printanimation(6, 11, "     Os ratos tem o organismo parecido com o dos humanos,"));
    if(encerrou) encerrou = (printanimation(6, 12, "por isso sao usados frequentemente para pesquisas em"));
    if(encerrou) encerrou = (printanimation(6, 13, "laboratorios."));
    if(encerrou) encerrou = (printanimation(6, 14, "     Os murideos foram os unicos mamiferos que nao"));
    if(encerrou) encerrou = (printanimation(6, 15, "sofreram com a radiacao nuclear causada pela bomba"));
    if(encerrou) encerrou = (printanimation(6, 16, "atomica de Hiroshima, no Japao."));
    if(encerrou) encerrou = (printanimation(44, 17, "- Wikipedia"));

    if(encerrou) {
        for (i=0; i<500; i++) {
            Sleep(1);
            if (kbhit()) {
                i=500; //pulo durante o sleep
                getch();
            }
        }
    }
    limpatabuleiro();
    cleanline(25);
    Sleep(333);
}

