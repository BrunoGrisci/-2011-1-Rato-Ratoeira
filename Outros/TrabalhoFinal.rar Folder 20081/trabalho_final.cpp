/* Algoritmos e Programa��o - Professora Mara Abel - CIC 2008/1
   Sistema de Controle A�reo - Bruno Jurkovski e Marcos Vin�cius Cavinato */

#include "sca.h"

//Separa Data///////////////////////////////////////////////////////////////////
/* Recebe como par�metros strings que ser�o preenchidas com o dia, mes e ano do
   sistema, separando a string de data do formato MMDDAA em 3 strings menores */
void separaData(char *dia, char *mes, char *ano)
{
     int i=0, j=0;
     char data[30];
     
     _strdate(data); //Pega a data do sistema
     
     while(i<strlen(data) && data[i] != '/'){ //Enquanto n�o achar um '/', copia o m�s para outra string
           mes[j] = data[i];
           j++;
           i++;
     }
     //Coloca o caracter especial, inicializa o �ndice 'j' e descarta a '/' (com o i++)
     mes[j] = '\0';
     i++; j=0;
     while(i<strlen(data) && data[i] != '/'){ //Enquanto n�o achar um '/', copia o dia para outra string
           dia[j] = data[i];
           j++;
           i++;
     }
     //Coloca o caracter especial, inicializa o �ndice 'j' e descarta a '/' (com o i++)
     dia[j] = '\0';
     i++; j=0;
     while(i<strlen(data)){//Vai at� o fim da string original da data
           ano[j] = data[i];
           j++;
           i++;
     }
     ano[j] = '\0'; //Coloca o caracter especial
}
////////////////////////////////////////////////////////////////////////////////


//Liga Status///////////////////////////////////////////////////////////////////
/* Alterna as cores do quadrado da barra inferior entre verde e vermelho, dependendo
   do valor recebido como par�metro (TRUE ou FALSE) */
void ligaStatus(int flag)
{
    int cor;
    if(flag == TRUE)
            cor = GREEN;
    else
            cor = RED;
    
    gotoxy(4,24);        
    textbackground(cor);
    printf(" ");
}
////////////////////////////////////////////////////////////////////////////////


//Desenha Topo//////////////////////////////////////////////////////////////////
/* Dado um determinado tamanho, desenha a parte superior de um 'quadro' */
void desenha_topo(int tamanho)
{
     int i;
     printf("%c", 201); //Canto esquerda-cima
     for (i=0; i<tamanho; i++)
        printf("%c", 205); //Borda horizontal
     printf("%c", 187); //Canto direita-cima
}
////////////////////////////////////////////////////////////////////////////////


//Desenha Base//////////////////////////////////////////////////////////////////
/* Dado um determinado tamanho, desenha a parte inferior de um 'quadro' */
void desenha_base(int tamanho)
{
     int i;
     printf("%c", 200); //Canto esquerda-baixo
     for (i=0; i<tamanho; i++)
        printf("%c", 205); //Borda horizontal
     printf("%c", 188); //Canto direita-baixo
}
////////////////////////////////////////////////////////////////////////////////


//Desenha Lateral///////////////////////////////////////////////////////////////
//A fun��o recebe como argumento uma linha e desenha a borda lateral desta.
void desenha_lateral(int linha)
{
     //Muda cor do fundo para cinza escuro e do texto para preto.
     textbackground(DARKGRAY);
     textcolor(BLACK);
     gotoxy(1,linha); //Vai para a linha recebida como argumento e come�a a desenhar a borda
     printf("%c", 186); //Borda lateral
     gotoxy(80,linha);
     printf("%c", 186); //Borda lateral
}
////////////////////////////////////////////////////////////////////////////////


//Backspace/////////////////////////////////////////////////////////////////////
/* Dados uma string, o �ndice atual e uma posi��o (x, y), troca o caracter atual
   e o anterior pelo sinal especial de fim de string, apaga o caracter digitado
   da tela e volta o cursor e o �ndice do vetor */
void backspace(char* comando, int* i, int* x, int* y)
{
     if(*i>0){  
         comando[*i] = '\0';    //Substitui o caracter digitado (backspace) e o anterior pelo
         comando[*i-1] = '\0'; //delimitador de fim de string
         gotoxy(*x-1,*y);     //Volta o cursor uma posi��o
         printf(" ");         //Coloca um espa�o no lugar do antigo caracter
         gotoxy(*x-2,*y);     //Volta o cursor duas posi��es
         (*i)--;              //Decrementa os �ndices para corrigir o vetor
         (*x)--;
     }
}
////////////////////////////////////////////////////////////////////////////////


//Ajuda/////////////////////////////////////////////////////////////////////////
/* Simula uma janela pop-up na tela com os comandos dispon�veis na linha de
   comando */
void ajuda()
{
    int i;
    
    //Troca o fundo para azul, a cor do texto para cinza e esconde o cursor
    textbackground(BLUE);
    textcolor(LIGHTGRAY);
    _setcursortype(_NOCURSOR);
    
    gotoxy(20,8);
    desenha_topo(40);

    gotoxy(20,9);
    printf("%c            AJUDA - COMANDOS            %c", 186, 186);
    gotoxy(20,10);
    printf("%c                                        %c", 186, 186);
    gotoxy(20,11);
    printf("%c - COD_VOO  COD_PISTA                   %c", 186, 186);
    gotoxy(20,12);
    printf("%c - parar                                %c", 186, 186);
    
    gotoxy(20,13);
    desenha_base(40);
    
    getch();
    //Ativa a interface gr�fica           
    desenha_tela(); 
}
////////////////////////////////////////////////////////////////////////////////


//Pop-up////////////////////////////////////////////////////////////////////////
/* Recebe como par�metro a cor do fundo, cor do texto, largura e altura e cria uma
   "janela" com essas cores e dimens�es */
void popup(int cor_fundo, int cor_texto, int tam_x, int tam_y)
{
     //Troca a cor do fundo e do texto para os valores recebidos e esconde o cursor
     textbackground(cor_fundo);
     textcolor(cor_texto);
     _setcursortype(_NOCURSOR);
     
     int i=4, j=0;
     int x_inicial = (LINHA - tam_x)/2; //Define a posi��o x inicial
    
     //Desenha o topo da pop-up
     gotoxy(x_inicial,i);
     desenha_topo(tam_x);
     
     for (i=5; i<(tam_y+5); i++){
         gotoxy(x_inicial,i);
         printf("%c", 186);
         for(j=0; j<tam_x; j++)
             printf(" ");
         printf("%c", 186);
     }
    
     textbackground(cor_fundo);
     textcolor(cor_texto);
     //Desenha a base da pop-up
     gotoxy(x_inicial,i);
     desenha_base(tam_x);
}
////////////////////////////////////////////////////////////////////////////////


//Linha de Comando - Highlight//////////////////////////////////////////////////
/* Faz com que a cor do fundo do campo 'Linha de Comando' alterne entre vermelho
   e verde, caso esteja selecionado */
void lc_highlight(int flag)
{
    int c_fundo, c_texto;
    
    if(flag){ //Se a flag for verdadeira (TRUE), troca as cores para verde e branco
             c_fundo = GREEN;
             c_texto = WHITE;
    }
    else { //Se for falsa (FALSE), troca as cores para vermelho e cinza claro
         c_fundo = RED;
         c_texto = LIGHTGRAY;
    }
    
    //Desenha o 't�tulo' da linha de comando
    gotoxy(3,14);
    textbackground(c_fundo);
    textcolor(c_texto);
    printf(" Linha de comando                                                           ");
    desenha_lateral(14);
    
    //Desenha o 'campo' da linha de comando
    gotoxy(3,15);
    textbackground(BLACK);
    textcolor(LIGHTGRAY);
    printf(" %c                                                                          ", 175);
    desenha_lateral(15);
}
////////////////////////////////////////////////////////////////////////////////


