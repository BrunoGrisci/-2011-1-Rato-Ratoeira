//Bibliotecas necessárias no decorrer do código
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
//Constantes das direções.
#define SETA_CIMA 72      //código ASCII da seta direcional para cima
#define SETA_BAIXO 80     //código ASCII da seta direcional para baixo
#define SETA_ESQ 75       //código ASCII da seta direcional para esquerda
#define SETA_DIR 77       //código ASCII da seta direcional para direita
#define ESQUERDA 'a'      //letras definidas para direcional, estão padronizadas como
#define DIREITA 'd'       //minúsculas para poder ser feito o uso das setas direcionais
#define CIMA 'w'          //devido ao fato de que o código ASCII da seta direcional para baixo
#define BAIXO 'x'         //ser o mesmo da letra 'P' quando maiúscula (código ASCII)
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
#define swap(x,y) ({ tmp=x; x=y; y=tmp; }) //atribui o valor de uma variável à outra e vice versa
//Protótipos.
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
typedef struct str_personagem str_personagem;//Definição de tipo da estrutura dos personagens.
typedef struct mapa{//Define um novo tipo para a estrutura responsável pelos dados do labirinto
        unsigned char labirinto[LINHAS][COLUNAS]; //área dos "caracteres" do mapa
        int moedas; //conta o número de moedas do mapa, para poder calcular o término das moedas para decretar "Vitória!"
        int numfantasmas; //conta o número de fantasmas existentes no arquivo para comparar com o limite de fantasmas
        }MAPA; //nome do tipo
