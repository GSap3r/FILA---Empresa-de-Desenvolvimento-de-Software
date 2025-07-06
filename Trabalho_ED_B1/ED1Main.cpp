#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <WINDOWS.h>
#include "TADFila.h"
#include <time.h>

void Moldura(int CI, int LI, int CF, int LF, int cortexto, int background){
	
	int i;
	
	textcolor(cortexto);
	textbackground(background);
	
	gotoxy(CI,LI); 
	printf("%c",201);		//superior esquerdo
	
	gotoxy(CF,LI);
	printf("%c",187);		//superior direito
	
	gotoxy(CI,LF);			
	printf("%c",200);		//inferior esquerdo
	
	gotoxy(CF,LF);
	printf("%c",188);		//inferior direito
	
	for(i=CI+1; i<CF; i++){		//linhas
		gotoxy(i,LI);
		printf("%c",205);		//linha superior
		gotoxy(i,LF);
		printf("%c",205);		//linha inferior
	}
	
	for(i=LI+1; i<LF; i++){		//colunas
		gotoxy(CI,i);
		printf("%c",186);		//coluna esquerda
		gotoxy(CF,i);
		printf("%c",186);		//coluna direita
	}
	
	textcolor(7);				//retorna ao normal as cores
	textbackground(0);
}

void MolduraMenu(){
	clrscr();		//limpar a tela
	Moldura(1, 1, 119, 30, 3, 0);		//moldura externa - 1 e 3 é azul claro
	Moldura(1, 1, 119, 5, 3, 0);		//moldura dentro acima - 5 e 13 é lilás
//	Moldura(1, 26, 100, 28, 3, 11);			//moldura fora baixo - 15 é branco brilhante ou 3 azul e 11 verde agua claro
}
void MolduraMenu2(){
	//	clrscr();		//limpar a tela
	Moldura(1, 1, 119, 30, 3, 0);		//moldura externa - 1 e 3 é azul claro
	Moldura(1, 1, 119, 5, 3, 0);		//moldura dentro acima - 5 e 13 é lilás
//	Moldura(1, 26, 100, 28, 3, 11);			//moldura fora baixo - 15 é branco brilhante ou 3 azul e 11 verde agua claro
}