//Separa Comandos///////////////////////////////////////////////////////////////
void separa_comando(char *comando, char *codVoo, char *codPista)
{
     int j=0, k=0;
     
     while((comando[j] != ' ') && (j<strlen(comando))){ //Enquanto n�o encontrar o espa�o
         codVoo[k] = toupper(comando[j]);              //copia os caracteres para a string codVoo
         k++;
         j++;
     }
     codVoo[k] = '\0'; //Coloca o caracter especial no final da string
     
     j++; //Descarta o espa�o
     k=0; //Vai para posi��o inicial da pr�xima string
     
     while(j<strlen(comando)){               //Enquanto n�o chegar ao fim da string
         codPista[k] = toupper(comando[j]); //copia os caracteres para a string codPista
         k++;
         j++;
     }
     codPista[k] = '\0';  //Coloca o caracter especial no final da string    
}
////////////////////////////////////////////////////////////////////////////////


//Busca Avi�o///////////////////////////////////////////////////////////////////
/* Recebe como par�metro o c�digo a ser procurado, o vetor de avi�es e o seu 
   tamanho e retorna o endere�o do avi�o com o c�digo recebido, caso este seja 
   encontrado. Caso contr�rio, retorna NULL */
AVIAO * busca_aviao(int codigo, AVIAO *arrAviao, int tamanho)
{
      int i;
      
      for (i=0; i<tamanho; i++){
          if(arrAviao[i].codAviao == codigo)
                     return &arrAviao[i];
      }
      
      return NULL;
}
////////////////////////////////////////////////////////////////////////////////


//Busca Cod. Aviao//////////////////////////////////////////////////////////////
/* Recebe como par�metro o c�digo de v�o a ser procurado, o vetor de v�os e o seu 
   tamanho e retorna o c�digo do avi�o daquele v�o, caso este seja  encontrado. 
   Caso contr�rio, retorna FALSE */
int busca_codAviao(char *codVoo, VOO *arrVoo, int tamVoo)
{
    int i;
    for (i=0; i<tamVoo; i++){
        if( strcmp(codVoo, arrVoo[i].codVoo) == 0 )
            return arrVoo[i].codAviao;
    }
    
    return FALSE;
}
////////////////////////////////////////////////////////////////////////////////


//Busca Pista///////////////////////////////////////////////////////////////////
/* Recebe como par�metro o c�digo de pista a ser procurado, o vetor de pistas e 
   o seu tamanho e retorna o �ndice em que essa pista se encontra no vetor de 
   pistas, caso seja  encontrado.  Caso contr�rio, retorna -1 */
int busca_pista(char *codPista, PISTA *arrPista, int tamanho)
{
      int i;
      
      for (i=0; i<tamanho; i++){
          if(strcmp(arrPista[i].codPista, codPista) == 0)
                     return i;
      }
      
      return -1;
}
////////////////////////////////////////////////////////////////////////////////


//Testa Pouso///////////////////////////////////////////////////////////////////
/* Recebe um avi�o, uma pista e a string com o c�digo da pista ocupada no turno
   atual e verifica se o avi�o pode pousar nesta pista */
int testa_pouso(AVIAO *av, PISTA p_pouso, char *codPista_ocupada)
{
     if(strcmp(p_pouso.codPista, codPista_ocupada) != 0) //Se a pista n�o estiver ocupada
        if(av->extensaoParaPouso <= p_pouso.extensao)    //e a extens�o da pista for suficiente para o aviao
           if(av->pesoMaximo <= p_pouso.peso){          //e o avi�o seja mais leve do que o peso suportado pela pista
               strcpy(codPista_ocupada, p_pouso.codPista); //muda o c�digo de pista ocupada
               return TRUE; //avisa que o avi�o pousou com sucesso
           }
           else { //se n�o, mostra mensagens de erro
                popup(RED, LIGHTGRAY, 62, 4);
                gotoxy(9,6);
                printf("%c                   Oops!                                      %c", 186, 186);
                gotoxy(9,7);
                printf("%c                   Aviao muito pesado!                        %c", 186, 186);
           }
        else{
             popup(RED, LIGHTGRAY, 62, 4);
             gotoxy(9,6);
             printf("%c       Oops!                                                  %c", 186, 186);
             gotoxy(9,7);
             printf("%c       Extensao de pista insuficiente para pouso!             %c", 186, 186);
        }
     else{
             popup(RED, LIGHTGRAY, 62, 4);
             gotoxy(9,6);
             printf("%c                      Oops!                                   %c", 186, 186);
             gotoxy(9,7);
             printf("%c                      Pista ocupada!                          %c", 186, 186);
        }
                
     getch();
     //Ativa a interface gr�fica           
     desenha_tela(); 
     return FALSE;
}
////////////////////////////////////////////////////////////////////////////////


//Deleta Voo////////////////////////////////////////////////////////////////////
/* Recebe um c�digo de v�o a ser deletado e o vetor de v�os e seu tamanho, e muda
   o c�digo deste v�o para DeLeTe, para n�o ser mais mostrado pelo programa */
void deletaVoo(VOO *arrVoo, int tamVoo, char *codVoo)
{
     int i;
     
     for(i=0; i<tamVoo; i++)
              if(strcmp(arrVoo[i].codVoo, codVoo) == 0)
                   strcpy(arrVoo[i].codVoo, "DeLeTe");;           
}
////////////////////////////////////////////////////////////////////////////////


//Testa Maior Aviao/////////////////////////////////////////////////////////////
/* Testa o maior avi�o que pousa em cada pista */
void testa_MaiorAviao(AVIAO *av, int *maiorAviao, AVIAO *arrAviao, int tamAviao, int indPista)
{
     int i;
     int ind_mAviao;
     ind_mAviao = maiorAviao[indPista];
     
     if(av->pesoMaximo > arrAviao[ind_mAviao].pesoMaximo) //Se o novo avi�o for maior (mais pesado)
            for(i=0; i<tamAviao; i++)                    //que o anterior, atualiza o vetor de maiorAviao daquela pista
                     if(strcmp(av->modelo, arrAviao[i].modelo) == 0)
                          maiorAviao[indPista] = i;
}
////////////////////////////////////////////////////////////////////////////////


//Quantidade de Pousos//////////////////////////////////////////////////////////
/* Procura o �ndice do avi�o que ir� pousar no vetor de avi�es e incrementa
   a quantidade de pousos deste avi�o (para o relat�rio) */
void quantPousos(AVIAO *av, AVIAO *arrAviao, int tamAviao, int *nroPousosAviao)
{
     int i;
     
     for(i=0; i<tamAviao; i++)
         if(strcmp(av->modelo, arrAviao[i].modelo) == 0)
              nroPousosAviao[i]++;
}
////////////////////////////////////////////////////////////////////////////////


