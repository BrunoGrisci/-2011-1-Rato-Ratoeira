#define VERSAO 1.4

//FAVOR TESTAR NOVAMENTE A CRIAÇÃO DE ARQUIVOS .txt NO WINDOWS XP (usar o .exe)

/*ALTERACOES DA VERSA0 1.4:
- Correcao da funcao limpatabuleiro (não limpava a última linha);
- Criacao da estrutura GAME (guarda as informações necessárias para salvar/abrir jogo);
- Atualização das estruturas TIPO_QUEIJO e RATOEIRAS (os campos "consumido" e "gasta" não eram necessários);
- Mudanças nos arquivos .txt (para facilitar, todos os queijos possuem apenas um caractere);
- Agora a funcao nivel funciona corretamente;

- Ainda é necessário corrigir a funcao ordenaqueijos (trechos comentados são apenas testes), com ela pronta será relativamente simples terminar o jogo;
- Pensei em adicionarmos as ratoeiras manualmente nos queijos, daí seria só mandar imprimir elas quando seu queijo respectivo fosse consumido;
- Quando as coordenadas de um dos caracteres do rato se igualar a do queijo[i] (queijo atual), queijo[i].visivel = 0, e queijo[i+1].visivel = 1, pontuacao += queijo[i].valor e QUEIJOS++;*/


/*ALTERACOES DA VERSAO 1.3:
- Correção das funções relacionadas à cor do rato;
- Melhoramento de alguns trechos do código;
- Melhor utilização das funções limpatabuleiro e printcolor;
- Aproveitamento da última linha para avisos ao usuário;
- Funções crianivel1, crianivel2 e crianivel3 para criacao dos arquivos txt.;
- Agora a estrutura TIPO_QUEIJOS recebe um arranjo com as suas ratoeiras;*/

//06-19-2011
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
} RATO;

typedef struct ratoeira
{
    int visivel;
    int cor;
    COORDENADA posicao;
} RATOEIRA;

typedef struct queijo
{
    int valor;
    int visivel;
    int ordem;
    int cor;
    COORDENADA posicao;
    RATOEIRA vrat[176];
} TIPO_QUEIJO;

typedef struct game
{
    RATO rato;
    TIPO_QUEIJO queijo;
    int pontuacao;
} GAME;

//PROTOTIPOS
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
int  menu (int limiteinf, int limitesup, int *cx, int *cy);
void printcolor(int inicio, int linha, int color, char texto[]);

void nivel(TIPO_QUEIJO *queijos, int n, char nivel[9], char narq[11]);
void crianivel1();
void crianivel2();
void crianivel3();
void msghumor ();

void ordenaqueijos (TIPO_QUEIJO queijos[], int n);

//FUNCOES
int main (){

    RATO rato = {{33, 13}, 0,{} , 0, BRANCO};

    TIPO_QUEIJO queijos1[10] = {{0,0,5,AMARELOCLARO,{0,0},{}},
                                {0,0,3,AMARELOCLARO,{0,0},{}},
                                {0,0,2,AMARELOCLARO,{0,0},{}},
                                {0,0,9,AMARELOCLARO,{0,0},{}},
                                {0,0,1,AMARELOCLARO,{0,0},{}},
                                {0,0,7,AMARELOCLARO,{0,0},{}},
                                {0,0,4,AMARELOCLARO,{0,0},{}},
                                {0,0,8,AMARELOCLARO,{0,0},{}},
                                {0,0,6,AMARELOCLARO,{0,0},{}},
                                {0,0,10,AMARELOCLARO,{0,0},{}}};

    TIPO_QUEIJO queijos2[15] = {{0,0,7,AMARELOCLARO,{0,0},{}},
                                {0,0,1,AMARELOCLARO,{0,0},{}},
                                {0,0,2,AMARELOCLARO,{0,0},{}},
                                {0,0,8,AMARELOCLARO,{0,0},{}},
                                {0,0,6,AMARELOCLARO,{0,0},{}},
                                {0,0,10,AMARELOCLARO,{0,0},{}},
                                {0,0,9,AMARELOCLARO,{0,0},{}},
                                {0,0,13,AMARELOCLARO,{0,0},{}},
                                {0,0,3,AMARELOCLARO,{0,0},{}},
                                {0,0,5,AMARELOCLARO,{0,0},{}},
                                {0,0,15,AMARELOCLARO,{0,0},{}},
                                {0,0,14,AMARELOCLARO,{0,0},{}},
                                {0,0,11,AMARELOCLARO,{0,0},{}},
                                {0,0,12,AMARELOCLARO,{0,0},{}},
                                {0,0,4,AMARELOCLARO,{0,0},{}}};

    TIPO_QUEIJO queijos3[16] = {{0,0,6,AMARELOCLARO,{0,0},{}},
                                {0,0,8,AMARELOCLARO,{0,0},{}},
                                {0,0,10,AMARELOCLARO,{0,0},{}},
                                {0,0,2,AMARELOCLARO,{0,0},{}},
                                {0,0,7,AMARELOCLARO,{0,0},{}},
                                {0,0,16,AMARELOCLARO,{0,0},{}},
                                {0,0,12,AMARELOCLARO,{0,0},{}},
                                {0,0,5,AMARELOCLARO,{0,0},{}},
                                {0,0,1,AMARELOCLARO,{0,0},{}},
                                {0,0,9,AMARELOCLARO,{0,0},{}},
                                {0,0,15,AMARELOCLARO,{0,0},{}},
                                {0,0,11,AMARELOCLARO,{0,0},{}},
                                {0,0,13,AMARELOCLARO,{0,0},{}},
                                {0,0,14,AMARELOCLARO,{0,0},{}},
                                {0,0,4,AMARELOCLARO,{0,0},{}},
                                {0,0,3,AMARELOCLARO,{0,0},{}}};

    int i;

    //time_t tinicio, tfim;
    //tinicio= time(NULL);
    //tfim= time(NULL);
    screen();
    introducao();
    jogador(&rato);
    menucor (&rato);
    nivel(queijos1, 10, "NIVEL 01", "nivel1.txt");

    for (i=0; i<10; i++)
    {
        gotoxy (queijos1[i].posicao.xy[0], queijos1[i].posicao.xy[1]);
        textcolor (queijos1[i].cor);
        printf ("%d", queijos1[i].valor);
        Sleep (700);
    }
    limpatabuleiro();
    nivel(queijos2,15,"NIVEL 02", "nivel2.txt");

    for (i=0; i<15; i++)
    {
        gotoxy (queijos2[i].posicao.xy[0], queijos2[i].posicao.xy[1]);
        textcolor (queijos2[i].cor);
        printf ("%d", queijos2[i].valor);
        Sleep (700);
    }
    limpatabuleiro();

    nivel(queijos3,16,"NIVEL 03", "nivel3.txt");

    for (i=0; i<16; i++)
    {
        gotoxy (queijos3[i].posicao.xy[0], queijos3[i].posicao.xy[1]);
        textcolor (queijos3[i].cor);
        printf ("%d", queijos3[i].valor);
        Sleep (700);
    }

    teclado(&rato);
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

    printstring(71, 3, "Krikkit!");
    printstring(71, 8, "Jogador:");
    printstring(71, 13, " Score:");
    printstring(71, 19, "Queijos:");
}