void principal(TpIniciar DD)
{
	int i, j,somaC=0,qtdC=0,somaI=0,qtdI=0,somaM=0,qtdM=0,contC=0,contI=0,contM=0;
	char Tipo;
	TpDevs Dev[DD.Devs];
	TpFILA FP;
	TpElemento elem;
	FILE *Ptr = fopen ("Tarefa.csv","r");
	
	inicializar(FP);
	
	//LimpaTela();
	
	MolduraMenu();
	gotoxy(39, 3);
	textcolor(8);
	printf("##### SIMULADOR - GERENCIADOR DE TAREFAS #####");
	for(i=0; i<DD.Devs;i++)
	{
		Dev[i].situacao=0;
		Dev[i].tipo='X';
		Moldura(45, 9, 77, 25, 14, 0);
		gotoxy(50,i+10);
		textcolor(10);
		printf("Dev[%d]: ",i+1);
		textcolor(7);
		printf("Disponivel - ");
		textcolor(14);
		printf("%d ",Dev[i].situacao);
		Sleep(100);
	}
	getch();
	
	MolduraMenu();
	gotoxy(39, 3);
	textcolor(8);
	printf("##### SIMULADOR - GERENCIADOR DE TAREFAS #####");
	for(i=DD.Dias; i>0; i--)
	{		
		srand(time(NULL));
		if(rand() % 10 <= 6) //aumentar número de ler e não ser só 0 e 1
		{
			elem=LerArquivo(Ptr);
			elem.espera=i;
			inserir(FP,elem);
		}
		 
		//LimpaTela();
		Moldura(8, 6, 24, 8, 8, 0);
		gotoxy(9,7);
		textcolor(7);
		printf("Faltam ");
		textcolor(10);
		printf("%d ",i);
		textcolor(7);
		printf("dias");
		gotoxy(100,6);
		printf("[");
		textcolor(12);
		printf("C");
		textcolor(7);
		printf("]");
		printf(" - Critico");
		gotoxy(100,7);
		printf("[");
		textcolor(14);
		printf("I");
		textcolor(7);
		printf("]");
		printf(" - Importante");
		gotoxy(100,8);
		printf("[");
		textcolor(10);
		printf("M");
		textcolor(7);
		printf("]");
		printf(" - Melhoria");
		
		for(j=0; j<DD.Devs; j++)
		{
			if(Dev[j].situacao>0)
				Dev[j].situacao--;
				
			if(Dev[j].situacao==0 && !vazia(FP.FIM))
			{
				gotoxy(26,8);
				elem=retirar(FP); //como um dev vai pegar alguma tarefa, uma tarefa vai sair, então antes de sair salva ela na variável, 
				//para repassar as informações para o vetor de Devs
				Dev[j].situacao=elem.tempo; //é o tempo que a tarefa demora
				Dev[j].espera=elem.espera; //elem.esperar é igual o i = DD.Dias que vai diminuindo 
				Dev[j].tipo=elem.tipo[0]; //Tipo 0 porque o que já começou ser atendido já saiu, e pega 0 que ta sempre no começo
				strcpy (Dev[j].nomeTarefa, elem.tarefa); //tentativa de deixar registrado o nome da tarefa do dev, com o dev
			}
			else
			{
				if(Dev[j].situacao-1==0)
				{
				
					switch(Dev[j].tipo)
					{
						case 'C':
							somaC+=Dev[j].espera-i;
							qtdC++;
							break;
							
						case 'I':
							somaI+=Dev[j].espera-i;
							qtdI++;
							break;
							
						case 'M':
							somaM+=Dev[j].espera-i;
							qtdM++;
							break;
					}
				}
			}
			gotoxy(20,j+12);
			if (Dev[j].situacao == 0)
			{	
				textcolor(7);
				printf("Dev[");
				textcolor(10);
				printf("%d",j+1);
				textcolor(7);
				printf("]");
				textcolor(12);
				printf("\tSem tarefa!");
			}
			else
			{
				textcolor(7);
				printf("Dev[");
				textcolor(10);
				printf("%d",j+1);
				textcolor(7);
				printf("]");
				textcolor(14);
				printf("\tTrab. em: ");
				textcolor(15);
				printf("%s - (",Dev[j].nomeTarefa);
				if(Dev[j].tipo == 'C')
				{
					textcolor(12);
					printf("%c",Dev[j].tipo);
				}
				if(Dev[j].tipo == 'I')
				{
					textcolor(14);
					printf("%c",Dev[j].tipo);
				}
				if(Dev[j].tipo == 'M')
				{
					textcolor(10);
					printf("%c",Dev[j].tipo);
				}
				textcolor(15);
				printf(") - ");
				textcolor(14);
				printf("Faltam: ");
				textcolor(10);
				printf("%d",Dev[j].situacao);
				textcolor(15);
				printf(" dia(s).");
				
			}
		}
		gotoxy(40,7);
		textcolor(9);
		printf("Tarefas na fila:");
		if(vazia(FP.FIM))
		{
			gotoxy(57,7);
			textcolor(7);
			printf("Nao ha tarefas no momento!");
		}
		else
		{
			MolduraMenu2();
			gotoxy(39, 3);
			textcolor(8);
			printf("##### SIMULADOR - GERENCIADOR DE TAREFAS #####");
			exibir(FP);
		}
		getch();
		
		MolduraMenu();
		gotoxy(39, 3);
		textcolor(8);
		printf("##### SIMULADOR - GERENCIADOR DE TAREFAS #####");
		Moldura(8, 6, 24, 8, 8, 0);
		gotoxy(9,7);
		textcolor(7);
		printf("Faltam ");
		textcolor(10);
		printf("%d ",i);
		textcolor(7);
		printf("dias");
		gotoxy(100,6);
		printf("[");
		textcolor(12);
		printf("C");
		textcolor(7);
		printf("]");
		printf(" - Critico");
		gotoxy(100,7);
		printf("[");
		textcolor(14);
		printf("I");
		textcolor(7);
		printf("]");
		printf(" - Importante");
		gotoxy(100,8);
		printf("[");
		textcolor(10);
		printf("M");
		textcolor(7);
		printf("]");
		printf(" - Melhoria");
	}
	//LimpaTela();
	
	MolduraMenu();
	gotoxy(39, 3);
	textcolor(8);
	printf("##### SIMULADOR - GERENCIADOR DE TAREFAS #####");
	//TAREFAS CONCLUIDAS POR TIPO:
	textcolor(15);
	gotoxy(39,10);
	textcolor(7);
	printf("O numero total de tarefas concluidas por tipo");
	Moldura(37, 13, 85, 17, 8, 0);
	if(qtdC>0)
	{
		gotoxy(45,14);
		textcolor(12);
		printf("Criticas");
		textcolor(7);
		printf(": ");
		textcolor(10);
		printf("%d", qtdC);
		textcolor(7);
		printf(" tarefas concluidas.");
	}
	else
	{
		gotoxy(45,14);
		textcolor(12);
		printf("Criticas: nenhuma");
		textcolor(7);
		printf(" foi concluida.");
	}
	if(qtdI>0)
	{
		gotoxy(45,15);
		textcolor(14);
		printf("Importantes");
		textcolor(7);
		printf(": ");
		textcolor(10);
		printf("%d", qtdI);
		textcolor(7);
		printf(" tarefas concluidas.");
		
	}
	else
	{
		gotoxy(45,15);
		textcolor(14);
		printf("Importantes");
		textcolor(7);
		printf(": ");
		textcolor(12);
		printf("nenhuma");
		textcolor(7);
		printf(" foi concluida.");
	}
	if(qtdM>0)
	{
		gotoxy(45,16);
		textcolor(10);
		printf("Melhoria");
		textcolor(7);
		printf(": ");
		textcolor(10);
		printf("%d",qtdM);
		textcolor(7);
		printf(" tarefas concluidas.");
	}
	else
	{
		gotoxy(45,16);
		textcolor(10);
		printf("Melhorias");
		textcolor(7);
		printf(": ");
		textcolor(12);
		printf("nenhuma");
		textcolor(7);
		printf(" foi concluida.");
	}
	
	getch();
	//LimpaTela();
	MolduraMenu();
	gotoxy(39, 3);
	textcolor(8);
	printf("##### SIMULADOR - GERENCIADOR DE TAREFAS #####");
	
	//TEMPO MÉDIO DE ESPERA POR TIPO:
	gotoxy(39,10);
	textcolor(7);
	printf("Tempo medio de espera de cada tipo de Tarefa");
	Moldura(37, 13, 85, 17, 8, 0);
	
	if(qtdC>0)
	{
		gotoxy(45,14);
		textcolor(12);
		printf("Criticas");
		textcolor(7);
		printf(": ");
		textcolor(10);
		printf("%d", (somaC+1)/qtdC);
		textcolor(7);
		printf(" dia(s) de espera.");
	}
	else
	{
		gotoxy(45,14);
		textcolor(12);
		printf("Criticas");
		textcolor(7);
		printf(": sem tempo medio.");
	}
	if(qtdI>0)
	{
		gotoxy(45,15);
		textcolor(14);
		printf("Importantes");
		textcolor(7);
		printf(": ");
		textcolor(10);
		printf("%d", (somaI+1)/qtdI);
		textcolor(7);
		printf(" dia(s) de espera.");
	}
	else
	{
		gotoxy(45,15);
		textcolor(14);
		printf("Importantes");
		textcolor(7);
		printf(": sem tempo medio.");
	}
	if(qtdM>0)
	{
		gotoxy(45,16);
		textcolor(10);
		printf("Melhoria");
		textcolor(7);
		printf(": ");
		textcolor(10);
		printf("%d",(somaM+1)/qtdM);
		textcolor(7);
		printf(" dia(s) de espera.");
	}
	else
	{
		gotoxy(45,16);
		textcolor(10);
		printf("Melhorias");
		textcolor(7);
		printf(": sem tempo medio.");
	}
	
	getch();
	//LimpaTela();

	//NÚMERO DE TAREFAS QUE NÃO FORAM CONCLUÍDAS:
	for (int i=0; i<=FP.FIM;i++)
	{
		elem=retirar(FP);
		switch(elem.tipo[i])
		{
			case 'C':
				contC++;
				break;
							
			case 'I':
				contI++;
				break;
							
			case 'M':
				contM++;
				break;
		}
	}

//ACRESCENTEI ISSO AQUI
	for (int i=0; i<DD.Devs; i++)
	{
		if(Dev[i].situacao>0)
			switch(Dev[i].tipo)
			{
				case 'C':
					contC++;
					break;
								
				case 'I':
					contI++;
					break;
								
				case 'M':
					contM++;
					break;
			}
	}

	MolduraMenu();
	gotoxy(39, 3);
	textcolor(8);
	printf("##### SIMULADOR - GERENCIADOR DE TAREFAS #####");
	
	gotoxy(39,10);
	textcolor(7);
	printf("O numero total de tarefas NAO concluidas por tipo");
	Moldura(37, 13, 90, 17, 8, 0);
	gotoxy(40,14);
	textcolor(12);
	printf("Criticas");
	textcolor(7);
	printf(": ");
	textcolor(10);
	printf("%d ", contC);
	textcolor(7);
	printf("tarefas nao concluidas.");
	
	gotoxy(40,15);
	textcolor(14);
	printf("Importantes");
	textcolor(7);
	printf(": ");
	textcolor(10);
	printf("%d ", contI);
	textcolor(7);
	printf("tarefas nao concluidas.");
	
	gotoxy(40,16);
	textcolor(10);
	printf("Melhoria");
	textcolor(7);
	printf(": ");
	textcolor(10);
	printf("%d ", contM);
	textcolor(7);
	printf("tarefas nao concluidas.");
	
	
	Moldura(37, 19, 90, 21, 9, 0);
	gotoxy(48,20);
	textcolor(3);
	printf("TOTAL");
	textcolor(7);
	printf(": ");
	textcolor(12);
	printf("%d ", contC+contI+contM);
	textcolor(7);
	printf("tarefas nao concluidas.");
	
	getch();
}