//Checa Texto///////////////////////////////////////////////////////////////////
/* Verifica se o texto digitado na linha de comando � um comando v�lido ou n�o */
int checa_texto(char *comando, VOO *arrVoo, int tamVoo, AVIAO *arrAviao, int tamAviao, PISTA *arrPista, int tamPista, FILE *log, char *codPista_ocupada, int *tent_pouso, int *tent_sucesso, int *maiorAviao, int *nroPousosAviao)
{
     int i;
     int retorno = FALSE;
     char codVoo[30];
     char codPista[10];
     int codAviao;
     AVIAO *av;
     PISTA p_pouso;
     
     //Verifica o que foi digitado     
     if(strcmp(comando,"XX")==0){
          potter();
          retorno = TRUE;
     }
     else if(strcmp(comando,"toninho")==0){
          toninho();
          retorno = TRUE;
     }
     else if(strcmp(comando,"mara abel")==0){
          marabel();
          retorno = TRUE;
     }
     else if(strcmp(comando,"/ajuda")==0){
          ajuda();
          retorno = TRUE;
     }
     else if(strcmp(comando,"parar")==0)
          retorno = TRUE;
     else {
          separa_comando(comando, codVoo, codPista);
          if( (codAviao = busca_codAviao(codVoo, arrVoo, tamVoo)) != FALSE) //Procura o c�digo do avi�o do v�o digitada
              if( (av = busca_aviao(codAviao, arrAviao, tamAviao)) != NULL) //Procura um avi�o com o c�digo de avi�o encontrado
                  if( (i = busca_pista(codPista, arrPista, tamPista)) != -1){ //Procura o �ndice da pista com o c�digo de pista digitado
                      p_pouso = arrPista[i];
                      tent_pouso[i]++;
                      if(testa_pouso(av, p_pouso, codPista_ocupada)){ //Se o a pista cumprir todos os requesitos do avi�o
                          deletaVoo(arrVoo, tamVoo, codVoo); //"Deleta" este v�o do vetor
                          fprintf(log, "Pouso [%s - %s - <font color=green>Sucesso</font>]<br>\n", codVoo, codPista); //Salva no log
                          (*tent_sucesso)++; //Incrementa o contador de tentativas de pouso bem sucedidas
                          testa_MaiorAviao(av, maiorAviao, arrAviao, tamAviao, i); //teste se � o maior avi�o que pousou nesta pista
                          quantPousos(av, arrAviao, tamAviao, nroPousosAviao); //aumenta a quantidade de pousos deste avi�o
                      }
                      else
                          fprintf(log, "Pouso [%s - %s - <font color=red>Falha</font>]<br>\n", codVoo, codPista);//Salva no log
                      retorno = TRUE;
                  }
     }
     
     return retorno;
}
////////////////////////////////////////////////////////////////////////////////


//Linha de Comando//////////////////////////////////////////////////////////////
/*  Controla as a��es da linha de comando (tamanho m�ximo de texto, fun��o para
    apagar, etc)*/
void linha_de_comando(int* opcao, PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int tamPista, int tamVoo, int tamAviao, char *codPista_ocupada, FILE *log, int *tent_pouso, int *tent_sucesso, int *maiorAviao, int *nroPousosAviao)
{
     int i=0, j=0, k=0;//�ndices
     int sair = FALSE; //flag
     int x=6, y=15;    //posi��o
     char tecla;
     //strings
     char comando[71];
     
     lc_highlight(TRUE); //Ativa linha de comando
     _setcursortype(_NORMALCURSOR); //Coloca o cursor na tela
     textbackground(BLACK); //Troca cor do fundo para preto
     textcolor(LIGHTGRAY); //Troca cor do texto para cinza claro
     
     do{
         do{
             gotoxy(x,y); //Vai para o in�cio da linha
             if (i>70){ //Se o caracter a ser lido ultrapassar o tamanho m�ximo da string
                comando[i] = '\0'; //Coloca o caracter especial no �ltimo caracter
                tecla = getch(); //L� uma tecla
                if(tecla == BACKSPACE) //Se usu�rio apertar BACSPACE, chama a fun��o para apagar texto
                      backspace(comando, &i, &x, &y);
             }
             else{ //Se a string ainda possuir espa�o
                 comando[i] = getch(); //L� o caracter daquela posi��o e passa para ma�uscula
                 if(comando[i] == BACKSPACE) //Se apertar BACKSPACE, chama a fun��o para apagar texto
                      backspace(comando, &i, &x, &y);
                 else{ //Sen�o imprime o caracter lido na tela e incrementa a posi��o x da linha
                       //e o �ndice do vetor
                      putchar(comando[i]);
                      x++;
                      i++;
                 }
             }
         } while((comando[i-1] != ENTER) && (tecla != ENTER)); //Enquanto usu�rio n�o apertar enter
         comando[i-1] = '\0'; //Troca o �ltimo caracter lido (o ENTER) pelo caracter especial
          
        //Se foi digitado algum comando v�lido, sai da linha de comando
        sair = checa_texto(comando, arrVoo, tamVoo, arrAviao, tamAviao, arrPista, tamPista, log, codPista_ocupada, tent_pouso, tent_sucesso, maiorAviao, nroPousosAviao);
          
     }while(!sair);     
     *opcao = 1; //Quando sair da fun��o, coloca a op��o "Continuar" do menu em destaque
     //Ativa a interface gr�fica           
     desenha_tela(); 
}
////////////////////////////////////////////////////////////////////////////////


//Iniciar///////////////////////////////////////////////////////////////////////
/* Come�a a gravar o registro de a��es nos logs, caso j� tenha aberto os arquivos
   de avi�es, pistas e v�os */
void iniciar(int *iniciado, int completa_quadros, int* opcao, PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int tamPista, int tamVoo, int tamAviao, char *codPista_ocupada, FILE *log, int *tent_pouso, int *tent_sucesso, int *maiorAviao, int *nroPousosAviao)
{
     char dia[3], mes[3], ano[3];
     char hora[30];

     
     if(completa_quadros == FALSE){ //Se os arquivos ainda n�o foram abertos, avisa o usu�rio
         popup(RED, LIGHTGRAY, 62, 4);
         gotoxy(9,6);
         printf("%c               Oops!                                          %c", 186, 186);
         gotoxy(9,7);
         printf("%c               Os arquivos nao foram abertos!                 %c", 186, 186);
         getch();
         //Ativa a interface gr�fica           
         desenha_tela();
         
         *iniciado = FALSE; 
     }
     else{ //Se os arquivos j� foram abertos, come�a a gravar as a��es no log e vai para a linha de comando
          _strtime(hora);
          separaData(dia, mes, ano);
          if(*iniciado == TRUE)
               fprintf(log, "<b>Fim Execu��o -</b> 20%s/%s/%s  %s<br><br>\n\n", ano, mes, dia, hora);
          fprintf(log, "<b>In�cio Execu��o -</b> 20%s/%s/%s  %s<br>\n", ano, mes, dia, hora);
          fprintf(log, "Carga de arquivos: <i>AVIOES.TXT</i><br>\n");
          fprintf(log, "Carga de arquivos: <i>PISTAS.TXT</i><br>\n");
          fprintf(log, "Carga de arquivos: <i>VOOS.TXT</i><br>\n");
          linha_de_comando(opcao, arrPista, arrVoo, arrAviao, tamPista, tamAviao, tamVoo, codPista_ocupada, log, tent_pouso, tent_sucesso, maiorAviao, nroPousosAviao);
          *iniciado = TRUE;
     }
}
////////////////////////////////////////////////////////////////////////////////


//Continuar/////////////////////////////////////////////////////////////////////
/* Se o programa j� tiver sido iniciado, vai para a linha de comando */
void continuar(int iniciado, int* opcao, PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int tamPista, int tamVoo, int tamAviao, char *codPista_ocupada, FILE *log, int *tent_pouso, int *tent_sucesso, int *maiorAviao, int *nroPousosAviao)
{
     if(iniciado == FALSE){
         popup(RED, LIGHTGRAY, 62, 4);
         gotoxy(9,6);
         printf("%c                   Oops!                                      %c", 186, 186);
         gotoxy(9,7);
         printf("%c                   Programa nao iniciado!                     %c", 186, 186);
         getch();
         //Ativa a interface gr�fica           
         desenha_tela();
     }
     else
         linha_de_comando(opcao, arrPista, arrVoo, arrAviao, tamPista, tamAviao, tamVoo, codPista_ocupada, log, tent_pouso, tent_sucesso, maiorAviao, nroPousosAviao);
}
////////////////////////////////////////////////////////////////////////////////