void introducao() {
    int i;
    printcolor(2,25,BRANCO, "Pressione qualquer tecla para pular");
    textcolor(BRANCO);
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
    if(carac!=32) Sleep(120); //se for o espaço não "sleepa"
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
        cleanline(15);
        gotoxy(32, 14); gets(jogador);
        printcolor(2,25,AMARELOCLARO, "Nome com maximo de 8 caracteres");
        textcolor(BRANCO);
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
    cleanline(25);
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

void nivel(TIPO_QUEIJO *queijos, int n, char nivel[9], char narq[11]) {

    int teste=1;
    int seguranca=0;
    int i, y, k, z=0, x;
    char fase[1452];
    char valor[2] = {};
    FILE *arq;
    printcolor (71, 3, BRANCO, nivel);

    do{
        arq = fopen(narq, "r");
        if (!arq)
        {
            seguranca++;
            fclose(arq);
            msghumor();
            if (n==10)
                crianivel1();
                else
                if (n==15)
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
    fprintf(arq1, "3                                   1                            3\n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n            1                                                     \n                                                                  \n                                                                  \n                                                                  \n               5                  4                               \n                                                                  \n                                                                  \n                                                                  \n                                                   2              \n                                                                  \n                                                                  \n                                                                  \n                                           1                      \n                                                                  \n1                                                                2\n");
    fclose(arq1);
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
    fprintf(arq2, "3                                   1                             \n       8                                                         2\n                                                        3         \n                                                                  \n                  2                                               \n                                                             2    \n                                                                  \n                                                                  \n                                                           3      \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                   1                           1                  \n                                                                  \n               2                                                  \n                                                                  \n                                                                  \n                                     3                            \n                                                     4            \n                                                                  \n2                                                             9   \n");
    fclose(arq2);
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
    fprintf(arq3, "                                                                  \n  1                          2 2                               8  \n                                                                  \n                                                                  \n               2                                        1         \n                                                                  \n                                                                  \n                                                                  \n                                               1       3          \n                                                                  \n             7                  2                                 \n                                                                  \n                                                                  \n                                                                  \n                                                                  \n                                                 1     1          \n                                                                  \n           3                                                      \n                                                                  \n                                                                  \n  1                              4                             1  \n                                                                  \n");
    fclose(arq3);
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

void ordenaqueijos (TIPO_QUEIJO *queijos, int n)
{
    int i, fim, sinal;
    TIPO_QUEIJO aux;
    fim = n-1;

    /*gotoxy(30,5);
    textcolor(queijos[0].cor);
    printf ("%d - %d", queijos[0].valor, queijos[0].ordem);
    Sleep(500);

    gotoxy(30,6);
    textcolor(queijos[1].cor);
    printf ("%d - %d", queijos[1].valor, queijos[1].ordem);
    Sleep(500);

    gotoxy(30,7);
    textcolor(queijos[2].cor);
    printf ("%d - %d", queijos[2].valor, queijos[2].ordem);
    Sleep(500);

    gotoxy(30,8);
    textcolor(queijos[3].cor);
    printf ("%d - %d", queijos[3].valor, queijos[3].ordem);
    Sleep(500);*/

    do{
        sinal=0;
        for (i=0;i<fim;i++)
            if (queijos[i].ordem > queijos[i+1].ordem)
            {
                aux = queijos[i];
                queijos[i+1] = aux;
                sinal=1;
            }
        fim--;
    } while ((sinal==1) && (fim>1));

    /*gotoxy(50,5);
    textcolor(queijos[0].cor);
    printf ("%d - %d", queijos[0].valor, queijos[0].ordem);
    Sleep(500);

    gotoxy(50,6);
    textcolor(queijos[1].cor);
    printf ("%d - %d", queijos[1].valor, queijos[1].ordem);
    Sleep(500);

    gotoxy(50,7);
    textcolor(queijos[2].cor);
    printf ("%d - %d", queijos[2].valor, queijos[2].ordem);
    Sleep(500);

    gotoxy(50,8);
    textcolor(queijos[3].cor);
    printf ("%d - %d", queijos[3].valor, queijos[3].ordem);
    Sleep(500);*/
}
