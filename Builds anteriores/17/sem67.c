void imprimequeijos (TIPO_QUEIJO *queijos, RATO *rat, GAME *game, int n)
{
    int i=0; int acabou = 0;

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
                if (!acabou) {
                    queijos[i].visivel = 1;
                    gotoxy (queijos[i].posicao.xy[0], queijos[i].posicao.xy[1]);
                    textcolor (queijos[i].cor);
                    printf ("%d", queijos[i].valor);
                    (*game).nroqueijos++;
                    printint(74,21,BRANCO,(*game).nroqueijos);
                    if (i == (n-1)) acabou = 1;
                }
        }
    }while(i<n);

    limpatabuleiro();
}
