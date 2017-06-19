/*Por Bruno Iochins Grisci
Exemplo de função para a criação de um menu com seletor. As opções são mostradas na tela e as teclas são usadas para selecioná-las*/

#include <stdio.h>
#include <conio2.h>

int main ()
{
    #define OPCOES 2
    #define LIMITESUP 14
    #define LIMITEINF 13
    char seletor;
    int fim=1, cx=28, cy=LIMITEINF, cont=0;
    //fflush ();
    putchxy(cx, cy, 'X');
    gotoxy(cx+2, cy); printf ("Retornar");
    gotoxy(cx+2, cy+1); printf ("Sair");
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
                     putchxy(cx, cy, 'X'); printf ("\a");
                     if (cy > (LIMITESUP))
                     {
                        putchxy(cx, cy, ' ');
                        cy=LIMITEINF;
                     };
                     putchxy(cx, cy, 'X');
                     break;

          case 'w':
          case 'W':
          case 56:
          case 72: putchxy(cx, cy, ' ');
                   cy--;
                   putchxy(cx, cy, 'X'); printf ("\a");
                   if (cy < (LIMITEINF))
                   {
                        putchxy(cx, cy, ' ');
                        cy=LIMITESUP;
                   };
                   putchxy(cx, cy, 'X');
                   break;
        }

    } while (fim);
    return 0;
}