//Cor Op��o/////////////////////////////////////////////////////////////////////
/* Recebe como argumento a op��o selecionada no menu e uma constante. Se a soma
   da constante com a op��o for igual a 6, muda a cor do texto para branco. Caso
   contr�rio, deixa o texto cinza (cor padr�o). */
int cor_opcao(int opcao, int constante)
{
    int cor;
    if( (opcao+constante) == 6 )
        cor = WHITE;
    else
        cor = LIGHTGRAY;
        
    return cor;
}
////////////////////////////////////////////////////////////////////////////////


//Desenha Fundo/////////////////////////////////////////////////////////////////
/* Dada uma posi��o y de in�cio e final, desenha um quadro preto para serem
   mostradas as informa��es na tela */
void desenha_fundo(int inicio, int final)
{
     int i;
     for(i=inicio; i<final; i++){
             gotoxy(3,i);
             textbackground(BLACK);
             printf("                                                                            ");
             desenha_lateral(i);
     }              
}
////////////////////////////////////////////////////////////////////////////////


//Menu//////////////////////////////////////////////////////////////////////////
/* Desenha e "seleciona" as op��es do menu, de acordo com um contador recebido
   como par�metro */
void menu(int opcao)
{
     gotoxy(1, 2);
     //Opcoes
     textbackground(DARKGRAY); 
     textcolor( cor_opcao(opcao, 6) ); //Passa o valor da op��o atual e uma constante para escolher a cor
     printf("  Iniciar      ");
     textcolor( cor_opcao(opcao, 5) ); //Passa o valor da op��o atual e uma constante para escolher a cor
     printf(" Continuar       ");
     textcolor( cor_opcao(opcao, 4) ); //Passa o valor da op��o atual e uma constante para escolher a cor
     printf(" Abrir      ");
     textcolor( cor_opcao(opcao, 3) ); //Passa o valor da op��o atual e uma constante para escolher a cor
     printf(" Salvar      ");
     textcolor( cor_opcao(opcao, 2) ); //Passa o valor da op��o atual e uma constante para escolher a cor
     printf(" Relatorio      ");
     textcolor( cor_opcao(opcao, 1) ); //Passa o valor da op��o atual e uma constante para escolher a cor
     printf(" Sair  ");
     desenha_lateral(2);
}
////////////////////////////////////////////////////////////////////////////////


//Desenha Tela//////////////////////////////////////////////////////////////////
/* Desenha a interface gr�fica */
void desenha_tela()
{
    int i, y;
    //Vai para a posi��o (1, 1) e muda a cor da tela para cinza escuro e do texto para preto
    gotoxy(1,1);
    textbackground(DARKGRAY);
    textcolor(BLACK);
    //Limpa a tela e esconde o cursor
    clrscr();
    _setcursortype(_NOCURSOR);
    
    desenha_topo(LINHA-2);
    desenha_lateral(2);
    
    gotoxy(1,3);
    printf("%c", 204); //Reparti��o lado esquerdo
    for (i=0; i<(LINHA-2); i++)
        printf("%c", 205); //Borda horizontal
    printf("%c", 185); //Reparti��o lado direito
    
    desenha_lateral(4);
    
    //Desenha topo do quadro dos v�os
    gotoxy(3,5);
    textbackground(BLUE);
    textcolor(LIGHTGRAY);
    printf("  Cod. Voo   Origem                      Cod. Aviao       Extensao   Peso   ");
    desenha_lateral(5);
    
    desenha_fundo(6, 13);
    
    desenha_lateral(13);
    //Linha de comando
    lc_highlight(FALSE); //Desenha linhas 14 e 15
    desenha_lateral(16); 
    
    //Desenha topo do quadro das pistas
    gotoxy(3,17);
    textbackground(BLUE);
    textcolor(LIGHTGRAY);
    printf("              Pistas                                         Situacao       ");
    desenha_lateral(17);
    
    desenha_fundo(18, 23);
    
    desenha_lateral(23);
   
    gotoxy(3,24);
    textbackground(LIGHTGRAY);
    printf("   Digite '/ajuda' para ver os comandos...                                  ");
    desenha_lateral(24);
    
    ligaStatus(FALSE);
   
    textbackground(DARKGRAY);
    gotoxy(1,25);
    desenha_base(LINHA-2);
    gotoxy(1,1);
}
////////////////////////////////////////////////////////////////////////////////


//Ordena Pistas/////////////////////////////////////////////////////////////////
/* Usa o bubblesort para ordenar o vetor de pistas em ordem alfab�tica        */
void ordena_pistas(PISTA *arrPista, int tamanho)
{ 
     int i, j;
     int troca;
     int final;
     PISTA auxiliar;
     
     final = tamanho - 1;
     do{
         troca = FALSE;
         for(i=0; i<final; i++){
             //Verifica qual string vem antes e muda os �ndices, caso necess�rio
             if(strcmp(arrPista[i].codPista, arrPista[i+1].codPista) == 1){
                   auxiliar = arrPista[i];
                   arrPista[i] = arrPista[i+1];
                   arrPista[i+1] = auxiliar;
                   troca = TRUE;
             }
         } 
         final--;
     }while(troca);  
}
////////////////////////////////////////////////////////////////////////////////


//Abre Pistas///////////////////////////////////////////////////////////////////
/* Abre o arquivo de pistas e passa os dados para um vetor                    */
void abre_pistas(FILE *arq_pistas, PISTA *arrPista, int *tamPista)
{
     int i=0, j=0;
     char c;
     char temporario[30];
     
     //Verifica se conseguiu abrir o arquivo corretamente
     if((arq_pistas=fopen("PISTAS.TXT", "r")) == NULL){
         popup(RED, LIGHTGRAY, 40, 5);
         gotoxy(20,6);
         printf("%c  Oops!                                 %c", 186, 186);
         gotoxy(20,8);
         printf("%c   Erro ao abrir arquivo de pistas...   %c", 186, 186);
         getch();
         exit(1);
     }
     while(!feof(arq_pistas)){
                              
         c = getc(arq_pistas); //Pega um caracter e v� se n�o � o marcador de fim de arquivo
         
         if ( c != EOF ) {
             
             //L� o c�digo da pista, enquanto n�o encontrar uma v�rgula
             j=0;
             while(c != ','){
                 arrPista[i].codPista[j] = c ;
                 j++;
                 c = getc(arq_pistas);
             }
             arrPista[i].codPista[j] = '\0'; //Coloca o caracter especial no fim da string
             
             c = getc(arq_pistas);//Descarta a v�rgula
             
             //L� a extens�o da pista como um vetor de chars e depois converte para inteiro
             j=0;
             while(c != ','){
                 temporario[j] = c ;
                 j++;
                 c = getc(arq_pistas);
             }
             temporario[j] = '\0'; //Coloca o caracter especial no fim da string
             arrPista[i].extensao = atoi(temporario); //converte string para inteiro
             
             c = getc(arq_pistas);//Descarta a v�rgula
             
             //L� o peso da pista como um vetor de chars e depois converte para inteiro
             j=0;    //enquanto n�o encontrar o caracter de fim de arquivo ou um 'enter'
             while(c != '\n' && c != EOF){	
                 temporario[j] = c ;
                 j++;
                 c = getc(arq_pistas);
             }
             temporario[j] = '\0'; //Coloca o caracter especial no fim da string
             arrPista[i].peso = atoi(temporario); //converte string para inteiro
             
             i++;
         }
     }
     fclose(arq_pistas); //Fecha o arquivo
     ordena_pistas(arrPista, i); //Ordena o vetor que foi preenchido
     *tamPista = i;
}
////////////////////////////////////////////////////////////////////////////////


