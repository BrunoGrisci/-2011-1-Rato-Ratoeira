//Bibliotecas necess�rias no decorrer do c�digo
#include<stdio.h>
#include<time.h>
#include<ctype.h>
#include<conio2.h>
#include<math.h>
#include<windows.h>
//Constantes do labirinto.
#define LINHAS 24
#define COLUNAS 80
#define MAXFANTASMAS 5
//Constantes das dire��es.
#define SETA_CIMA 72      //c�digo ASCII da seta direcional para cima
#define SETA_BAIXO 80     //c�digo ASCII da seta direcional para baixo
#define SETA_ESQ 75       //c�digo ASCII da seta direcional para esquerda
#define SETA_DIR 77       //c�digo ASCII da seta direcional para direita
#define ESQUERDA 'a'      //letras definidas para direcional, est�o padronizadas como
#define DIREITA 'd'       //min�sculas para poder ser feito o uso das setas direcionais
#define CIMA 'w'          //devido ao fato de que o c�digo ASCII da seta direcional para baixo
#define BAIXO 'x'         //ser o mesmo da letra 'P' quando mai�scula (c�digo ASCII)
#define PARAR 's'
#define PAUSE 'p'
#define SAIR '\e'
//Constantes de flag
#define FALSE 0
#define TRUE 1
//Constantes de controle de velocidade de jogo.
#define DELAY_FANTASMA 3
#define DELAY_PACMAN 2
#define CICLO_DELAY 6
#define DELAY 0.05
//Constantes de controle de menu
#define INICIAL 0
#define NEWGAME 1
#define swap(x,y) ({ tmp=x; x=y; y=tmp; }) //atribui o valor de uma vari�vel � outra e vice versa
//Prot�tipos.
void desenha_lugar(int y, int x);
int move_fantasmas();
int ler_labirinto(char nome[]);
void game(char);
void start();
char menu(int,int);
void imprime_pontilhado();
void comandos();
//Estado do jogo.
struct str_personagem{//Estrutura para o pacman e os fantasmas.
	int x;
	int y;
	char direcao;
	char pretensao;
};
typedef struct str_personagem str_personagem;//Defini��o de tipo da estrutura dos personagens.
typedef struct mapa{//Define um novo tipo para a estrutura respons�vel pelos dados do labirinto
        unsigned char labirinto[LINHAS][COLUNAS]; //�rea dos "caracteres" do mapa
        int moedas; //conta o n�mero de moedas do mapa, para poder calcular o t�rmino das moedas para decretar "Vit�ria!"
        int numfantasmas; //conta o n�mero de fantasmas existentes no arquivo para comparar com o limite de fantasmas
        }MAPA; //nome do tipo
