//07-05-2011
//Bruno Iochins Grisci - E - 208151
//Jorge Alberto Wagner Filho - E - 205975
//Rato_Ratoeira

//Para este programa, foram enviados um arquivo .exe contendo o executavel do jogo, um arquivo fonte (este), 3 arquivos .txt contendo os valores e posicoes dos queijos em cada nivel e um arquivo binario como exemplo para o ranking.

//Este eh um jogo desenvolvido por alunos do primeiro semestre do curso de Ciencia da Computacao - UFRGS, para a cadeira de Algoritmos e Programacao.

//BIBLIOTECAS
#include <stdio.h> //printf, etc
#include <conio2.h> //putchxy, gotoxy, kbhit
#include <windows.h> //sleep
#include <string.h> //gets, strlen, strcpy
#include <time.h> //clock

//VERSAO
#define VERSAO 2.0
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
#define RELOGIO PRETO
//VELOCIDADES
#define BAIXA 120
#define MEDIA 90
#define ALTA 60
//QUEIJOS E RATOEIRAS
#define LIMQ1 10
#define LIMQ2 15
#define LIMQ3 16
#define NRTRS 109
#define NRR1 23
#define NRR2 46
#define NRR3 40

//ESTRUTURAS
typedef struct coordenada
{//Armazena as coordenadas de algo.
    int xy[2];
} COORDENADA;

typedef struct game
{//Armazena informacoes sobre a partida.
    int nivel;
    float pontuacao;
    float pontos;
    int nroqueijos;
    int queijoatual;
    int numratoeiras;
    int temptempo;
} GAME;

typedef struct rato
{//Armazena informacoes sobre o rato.
    COORDENADA pos_inicial;
    int dir;
    char player[9];
    int tempo;
    int cor;
    int speed;
    GAME game;
} RATO;

typedef struct ratoeira
{//Armazena informacoes sobre as ratoeiras.
    char simbolo;
    int visivel;
    int cor;
    COORDENADA posicao;
} RATOEIRA;

typedef struct queijo
{//Armazena informacoes sobre os queijos.
    int valor;
    int visivel;
    int cor;
    COORDENADA posicao;
} TIPO_QUEIJO;

typedef struct ranking
{//Armazena informacoes sobre o ranking.
    char nome[10];
    float pontuacao;
    int cor;
} RANKING;

//PROTOTIPOS
//FUNCOES PARA IMPRESSAO/LIPEZA
void printint (int x, int y, int cor, int i);
void printfloat (int x, int y, int cor, float f);
void printstring (int inicio, int linha, char texto[]);
int  printanimation (int inicio, int linha, char texto[]);
void printcolor (int inicio, int linha, int color, char texto[]);
void cleanline (int line);
void limpatabuleiro();

//FUNCOES GERAIS
void screen(); //monta tela
void introducao(); //mostra autores
void jogador (RATO *rat);
void jogo (TIPO_QUEIJO queijos1[], TIPO_QUEIJO queijos2[], TIPO_QUEIJO queijos3[],
           RATOEIRA ratoeiras1[], RATOEIRA ratoeiras2[], RATOEIRA ratoeiras3[]);
void incrementatempo (RATO *rat);
void song();

//FUNCOES PARA A MOVIMENTACAO DO RATO
void movimento (RATO *rat, TIPO_QUEIJO *queijos, RATOEIRA *ratoeira, int i, int *encerra, int *morte);
int  teclado (RATO *rat, TIPO_QUEIJO *queijos, RATOEIRA *ratoeira, int i, int *morte);
void plot4chars (RATO *rat, char carac);

//FUNCOES PARA MENUS
int  menu (int limiteinf, int limitesup, int *cx, int *cy);
int  mainmenu (RATO *rat);
int  pausemenu (RATO *rat);
void menucor (RATO *rat);
void colorerato(int *cy, RATO *rat);
void menuspeed (RATO *rat);
void mudaspeed (int *cy, RATO *rat);

//FUNCOES PARA NIVEIS
void nivel (RATO *rat, TIPO_QUEIJO *queijos, int n, char nivel[9], char narq[11]);
void crianivel1();
void crianivel2();
void crianivel3();
void msghumor();
void cutscene1();
void cutscene2();
void cutscene3();

//FUNCOES PARA QUEIJOS E RATOEIRAS
void colorequeijos (TIPO_QUEIJO *queijos, int n, int cor);
void inicializaratoeiras(RATOEIRA *ratoeiras, int n);
int  imprimequeijos (TIPO_QUEIJO *queijos, RATO *rat, RATOEIRA *ratoeira, int n);
int  testaposratoqueijo (RATO *rat, TIPO_QUEIJO *queijos, int i);
int  testaposratoeiras (RATO *rat, RATOEIRA *ratoeira);
void matarato (RATO *rat);