TpIniciar Iniciar(void)
{
	TpIniciar reg;
	
	//LimpaTela();
	//MolduraMenu();
	//gotoxy(39, 3);
	//textcolor(8);
	//printf("##### SIMULADOR - GERENCIADOR DE TAREFAS #####");
	do
	{
		MolduraMenu();
		gotoxy(39, 3);
		textcolor(8);
		printf("##### SIMULADOR - GERENCIADOR DE TAREFAS #####");
		gotoxy(45,10);
		textcolor(15);
		printf("Digite a quantidade de ");
		textcolor(10);
		printf("DEV's: ");
		textcolor(14);
		scanf("%d",&reg.Devs);
		if(reg.Devs>MAXDEVS)
		{
			clrscr();
			Moldura(44, 12, 77, 14, 12, 0);
			textcolor(12);
			gotoxy(46, 13);
			printf("Erro: ");
			textcolor(7);
			printf("Existem apenas 15 Dev's!");
			getch();
		
			//gotoxy(9, 9);
			//printf("                     ");
			//gotoxy(9, 10);
			//printf("                         ");
		}
	}while(reg.Devs>MAXDEVS);
	do{
		textcolor(15);
		gotoxy(39, 12);
		printf("Digite quantos dias ficara rodando as tarefas: ");
		textcolor(14);
		scanf("%d",&reg.Dias);
	}while(reg.Dias>=9999);
	
	
	return reg;
}