//Abre Voos/////////////////////////////////////////////////////////////////////
/* Abre o arquivo de v�os e passa os dados para um vetor                      */
void abre_voos(FILE *arq_voos, VOO *arrVoo, int *tamVoo)
{
     int i=0, j=0;
     char c;
     char temporario[30];
     
     //Verifica se conseguiu abrir o arquivo corretamente
     if((arq_voos=fopen("VOOS.TXT", "r")) == NULL){
         popup(RED, LIGHTGRAY, 40, 5);
         gotoxy(20,6);
         printf("%c  Oops!                                 %c", 186, 186);
         gotoxy(20,8);
         printf("%c    Erro ao abrir arquivo de voos...    %c", 186, 186);
         getch();
         exit(1);
     }
     while(!feof(arq_voos)){
         
         c = getc(arq_voos); //Pega um caracter e v� se n�o � um marcador de fim de arquivo
         
         if ( c != EOF ) {                     
             //L� o c�digo do v�o enquanto n�o encontrar a v�rgula
             j=0;
             while(c != ','){
                 arrVoo[i].codVoo[j] = c ;
                 j++;
                 c = getc(arq_voos);
             }
             arrVoo[i].codVoo[j] = '\0'; //Coloca caracter especial no fim da string
             
             c = getc(arq_voos);//Descarta a v�rgula
             
             //L� a origem do v�o enquanto n�o encontrar a v�rgula
             j=0;
             while(c != ','){
                 arrVoo[i].origem[j] = c ;
                 j++;
                 c = getc(arq_voos);
             }
             arrVoo[i].origem[j] = '\0'; //Coloca caracter especial no fim da string
             
             c = getc(arq_voos);//Descarta a v�rgula
             
             //L� o c�digo do avi�o como um vetor de chars e depois converte para inteiro
             j=0;     //Enquanto n�o encontrar o caracter de fim de arquivo ou um 'enter'
             while(c != '\n' && c != EOF){	
                 temporario[j] = c ;
                 j++;
                 c = getc(arq_voos);
             }
             temporario[j] = '\0';
             arrVoo[i].codAviao = atoi(temporario); //converte string para inteiro
    
             i++;
         }
     }
     fclose(arq_voos); //Fecha o arquivo
     *tamVoo = i;
}
////////////////////////////////////////////////////////////////////////////////


//Abre Avioes///////////////////////////////////////////////////////////////////
/* Abre o arquivo de avi�es e passa os dados para um vetor                    */
void abre_avioes(FILE *arq_avioes, AVIAO *arrAviao, int *tamAviao)
{
     int i=0, j=0;
     char c;
     char temporario[30];
     
     //Verifica se conseguiu abrir o arquivo corretamente
     if((arq_avioes=fopen("AVIOES.TXT", "r")) == NULL){
         popup(RED, LIGHTGRAY, 40, 5);
         gotoxy(20,6);
         printf("%c  Oops!                                 %c", 186, 186);
         gotoxy(20,8);
         printf("%c   Erro ao abrir arquivo de avioes...   %c", 186, 186);
         getch();
         exit(1);
     }
     while(!feof(arq_avioes)){
                              
         c = getc(arq_avioes); //Pega um caracter e v� se n�o � o marcador de fim de arquivo
         
         if ( c != EOF ) {
             //L� o c�digo do avi�o como um vetor de chars e depois converte pra inteiro
             j=0;    //enquanto n�o encontrar a v�rgula
             while(c != ','){
                 temporario[j] = c ;
                 j++;
                 c = getc(arq_avioes);
             }
             temporario[j] = '\0'; //Coloca caracter especial no fim da string
             arrAviao[i].codAviao = atoi(temporario); //converte string para inteiro
             
             c = getc(arq_avioes);//Descarta a v�rgula
             
             //L� o modelo do avi�o enquanto n�o encontrar a v�rgula
             j=0;
             while(c != ','){
                 arrAviao[i].modelo[j] = c ;
                 j++;
                 c = getc(arq_avioes);
             }
             arrAviao[i].modelo[j] = '\0'; //Coloca caracter especial no fim da string
             
             c = getc(arq_avioes);//Descarta a v�rgula
             
             //L� a extens�o para pouso do avi�o como um vetor de chars e depois converte para inteiro
             j=0;     //enquanto n�o encontrar a v�rgula
             while(c != ','){
                 temporario[j] = c ;
                 j++;
                 c = getc(arq_avioes);
             }
             temporario[j] = '\0'; //Coloca caracter especial no fim da string
             arrAviao[i].extensaoParaPouso = atoi(temporario); //converte string para inteiro
             
             c = getc(arq_avioes);//Descarta a v�rgula
             
             //L� o peso m�ximo do avi�o como um vetor de chars e depois converte para inteiro
             j=0;            //Enquanto n�o encontrar caracter de fim de arquivo ou um 'enter'
             while(c != '\n' && c != EOF){	
                 temporario[j] = c ;
                 j++;
                 c = getc(arq_avioes);
             }
             temporario[j] = '\0'; //Coloca caracter especial no fim da string
             arrAviao[i].pesoMaximo = atoi(temporario); //converte string para inteiro
             
             i++;
         }
     }
     fclose(arq_avioes); //Fecha arquivo de avi�es
     *tamAviao = i;
}
////////////////////////////////////////////////////////////////////////////////


//Simula��o Nova////////////////////////////////////////////////////////////////
/* Recebe como par�metros uma flag para completar os quadros com as informa��es 
   dos vetores e os vetores com os dados dos arquivos */
void sim_nova(PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int *completa_quadros, int *tamPista, int *tamVoo, int *tamAviao)
{
     FILE *arq_pistas, *arq_voos, *arq_avioes;
     
     //Passa os dados dos arquivos para os vetores e ativa a flag
     abre_pistas(arq_pistas, arrPista, tamPista);
     abre_avioes(arq_avioes, arrAviao, tamAviao);
     abre_voos(arq_voos, arrVoo, tamVoo);
     *completa_quadros = TRUE;
}
////////////////////////////////////////////////////////////////////////////////


//Abre Pistas - Bin�rio/////////////////////////////////////////////////////////
/* Abre o arquivo bin�rio das pistas */
void abrePistas_bin(FILE *arqPistas_bin, PISTA *arrPista, int *tamPista)
{
     int i=0;
     
     if ((arqPistas_bin = fopen("PISTAS.BIN", "rb")) == NULL){
           popup(RED, LIGHTGRAY, 40, 5);
           gotoxy(20,6);
           printf("%c  Oops!                                 %c", 186, 186);
           gotoxy(20,8);
           printf("%c   Erro ao abrir arquivo de pistas...   %c", 186, 186);
           getch();
           exit(1);
     }
      while(!feof(arqPistas_bin)){ //Preenche o vetor de pistas com os dados do arquivo
           fread(&arrPista[i], sizeof(PISTA), 1, arqPistas_bin);
           i++;
      }
      
      fclose(arqPistas_bin);
      *tamPista = i;
}
////////////////////////////////////////////////////////////////////////////////


//Abre V�os - Bin�rio///////////////////////////////////////////////////////////
/* Abre o arquivo bin�rio dos v�os */
void abreVoos_bin(FILE *arqVoos_bin, VOO *arrVoo, int *tamVoo)
{
     int i=0;
     
     if ((arqVoos_bin = fopen("VOOS.BIN", "rb")) == NULL){
           popup(RED, LIGHTGRAY, 40, 5);
           gotoxy(20,6);
           printf("%c  Oops!                                 %c", 186, 186);
           gotoxy(20,8);
           printf("%c    Erro ao abrir arquivo de voos...    %c", 186, 186);
           getch();
           exit(1);
     }
      while(!feof(arqVoos_bin)){ //Preenche o vetor dos v�os com os dados do arquivo
           fread(&arrVoo[i], sizeof(VOO), 1, arqVoos_bin);
           i++;
      }
      
      fclose(arqVoos_bin);
      *tamVoo = i;
}
////////////////////////////////////////////////////////////////////////////////