MAPA labirinto; //declaração da variável para o labirinto
str_personagem pacman; //declaração da variável para o pacman
str_personagem fantasmas[MAXFANTASMAS]; //declaração da variável para os fantasmas, que é um vetor de estruturas
struct str_rota{//Estruturas de AI.
	double distancia;
	unsigned char direcao;
};
typedef struct str_rota str_rota;
//Função que lê um labirinto de um arquivo .txt e retorna TRUE ou FALSE, dependendo da
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
			labirinto.labirinto[y][x] = toupper(fgetc(arq)); //atribui o caracter lido do arquivo a uma posição do vetor
			switch (labirinto.labirinto[y][x]){
				case '\n':
				case '\r':
					x=-1;  //Descarta o \n da linha anterior.
					break;
				case '*'://Caso o caracter lido do arquivo for um asterisco, incrementa contador de moedas.
					labirinto.moedas++; //incrementa o campo moedas da struct labirinto a cada '*' encontrado
					break;
				case 'Q'://Caso o caracter seja Q, atribui as coordenadas à estrutura do pacman, e a direção e pretensão como paradas.
					if(numpac < 1){ //evita um possível erro de existência de mais de um pacman no mapa
                              pacman.y = y;
					          pacman.x = x;
					          pacman.direcao = PARAR;
					          pacman.pretensao = PARAR;
					          numpac++;
                           }else{ //caso já tenha sido lido um pacman, o local no qual se encontra o segundo vira uma "moeda"
                                 labirinto.labirinto[y][x] = '*';
                                 labirinto.moedas++;
                                 }
					break;
				case 'X'://Caso o caracter seja X, testa se já não foi atingido o limite de fantasmas.
//Se não foi, atribui às coordenadas à estrutura do fantasma primeiro, e incrementa o contador de fantasmas,
//atribuindo assim as próximas coordenadas a outro fantasma.
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
				case '#'://Caso o caracter lido seja um # ou espaço em branco, não há ação.
				case ' ':
					break;
				default://Se o caracter lido for diferente dos citados, atribui um espaço em branco.
					labirinto.labirinto[y][x] = ' ';
			}
		}
	}
	fclose(arq); //fecha o arquivo do labirinto
	return TRUE;
}
void desenha_labirinto(){//Função "principal" que, após lido o labirinto, escreve-o na tela.
	int y, x;
	clrscr(); //limpa a tela para a impressão do labirinto
	for (y=0; y<LINHAS; y++){
		for (x=0; x<COLUNAS; x++){
			desenha_lugar(y, x);
		}
		if(y < LINHAS - 1){
             cprintf("\n"); //quebra a linha para que o mapa seja impresso de forma correta na tela
             }
    }
}
void delay(float t){//Função que controla os turnos de movimento
	clock_t start;
	int interval;
	interval = (int) (CLOCKS_PER_SEC * t);
	start = clock();
	while (clock() - start < interval) ;
}
//Função responsável pelos movimentos dos personagens
//de acordo com a direção incrementa/decrementa a coordenada
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
			return '_'; //não há movimento algum
		default:
			printf("** Direcao invalida: %d **\n", direcao); //se for "atacada" uma tecla que não corresponde aos movimentos possíveis
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
			origem_depois = ' ';                        //mostra-se o espaço vazio que estaria "oculto"
	}
	if (destino_antes == ' ') //se existe um espaço vazio
		destino_depois = toupper(origem_antes); //é colocado o que efetuou o movimento para a coordenada
	else{
		if (destino_antes == '*'){ //caso o destino antes do movimento for uma "moeda"
			if (origem_antes == 'Q'){ //e quem estiver executando o movimento for o PacMan
				destino_depois = 'Q'; //é colocado o pacman no lugar da moeda
				labirinto.moedas--; //e é decrementado o número de moedas
			}else{
				destino_depois = 'x'; //caso seja um fanstasma coloca um fanstasma indicando uma moeda "oculta"
			}
		}else{
			if ((toupper(origem_antes) == 'X') && (toupper(destino_antes) == 'X')) //se ambos os locais forem fantasmas
				return '_';                                                    //não ocorre movimento algum
			else{
				destino_depois = '+'; //Caso ocorra a colisão entre um fantasma e o PacMan, este caracter indicará a "morte" do pacman
			}
		}
	}
	labirinto.labirinto[pers->y][pers->x] = origem_depois; //atribui o caracter devido às coordenadas do mapa
	labirinto.labirinto[y_final][x_final] = destino_depois; //atribui ao destino o que realizou o movimento
	desenha_lugar(pers->y, pers->x); //chama a função de desenho para colocar o caracter correspondente na coordenada de origem
	desenha_lugar(y_final, x_final); //chama a função de desenho para colocar o caracter correspondente na coordenada de destino
	pers->x = x_final; //atribui a coordenada de destino à estrutura do personagem
	pers->y = y_final;
	pers->direcao = direcao; //atribui a direção indicada pela tecla para a estrutura do personagem
	return destino_antes;
}
void desenha_lugar(int y, int x){//Função "auxiliar" a desenha_labirinto, para a impressão do mapa
	gotoxy(x+1, y+1);
	switch (labirinto.labirinto[y][x]){
		case '#': //caso seja o '#', caracter dado como padrão para as paredes, troca para o caracter 'bloco' (ASCII 219)
			textcolor(BLUE); //cor do bloco AZUL
			printf("%c", 219);
			break;
		case '*': //caso seja o '*', caracter dado como padrão para as 'moedas', o imprime na cor branca
			textcolor(WHITE);
			cprintf("*");
			break;
		case 'Q': //caso seja o 'Q', caracter dado como padrão para o PacMan, o imprime na cor amarela, como no jogo clássico
			textcolor(YELLOW);
			cprintf("Q");
			break;
		case 'x':
		case 'X': //caso seja o 'X', caracter dado como padrão para os fantasmas, os imprime na cor verde
			textcolor(GREEN);
			cprintf("X");
			break;
		case ' ': //Se for um espaço em branco, imprime um caracter "vazio", livre para movimentação
			cprintf(" ");
			break;
		case '+': //Caracter que só será imprimido, quando o jogador "morrer", para ilustrar o fim do jogo
			textcolor(RED);
			cprintf("+");
			break;
		default: //caracter desconhecido
			cprintf("?");
			break;
	}
}
int jogo(){//Função que "controla" as ações do jogo
    int fim = 2;
    int fim_de_jogo = FALSE; //inicia a variável de fim de jogo como falsa, para o jogo "startar"
	int pause = FALSE; //indica que o jogo inicia em movimento
	unsigned char tecla; //variável responsável pela leitura da tecla de movimento
	unsigned int turno; //contador de turnos do jogo
	unsigned char o_que_havia_no_lugar_aonde_fui;
    if(GetKeyState(20) == 1) //testa se o caps foi ativado durante o jogo
                       keybd_event(20, 0, 0, 0);//esta função desliga a tecla caps lock    
	for (turno=0; !fim_de_jogo; turno++){
        if (kbhit()){ //se alguma tecla foi pressionada
            tecla = getch(); //atribui esta tecla à variável tecla
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
					pacman.direcao = PARAR; //aqui é atribuido a "direção" de pare
					pacman.pretensao = PARAR; //define que o pacman deve parar
					break;
				case PAUSE:
					if (pause)
						pause = FALSE; //caso o jogo já esteja pausado, ele recomeça
					else
						pause = TRUE; //caso ainda não esteja, ele pausa
					break;
				case SAIR:
					fim = 0; //se for ESC, o jogo é encerrado da forma como estiver
			}
			if(GetKeyState(20) == 1) //testa se o caps foi ativado durante o jogo
			                   keybd_event(20, 0, 0, 0); 
  }
  if(fim != 0){ //caso não houve mudança de estado da variável que indica o fim de jogo
		if ((turno%DELAY_PACMAN == 0) && (pause == FALSE)){ //se o turno for divisível por 2, com jogo em movimento
			o_que_havia_no_lugar_aonde_fui = move(&pacman, pacman.pretensao); //é realizado o movimento do pacman
			if (o_que_havia_no_lugar_aonde_fui == '_')//teste de colisão, caso o próximo caracter for " '_' ", o pacman para de andar
				o_que_havia_no_lugar_aonde_fui = move(&pacman, pacman.direcao);
			if (toupper(o_que_havia_no_lugar_aonde_fui) == 'X'){//se o próximo caracter for " 'X' ", significa que ocorreu colisão
				clrscr();                                       //entre o pacman e um fantasma
                textcolor(RED);                                 //decretando assim, fim de jogo, com derrota
				cprintf("\t\t\t\tPerdeste!\n");
				fim = 1; //retorno para diferenciar o tipo de mensagem
			}
		}
		if(fim == 2){ //caso não houve mudança de estado da variável que indica o fim de jogo
		if ((turno%DELAY_FANTASMA == 0) && (pause == FALSE)){ //se o turno for divisivel por 3, com jogo em movimento
			if (move_fantasmas()){                        //é realizado o movimento do(s) fantansma(s)
				clrscr();
                textcolor(RED);
				cprintf("\t\t\t\tPerdeste!\n");
				fim = 1; //retorno para diferenciar o tipo de mensagem que será exibida
			}
		  }
        }
		if(fim == 2){ //caso não houve mudança de estado da variável que indica o fim de jogo
        if (labirinto.moedas == 0){ //caso o usuário já tenha coletado todas as "moedas", o jogo encerra, com vitória
                   clrscr();
                   textcolor(GREEN);
                   cprintf("\t\t\t\t   Venceste!\n");
                   fim = 1; //retorno para diferenciar o tipo de mensagem que será exibida
                       }
                   }
        }
		delay(DELAY);//chama a função que calcula o número de turnos em um determinado tempo
		if((fim == 0) || (fim == 1)) //verifica se houve mudança do estado de fim de jogo
        return fim;
	}
}//Função que calcula qual é a menor distância entre qualquer fantasma e o pacman.
double distancia(str_personagem *p1, str_personagem *p2, int incy, int incx){ 
	return sqrt(pow((p1->x + incx) - p2->x, 2) +
	            pow((p1->y + incy) - p2->y, 2));
}
int move_fantasmas(){ //função que controla o movimento dos fantasmas
	str_rota rotas[4];  //vetor com as quatro possibilidades de rotas (cima, baixo, esquerda, direita)
	str_rota tmp;
	int fantasma;
	int rota;
	unsigned char o_que_havia_no_lugar_aonde_fui;
	for (fantasma=0; fantasma<labirinto.numfantasmas; fantasma++){  //repetições para aplicar a função a todos os fantasmas existentes
		rotas[0].direcao = CIMA;  //atribui à primeira posição do vetor a direção "cima"
		rotas[0].distancia = distancia(&fantasmas[fantasma], &pacman, -1, 0); //calcula a distância, por essa direção, do fantasma ao pacman
		rotas[1].direcao = BAIXO; //atribui "baixo" à segunda posição do vetor
		rotas[1].distancia = distancia(&fantasmas[fantasma], &pacman, 1, 0);
		rotas[2].direcao = ESQUERDA; //atribui "esquerda" à terceira posição do vetor
		rotas[2].distancia = distancia(&fantasmas[fantasma], &pacman, 0, -1);
		rotas[3].direcao = DIREITA; //atribui "direita" à quarta posição do vetor
		rotas[3].distancia = distancia(&fantasmas[fantasma], &pacman, 0, 1);
//evita que os fantasmas retrocedam, ficando assim "sem movimento". Só retrocedem se for a única opção permitida.
		switch (fantasmas[fantasma].direcao){ //switch com os casos das direções do fantasma e correspondente ordenamento de vetor
			case CIMA:                      //se a direção for "cima", coloca "baixo" como última posição do vetor
				swap(rotas[1], rotas[3]);
				break;
			case BAIXO:                    //se a direção for "baixo", coloca "cima" como última posição do vetor
				swap(rotas[0], rotas[3]);
				break;
			case ESQUERDA:                 //se a direção for "esquerda", coloca "direita" como última posição do vetor
				// swap(rotas[3], rotas[3]);
				break;
	        case DIREITA:                  //se a direção for "direita", coloca "esquerda" como última posição do vetor
				swap(rotas[2], rotas[3]);
				break;
                      }
		if (rotas[0].distancia > rotas[1].distancia) //se a distância calculada para a primeira rota for maior que para a segunda,
			swap(rotas[0], rotas[1]);                //troca-as de posição no vetor
		if (rotas[1].distancia > rotas[2].distancia) //se a distância calculada para a segunda rota for maior que para a terceira, 
			swap(rotas[1], rotas[2]);                //troca-as de posição no vetor
		if (rotas[0].distancia > rotas[1].distancia) //se a distância calculada para a primeira rota for maior que para a segunda,
			swap(rotas[0], rotas[1]);                //troca-as de posição no vetor
		for (rota=0; rota<4; rota++) {
			o_que_havia_no_lugar_aonde_fui = move(&fantasmas[fantasma], rotas[rota].direcao); //atribui à coordenada correspondente,
			                                                     //variando esta de acordo com a direção, o resultado da função move
			if (o_que_havia_no_lugar_aonde_fui != '_')           //se o que havia antes na coordenada correspondente era "_", indicando
				rota = 4;                                        //impossibilidade de movimento, atribui o inverso da direção executada até então
                                                                 //ao movimento do fantasma
		}
		if (o_que_havia_no_lugar_aonde_fui == 'Q') {             //se era o pacman, retorna TRUE para a função jogo
			return TRUE;                                         //indicando derrota
		}
	}
	return FALSE;
}
void imprime_pontilhado(){ //Função que apenas gera uma linha pontilhada para separar partes dos menus
     int i;
     for(i=0;i<80;i++)
                      printf("-");
}
char menu(int tipo, int modo){ //Função responsável pelo menu inicial do jogo
     int i, tipo_impress;
     char escolha; //caracter que armazenará a escolha do usuário
     textcolor(YELLOW); //o texto será impresso em amarelo
     switch(tipo){
                  case 0: //número que representa o uso da função para menu principal
                       do{
                            clrscr();
                            imprime_pontilhado();
                            printf("\t\t\t      Bem vindo ao PacMan \n"); //mensagens de menu
                            imprime_pontilhado();
                            comandos();
                            printf("\t\tJ - Para jogar\t\t\tS- Para sair\n"); //opções existentes
                            fflush(stdin); //limpa o buffer do teclado para ocorrer uma leitura correta da escolha do usuário
                            escolha = getch(); //lê a escolha
                            imprime_pontilhado();
                            }while((toupper(escolha) != 'J') && (toupper(escolha) != 'S'));
                       break;
                  case 1: //número que representa o uso da função para menu de novo jogo após uma partida
                       do{
                             if(modo == 0)
                                     clrscr();
                             imprime_pontilhado();
                             printf("\t\t\t   Deseja Jogar Novamente  \n");
                             imprime_pontilhado();
                             printf("\t\tS - Para sim\t\t\tN - Para nao\n");
                             fflush(stdin); //limpa o buffer para verificar se o usuário deseja jogar novamente
                             escolha = getch(); //lê a escolha do usuário
                             imprime_pontilhado();
                             }while((toupper(escolha) != 'S') && (toupper(escolha)!= 'N'));
                       break;
                       }
     return escolha; //retorna o valor da escolha do usuário para a função start
} //Função que verifica a entrada do menu principal e define o que será feito: ou iniciará um novo jogo ou não terá nada a fazer
void game(char comecar){ //função que começa um novo jogo, não começa jogo algum ou começa uma "segunda" partida
     char continua, tipo_impress;
     switch(toupper(comecar)){ //verifica qual caracter foi inserido pelo usuário no menu
                      case 'J'://caso a opção escolhida pelo usuário deja 'J' (caracter definido como "Jogar"), entra no jogo
                           fflush(stdin); //limpa o buffer para não passar direto para o jogo
                           printf("\t\t   Prepare-se (aperte ENTER para comecar)\n"); //Só para não pegar o player de surpresa
                           getchar(); //segura a tela para dar um "tempo" para que o usuário se prepare
                           clrscr(); //limpa tela para "eliminar" a visualização do menu principal
                           do{//entra no laço que começo de jogo
                                      ler_labirinto("labirinto.txt"); //lê o labirinto
	                                  desenha_labirinto(); //o imprime na tela
	                                  tipo_impress = jogo(); //realiza todo o jogo
                                      continua = menu(NEWGAME, tipo_impress);
                                      }while(toupper(continua) == 'S'); //caso ele tecle 'S'/'s' o laço se repete
                           break;
                      case 'S':
                           printf("\n\n");     
                           imprime_pontilhado();
                           printf("\t\tTudo bem, volte quando estiver com vontade de jogar\n"); //caso ele não queira iniciar uma
                           imprime_pontilhado();                                                //partida
                           break;
                            }                                                                      
}//Função que exibe na tela inicial do jogo os possíveis comandos para o usuário
void comandos(){
     textcolor(GREEN);
     printf("\t  Comandos:\t\t\t\tComandos Alternativos:\n");                   //divide em duas pseudo-colunas
     printf("\tW - Cima\t\t\tSeta para cima       - Cima\n");                   //a da esquerda os comandos dados como padrão
     printf("\tA - Esquerda\t\t\tSeta para a esquerda - Esquerda\n");           //na definição do trabalho
     printf("\tD - Direita\t\t\tSeta para a direita  - Direita\n");
     printf("\tX - Baixo\t\t\tSeta para baixo      - Baixo\n");                 //a da direita comandos alternativos
     printf("\tS - Para apenas o PacMan\n");                                    //explorados por nós
     printf("\tP - Pausa o jogo\n");
     printf("\tESC - Sai do jogo\n\n");
     printf("\t    OBS: Nao existe diferenciacao entre maiusculas e minusculas\n");//avisa que não tem diferença entre jogar com caps lock
     textcolor(YELLOW);                                                            //ligado ou desligado
     imprime_pontilhado();
} //Função responsável por receber o retorno da função menu e chamar uma outra função para ver o que vai ser feito
void start(){
     char novo_jogo, comecar; //variáveis para a entrada de "inicio de jogo", e de "jogar novamente"
	 comecar = menu(INICIAL, 0); //atribui a variável começar o retorno da função que realiza a função de menu principal
	 game(comecar); //função que verifica se vai ser iniciado um novo jogo ou não
}
int main(){ //Função principal
	start(); //função que chama as funções responsáveis pelo início do jogo
    getch(); //Para pausar o programa
    return 0;
}
