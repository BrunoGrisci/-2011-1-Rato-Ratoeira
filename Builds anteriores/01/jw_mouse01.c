//Mouse 0.1 05-20-2011
//Jorge Alberto Wagner Filho - E

//Relatorio de Andamento: 09 de Junho
//Apresentacao na aula pratica do codigo do
//trabalho onde sera formalizada a dupla, e mostrada
//a tela de movimentacao do rato funcionando e as
//estruturas de dados necessarias.

#include <stdio.h>
#include <conio2.h>
//#include <windows.h>

int main (){
    /*int i, j;
    for (i=0; i<70; i++) printf ("%c", 178); printf ("\n");
    for (i=0; i<22; i++) {
        printf("%c", 178);
        for (j=0; j<68; j++) printf (" ");
        printf("%c", 178); printf("\n");
    }
    for (i=0; i<70; i++) printf ("%c", 178); printf ("\n");*/

    //////////////////MONTA TELA
    int i, j;
    for (i=0; i<80; i++) printf ("%c", 178);
    for (i=0; i<23; i++) {
        printf("%c", 178);
        for (j=0; j<67; j++) printf (" ");
        printf("%c", 178);
        for (j=0; j<10; j++) printf (" ");
        printf("%c", 178);
    }
    for (i=0; i<79; i++) printf ("%c", 178); //com 80 pula linha
    //maximo 70x24. aqui: 68x25 + 12x25
    //caractere de bloco usado foi o 178 e nao 219

    //////////////////IMPRIME SIDEBAR
    gotoxy(71, 3); printf ("NIVEL 01");
    gotoxy(71, 8); printf ("Jogador:");
    gotoxy(71, 14); printf (" Score:");
    gotoxy(71, 20); printf ("Queijos:");

    /*/////////////////SWITCH DE TECLAS
    //q – encerra o jogo
    //↑ – muda a direção de movimentação do rato para cima
    //↓ – muda a direção de movimentação do rato para baixo
    //← – muda a direção de movimentação do rato para a esquerda
    //→ – muda a direção de movimentação do rato para a direita
    //barra de espaço para pausa (o tempo do jogo deve descontar as pausas).
    getch();
    switch(getch()) {
        case 72: printf ("CIMA"); break;
        case 80: printf ("BAIXO"); break;
        case 75: printf ("ESQUERDA"); break;
        case 77: printf ("DIREITA"); break;
        case 27: printf ("ESC"); break;
        case 32: break; //space
        case 81: break; //q
        default: printf ("DESCONHECIDA"); break;
    }*/

    ///////////////////RATO POBRE (INSPIRADO POR PING PONG)
    int encerra = 1, x=33, y=13;
    do {
        gotoxy(x,y);
        //putch(82);
        putchxy (x, y, 'R');
        //Sleep(30);
        putchxy (x, y, 32);

        if(x==2 || x==67 || y==2 || y==24) {
            // Sleep(30);


                  // dx = -dx;
        }


        kbhit();
        switch(getch()) {
        case 72: while (!kbhit()) y--; break;
        case 80: while (!kbhit()) y++; break;
        case 75: while (!kbhit()) x--; break;
        case 77: while (!kbhit()) x++; break;
        case 32: break; //space = pause
        case 81: encerra = 0; break; //q
        default: break;
        }
    } while(encerra);

    return 0;
}