//Abre Avi�es - Bin�rio/////////////////////////////////////////////////////////
/* Abre o arquivo bin�rio daos avi�es */
void abreAvioes_bin(FILE *arqAvioes_bin, AVIAO *arrAviao, int *tamAviao)
{
     int i=0;
     
     if ((arqAvioes_bin = fopen("AVIOES.BIN", "rb")) == NULL){
           popup(RED, LIGHTGRAY, 40, 5);
           gotoxy(20,6);
           printf("%c  Oops!                                 %c", 186, 186);
           gotoxy(20,8);
           printf("%c   Erro ao abrir arquivo de avioes...   %c", 186, 186);
           getch();
           exit(1);
     }
      while(!feof(arqAvioes_bin)){ //Preenche o vetor de avi�es com os dados do arquivo
           fread(&arrAviao[i], sizeof(AVIAO), 1, arqAvioes_bin);
           i++;
      }
      
      fclose(arqAvioes_bin);
      *tamAviao = i;
}
////////////////////////////////////////////////////////////////////////////////


//Abre Status da Pista//////////////////////////////////////////////////////////
/* Abre o arquivo de status de ocupa��o das pistas */
void abreStatus_bin(FILE *arqStatus_bin, char *codPista_ocupada)
{
     int i=0;
     
     if((arqStatus_bin = fopen("STATUS.BIN", "rb")) == NULL)
        return;
        
     while(!feof(arqStatus_bin)){
           fread(&codPista_ocupada[i], sizeof(char), 1, arqStatus_bin);
           i++;
     }
     fclose(arqStatus_bin);
}
////////////////////////////////////////////////////////////////////////////////


//Continuar Simula��o///////////////////////////////////////////////////////////
void continuar_sim(PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int *completa_quadros, int *tamPista, int *tamVoo, int *tamAviao, char *codPista_ocupada)
{
     FILE *arqPistas_bin, *arqVoos_bin, *arqAvioes_bin, *arqStatus_bin;
     
     //Passa os dados dos arquivos para os vetores e ativa as flags
     abrePistas_bin(arqPistas_bin, arrPista, tamPista);
     abreAvioes_bin(arqVoos_bin, arrAviao, tamAviao);
     abreVoos_bin(arqAvioes_bin, arrVoo, tamVoo);
     abreStatus_bin(arqStatus_bin, codPista_ocupada);
     *completa_quadros = TRUE;
}
////////////////////////////////////////////////////////////////////////////////


//Cores Abrir///////////////////////////////////////////////////////////////////
/* Recebe como par�metro a op��o selecionada no menu de abrir() e uma constante
   e retorna uma cor a ser utilizada no programa em fun��o do somat�rio da op��o
   com a constante */
int cores_abrir(int opcao, int constante)
{
    int cor;
    if(opcao == 0)
       switch(constante){
                         case 1: cor = RED; break;       //Cor do fundo #1
                         case 2: cor = LIGHTGRAY; break; //Cor do texto #1
                         case 3: cor = LIGHTGRAY; break; //Cor do fundo #2
                         case 4: cor = BLACK; break;    //Cor do texto #2
                         case 5: cor = LIGHTGRAY; break; //Cor do fundo #3
                         case 6: cor = BLACK;           //Cor do texto #3
       }
       
    else if (opcao == 1)
          switch(constante){
                         case 1: cor = LIGHTGRAY; break; //Cor do fundo #1
                         case 2: cor = BLACK; break;     //Cor do texto #1
                         case 3: cor = RED; break;       //Cor do fundo #2
                         case 4: cor = LIGHTGRAY; break; //Cor do texto #2
                         case 5: cor = LIGHTGRAY; break; //Cor do fundo #3
                         case 6: cor = BLACK;           //Cor do texto #3
          }
          
    else if (opcao == 2)
          switch(constante){
                         case 1: cor = LIGHTGRAY; break; //Cor do fundo #1
                         case 2: cor = BLACK; break;     //Cor do texto #1
                         case 3: cor = LIGHTGRAY; break; //Cor do fundo #2
                         case 4: cor = BLACK; break;     //Cor do texto #2
                         case 5: cor = RED; break;       //Cor do fundo #3
                         case 6: cor = LIGHTGRAY;        //Cor do texto #3
          }
          
    return cor;
}
////////////////////////////////////////////////////////////////////////////////


//Desenha Abrir/////////////////////////////////////////////////////////////////
/* Desenha a "pop-up" e o fundo da fun��o abrir                               */
void desenha_abrir()
{
    _setcursortype(_NOCURSOR);
    
    popup(LIGHTGRAY, BLACK, 62, 2);
    gotoxy(9,5);
    printf("%c Deseja comecar uma simulacao nova ou continuar uma anterior? %c", 186, 186);
    gotoxy(9,6);
    printf("%c                                                              %c", 186, 186);
}
////////////////////////////////////////////////////////////////////////////////


//Abrir/////////////////////////////////////////////////////////////////////////
/* Chama a fun��o sim_nova(), caso o usu�rio deseje come�ar uma simula��o nova 
   ou a fun��o continuar_sim(), caso o usu�rio deseje continuar uma simula��o 
   anterior */
void abrir(PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int *completa_quadros, int *tamPista, int *tamVoo, int *tamAviao, char *codPista_ocupada)
{
    int opcao = 0;
    int pronto = FALSE;
    char tecla;
     
    desenha_abrir();
    
    do{        
        gotoxy(22,6);
        textbackground(cores_abrir(opcao, 1)); //Chama fun��o para controlar as cores de texto e fundo
        textcolor(cores_abrir(opcao, 2));
        printf(" Iniciar nova ");
        textbackground(cores_abrir(opcao, 3));
        textcolor(cores_abrir(opcao, 4));
        printf(" Continuar ");
        textbackground(cores_abrir(opcao, 5));
        textcolor(cores_abrir(opcao, 6));
        printf(" Cancelar "); 
        
        tecla = getch();
        if(tecla==TAB)
            opcao++;
        if(tecla==ENTER){
            switch(opcao){
                      case 0: sim_nova(arrPista, arrVoo, arrAviao, completa_quadros, tamPista, tamVoo, tamAviao); break;
                      case 1: continuar_sim(arrPista, arrVoo, arrAviao, completa_quadros, tamPista, tamVoo, tamAviao, codPista_ocupada); break;
            }
            pronto = TRUE;
        }
        
        if(opcao>2)
            opcao = 0;      
    
    }while(!pronto);
    
    //Ativa a interface gr�fica           
    desenha_tela(); 
}
////////////////////////////////////////////////////////////////////////////////


//Mostra Conte�do///////////////////////////////////////////////////////////////
/* Recebe como par�metro os vetores com os dados dos arquivos e mostra seu
   conte�do na tela */
