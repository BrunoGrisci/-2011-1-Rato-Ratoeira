//INCLUDES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>
#include "conio.h"
#include "conio.c"

//CONSTANTES
//Constante de tamanhos máximos
#define LINHA 80
#define TAM 50
//Flags: Verdadeiro/Falso
#define TRUE 1
#define FALSE 0
//Teclas e seu código ASCII
#define BACKSPACE 8
#define ENTER 13
#define TAB 9

//ESTRUTURAS
typedef struct  { 
      char codVoo[30]; 
      char origem[20];
      int codAviao; 
} VOO;

typedef struct  { 
      char codPista[10]; 
      int extensao; 
      int peso; 
} PISTA; 
 
typedef struct  { 
      int codAviao; 
      char modelo[30]; 
      int extensaoParaPouso; 
      int pesoMaximo; 
} AVIAO; 


//CABEÇALHOS
//Desenhar
void desenha_topo(int tamanho);
void desenha_base(int tamanho);
void desenha_lateral(int linha);
void desenha_fundo(int inicio, int final);
void desenha_tela();
void popup(int cor_fundo, int cor_texto, int tam_x, int tam_y);
void desenha_abrir();
//Linha de Comando
void lc_highlight(int flag);
void backspace(char* comando, int* i, int* x, int* y);
void ajuda();
void separa_comando(char *comando, char *codVoo, char *codPista);
void deletaVoo(VOO *arrVoo, int tamVoo, char *codVoo);
void linha_de_comando(int* opcao, PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int tamPista, int tamVoo, int tamAviao, char *codPista_ocupada, FILE *log, int *tent_pouso, int *tent_sucesso, int *maiorAviao, int *nroPousosAviao);
int testa_pouso(AVIAO *av, PISTA p_pouso, char *codPista_ocupada);
void testa_MaiorAviao(AVIAO *av, int *maiorAviao, AVIAO *arrAviao, int tamAviao, int indPista);
void quantPousos(AVIAO *av, AVIAO *arrAviao, int tamAviao, int *nroPousosAviao);
int checa_texto(char *comando, VOO *arrVoo, int tamVoo, AVIAO *arrAviao, int tamAviao, PISTA *arrPista, int tamPista, FILE *log, char *codPista_ocupada, int *tent_pouso, int *tent_sucesso, int *maiorAviao, int *nroPousosAviao);
//Busca
AVIAO * busca_aviao(int codigo, AVIAO *arrAviao, int tamanho);
int busca_codAviao(char *codVoo, VOO *arrVoo, int tamVoo);
int busca_pista(char *codPista, PISTA *arrPista, int tamanho);
//Menu
void menu(int opcao);
void iniciar(int *iniciado, int completa_quadros, int* opcao, PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int tamPista, int tamVoo, int tamAviao, char *codPista_ocupada, FILE *log, int *tent_pouso, int *tent_sucesso, int *maiorAviao, int *nroPousosAviao);
void continuar(int iniciado, int* opcao, PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int tamPista, int tamVoo, int tamAviao, char *codPista_ocupada, FILE *log, int *tent_pouso, int *tent_sucesso, int *maiorAviao, int *nroPousosAviao);
void abrir(PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int *completa_quadros, int *tamPista, int *tamVoo, int *tamAviao, char *codPista_ocupada);
void salvar(int completa_quadros, PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int tamPista, int tamVoo, int tamAviao, char *codPista_ocupada);
void relatorio(PISTA *arrPista, int tamPista, AVIAO *arrAviao, int tamAviao, int *tent_pouso, int tent_sucesso, int *maiorAviao, int *nroPousosAviao);
void fsair(int *sair, FILE *log, int iniciado);
void mostra_conteudo(PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, char *codPista_ocupada, int tamVoo);
void ligaStatus(int flag);
//Controle de cores
int cor_opcao(int opcao, int constante);
int cores_abrir(int opcao, int constante);
int cores_relatorio(int opcao, int constante);
//Abrir
void abrePistas_bin(FILE *arqPistas_bin, PISTA *arrPista, int *tamPista);
void abreAvioes_bin(FILE *arqAvioes_bin, AVIAO *arrAviao, int *tamAviao);
void abreStatus_bin(FILE *arqStatus_bin, char *codPista_ocupada);
void ordena_pistas(PISTA *arrPista, int tamanho);
void abre_voos(FILE *arq_voos, VOO *arrVoo, int *tamVoo);
void abre_pistas(FILE *arq_pistas, PISTA *arrPista, int *tamPista);
void abre_avioes(FILE *arq_avioes, AVIAO *arrAviao, int *tamAviao);
void sim_nova(PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int *completa_quadros, int *tamPista, int *tamVoo, int *tamAviao);
void continuar_sim(PISTA *arrPista, VOO *arrVoo, AVIAO *arrAviao, int *completa_quadros, int *tamPista, int *tamVoo, int *tamAviao, char *codPista_ocupada);
//Salvar
void salva_pistas(PISTA *arrPista, int tamPista);
void salva_voos(VOO *arrVoo, int tamVoo);
void salva_avioes(AVIAO *arrAviao, int tamAviao);
void salva_status(char *codPista_ocupada);
//Log
void criaNome_log(char *slog);
//Relatório
void tentPista(PISTA *arrPista, int tamPista, int *tent_pouso);
void tentBemSuc(int tent_sucesso);
void maAvPista(PISTA *arrPista, int tamPista, AVIAO *arrAviao, int *maiorAviao);
void quantPousosAv(AVIAO *arrAviao, int tamAviao, int *nroPousosAviao);
void separaData(char *dia, char *mes, char *ano);
//Easter Eggs
//Potter////////////////////////////////////////////////////////////////////////
void potter()
{
     //Esconde o cursor e chama função para desenhar a janela
     _setcursortype(_NOCURSOR);
    
     popup(MAGENTA, WHITE, 62, 3);
     gotoxy(9,6);
     printf("%c                     O Potter nao pagou!!                     %c", 186, 186);
     
     getch();
     //Ativa a interface gráfica           
     desenha_tela(); 
}
////////////////////////////////////////////////////////////////////////////////