MAPA labirinto; //declara��o da vari�vel para o labirinto
str_personagem pacman; //declara��o da vari�vel para o pacman
str_personagem fantasmas[MAXFANTASMAS]; //declara��o da vari�vel para os fantasmas, que � um vetor de estruturas
struct str_rota{//Estruturas de AI.
	double distancia;
	unsigned char direcao;
};
typedef struct str_rota str_rota;
//Fun��o que l� um labirinto de um arquivo .txt e retorna TRUE ou FALSE, dependendo da
//compatibilidade do arquivo.
int ler_labirinto(char nome[]){
	int y, x,numpac=0;
	FILE *arq;
	arq = fopen(nome, "r"); //abertura do arquivo
	if (!arq){
		cprintf("Erro ao abrir o arquivo!\n");
		getch();
		return FALSE;
	}
	labirinto.moedas = 0; //Inicia contador de moedas e de fantasmas em 0
	labirinto.numfantasmas = 0;
	for (y=0; y<LINHAS; y++){
		for (x=0; x<COLUNAS; x++){
			labirinto.labirinto[y][x] = toupper(fgetc(arq)); //atribui o caracter lido do arquivo a uma posi��o do vetor
			switch (labirinto.labirinto[y][x]){
				case '\n':
				case '\r':
					x=-1;  //Descarta o \n da linha anterior.
					break;
				case '*'://Caso o caracter lido do arquivo for um asterisco, incrementa contador de moedas.
					labirinto.moedas++; //incrementa o campo moedas da struct labirinto a cada '*' encontrado
					break;
				case 'Q'://Caso o caracter seja Q, atribui as coordenadas � estrutura do pacman, e a dire��o e pretens�o como paradas.
					if(numpac < 1){ //evita um poss�vel erro de exist�ncia de mais de um pacman no mapa
                              pacman.y = y;
					          pacman.x = x;
					          pacman.direcao = PARAR;
					          pacman.pretensao = PARAR;
					          numpac++;
                           }else{ //caso j� tenha sido lido um pacman, o local no qual se encontra o segundo vira uma "moeda"
                                 labirinto.labirinto[y][x] = '*';
                                 labirinto.moedas++;
                                 }
					break;
				case 'X'://Caso o caracter seja X, testa se j� n�o foi atingido o limite de fantasmas.
//Se n�o foi, atribui �s coordenadas � estrutura do fantasma primeiro, e incrementa o contador de fantasmas,
//atribuindo assim as pr�ximas coordenadas a outro fantasma.
					if(labirinto.numfantasmas < MAXFANTASMAS){ 
						labirinto.labirinto[y][x] = 'x';
						fantasmas[labirinto.numfantasmas].y = y;
						fantasmas[labirinto.numfantasmas].x = x;
						labirinto.numfantasmas++;
					}else{ //Se o limite de fantasmas foi atingido, atribui um asterisco no lugar e incrementa moedas.
						labirinto.labirinto[y][x] = '*';
						}
					labirinto.moedas++;
					break;
				case '#'://Caso o caracter lido seja um # ou espa�o em branco, n�o h� a��o.
				case ' ':
					break;
				default://Se o caracter lido for diferente dos citados, atribui um espa�o em branco.
					labirinto.labirinto[y][x] = ' ';
			}
		}
	}
	fclose(arq); //fecha o arquivo do labirinto
	return TRUE;
}
void desenha_labirinto(){//Fun��o "principal" que, ap�s lido o labirinto, escreve-o na tela.
	int y, x;
	clrscr(); //limpa a tela para a impress�o do labirinto
	for (y=0; y<LINHAS; y++){
		for (x=0; x<COLUNAS; x++){
			desenha_lugar(y, x);
		}
		if(y < LINHAS - 1){
             cprintf("\n"); //quebra a linha para que o mapa seja impresso de forma correta na tela
             }
    }
}
void delay(float t){//Fun��o que controla os turnos de movimento
	clock_t start;
	int interval;
	interval = (int) (CLOCKS_PER_SEC * t);
	start = clock();
	while (clock() - start < interval) ;
}
//Fun��o respons�vel pelos movimentos dos personagens
//de acordo com a dire��o incrementa/decrementa a coordenada
unsigned char move(str_personagem *pers, char direcao){
	int x_final = pers->x;
	int y_final = pers->y;
	unsigned char origem_antes, origem_depois;
	unsigned char destino_antes, destino_depois;
	switch (direcao){
		case ESQUERDA:
        case SETA_ESQ:
			x_final--; //decrementa a coordenada x, tendo a coordenada y fixa, indo para a esquerda
			break;
		case DIREITA:
        case SETA_DIR:
			x_final++; //incrementa a coordenada x, tendo a coordenada y fixa, indo para a direita
			break;
		case CIMA:
        case SETA_CIMA:
			y_final--; //decrementa a coordenada y, tendo a coordenada x fixa, indo para cima
			break;
		case BAIXO:
        case SETA_BAIXO:
			y_final++; //incrementa a coordenada y, tendo a coordenada x fixa, indo para baixo
			break;
		case PARAR:
			return '_'; //n�o h� movimento algum
		default:
			printf("** Direcao invalida: %d **\n", direcao); //se for "atacada" uma tecla que n�o corresponde aos movimentos poss�veis
			getch();                                         //imprime esta mensagem
			return FALSE;
	}
	origem_antes = labirinto.labirinto[pers->y][pers->x]; //o que havia na coordenada antes do movimento ocorrer
	destino_antes = labirinto.labirinto[y_final][x_final]; //o que tinha na coordenada pra onde o movimento ocorre
	if (destino_antes == '#') //se havia uma parede
		return '_'; //retorna
	if (origem_antes == 'x') //se havia um "fantasma" sobre uma moeda, ao ocorrer o movimento do fantasma
		origem_depois = '*'; //mostra-se a moeda que estaria "oculta"
	else{
		if ((origem_antes == 'X') || (origem_antes == 'Q')) //se havia um "fantasma" ou o PacMan sobre um local vazio
			origem_depois = ' ';                        //mostra-se o espa�o vazio que estaria "oculto"
	}
	if (destino_antes == ' ') //se existe um espa�o vazio
		destino_depois = toupper(origem_antes); //� colocado o que efetuou o movimento para a coordenada
	else{
		if (destino_antes == '*'){ //caso o destino antes do movimento for uma "moeda"
			if (origem_antes == 'Q'){ //e quem estiver executando o movimento for o PacMan
				destino_depois = 'Q'; //� colocado o pacman no lugar da moeda
				labirinto.moedas--; //e � decrementado o n�mero de moedas
			}else{
				destino_depois = 'x'; //caso seja um fanstasma coloca um fanstasma indicando uma moeda "oculta"
			}
		}else{
			if ((toupper(origem_antes) == 'X') && (toupper(destino_antes) == 'X')) //se ambos os locais forem fantasmas
				return '_';                                                    //n�o ocorre movimento algum
			else{
				destino_depois = '+'; //Caso ocorra a colis�o entre um fantasma e o PacMan, este caracter indicar� a "morte" do pacman
			}
		}
	}
	labirinto.labirinto[pers->y][pers->x] = origem_depois; //atribui o caracter devido �s coordenadas do mapa
	labirinto.labirinto[y_final][x_final] = destino_depois; //atribui ao destino o que realizou o movimento
	desenha_lugar(pers->y, pers->x); //chama a fun��o de desenho para colocar o caracter correspondente na coordenada de origem
	desenha_lugar(y_final, x_final); //chama a fun��o de desenho para colocar o caracter correspondente na coordenada de destino
	pers->x = x_final; //atribui a coordenada de destino � estrutura do personagem
	pers->y = y_final;
	pers->direcao = direcao; //atribui a dire��o indicada pela tecla para a estrutura do personagem
	return destino_antes;
}
void desenha_lugar(int y, int x){//Fun��o "auxiliar" a desenha_labirinto, para a impress�o do mapa
	gotoxy(x+1, y+1);
	switch (labirinto.labirinto[y][x]){
		case '#': //caso seja o '#', caracter dado como padr�o para as paredes, troca para o caracter 'bloco' (ASCII 219)
			textcolor(BLUE); //cor do bloco AZUL
			printf("%c", 219);
			break;
		case '*': //caso seja o '*', caracter dado como padr�o para as 'moedas', o imprime na cor branca
			textcolor(WHITE);
			cprintf("*");
			break;
		case 'Q': //caso seja o 'Q', caracter dado como padr�o para o PacMan, o imprime na cor amarela, como no jogo cl�ssico
			textcolor(YELLOW);
			cprintf("Q");
			break;
		case 'x':
		case 'X': //caso seja o 'X', caracter dado como padr�o para os fantasmas, os imprime na cor verde
			textcolor(GREEN);
			cprintf("X");
			break;
		case ' ': //Se for um espa�o em branco, imprime um caracter "vazio", livre para movimenta��o
			cprintf(" ");
			break;
		case '+': //Caracter que s� ser� imprimido, quando o jogador "morrer", para ilustrar o fim do jogo
			textcolor(RED);
			cprintf("+");
			break;
		default: //caracter desconhecido
			cprintf("?");
			break;
	}
}
int jogo(){//Fun��o que "controla" as a��es do jogo
    int fim = 2;
    int fim_de_jogo = FALSE; //inicia a vari�vel de fim de jogo como falsa, para o jogo "startar"
	int pause = FALSE; //indica que o jogo inicia em movimento
	unsigned char tecla; //vari�vel respons�vel pela leitura da tecla de movimento
	unsigned int turno; //contador de turnos do jogo
	unsigned char o_que_havia_no_lugar_aonde_fui;
    if(GetKeyState(20) == 1) //testa se o caps foi ativado durante o jogo
                       keybd_event(20, 0, 0, 0);//esta fun��o desliga a tecla caps lock    
	for (turno=0; !fim_de_jogo; turno++){
        if (kbhit()){ //se alguma tecla foi pressionada
            tecla = getch(); //atribui esta tecla � vari�vel tecla
            switch (tecla){ //verifica qual deve ser o comando para o jogo
				case ESQUERDA: 
                case DIREITA:
				case CIMA:
				case BAIXO:
                case SETA_CIMA:
                case SETA_BAIXO:
                case SETA_ESQ:
                case SETA_DIR:
					pacman.pretensao = tecla; //caso seja uma tecla para movimento, a atribui a estrutura do pacman
					break;
				case PARAR:
					pacman.direcao = PARAR; //aqui � atribuido a "dire��o" de pare
					pacman.pretensao = PARAR; //define que o pacman deve parar
					break;
				case PAUSE:
					if (pause)
						pause = FALSE; //caso o jogo j� esteja pausado, ele recome�a
					else
						pause = TRUE; //caso ainda n�o esteja, ele pausa
					break;
				case SAIR:
					fim = 0; //se for ESC, o jogo � encerrado da forma como estiver
			}
			if(GetKeyState(20) == 1) //testa se o caps foi ativado durante o jogo
			                   keybd_event(20, 0, 0, 0); 
  }
  if(fim != 0){ //caso n�o houve mudan�a de estado da vari�vel que indica o fim de jogo
		if ((turno%DELAY_PACMAN == 0) && (pause == FALSE)){ //se o turno for divis�vel por 2, com jogo em movimento
			o_que_havia_no_lugar_aonde_fui = move(&pacman, pacman.pretensao); //� realizado o movimento do pacman
			if (o_que_havia_no_lugar_aonde_fui == '_')//teste de colis�o, caso o pr�ximo caracter for " '_' ", o pacman para de andar
				o_que_havia_no_lugar_aonde_fui = move(&pacman, pacman.direcao);
			if (toupper(o_que_havia_no_lugar_aonde_fui) == 'X'){//se o pr�ximo caracter for " 'X' ", significa que ocorreu colis�o
				clrscr();                                       //entre o pacman e um fantasma
                textcolor(RED);                                 //decretando assim, fim de jogo, com derrota
				cprintf("\t\t\t\tPerdeste!\n");
				fim = 1; //retorno para diferenciar o tipo de mensagem
			}
		}
		if(fim == 2){ //caso n�o houve mudan�a de estado da vari�vel que indica o fim de jogo
		if ((turno%DELAY_FANTASMA == 0) && (pause == FALSE)){ //se o turno for divisivel por 3, com jogo em movimento
			if (move_fantasmas()){                        //� realizado o movimento do(s) fantansma(s)
				clrscr();
                textcolor(RED);
				cprintf("\t\t\t\tPerdeste!\n");
				fim = 1; //retorno para diferenciar o tipo de mensagem que ser� exibida
			}
		  }
        }
		if(fim == 2){ //caso n�o houve mudan�a de estado da vari�vel que indica o fim de jogo
        if (labirinto.moedas == 0){ //caso o usu�rio j� tenha coletado todas as "moedas", o jogo encerra, com vit�ria
                   clrscr();
                   textcolor(GREEN);
                   cprintf("\t\t\t\t   Venceste!\n");
                   fim = 1; //retorno para diferenciar o tipo de mensagem que ser� exibida
                       }
                   }
        }
		delay(DELAY);//chama a fun��o que calcula o n�mero de turnos em um determinado tempo
		if((fim == 0) || (fim == 1)) //verifica se houve mudan�a do estado de fim de jogo
        return fim;
	}
}//Fun��o que calcula qual � a menor dist�ncia entre qualquer fantasma e o pacman.
double distancia(str_personagem *p1, str_personagem *p2, int incy, int incx){ 
	return sqrt(pow((p1->x + incx) - p2->x, 2) +
	            pow((p1->y + incy) - p2->y, 2));
}
int move_fantasmas(){ //fun��o que controla o movimento dos fantasmas
	str_rota rotas[4];  //vetor com as quatro possibilidades de rotas (cima, baixo, esquerda, direita)
	str_rota tmp;
	int fantasma;
	int rota;
	unsigned char o_que_havia_no_lugar_aonde_fui;
	for (fantasma=0; fantasma<labirinto.numfantasmas; fantasma++){  //repeti��es para aplicar a fun��o a todos os fantasmas existentes
		rotas[0].direcao = CIMA;  //atribui � primeira posi��o do vetor a dire��o "cima"
		rotas[0].distancia = distancia(&fantasmas[fantasma], &pacman, -1, 0); //calcula a dist�ncia, por essa dire��o, do fantasma ao pacman
		rotas[1].direcao = BAIXO; //atribui "baixo" � segunda posi��o do vetor
		rotas[1].distancia = distancia(&fantasmas[fantasma], &pacman, 1, 0);
		rotas[2].direcao = ESQUERDA; //atribui "esquerda" � terceira posi��o do vetor
		rotas[2].distancia = distancia(&fantasmas[fantasma], &pacman, 0, -1);
		rotas[3].direcao = DIREITA; //atribui "direita" � quarta posi��o do vetor
		rotas[3].distancia = distancia(&fantasmas[fantasma], &pacman, 0, 1);
//evita que os fantasmas retrocedam, ficando assim "sem movimento". S� retrocedem se for a �nica op��o permitida.
		switch (fantasmas[fantasma].direcao){ //switch com os casos das dire��es do fantasma e correspondente ordenamento de vetor
			case CIMA:                      //se a dire��o for "cima", coloca "baixo" como �ltima posi��o do vetor
				swap(rotas[1], rotas[3]);
				break;
			case BAIXO:                    //se a dire��o for "baixo", coloca "cima" como �ltima posi��o do vetor
				swap(rotas[0], rotas[3]);
				break;
			case ESQUERDA:                 //se a dire��o for "esquerda", coloca "direita" como �ltima posi��o do vetor
				// swap(rotas[3], rotas[3]);
				break;
	        case DIREITA:                  //se a dire��o for "direita", coloca "esquerda" como �ltima posi��o do vetor
				swap(rotas[2], rotas[3]);
				break;
                      }
		if (rotas[0].distancia > rotas[1].distancia) //se a dist�ncia calculada para a primeira rota for maior que para a segunda,
			swap(rotas[0], rotas[1]);                //troca-as de posi��o no vetor
		if (rotas[1].distancia > rotas[2].distancia) //se a dist�ncia calculada para a segunda rota for maior que para a terceira, 
			swap(rotas[1], rotas[2]);                //troca-as de posi��o no vetor
		if (rotas[0].distancia > rotas[1].distancia) //se a dist�ncia calculada para a primeira rota for maior que para a segunda,
			swap(rotas[0], rotas[1]);                //troca-as de posi��o no vetor
		for (rota=0; rota<4; rota++) {
			o_que_havia_no_lugar_aonde_fui = move(&fantasmas[fantasma], rotas[rota].direcao); //atribui � coordenada correspondente,
			                                                     //variando esta de acordo com a dire��o, o resultado da fun��o move
			if (o_que_havia_no_lugar_aonde_fui != '_')           //se o que havia antes na coordenada correspondente era "_", indicando
				rota = 4;                                        //impossibilidade de movimento, atribui o inverso da dire��o executada at� ent�o
                                                                 //ao movimento do fantasma
		}
		if (o_que_havia_no_lugar_aonde_fui == 'Q') {             //se era o pacman, retorna TRUE para a fun��o jogo
			return TRUE;                                         //indicando derrota
		}
	}
	return FALSE;
}
void imprime_pontilhado(){ //Fun��o que apenas gera uma linha pontilhada para separar partes dos menus
     int i;
     for(i=0;i<80;i++)
                      printf("-");
}
char menu(int tipo, int modo){ //Fun��o respons�vel pelo menu inicial do jogo
     int i, tipo_impress;
     char escolha; //caracter que armazenar� a escolha do usu�rio
     textcolor(YELLOW); //o texto ser� impresso em amarelo
     switch(tipo){
                  case 0: //n�mero que representa o uso da fun��o para menu principal
                       do{
                            clrscr();
                            imprime_pontilhado();
                            printf("\t\t\t      Bem vindo ao PacMan \n"); //mensagens de menu
                            imprime_pontilhado();
                            comandos();
                            printf("\t\tJ - Para jogar\t\t\tS- Para sair\n"); //op��es existentes
                            fflush(stdin); //limpa o buffer do teclado para ocorrer uma leitura correta da escolha do usu�rio
                            escolha = getch(); //l� a escolha
                            imprime_pontilhado();
                            }while((toupper(escolha) != 'J') && (toupper(escolha) != 'S'));
                       break;
                  case 1: //n�mero que representa o uso da fun��o para menu de novo jogo ap�s uma partida
                       do{
                             if(modo == 0)
                                     clrscr();
                             imprime_pontilhado();
                             printf("\t\t\t   Deseja Jogar Novamente  \n");
                             imprime_pontilhado();
                             printf("\t\tS - Para sim\t\t\tN - Para nao\n");
                             fflush(stdin); //limpa o buffer para verificar se o usu�rio deseja jogar novamente
                             escolha = getch(); //l� a escolha do usu�rio
                             imprime_pontilhado();
                             }while((toupper(escolha) != 'S') && (toupper(escolha)!= 'N'));
                       break;
                       }
     return escolha; //retorna o valor da escolha do usu�rio para a fun��o start
} //Fun��o que verifica a entrada do menu principal e define o que ser� feito: ou iniciar� um novo jogo ou n�o ter� nada a fazer
void game(char comecar){ //fun��o que come�a um novo jogo, n�o come�a jogo algum ou come�a uma "segunda" partida
     char continua, tipo_impress;
     switch(toupper(comecar)){ //verifica qual caracter foi inserido pelo usu�rio no menu
                      case 'J'://caso a op��o escolhida pelo usu�rio deja 'J' (caracter definido como "Jogar"), entra no jogo
                           fflush(stdin); //limpa o buffer para n�o passar direto para o jogo
                           printf("\t\t   Prepare-se (aperte ENTER para comecar)\n"); //S� para n�o pegar o player de surpresa
                           getchar(); //segura a tela para dar um "tempo" para que o usu�rio se prepare
                           clrscr(); //limpa tela para "eliminar" a visualiza��o do menu principal
                           do{//entra no la�o que come�o de jogo
                                      ler_labirinto("labirinto.txt"); //l� o labirinto
	                                  desenha_labirinto(); //o imprime na tela
	                                  tipo_impress = jogo(); //realiza todo o jogo
                                      continua = menu(NEWGAME, tipo_impress);
                                      }while(toupper(continua) == 'S'); //caso ele tecle 'S'/'s' o la�o se repete
                           break;
                      case 'S':
                           printf("\n\n");     
                           imprime_pontilhado();
                           printf("\t\tTudo bem, volte quando estiver com vontade de jogar\n"); //caso ele n�o queira iniciar uma
                           imprime_pontilhado();                                                //partida
                           break;
                            }                                                                      
}//Fun��o que exibe na tela inicial do jogo os poss�veis comandos para o usu�rio
void comandos(){
     textcolor(GREEN);
     printf("\t  Comandos:\t\t\t\tComandos Alternativos:\n");                   //divide em duas pseudo-colunas
     printf("\tW - Cima\t\t\tSeta para cima       - Cima\n");                   //a da esquerda os comandos dados como padr�o
     printf("\tA - Esquerda\t\t\tSeta para a esquerda - Esquerda\n");           //na defini��o do trabalho
     printf("\tD - Direita\t\t\tSeta para a direita  - Direita\n");
     printf("\tX - Baixo\t\t\tSeta para baixo      - Baixo\n");                 //a da direita comandos alternativos
     printf("\tS - Para apenas o PacMan\n");                                    //explorados por n�s
     printf("\tP - Pausa o jogo\n");
     printf("\tESC - Sai do jogo\n\n");
     printf("\t    OBS: Nao existe diferenciacao entre maiusculas e minusculas\n");//avisa que n�o tem diferen�a entre jogar com caps lock
     textcolor(YELLOW);                                                            //ligado ou desligado
     imprime_pontilhado();
} //Fun��o respons�vel por receber o retorno da fun��o menu e chamar uma outra fun��o para ver o que vai ser feito
void start(){
     char novo_jogo, comecar; //vari�veis para a entrada de "inicio de jogo", e de "jogar novamente"
	 comecar = menu(INICIAL, 0); //atribui a vari�vel come�ar o retorno da fun��o que realiza a fun��o de menu principal
	 game(comecar); //fun��o que verifica se vai ser iniciado um novo jogo ou n�o
}
int main(){ //Fun��o principal
	start(); //fun��o que chama as fun��es respons�veis pelo in�cio do jogo
    getch(); //Para pausar o programa
    return 0;
}