void mostra_conteudo(PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, char *codPista_ocupada, int tamVoo)
{
     int i, j;
     int y;
     int cor;
     char status[10];
     AVIAO *avProcurado;
     //Define um avi�o a ser mostrado em caso de erro
     AVIAO erro;
     strcpy(erro.modelo, " ");
     erro.extensaoParaPouso = 0;
     erro.pesoMaximo = 0;
     
     textbackground(BLACK);
     textcolor(LIGHTGRAY);
     //Tela de cima
     y=6; i=0; j=0;
     while(i<7 && j<tamVoo){
              gotoxy(4,y);
              if(strcmp(arrVoo[j].codVoo, "DeLeTe") != 0 && j<tamVoo){
                 printf("%8s   %s", arrVoo[j].codVoo, arrVoo[j].origem);
                 y++;
                 i++;
              }
              j++;
     };
     y=6; i=0; j=0;
     while(i<7 && j<tamVoo){
              gotoxy(42,y);
              if(strcmp(arrVoo[j].codVoo, "DeLeTe") != 0){
                 avProcurado = busca_aviao(arrVoo[j].codAviao, arrAviao, TAM);
                 printf("%s", avProcurado->modelo);
                 gotoxy(62,y);
                 printf("%4dm", avProcurado->extensaoParaPouso);
                 gotoxy(71,y);
                 printf("%4.1ft", (float) avProcurado->pesoMaximo/1000);
                 y++;
                 i++;
              }
              j++;
     };
     
     //Tela de baixo
     y=18;
     for(i=0; i<5; i++){
              gotoxy(4,y);
              printf(" Pista %3s - %5dm - Capacidade: %3dt", arrPista[i].codPista, arrPista[i].extensao, arrPista[i].peso/1000);
              y++;
     };
     
     y=18;
     for(i=0; i<5; i++){
              if(strcmp(arrPista[i].codPista, codPista_ocupada) != 0){
                   cor = GREEN;
                   strcpy(status, "Livre");
              }
              else{
                   cor = RED;
                   strcpy(status, "Ocupada");
              }
              gotoxy(62,y);
              textcolor(LIGHTGRAY);
              printf("Status - ");
              textcolor(cor);
              printf("%s", status);
              y++;
     };
}
////////////////////////////////////////////////////////////////////////////////


//Salva Pistas//////////////////////////////////////////////////////////////////
/* Salva o vetor de pistas em um arquivo bin�rio */
void salva_pistas(PISTA *arrPista, int tamPista)
{
     FILE *arqPistas_bin;
     int i;
     
     arqPistas_bin = fopen("PISTAS.BIN", "wb");
     for(i=0; i<tamPista; i++)
              fwrite(&arrPista[i], sizeof(PISTA), 1, arqPistas_bin);
     
     fclose(arqPistas_bin);
}
////////////////////////////////////////////////////////////////////////////////


//Salva Voos////////////////////////////////////////////////////////////////////
/* Salva o vetor de v�os em um arquivo bin�rio */
void salva_voos(VOO *arrVoo, int tamVoo)
{
     FILE *arqVoos_bin;
     int i;
     
     arqVoos_bin = fopen("VOOS.BIN", "wb");
     for(i=0; i<tamVoo; i++)
              fwrite(&arrVoo[i], sizeof(VOO), 1, arqVoos_bin);
     
     fclose(arqVoos_bin);
}
////////////////////////////////////////////////////////////////////////////////


//Salva Avioes//////////////////////////////////////////////////////////////////
/* Salva o vetor de avi�es em um arquivo bin�rio */
void salva_avioes(AVIAO *arrAviao, int tamAviao)
{
     FILE *arqAvioes_bin;
     int i;
     
     arqAvioes_bin = fopen("AVIOES.BIN", "wb");
     for(i=0; i<tamAviao; i++)
              fwrite(&arrAviao[i], sizeof(AVIAO), 1, arqAvioes_bin);
     
     fclose(arqAvioes_bin);
}
////////////////////////////////////////////////////////////////////////////////


//Salva Status//////////////////////////////////////////////////////////////////
/* Salva o c�digo da pista ocupada em um arquivo bin�rio */
void salva_status(char *codPista_ocupada)
{
     FILE *arqStatus_bin;
     int i;
     
     arqStatus_bin = fopen("STATUS.BIN", "wb");
     for(i=0; i<strlen(codPista_ocupada); i++)
              fwrite(&codPista_ocupada[i], sizeof(char), 1, arqStatus_bin);
     
     fclose(arqStatus_bin);
}
////////////////////////////////////////////////////////////////////////////////


//Salvar////////////////////////////////////////////////////////////////////////
/* Chama as fun��es auxiliares para salvar cada um dos vetores e o c�digo da pista
   ocupada no momento */
void salvar(int completa_quadros, PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int tamPista, int tamVoo, int tamAviao, char *codPista_ocupada)
{
     if(!completa_quadros){
        popup(GREEN, WHITE, 25, 3);
        gotoxy(27,6);
        printf("%c  Programa nao iniciado! %c", 186, 186);
     }  else{
          salva_pistas(arrPista, tamPista);
          salva_voos(arrVoo, tamVoo);
          salva_avioes(arrAviao, tamAviao);
          salva_status(codPista_ocupada);
          
          popup(GREEN, WHITE, 30, 3);
          gotoxy(25,6);
          printf("%c Arquivos salvos com sucesso! %c", 186, 186);
        }
        
     getch();
     //Ativa a interface gr�fica           
     desenha_tela(); 
}
////////////////////////////////////////////////////////////////////////////////


//Sair//////////////////////////////////////////////////////////////////////////
void fsair(int *sair, FILE *log, int iniciado)
{
    int opcao = 0;
    int pronto = FALSE;
    char tecla;
    char hora[30], dia[3], mes[3], ano[3];
    
     _setcursortype(_NOCURSOR);
     
    popup(LIGHTGRAY, BLACK, 40, 2);
    gotoxy(20,5);
    printf("%c      Tem certeza que deseja sair?      %c", 186, 186);
    gotoxy(20,6);
    printf("%c                                        %c", 186, 186);
     
    
    do{        
        gotoxy(34,6);
        textbackground(cores_abrir(opcao, 1));
        textcolor(cores_abrir(opcao, 2));
        printf("  Sim  ");
        textbackground(cores_abrir(opcao, 3));
        textcolor(cores_abrir(opcao, 4));
        printf("  Nao  ");
        
        tecla = getch();
        if(tecla==TAB)
            opcao++;
        if(tecla==ENTER){
            switch(opcao){
                      case 0: if(iniciado==TRUE){
                                   _strtime(hora);
                                   separaData(dia, mes, ano);
                                   //Salva a data e hora de fim de execu��o no log
                                   fprintf(log, "<b>Fim Execu��o -</b> 20%s/%s/%s  %s<br><br>\n\n", ano, mes, dia, hora); 
                              }
                              fclose(log); 
                              *sair = TRUE; 
                              break;
                      case 1: desenha_tela(); //Ativa a interface gr�fica  
            }
            pronto = TRUE;
        }
        
        if(opcao>1)
            opcao = 0;      
    
    }while(!pronto);    
}
////////////////////////////////////////////////////////////////////////////////


//Cria Nome Log/////////////////////////////////////////////////////////////////
/* Gera um nome novo para o arquivo de logs, dependendo do dia */
void criaNome_log(char *slog)
{
     char new_data[30];
     char dia[3], mes[3], ano[3];
     
     strcpy(slog, "LOG_"); //Inicializa a string com a palavra LOG
     
     separaData(dia, mes, ano);
     
     //Muda o formato de data para AAMMDD
     strcpy(new_data, ano); //Copia o ano para uma nova string
     strcat(new_data, mes); //Concatena o m�s
     strcat(new_data, dia); //Concatena o dia

     strcat(slog, new_data);//Adiciona a nova data no final da string slog
     strcat(slog, ".HTML");//Adiciona a extens�o .HTML no fim da string slog
}
////////////////////////////////////////////////////////////////////////////////


//Tentativas de pouso em cada pista/////////////////////////////////////////////
/* Salva um relat�rio com as tentativas de pouso em cada pista */
void tentPista(PISTA *arrPista, int tamPista, int *tent_pouso)
{
     int i;
     FILE *relatorio;
     relatorio = fopen("TENT_PISTA.HTML", "wb");
     
     fprintf(relatorio, "<b><font color=blue>Tentativas de pouso em cada pista</font></b><br><br>\n\n");
     for(i=0; i<tamPista; i++)
              fprintf(relatorio, "<b>Pista %s:</b> %d<br>\n", arrPista[i].codPista, tent_pouso[i]);
     
     fclose(relatorio);
}
////////////////////////////////////////////////////////////////////////////////