void Menu(void){
	char op;
	TpIniciar reg;
	
	gotoxy(48,10);
	textcolor(15);
	printf("TRABALHO ED I ");
	textcolor(8);
	printf("[BIMESTRE 1]");
	Moldura(1, 1, 119, 30, 3, 0);
	Moldura(30, 12, 90, 20, 8, 0);
	
	gotoxy(37,14);
	textcolor(7);
	printf("Caio dos Santos Silva Furlan - ");
	textcolor(15);
	printf("RA: ");
	textcolor(9);
	printf("00262412705");
	
	gotoxy(37,16);
	textcolor(7);
	printf("Lais La Casa Sitolino - ");
	textcolor(15);
	printf("RA: ");
	textcolor(9);
	printf("00262411717");
	
	gotoxy(37,18);
	textcolor(7);
	printf("Guilherme Sales Pereira- ");
	textcolor(15);
	printf("RA: ");
	textcolor(9);
	printf("00262411873");
	
	getch();
	
	do{	
		//LimpaTela();
		//LimpaTitulo();
		MolduraMenu();
		// MUDEI AQUI O 30 PRA 28
		gotoxy(39, 3);
		printf("##### SIMULADOR - GERENCIADOR DE TAREFAS #####");
		gotoxy(58, 10);
		printf("MENU");
		gotoxy(51, 13);
		printf("[ENTER] ");
		textcolor(10);
		gotoxy(62, 13);
		printf("CONTINUAR");
		gotoxy(52, 15);
		textcolor(15);
		printf("[ESC] ");
		textcolor(4);
		gotoxy(62, 15);
		printf("SAIR");
		gotoxy(53, 18);
		textcolor(14);
		printf("Tecle a Opcao: ");
		fflush(stdin);
		op=toupper(getch());
		if(op!=27)
		{
			reg=Iniciar();
			principal(reg);
		}
	}while(op!=27);
}

int main(void){
	
	Menu();
	
	return 0;
}