//FUNCOES PARA SALVAR/CARREGAR O JOGO
void loader (RATO *rat);
void save (RATO *rat);
void atualizatela (RATO *rat, RATOEIRA r1[], RATOEIRA r2[], RATOEIRA r3[]);
void continuajogo (RATO *rat, RATOEIRA *r, TIPO_QUEIJO queijo);

//FUNCOES PARA O RANKING
void leranking (RATO *rat);
int  lowscore (RATO *rat, RANKING *king);
void criaranking (RANKING *king);
void imprimeranking (RANKING *king);
void ordenaranking (RANKING *king);
void troca (RANKING *king, int i);
void escreveranking (RANKING *king);
void ranking (RATO *rat);

//FUNCOES
int main (){

    int jogar = 1; int opcoes = 0;

    TIPO_QUEIJO queijos1[LIMQ1];
    TIPO_QUEIJO queijos2[LIMQ2];
    TIPO_QUEIJO queijos3[LIMQ3];
    RATOEIRA ratoeiras1[NRR1];
    RATOEIRA ratoeiras2[NRR2];
    RATOEIRA ratoeiras3[NRR3];

    colorequeijos (queijos1,LIMQ1,AMARELOCLARO);
    colorequeijos (queijos2,LIMQ2,AMARELOCLARO);
    colorequeijos (queijos3,LIMQ3,AMARELOCLARO);

    screen();
    introducao();
    jogo(queijos1, queijos2, queijos3, ratoeiras1, ratoeiras2, ratoeiras3);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void jogo (TIPO_QUEIJO queijos1[], TIPO_QUEIJO queijos2[], TIPO_QUEIJO queijos3[], RATOEIRA ratoeiras1[], RATOEIRA ratoeiras2[], RATOEIRA ratoeiras3[]) {
    int jogar = 1, opcoes = 0, fimdenivel = 0;

    while(jogar) {

        RATO rato = {{33, 13}, 0,{} , 0, BRANCO, BAIXA, {1, 0, 0, 0, 0, 0, 0}};

        inicializaratoeiras(ratoeiras1, NRR1);
        inicializaratoeiras(ratoeiras2, NRR2);
        inicializaratoeiras(ratoeiras3, NRR3);

        do {
            opcoes = mainmenu(&rato);
            if(opcoes) {
                if(opcoes==1) {
                    loader(&rato);
                    atualizatela(&rato, ratoeiras1, ratoeiras2, ratoeiras3);
                }
                if (opcoes==2) jogar = 0;
            }
        } while (opcoes<0);

        if(jogar) {
            rato.game.temptempo = clock();

            if((rato.game.nivel)==1) {
                if (rato.game.queijoatual == 0) cutscene1();
                rato.game.temptempo = clock();
                nivel(&rato,queijos1,LIMQ1,"NIVEL 01","nivel1.txt");
                if(imprimequeijos (queijos1,&rato,ratoeiras1,LIMQ1)) {
                    rato.game.pontos+=10;
                    rato.game.pontuacao = rato.game.pontos / ((float)rato.tempo/60);
                    printfloat(72,14,BRANCOBRILHANTE,rato.game.pontuacao);
                }
            }
            if((rato.game.nivel)==2) {
                if (rato.game.queijoatual == 0) cutscene2();
                rato.game.temptempo = clock();
                nivel(&rato,queijos2,LIMQ2,"NIVEL 02","nivel2.txt");
                if(imprimequeijos (queijos1,&rato,ratoeiras1,LIMQ1)) {
                    rato.game.pontos+=20;
                    rato.game.pontuacao = rato.game.pontos / ((float)rato.tempo/60);
                    printfloat(72,14,BRANCOBRILHANTE,rato.game.pontuacao);
                }
            }
            if((rato.game.nivel)==3) {
                if (rato.game.queijoatual == 0) cutscene3();
                rato.game.temptempo = clock();
                nivel(&rato,queijos3,LIMQ3,"NIVEL 03", "nivel3.txt");
                if(imprimequeijos (queijos3,&rato,ratoeiras3,LIMQ3)) {
                    rato.game.pontos+=30;
                    rato.game.pontuacao = rato.game.pontos / ((float)rato.tempo/60);
                    printfloat(72,14,BRANCOBRILHANTE,rato.game.pontuacao);
                    limpatabuleiro();
                    Sleep(500);
                    printcolor(23,13, AMARELOCLARO, "Obrigado, gracas a voce!!!!");
                    printcolor(17,14, AMARELOCLARO, "o nosso ratinho nao vai morrer de fome!!!!");
                    Sleep(2500); cleanline(13); cleanline(14);
                    ranking(&rato);
                }
            }
            printfloat(72,14,BRANCOBRILHANTE, 0.0);
            printint(74,21,BRANCO, 0);
            if((rato.game.nivel)==4) jogar = 0;
        }
    }
}

void cleanline(int line) {
    //Apaga uma linha passada por parametro.
    int i, x;
    for (i=0, x=2; i<67; i++, x++) putchxy(x, line, 32);
}

void printstring(int inicio, int linha, char texto[]) {
    //Imprime um string em uma posicao determinada.
    gotoxy(inicio, linha); printf ("%s", texto);
}

int printanimation(int inicio, int linha, char texto[]) {
    //Imprime uma string animada.
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
    //Imprime a tela.
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
    //Imprime a introducao.
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
    if (encerrou) song();
    limpatabuleiro();
    cleanline(25);
    Sleep(333);
}

void plot4chars(RATO *rat, char carac) {
    //plota 4 caracteres na tela
    textcolor((*rat).cor);
    putchxy ((*rat).pos_inicial.xy[0], (*rat).pos_inicial.xy[1], carac);
    putchxy ((*rat).pos_inicial.xy[0]+1, (*rat).pos_inicial.xy[1], carac);
    putchxy ((*rat).pos_inicial.xy[0], (*rat).pos_inicial.xy[1]+1, carac);
    putchxy ((*rat).pos_inicial.xy[0]+1, (*rat).pos_inicial.xy[1]+1, carac);
   if(carac!=32) Sleep((*rat).speed); //se for o espa�o n�o "sleepa"
}

void movimento (RATO *rat, TIPO_QUEIJO *queijos, RATOEIRA *ratoeira, int i, int *encerra, int *morte) {
    //move o rato

	switch((*rat).dir) {
		case 0: while (((!kbhit())&&((*rat).pos_inicial.xy[1]!=2)&&(*encerra))) { //PARA CIMA
                    plot4chars(rat, 32);
                    (*rat).pos_inicial.xy[1]--; plot4chars(rat, 30);
                    if (!testaposratoqueijo(rat,queijos,i))
                        *encerra=0;
                    if (!testaposratoeiras(rat,ratoeira))
                        {
                        *encerra=0;
                        *morte=1;
                        }
                } break;
        case 1: while (((!kbhit())&&(((*rat).pos_inicial.xy[1]+1)!=23)&&(*encerra))) { //PARA BAIXO

                    plot4chars(rat, 32);
                    (*rat).pos_inicial.xy[1]++; plot4chars(rat, 31);
                    if (!testaposratoqueijo(rat,queijos,i))
                        *encerra=0;
                    if (!testaposratoeiras(rat,ratoeira))
                        {
                        *encerra=0;
                        *morte=1;
                        }
                } break;
        case 2: while (((!kbhit())&&((*rat).pos_inicial.xy[0]!=2)&&(*encerra))) { //ESQUERDA
                    plot4chars(rat, 32);
                    (*rat).pos_inicial.xy[0]--; plot4chars(rat, 17);
                    if (!testaposratoqueijo(rat,queijos,i))
                        *encerra=0;
                    if (!testaposratoeiras(rat,ratoeira))
                        {
                        *encerra=0;
                        *morte=1;
                        }
                } break;
        case 3: while (((!kbhit())&&(((*rat).pos_inicial.xy[0]+1)!=68)&&(*encerra))) { //DIREITA
                    plot4chars(rat, 32);
                    (*rat).pos_inicial.xy[0]++; plot4chars(rat, 16);
                    if (!testaposratoqueijo(rat,queijos,i))
                        *encerra=0;
                    if (!testaposratoeiras(rat,ratoeira))
                        {
                        *encerra=0;
                        *morte=1;
                        }
                } break;
        default: break;
    }
}

int teclado(RATO *rat, TIPO_QUEIJO *queijos, RATOEIRA *ratoeira, int i, int *morte) {
    //detecta comandos pelo teclado
    int encerra=1, fimdejogo=0, pause;

    movimento(rat, queijos, ratoeira, i, &encerra, morte);
    do {
        kbhit();
        switch(getch()) {
        case 'w': case 'W':
        case 56:  case 72: (*rat).dir=0;
                           movimento(rat, queijos, ratoeira, i, &encerra, morte); break; //PARA CIMA
        case 's': case 'S':
        case 'x': case 'X':
        case 50:  case 80: (*rat).dir=1;
                           movimento(rat, queijos, ratoeira, i, &encerra, morte); break; //PARA BAIXO
        case 'a': case 'A':
        case 52:  case 75: (*rat).dir=2;
                           movimento(rat, queijos, ratoeira, i, &encerra, morte); break; //ESQUERDA
        case 'd': case 'D':
        case 54:  case 77: (*rat).dir=3;
                           movimento(rat, queijos, ratoeira, i, &encerra, morte); break; //DIREITA
        case 32: incrementatempo(rat);
                 limpatabuleiro();
                 pause = pausemenu(rat);
                 if(pause) {
                    if (pause==1) {
                        continuajogo(rat, ratoeira, queijos[i]);
                        (*rat).game.temptempo = clock();
                        movimento(rat, queijos, ratoeira, i, &encerra, morte);
                    }
                    else fimdejogo = 2;
                } break;//space = pause
        case 'Q': case 'q': fimdejogo = 1;
                            textcolor (AMARELOCLARO);
                            gotoxy(2, 24); break;  //quit
        default: movimento(rat, queijos, ratoeira, i, &encerra, morte); break;
        }

    } while((encerra)&&(!fimdejogo));
    return fimdejogo;
}

void jogador (RATO *rat) {
    //novo jogador
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
    cleanline(13); cleanline(14); cleanline(25);
    printstring(71, 9, "         "); textcolor(BRANCO);
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
    printstring(25,13, "Seja bem-vindo(a),");
    printstring(44,13,jogador);
    Sleep(1000);
    cleanline(13);
}

void printcolor(int inicio, int linha, int color, char texto[]) {
    //imprime texto colorido
    textcolor (color);
    gotoxy(inicio, linha); printf ("%s", texto);
}

void menucor (RATO *rat) {
    //Funcao para criacao do menu de troca de cor do rato.
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
    //Funcao para a criacao de menus com seletor.
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
    //Muda cor do rato
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
    if((*rat).tempo) pausemenu(rat);
}

void limpatabuleiro() {
//Limpa toda a tela de jogo.
    int li;
    for (li=2; li<24; li++)
        cleanline(li);
    cleanline(25);
}

void nivel(RATO *rat, TIPO_QUEIJO *queijos, int n, char nivel[9], char narq[11]) {
    //funcao de niveis

    int teste=1;
    int seguranca=0;
    int i, y, k, z=0, x;
    char fase[1452];
    char valor[2] = {};

    //(*rat).pos_inicial.xy[0]=33;
    //(*rat).pos_inicial.xy[1]=13;

    FILE *arq;
    printcolor (71, 3, BRANCO, nivel);

    do{
        arq = fopen(narq, "r");
        if (!arq)
        {
            seguranca++;
            //fclose(arq);
            msghumor();
            if (n == LIMQ1)
                crianivel1();
                else
                if (n == LIMQ2)
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
{//Cria o arquivo nivel1.txt
    FILE *arq1;
    arq1 = fopen("nivel1.txt", "w+");
    if (!arq1) printcolor(2,25,AMARELOCLARO, "Erro na criacao do arquivo");
    else
    {
        fprintf(arq1, "3                                   1                            3\n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n            1                                                     \n                                                                  \n                                                                  \n               5                  4                               \n                                                                  \n                                                                  \n                                                                  \n                                                   2              \n                                                                  \n                                                                  \n                                                                  \n                                           1                      \n                                                                  \n1                                                                2\n");
        if (ferror(arq1))
            printcolor(2,25,AMARELOCLARO, "Erro na criacao do arquivo");
        else fclose(arq1);
    }
}

void crianivel2()
{//Cria o arquivo nivel2.txt
    FILE *arq2;
    arq2 = fopen("nivel2.txt", "w+");
    if (!arq2) printcolor(2,25,AMARELOCLARO, "Erro na criacao do arquivo");
    else
    {
        fprintf(arq2, "3                                   1                             \n       8                                                         2\n                                                                  \n                                                       3          \n                  2                                               \n                                                             2    \n                                                                  \n                                                                  \n                                                           3      \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                   1                           1                  \n                                                                  \n               2                                                  \n                                                                  \n                                                                  \n                                     9                            \n                                                     4            \n                                                                  \n2                                                             3   \n");
        if (ferror(arq2)) printcolor(2,25,AMARELOCLARO, "Erro na criacao do arquivo");
        else fclose(arq2);
    }
}

void crianivel3()
{//Cria o arquivo nivel3.txt
    FILE *arq3;
    arq3 = fopen("nivel3.txt", "w+");
    if (!arq3) printcolor(2,25,AMARELOCLARO, "Erro na criacao do arquivo");
    else
    {
        fprintf(arq3, "                                                                  \n  1                          2 2                               8  \n                                                                  \n                                                                  \n               2                                        1         \n                                                                  \n                                                                  \n                                                                  \n                                               1       3          \n                                                                  \n             7                  2                                 \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                                                 1     1          \n                                                                  \n           3                                                      \n                                                                  \n                                                                  \n  1                              4                             1  \n                                                                  \n");
        if (ferror(arq3))
            printcolor(2,25,AMARELOCLARO, "Erro na criacao do arquivo");
        else fclose(arq3);
    }
}


void msghumor ()
{//Imprime algumas mensagens engracadas.
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
{//Colore os queijos.
    int i;
    for (i=0;i<n;i++)
        queijos[i].cor = cor;
}

int imprimequeijos (TIPO_QUEIJO *queijos, RATO *rat, RATOEIRA *ratoeira, int n)
//apresenta ratos e ratoeiras na tela
{
    int i=(*rat).game.queijoatual,w=(*rat).game.numratoeiras,j,morte=0;
    int acabou = 0, voltar = 0;

    incrementatempo(rat);
    plot4chars(rat, 004);
    queijos[i].visivel = 1;
    gotoxy (queijos[i].posicao.xy[0], queijos[i].posicao.xy[1]);
    textcolor (queijos[i].cor);
    printf ("%d", queijos[i].valor);

    do
    {
        if (queijos[i].visivel == 1) {
                if(teclado(rat, queijos, ratoeira, i, &morte)) {
                    n=0;
                    voltar = 1;
                    (*rat).game.nivel = 5;
                }
                if (!morte)
                {
                    (*rat).game.pontos += queijos[i].valor;
                    incrementatempo(rat);
                    printcolor(71, 25, RELOGIO, ""); printf ("%.2f | %d", (float)(*rat).tempo/60, (*rat).tempo);
                    (*rat).game.pontuacao = (*rat).game.pontos / ((float)(*rat).tempo/60);
                    (*rat).game.nroqueijos++;
                    printfloat(72,14,BRANCOBRILHANTE,(*rat).game.pontuacao);
                    i++;
                    queijos[i-1].visivel = 0;
                    if (!acabou) {
                        queijos[i].visivel = 1;
                        gotoxy (queijos[i].posicao.xy[0], queijos[i].posicao.xy[1]);
                        textcolor (queijos[i].cor);
                        printf ("%d", queijos[i].valor);
                        printf ("\a");
                        if (i == (n-1)) acabou = 1;
                    }
                    (*rat).game.queijoatual = i;

                    for (j=0;j<(queijos[i-1].valor);j++)
                    {
                        gotoxy(ratoeira[w].posicao.xy[0], ratoeira[w].posicao.xy[1]);
                        textcolor(ratoeira[w].cor);
                        printf ("%c", ratoeira[w].simbolo);
                        ratoeira[w].visivel=1;
                        (*rat).game.numratoeiras++;
                        w++;
                    }
                    printint(74,21,BRANCO,(*rat).game.nroqueijos);
                }
                if (morte)
                {
                    n=0;
                    matarato(rat);
                }
        }
    } while (i<n);
    //gotoxy(2,25); //????
    if(!morte) {
        if((*rat).game.nivel<3) (*rat).game.nivel++;
        (*rat).game.queijoatual = 0;
        (*rat).game.numratoeiras = 0;
        limpatabuleiro();
        if(!voltar) return 1;
    }
    limpatabuleiro();
    return 0;
}

void menuspeed (RATO *rat) {
    //Funcao para o menu da selecao de velocidade do rato.
    int linha, cx=28, cy=13; //LIMITEINF = 10
    char seletor = '>';
    printcolor(15, 11, BRANCOBRILHANTE, "Escolha a velocidade do nosso amiguinho");
    putchxy(cx, cy, seletor);
    printcolor(cx+2, cy, BRANCOBRILHANTE, "BAIXA");
    printcolor(cx+2, cy+1, BRANCOBRILHANTE, "MEDIA");
    printcolor(cx+2, cy+2, BRANCOBRILHANTE, "ALTA");
    linha = menu(13, 15, &cx, &cy); //LIMITEINF=10, LIMITESUP=12
    mudaspeed(&linha, rat);
}

void mudaspeed (int *cy, RATO *rat) {
    //Funcao que troca a velocidade do rato.
    int limiteinf = 10;

    switch (*cy)
    {
        case 13: (*rat).speed = BAIXA; break;
        case 14: (*rat).speed = MEDIA; break;
        case 15: (*rat).speed = ALTA; break;
    }
    limpatabuleiro();
    if((*rat).tempo) pausemenu(rat);
}

int testaposratoqueijo (RATO *rat, TIPO_QUEIJO *queijos, int i)
{//Verifica se o rato passou por um queijo.
    if ((((*rat).pos_inicial.xy[0] == queijos[i].posicao.xy[0]) && ((*rat).pos_inicial.xy[1] == queijos[i].posicao.xy[1])) ||
        ((((*rat).pos_inicial.xy[0]+1) == queijos[i].posicao.xy[0]) && (((*rat).pos_inicial.xy[1]) == queijos[i].posicao.xy[1])) ||
        (((*rat).pos_inicial.xy[0] == queijos[i].posicao.xy[0]) && (((*rat).pos_inicial.xy[1]+1) == queijos[i].posicao.xy[1])) ||
        ((((*rat).pos_inicial.xy[0]+1) == queijos[i].posicao.xy[0]) && (((*rat).pos_inicial.xy[1]+1) == queijos[i].posicao.xy[1]))
        )
        return 0;
    else
        return 5;
}

int testaposratoeiras (RATO *rat, RATOEIRA *ratoeira)
{//Verifica se o rato passou por uma ratoeira.
    int i=0;

    while (ratoeira[i].visivel)
    {
        if ((((*rat).pos_inicial.xy[0] == ratoeira[i].posicao.xy[0]) && ((*rat).pos_inicial.xy[1] == ratoeira[i].posicao.xy[1])) ||
        ((((*rat).pos_inicial.xy[0]+1) == ratoeira[i].posicao.xy[0]) && (((*rat).pos_inicial.xy[1]) == ratoeira[i].posicao.xy[1])) ||
        (((*rat).pos_inicial.xy[0] == ratoeira[i].posicao.xy[0]) && (((*rat).pos_inicial.xy[1]+1) == ratoeira[i].posicao.xy[1])) ||
        ((((*rat).pos_inicial.xy[0]+1) == ratoeira[i].posicao.xy[0]) && (((*rat).pos_inicial.xy[1]+1) == ratoeira[i].posicao.xy[1]))
        )
            return 0;
        else
            i++;
    }
    return 5;
}

void printint (int x, int y, int cor, int i)
    {//Imprime um int em uma posicao e cor determinadas.
        textcolor(cor);
        gotoxy(x,y);
        printf("  ");
        gotoxy(x,y);
        printf("%d",i);
    }

void printfloat (int x, int y, int cor, float f)
    {//Imprime um float em uma posicao e cor determinadas.
        textcolor(cor);
        gotoxy(x,y);
        printf("       ");
        gotoxy(x,y);
        printf("%.2f ",f);
    }

void cutscene1 ()
{//Imprime a primeira cutscene.
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
    if (encerrou) song();
    limpatabuleiro();
    cleanline(25);
    Sleep(333);
}

void cutscene2()
{//Imprime a segunda cutscene.
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
    if (encerrou) song();
    limpatabuleiro();
    cleanline(25);
    Sleep(333);
}

void cutscene3()
{//Imprime a terceira cutscene.
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
    if (encerrou) song();
    limpatabuleiro();
    cleanline(25);
    Sleep(333);
}

void inicializaratoeiras(RATOEIRA *ratoeiras, int n)
{//Inicializa os valores da estrutura ratoeira.
    int i,x=7,y=4;

    for (i=0;i<n;i++)
    {
        ratoeiras[i].simbolo = '*';
        ratoeiras[i].cor = AZUL;
        ratoeiras[i].visivel = 0;
        if (x>=66) {
            x=7; y += 1;}
        if (y>=22) {
            y=4; x += 1;}
        ratoeiras[i].posicao.xy[0] = x;
        ratoeiras[i].posicao.xy[1] = y;
        x += 7;
        y += 5;
    }
}

void matarato (RATO *rat)
{//Animacao para a morte do rato.
    gotoxy((*rat).pos_inicial.xy[0],(*rat).pos_inicial.xy[1]);
    textbackground(VERMELHO);
    plot4chars(rat, 004);
    textbackground(PRETO);
    printcolor(2,25,VERDEAGUACLARO, "O... frio... frio...");
    Beep(90,2000);
    Sleep(5000);
    ranking(rat);
}

void song ()
{//Toca uma musica.
    gotoxy(2,2);
    Beep(523,500); // 523 hertz (C5) for 500 milliseconds
    Beep(587,500);
    Beep(659,500);
    Beep(698,500);
    Beep(784,500);
    Sleep(500); // 500 ms delay
    puts("\n");
    Sleep(500);
    puts("\a");
    Sleep(500);
    puts("\a");
}

int mainmenu(RATO *rat) {
    //menu principal do jogo
    int carregar = 0, encerrar = 0, denovo = 0;
    int linha, cx=28, cy=17; //LIMITEINF = 10
    char seletor = '>';

    printcolor(27, 5, AMARELOCLARO, "RATO-RATOEIRA v"); printf("%.1f", VERSAO);
    printcolor(18, 9, AMARELOCLARO, "<W> <A> <S> <D> ou SETAS"); printcolor(44, 9, BRANCOBRILHANTE, "para mover");
    printcolor(16, 11, AMARELOCLARO, "<SPACE>"); printcolor(24, 11, BRANCOBRILHANTE, "para pausar");
    printcolor(38, 11, AMARELOCLARO, "<Q>"); printcolor(42, 11, BRANCOBRILHANTE, "para encerrar");

    textcolor(BRANCO); putchxy(cx, cy, seletor);
    printcolor(cx+2, cy, BRANCOBRILHANTE, "NOVO JOGO");
    printcolor(cx+2, cy+1, BRANCOBRILHANTE, "CARREGAR JOGO");
    printcolor(cx+2, cy+2, BRANCOBRILHANTE, "VER RANKING");
    printcolor(cx+2, cy+3, BRANCOBRILHANTE, "ENCERRAR");
    linha = menu(17, 20, &cx, &cy);
    limpatabuleiro();
    switch (linha)
    {
        case 17: jogador(rat);
                 menucor(rat);
                 menuspeed(rat); break;
        case 18: carregar = 1; break;
        case 19: ranking(rat);
                 denovo = 1; break;
        case 20: encerrar = 1; break;
    }
    if(carregar) return 1;
    if(encerrar) return 2;
    if(denovo) return -1;
    else return 0;
}

void loader (RATO *rat) {
    //solicita nome e carrega arquivo correspondente
    int x, y, i; char jogador[9];//8 + \0
    FILE *arq;
    do {
        printstring(30, 13, "Qual o seu nome?");
        cleanline(14);
        gotoxy(32, 14); gets(jogador);
        cleanline(13); cleanline(14); cleanline(25);

        arq = fopen(jogador, "rb");
        if(!arq) printstring(2, 25, "Arquivo nao encontrado!");
    } while (!arq);

    fread(rat, sizeof(RATO), 1, arq);
    fclose(arq);

    printstring(71, 9, "         "); textcolor(BRANCO);
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
    printstring(25,13, "Seja bem-vindo(a),");
    printstring(44,13,jogador);
    Sleep(1000);
    cleanline(13);
}

void save (RATO *rat) {
    //salva jogo
    FILE *arq;
    arq = fopen ((*rat).player, "wb");
    if (!arq) printstring (2, 25, "Erro no salvamento");
    else {
        fwrite(rat, sizeof(RATO), 1, arq);
        fclose(arq);
    }
    cleanline(25);
    pausemenu(rat);
}

void atualizatela (RATO *rat, RATOEIRA r1[], RATOEIRA r2[], RATOEIRA r3[]) {
    //atualiza informacoes da tela apos carregar arquivo

    int i = 0;
    printcolor (71, 3, BRANCO, "NIVEL 0"); printf("%d", (*rat).game.nivel);
    printint(74,21, BRANCO,(*rat).game.nroqueijos);
    printfloat(72,14, BRANCOBRILHANTE,(*rat).game.pontuacao);

    switch((*rat).game.nivel) {
        case 1: for (i=0; i<(*rat).game.numratoeiras; i++) {
                    gotoxy(r1[i].posicao.xy[0], r1[i].posicao.xy[1]);
                    textcolor(r1[i].cor); printf ("%c", r1[i].simbolo);
                    r1[i].visivel=1;
                } break;
        case 2: for (i=0; i<(*rat).game.numratoeiras; i++) {
                    gotoxy(r2[i].posicao.xy[0], r2[i].posicao.xy[1]);
                    textcolor(r2[i].cor); printf ("%c", r2[i].simbolo);
                    r2[i].visivel=1;
                } break;
        case 3: for (i=0; i<(*rat).game.numratoeiras; i++) {
                    gotoxy(r3[i].posicao.xy[0], r3[i].posicao.xy[1]);
                    textcolor(r3[i].cor); printf ("%c", r3[i].simbolo);
                    r3[i].visivel=1;
                } break;
    }
}

void incrementatempo (RATO *rat) {
    //incrementa o contador de tempo
    int agora;
    clock_t tempo;
    agora = clock();
    tempo = (agora - (*rat).game.temptempo) / CLOCKS_PER_SEC;
    (*rat).tempo += tempo;
    (*rat).game.temptempo = clock();
}

int pausemenu(RATO *rat) {
    //menu de pausa
    int continuar=1;
    int linha, cx=28, cy=11; //LIMITEINF = 10
    char seletor = '>';
    textcolor(BRANCOBRILHANTE); putchxy(cx, cy, seletor);
    printcolor(cx+2, cy, BRANCOBRILHANTE, "CONTINUAR");
    printcolor(cx+2, cy+1, BRANCOBRILHANTE, "TROCAR COR");
    printcolor(cx+2, cy+2, BRANCOBRILHANTE, "TROCAR VELOCIDADE");
    printcolor(cx+2, cy+3, BRANCOBRILHANTE, "SALVAR");
    printcolor(cx+2, cy+4, BRANCOBRILHANTE, "ENCERRAR");
    linha = menu(11, 15, &cx, &cy);
    limpatabuleiro();
    switch (linha)
    {
        case 11: continuar=1; break;
        case 12: menucor(rat); break;
        case 13: menuspeed(rat); break;
        case 14: printcolor(2,25,AMARELOCLARO, "Jogo salvo com sucesso!"); Sleep(999);
                 save(rat); break;
        case 15: continuar = 2; break;
    }
    return continuar;
}

void continuajogo (RATO *rat, RATOEIRA *r, TIPO_QUEIJO queijo) {
    //atualiza informacoes apos pausa
    int i=0;
    plot4chars(rat, 004);
    while (r[i].visivel) {
        gotoxy(r[i].posicao.xy[0], r[i].posicao.xy[1]);
        textcolor(r[i].cor);
        printf ("%c", r[i].simbolo);
        i++;
    }
    gotoxy (queijo.posicao.xy[0], queijo.posicao.xy[1]);
    textcolor (queijo.cor); printf ("%d", queijo.valor);
}

///////////////////////////////////////////////////////////////////////////////////// RANKING

void ranking (RATO *rat)
{//Chama as funcoes para o ranking.
    leranking (rat);
}

void leranking (RATO *rat)
{//Le as informacoes do ranking de um arquivo binario, atualiza e salva.
    RANKING king[10];
    int ind, teste=1, seguranca=2;
    FILE *arq;

    do {
        arq = fopen ("ratoranking", "rb");
        if (!arq)
        {
            printcolor(2,25,AMARELOCLARO, "Gerando ranking!");
            Sleep(500);
            cleanline(25);
            criaranking(king);
            //fclose(arq);
            seguranca = seguranca-1;
        }
        else
        {
            fread (king,sizeof(king),1,arq);
            ind = lowscore (rat, king);
            if (ind != 777)
            {
                strcpy (king[ind].nome, (*rat).player);
                king[ind].pontuacao = (*rat).game.pontuacao;
                king[ind].cor = (*rat).cor;

            }
            teste = 0;
            fclose(arq);
        }


    } while(teste && seguranca);

    arq = fopen ("ratoranking", "wb");
    if (!arq)
    {
        printcolor(2,25,AMARELOCLARO, "Erro na criacao do ranking!");
        fclose(arq);
    }
    else
    {
        fwrite (king, sizeof(king),1,arq);
        if (ferror(arq))
        {
            printcolor(2,25,AMARELOCLARO, "Erro na criacao do ranking!");
            //fclose(arq);
        }
        else
        {
            fclose(arq);
        }
    }
    ordenaranking(king);
}

int lowscore (RATO *rat, RANKING *king)
{//Devolve o indice da menor pontucao no ranking.
    int i, aux=1000, auxi;
    for (i=0;i<10;i++)
    {
        if (king[i].pontuacao < aux)
        {
            aux = king[i].pontuacao;
            auxi = i;
        }
    }

    if ((*rat).game.pontuacao > aux)
        return auxi;
    else
        return 777;
}

void criaranking (RANKING *king)
{//Cria o arquivo binario que contem a estrutura ranking.
    FILE *arq;
    int i, ind;

    for (i=0;i<10;i++)
    {
        strcpy (king[i].nome, "vazio");
        king[i].pontuacao = 0.00;
    }

    arq = fopen ("ratoranking", "wb");
    if (!arq) printcolor(2,25,AMARELOCLARO, "Erro na criacao do ranking!");
    else
    {
        fwrite (king, sizeof(king),1,arq);
        if (ferror(arq)) printcolor(2,25,AMARELOCLARO, "Erro na criacao do ranking!");
        else fclose(arq);
    }
}

void imprimeranking (RANKING *king)
{//Imprime o ranking na tela.
    int x=30, y=10, i, teste=1;
    limpatabuleiro();
    printcolor(2,25,AMARELOCLARO, "Pressione <ESC> para sair.");
    printcolor(30,6,BRANCOBRILHANTE,"- TOP 10 -");
    printfloat(29,9,king[0].cor,king[0].pontuacao);
    printcolor(36,9,king[0].cor,king[0].nome);

    for (i=1;i<10;i++)
    {

        printfloat(x,y,BRANCO,king[i].pontuacao);
        printcolor(x+6,y,BRANCO,king[i].nome);
        y++;
    }
    do{
        switch(getch())
        {
            case  27: limpatabuleiro();
                      teste=0;
                      break;
            case 'c':
            case 'C': cleanline(25);
                      printcolor(2,25,AMARELOCLARO, "The cheese is a lie.");
                      break;
            case 'R':
            case 'r': cleanline(25);
                      printcolor(2,25,AMARELOCLARO, "Nenhum rato foi ferido durante a realizacao deste jogo.");
                      break;
            case 'V':
            case 'v': cleanline(25);
                      printcolor(2,25,AMARELOCLARO, "Vitoria nao e tudo, so a melhor parte.");
                      break;
            case ' ': //teste = 0;
                        break;
            default: //cleanline(25);
                      break;
        }
    } while (teste);
}

void ordenaranking (RANKING *king)
{//Ordena o ranking pela pontuacao.
    int i,trocou,qnt=10;

    do {
        qnt--;
        trocou=0;
        for (i=0;i<qnt;i++)
            if (king[i].pontuacao < king[i+1].pontuacao)
            {
                troca (king,i);
                trocou=1;
            }
    } while (trocou);

    imprimeranking(king);
}

void troca (RANKING *king, int i)
{//Realiza a troca de dois valores dentro do ranking.
    int aux=0;
    char auxchar[9];

    aux = king[i].pontuacao;
    strcpy (auxchar,king[i].nome);

    king[i].pontuacao = king[i+1].pontuacao;
    strcpy (king[i].nome, king[i+1].nome);

    king[i+1].pontuacao = aux;
    strcpy (king[i+1].nome, auxchar);
}

//Fim do codigo fonte.
