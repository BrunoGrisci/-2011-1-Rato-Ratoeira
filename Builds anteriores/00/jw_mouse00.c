//Mouse 0.0 05-18-2011
//Jorge Alberto Wagner Filho - E - 2059753
//06/09 -> relatorio //07/06 -> apresentar

#include <stdio.h>
#include <conio2.h>
#include <time.h>

int main () {
    int score;

    int i=0, j=0;
    for (i=0; i<80; i++) printf("%c", 219);
    //printf ("\n");
    do {
        printf("%c", 219);
        for (i=0; i<67; i++) printf(" ");
        printf("%c", 219);
        for (i=0; i<10; i++) printf(" ");
        printf("%c", 219);
        // printf("\n");
        j++;
    } while (j<23);
    for (i=0; i<80; i++) printf("%c", 219);
    getch();

    return 0;
}