//Toninho///////////////////////////////////////////////////////////////////////
void toninho()
{
     //Esconde o cursor e chama a função para desenhar a janela
     _setcursortype(_NOCURSOR);
    
     popup(MAGENTA, WHITE, 62, 3);
     gotoxy(9,6);
     printf("%c               \"so' ate' a setima serie...\"                   %c", 186, 186);
    
     getch();
     //Ativa a interface gráfica           
     desenha_tela(); 
}
////////////////////////////////////////////////////////////////////////////////


//Mara Abel/////////////////////////////////////////////////////////////////////
void marabel(){
    int tela[20][20] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,3,3,0,0,3,3,0,0,0,0,
        0,0,0,0,0,0,0,0,0,3,0,0,3,3,0,0,3,0,0,0,
        0,0,0,0,0,0,0,0,3,0,0,3,0,0,3,0,0,3,0,0,
        0,0,0,0,0,0,0,3,0,0,3,0,0,0,0,3,0,0,3,0,
        0,0,0,0,0,0,0,3,0,0,3,0,0,0,0,3,0,0,3,0,
        0,0,0,0,0,0,0,3,0,0,3,0,0,0,0,3,0,0,3,0,
        0,0,0,0,0,0,0,0,3,0,0,3,0,0,3,0,0,3,0,0,
        0,0,0,0,0,0,0,0,0,3,0,0,3,3,0,0,3,0,0,0,
        0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,
        0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,0,
        0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,0,
        0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0
    };
    int i, j;
    
    _setcursortype(_NOCURSOR);
    system("color FD");
    system("cls");
    for (i=0; i<20; i++){
        for(j=0; j<20; j++){
                 if(tela[i][j] == 0)
                      printf(" ");
                 if(tela[i][j] == 1)
                      printf(":");
                 if(tela[i][j] == 3)
                      printf("@");
        }
        printf("\n");
    }
    
    getch();
    //Ativa a interface gráfica           
    desenha_tela();             
}


