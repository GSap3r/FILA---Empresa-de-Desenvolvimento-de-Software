#define MAXFILA 30
#define MAXDEVS 10

struct TpElemento{
	char tipo[12];
	int tempo;
	char tarefa[50];
	char resp[20];
	char data[12];
	int espera;
};

struct TpFILA{
	TpElemento FILA[MAXFILA];
	int FIM;
};

struct TpIniciar{
	int Devs, Dias;
};

struct TpDevs{
	int situacao, espera;
	char tipo, nomeTarefa[50];
};

//Protótipos das Operações Associadas
void inicializar(TpFILA &FP);
void inserir(TpFILA &FP, TpElemento Elem);
TpElemento retirar(TpFILA &FP);
int cheia(int fim);
int vazia(int fim);
void exibir(TpFILA FP);

TpElemento LerArquivo(FILE *Ptr);

void LimpaTitulo(void);
void LimpaTela(void);

//Operações Associadas FILA
void inicializar(TpFILA &FP)
{
	FP.FIM=-1;
}

void inserir(TpFILA &FP, TpElemento Elem)
{
	if(!cheia(FP.FIM)){
	
		FP.FILA[++FP.FIM]=Elem;
		int i=FP.FIM;
		while(i>0 && strcmp(FP.FILA[i-1].tipo, FP.FILA[i].tipo)>0)
		{
			FP.FILA[i]=FP.FILA[i-1];
			FP.FILA[i-1]=Elem;
			i--;
		}
	}else
		printf("Esta cheio!");
}

TpElemento retirar(TpFILA &FP)
{
	TpElemento elem;
	elem=FP.FILA[0];
	for(int i=0; i<FP.FIM;i++)
		FP.FILA[i]=FP.FILA[i+1];
	FP.FIM--;
	return elem;
}

int cheia(int fim)
{
	return fim==MAXFILA-1;
}
 
int vazia(int fim)
{
	return fim==-1;
}

void exibir(TpFILA FP)
{	
	int O = 0;
	TpElemento elem;
	while(!vazia(FP.FIM))
	{
		gotoxy(50,22);
		elem=retirar(FP);
		textcolor(7);
		printf("Tarefas na fila:");
		gotoxy(20,23+O);
		textcolor(3);
		printf("%s",elem.tipo);
		textcolor(15);
		printf(" | ");
		textcolor(12);
		printf("%d",elem.tempo);
		textcolor(15);
		printf(" | ");
		textcolor(8);
		printf("%s",elem.tarefa);
		textcolor(15);
		printf(" | ");
		textcolor(14);
		printf("%s",elem.resp);
		textcolor(15);
		printf(" | ");
		textcolor(10);
		printf("%s",elem.data);
		
		
		O++;
		if(O>6 && !vazia(FP.FIM)){
			getch();
			LimpaTela();
			O=0;
		}
	}
	//printf("\n");
}
 
//Operações Associadas ARQUIVO

TpElemento LerArquivo(FILE *Ptr)
{
	TpElemento reg;
	fscanf(Ptr,"%[^,],%d,%[^,],%[^,],%[^\n]\n",&reg.tipo,&reg.tempo,&reg.tarefa, &reg.resp, &reg.data);
	return reg;
}

void LimpaTela(void){
	int x1 = 7, x2 = 118, y1 = 6, y2 = 30, i, j;
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++){
			gotoxy(i,j);
			printf(" ");
		}
}

void LimpaTitulo(void){
	int i;
	for(i=3; i<99; i++){
		gotoxy(i,3);
		printf(" ");
	}
}




