//Mouse 0.3 05-20-2011
//Jorge Alberto Wagner Filho - E - 205975
//Bruno Iochins Grisci - E - 208151

//Relatorio de Andamento: 09 de Junho
//Apresentacao na aula pratica do codigo do
//trabalho onde sera formalizada a dupla, e mostrada
//a tela de movimentacao do rato funcionando e as
//estruturas de dados necessarias.

#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include <time.h>

void screen (); //monta tela
void introducao (); //autores
void movimento (); //move rato pobre

int main (){
    screen();
    introducao();
    movimento();
    return 0;
}

void screen () {
    /*int i, j;
    for (i=0; i<70; i++) printf ("%c", 178); printf ("\n");
    for (i=0; i<22; i++) {
        printf("%c", 178);
        for (j=0; j<68; j++) printf (" ");
        printf("%c", 178); printf("\n");
    }
    for (i=0; i<70; i++) printf ("%c", 178); printf ("\n");*/
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
}

void introducao() {
    int x, y, i;
    char autor1[] = "Jorge Alberto Wagner Filho e",
         autor2[] = "Bruno Iochins Grisci",
         apresenta[] = "apresentam...",
         ratoratoeira[]= "Rato_Ratoeira",
         versao[]= "versao 0.3";

    for (x=6, y=7, i=0; x<34; x++, i++) {
        putchxy (x, y, autor1[i]);
        Sleep(120);
    }
    for (x=6, y=8, i=0; x<26; x++, i++) {
        putchxy (x, y, autor2[i]);
        Sleep(120);
    }
    for (x=6, y=9, i=0; x<19; x++, i++) {
        putchxy (x, y, apresenta[i]);
        Sleep(120);
    }
    for (x=44, y=15, i=0; x<57; x++, i++) {
        putchxy (x, y, ratoratoeira[i]);
        Sleep(120);
    }
    for (x=44, y=16, i=0; x<54; x++, i++) {
        putchxy (x, y, versao[i]);
        Sleep(120);
    }
    Sleep(4000);
    for (x=6, y=7; x<34; x++) putchxy (x, y, 32);
    for (x=6, y=8; x<26; x++) putchxy (x, y, 32);
    for (x=6, y=9; x<19; x++) putchxy (x, y, 32);
    for (x=44, y=15; x<57; x++) putchxy (x, y, 32);
    for (x=44, y=16; x<54; x++) putchxy (x, y, 32);
    Sleep(666);
}

void movimento() {
    ///////////////////RATO POBRE
    int encerra = 1, x=33, y=13;
    putchxy (x, y, 'R');
    do {
        kbhit();
        switch(getch()) {
        case 'w':
        case 72: while ((!kbhit())&&(y!=2)) {
                    putchxy (x, y, 32); y--; putchxy (x, y, 'R'); Sleep(120);
                } break;
        case 's':
        case 80: while ((!kbhit())&&(y!=24)) {
                    putchxy (x, y, 32); y++; putchxy (x, y, 'R'); Sleep(120);
                } break;
        case 'a':
        case 75: while ((!kbhit())&&(x!=2)) {
                    putchxy (x, y, 32); x--; putchxy (x, y, 'R'); Sleep(120);
                } break;
        case 'd':
        case 77: while ((!kbhit())&&(x!=68)) {
                    putchxy (x, y, 32); x++; putchxy (x, y, 'R'); Sleep(120);
                } break;
        case 32: break; //space = pause
        case 'q': encerra = 0; break; //q = quit
        }
    } while(encerra);
}