//Tentativas de Pouso bem sucedidas/////////////////////////////////////////////
/* Salva um relat�rio com as tentativas de pouso bem sucedidas */
void tentBemSuc(int tent_sucesso)
{
     FILE *relatorio;
     relatorio = fopen("TENT_SUCESSO.HTML", "wb");
     
     fprintf(relatorio, "<b>Tentativas de pouso bem sucedidas:</b> %d<br>\n", tent_sucesso);
     
     fclose(relatorio);
}
////////////////////////////////////////////////////////////////////////////////


//Maior Aviao de cada Pista/////////////////////////////////////////////////////
/* Salva um relat�rio com o maior avi�o que pousou em cada pista */
void maAvPista(PISTA *arrPista, int tamPista, AVIAO *arrAviao, int *maiorAviao)
{
     int i;
     int indAviao;
     FILE *relatorio;
     relatorio = fopen("MAIOR_AV_PISTA.HTML", "wb");
     
     fprintf(relatorio, "<b><font color=blue>Maior aviao que pousou em cada pista</font></b><br><br>\n\n");
     for(i=0; i<tamPista; i++){
              indAviao = maiorAviao[i];
              if(indAviao > 0)
                          fprintf(relatorio, "<b>Pista %s:</b> %s<br>\n", arrPista[i].codPista, arrAviao[indAviao].modelo);
     }
     
     fclose(relatorio);
}
////////////////////////////////////////////////////////////////////////////////


//Quantidade de pousos de cada aviao/////////////////////////////////////////////
/* Salva um relat�rio com a quantidade de pousos de cada modelo de avi�o */
void quantPousosAv(AVIAO *arrAviao, int tamAviao, int *nroPousosAviao)
{
     int i;
     FILE *relatorio;
     relatorio = fopen("QUANT_POUSO_AV.HTML", "wb");
     
     fprintf(relatorio, "<b><font color=blue>Quantidade de pousos de cada aviao</font></b><br><br>\n\n");
     for(i=0; i<tamAviao; i++)
              fprintf(relatorio, "<b>%s:</b> %d<br>\n", arrAviao[i].modelo, nroPousosAviao[i]);
     
     fclose(relatorio);
}
////////////////////////////////////////////////////////////////////////////////


//Cores Relatorio///////////////////////////////////////////////////////////////
/* Controla as cores das op��es do menu de relat�rios */
int cores_relatorio(int opcao, int constante)
{
    if(opcao+constante == 5)
       return RED;
    else
       return BLACK;
}
////////////////////////////////////////////////////////////////////////////////


//Relatorio/////////////////////////////////////////////////////////////////////
/* Chama o menu de escolha de relat�rios a serem salvos */
void relatorio(PISTA *arrPista, int tamPista, AVIAO *arrAviao, int tamAviao, int *tent_pouso, int tent_sucesso, int *maiorAviao, int *nroPousosAviao)
{
    int opcao = 0;
    int pronto = FALSE;
    char tecla;
    
     _setcursortype(_NOCURSOR);
     
    popup(LIGHTGRAY, BLACK, 42, 7);
    gotoxy(19,5);
    printf("%c Opcoes de relatorio:                     %c", 186, 186);
     
    
    do{        
        gotoxy(20,7);
        textcolor(cores_relatorio(opcao, 5));
        printf(" Tentativas de pouso em cada pista        ");
        gotoxy(20,8);
        textcolor(cores_relatorio(opcao, 4));
        printf(" Tentativas de pouso bem sucedidas        ");
        gotoxy(20,9);
        textcolor(cores_relatorio(opcao, 3));
        printf(" Maior aviao que pousou em cada pista     ");
        gotoxy(20,10);
        textcolor(cores_relatorio(opcao, 2));
        printf(" Quant. de pousos de cada modelo de aviao ");
        gotoxy(20,11);
        textcolor(cores_relatorio(opcao, 1));
        printf(" Cancelar                                 ");
        
        tecla = getch();
        if(tecla==TAB)
            opcao++;
        if(tecla==ENTER){
            switch(opcao){
                      case 0: tentPista(arrPista, tamPista, tent_pouso); break;
                      case 1: tentBemSuc(tent_sucesso); break;
                      case 2: maAvPista(arrPista, tamPista, arrAviao, maiorAviao); break;
                      case 3: quantPousosAv(arrAviao, tamAviao, nroPousosAviao);
            }
            pronto = TRUE;
        }
        
        if(opcao>4)
            opcao = 0;      
    
    }while(!pronto);    
     
     //Ativa a interface gr�fica 
     desenha_tela();
}
////////////////////////////////////////////////////////////////////////////////


//Main//////////////////////////////////////////////////////////////////////////
/* Controla as op��es do menu e chama as outras fun��es */
int main(){
    //Arquivo do log
    FILE *log;
    //Vetores com os dados do arquivo
    PISTA arrPista[TAM];
    VOO arrVoo[TAM];
    AVIAO arrAviao[TAM];
    //Tamanho dos vetores
    int tamPista=0,
        tamVoo=0,
        tamAviao=0;
    //Nome do arquivo de logs
    char slog[30];
    //Contadores do relat�rio
    int tent_pouso[5] = {0, 0, 0, 0, 0};
    int tent_sucesso = 0;
    int maiorAviao[5] = {-1, -1, -1, -1, -1};
    int nroPousosAviao[30] = {0};
    //Tempor�rio
    char tecla;
    char codPista_ocupada[10];
    //Flags
    int sair = FALSE,              //Programa continua executando enquanto sair = FALSE
        opcao = 2,                 //Inicia o programa com a op��o Abrir destacada
        completa_quadros = FALSE,  //Arquivos ainda n�o foram abertos
        iniciado = FALSE;          //Programa n�o foi iniciado
    
    criaNome_log(slog);
    log = fopen(slog, "a+");
    
    //Ativa a interface gr�fica           
    desenha_tela(); 
    do{  
        //Seleciona a op��o do menu e mostra os arquivos na tela
        menu(opcao);
        if(completa_quadros == TRUE){
              mostra_conteudo(arrPista, arrVoo, arrAviao, codPista_ocupada, tamVoo);
              ligaStatus(TRUE);
              }
        
        //Ler do teclado e comparar
        tecla = getch();
        if(tecla==TAB) //Se apertar tab, muda op��o selecionada
             opcao++;
        
        //Corrige o contador, caso ultrapasse os limites
        if(opcao > 5)
             opcao = 0;
        if(opcao < 0)
             opcao = 5;
        
                 
        if(tecla==ENTER) //Se apertar enter, testa a op��o selecionada
              switch(opcao){
                            case 0: iniciar(&iniciado, completa_quadros, &opcao, arrPista, arrVoo, arrAviao, tamPista, tamAviao, tamVoo, codPista_ocupada, log, tent_pouso, &tent_sucesso, maiorAviao, nroPousosAviao); break;
                            case 1: continuar(iniciado, &opcao, arrPista, arrVoo, arrAviao, tamPista, tamAviao, tamVoo, codPista_ocupada, log, tent_pouso, &tent_sucesso, maiorAviao, nroPousosAviao); break;
                            case 2: abrir(arrPista, arrVoo, arrAviao, &completa_quadros, &tamPista, &tamVoo, &tamAviao, codPista_ocupada); break;
                            case 3: salvar(completa_quadros, arrPista, arrVoo, arrAviao, tamPista, tamVoo, tamAviao, codPista_ocupada); break;
                            case 4: relatorio(arrPista, tamPista, arrAviao, tamAviao, tent_pouso, tent_sucesso, maiorAviao, nroPousosAviao); break;
                            case 5: fsair(&sair, log, iniciado);
              }
                          
    }while(!sair);
                   
}
////////////////////////////////////////////////////////////////////////////////
