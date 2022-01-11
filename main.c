#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//-------------------------------------------------------
typedef struct {
	char codigo[50];
	char tipoMM[50];
	float custo;
	int autonomia;
}mMobilidade;
//-------------------------------------------------------
typedef struct {
    int ordem;
    int nif;
	char codTipoMM[50];
    int tempo;
    int distancia;
}pUtilizacao;
//-------------------------------------------------------
struct m
{
	mMobilidade itemMM;
	struct m *prox;
};
typedef struct m tcelulaM;
//-------------------------------------------------------
struct p
{
	pUtilizacao itemPU;
	struct p *prox;
};
typedef struct p tcelulaP;
//#####################################################################################################
//#####################################################################################################
int yes_no() {
    char option;

    while (1) {
        printf("(Y - y/N - n): ");
        if (scanf(" %c", &option) != 1) {
            printf("Error occurred while reading option.\n");
            continue;
        }

        if (option == 'y' || option == 'Y') {
            return 1;
        } else if (option == 'n' || option == 'N') {
            return 0;
        } else {
            printf("Only (y)es or (n)o are acceptable.\n");
        }
    }
}
//#####################################################################################################
void iniM(mMobilidade *meio)
{
	strcpy((*meio).codigo,"--");
	strcpy((*meio).tipoMM,"--");
	(*meio).custo=0;
	(*meio).autonomia=0;
}
//#####################################################################################################
void iniP(pUtilizacao *pedido)
{
	(*pedido).ordem=0;
	(*pedido).nif=0;
	strcpy((*pedido).codTipoMM,"--");
	(*pedido).tempo=0;
	(*pedido).distancia=0;
}
//#####################################################################################################
void lerM(mMobilidade *m){
    printf("Diga o codigo do meio de mobilidade que pertende adicionar: ");
    fflush(stdin);				
    gets((*m).codigo);
    printf("Diga o tipo do meio de mobilidade que pertende adicionar: ");
    fflush(stdin);				
    gets((*m).tipoMM);
    printf("Diga o custo: ");
    scanf("%f",&(*m).custo);
    printf("Diga a autonomia: ");
    scanf("%d",&(*m).autonomia);
}
//#####################################################################################################
void lerP(pUtilizacao *p){
    printf("Diga o n de ordem: ");
    scanf("%d",&(*p).ordem);
    printf("Diga o nif: ");
    scanf("%d",&(*p).nif);
    printf("Diga o codigo do tipo de meio de mobilidade: ");
    fflush(stdin);				
    gets((*p).codTipoMM);
    printf("Diga o tempo: ");
    scanf("%d",&(*p).tempo);
    printf("Diga a distancia: ");
    scanf("%d",&(*p).distancia);
}
//#####################################################################################################
void imprimirM(mMobilidade m)
{
	printf("\n\nCodigo-(%s)\nTipoMM-(%s)\nCusto-(%.2f)\nAutonomia-(%d)\n",m.codigo,m.tipoMM,m.custo,m.autonomia);
}
//#####################################################################################################
void imprimirP(pUtilizacao p)
{
	printf("\n\nN de Ordem-(%d)\nNif-(%d)\nCod TipoMM-(%s)\nTempo-(%d)\nDistancia-(%d)\n",p.ordem,p.nif,p.codTipoMM,p.tempo,p.distancia);
}
//#####################################################################################################
tcelulaM *inicializarM(){
	tcelulaM * ap;
	ap = (tcelulaM *) malloc( sizeof(tcelulaM));
	
	if(ap==NULL)
	{
		system("cls");
		printf("E impossivel criar a lista");
		getch();
		return(NULL);
	}
	else
	{
		iniM(&(*ap).itemMM);
		(*ap).prox=NULL;
		return(ap);
	}
}
//#####################################################################################################
tcelulaP *inicializarP(){
	tcelulaP * ap;
	ap = (tcelulaP *) malloc( sizeof(tcelulaP));
	
	if(ap==NULL)
	{
		system("cls");
		printf("E impossivel criar a lista");
		getch();
		return(NULL);
	}
	else
	{
		iniP(&(*ap).itemPU);
		(*ap).prox=NULL;
		return(ap);
	}
}
//#####################################################################################################
void inserirMeioMobilidade(tcelulaM *m, int *sizeM){
    tcelulaM * ap;
	mMobilidade aux;
	ap=(tcelulaM *)malloc(sizeof(tcelulaM));
	
	system("cls");
	if(ap==NULL)
	{ 
		printf("Nao existe mais espaço em memoria. E impossivel inserir");
		getch();
	}
	else
	{
        inicializarM(&(*ap).itemMM);
        (*ap).prox=NULL;
		
		system("cls");
		lerM(&aux);
        (*sizeM)++;
		while((*m).prox!=NULL){
			m=(*m).prox;
		}
		(*m).itemMM=aux;
		(*m).prox=ap;
	}
}
//#####################################################################################################
void inserirPedidoUtilizacao(tcelulaP *p, int *sizeP){
    tcelulaP * ap;
	pUtilizacao aux;
	ap=(tcelulaP *)malloc(sizeof(tcelulaP));
	
	system("cls");
	if(ap==NULL)
	{ 
		printf("Nao existe mais espaço em memoria. E impossivel inserir");
		getch();
	}
	else
	{
        inicializarP(&(*ap).itemPU);
        (*ap).prox=NULL;
		
		system("cls");
		lerP(&aux);
        (*sizeP)++;
		while((*p).prox!=NULL){
			p=(*p).prox;
		}
		(*p).itemPU=aux;
		(*p).prox=ap;
	}
}
//#####################################################################################################
void listarMeioMobilidade(tcelulaM * m, int sizeM)
{
	system("cls");
	puts("Dados disponiveis: ");
	if((*m).prox==NULL)
	{
		puts("Nenhum");
	}
	else
	{
        printf("A lista de pedidos de utilizacao contem %d pedidos",sizeM);
		while((*m).prox != NULL)
		{
			imprimirM((*m).itemMM);
			m=(*m).prox;
		}
	}
	getch();
}
//#####################################################################################################
void listarPedidoUtilizacao(tcelulaP * p, int sizeP)
{
	system("cls");
	puts("Dados disponiveis: ");
	if((*p).prox==NULL)
	{
		puts("Nenhum");
	}
	else
	{
        printf("A lista de pedidos de utilizacao contem %d pedidos",sizeP);
		while((*p).prox != NULL)
		{
			imprimirP((*p).itemPU);
			p=(*p).prox;
		}
	}
	getch();
}
//#####################################################################################################
void removerMeioMobilidade(tcelulaM **m, int *sizeM)
{
	tcelulaM *y, *atras, *frente, *aux;
	char elemRetirar[30];
	
	system ("cls");
	y=(*m);
	
	if(((*y).prox)==NULL)
	{ 
		printf("A lista nao tem dados"); 
	}
	else
	{
		printf("Diga o codigo cujo meio de mobilidade quer retirar?\n");
		fflush(stdin);
		gets(elemRetirar);
		strupr(elemRetirar);
		
		if(strcmp(elemRetirar,(*(*m)).itemMM.codigo)==0)
		{
			system ("cls");
			printf("O elemento foi retirado\n");
			imprimirM((*(*m)).itemMM);
			(*m)=(*(*m)).prox;
            (*sizeM)--;
			free(y);
		}
		else
		{
			aux=(*m);
			while ((strcmp(elemRetirar,(*aux).itemMM.codigo)!=0) && ((*(*aux).prox).prox!=NULL))
			{
				atras=aux;
				aux=(*aux).prox;
				frente=(*aux).prox;
			}
			
			if (strcmp(elemRetirar,(*aux).itemMM.codigo)==0)
			{
				(*atras).prox=frente;
				printf("O elemento foi retirado\n");
				imprimirM((*aux).itemMM);
                (*sizeM)--;
				free(aux);
			}
			else
			{
				system("cls"); 
				printf("O elemento com o codigo %s nao existe na lista", elemRetirar);
			}
		}
	}
	getch();
}
//#####################################################################################################
void removerPedidoUtilizacao(tcelulaP **p, int *sizeP)
{
	tcelulaP *y, *atras, *frente, *aux;
	char elemRetirar[30];
	
	system ("cls");
	y=(*p);
	
	if(((*y).prox)==NULL)
	{ 
		printf("A lista nao tem dados"); 
	}
	else
	{
		printf("Diga o codigo cujo meio de mobilidade quer retirar?\n");
		fflush(stdin);
		gets(elemRetirar);
		strupr(elemRetirar);
		
		if(strcmp(elemRetirar,(*(*p)).itemPU.ordem)==0)
		{
			system ("cls");
			printf("O elemento foi retirado\n");
			imprimirP((*(*p)).itemPU);
			(*p)=(*(*p)).prox;
            (*sizeP)--;
			free(y);
		}
		else
		{
			aux=(*p);
			while ((strcmp(elemRetirar,(*aux).itemPU.ordem)!=0) && ((*(*aux).prox).prox!=NULL))
			{
				atras=aux;
				aux=(*aux).prox;
				frente=(*aux).prox;
			}
			
			if (strcmp(elemRetirar,(*aux).itemPU.ordem)==0)
			{
				(*atras).prox=frente;
				printf("O elemento foi retirado\n");
				imprimirP((*aux).itemPU);
                (*sizeP)--;
				free(aux);
			}
			else
			{
				system("cls"); 
				printf("O elemento com o codigo %s nao existe na lista", elemRetirar);
			}
		}
	}
	getch();
}
//#####################################################################################################
//#####################################################################################################
main() {
    int opcao, listSizeM = 0, listSizeP = 0;
	tcelulaM *listaM;
	tcelulaP *listaP;
    //int size,ctn,ctgMM=0,ctgPU=0;

    listaM=inicializarM();
    listaP=inicializarP();
    do{
        do
        {
            system("cls");
            printf("-------------------------------------------------------------------------------------------------------------- \n"
                   "|                                               MENU                                                         | \n"
                   "|   0 - Leave                                                                                                | \n"
                   "|   1 - Inserir Meio de Mobilidade                     4 - Inserir Pedido de Utilizacao                      | \n"
                   "|   2 - Listagem de todos os Meios de mobilidade       5 - Listagem de todos os Pedidos de utilizacao        | \n"
                   "|   3 - Remover Meio de mobilidade                     6 - Remover Pedidos de Utilizacao                     | \n"
                   "|____________________________________________________________________________________________________________| \n"
                   "|                                                                                                            | \n"
                   "|   7 - Calculo do custo de utilizacao                                                                       | \n"
                   "|   8 - Distribuir meios de mobilidade                 9 - Listagem de utilizacao de um meio de mobilidade   | \n"
                   "|   10 - Armazenar pedidos de utilizacao               11 - Armazenar meios de mobilidade                    | \n"
                   "-------------------------------------------------------------------------------------------------------------- \n"
                   "Opcao: ");
            scanf("%d",&opcao);
        } while ((opcao>11)||(opcao<0));


        switch (opcao)
        {
            case 0: printf("Xau"); break;
            case 1: inserirMeioMobilidade(listaM,&listSizeM); break;
            case 2: listarMeioMobilidade(listaM,listSizeM); break;
            case 3: removerMeioMobilidade(&listaM,&listSizeM); break;
            case 4: inserirPedidoUtilizacao(listaP,&listSizeP); break;
            case 5: listarPedidoUtilizacao(listaP,listSizeP); break;
            case 6: removerPedidoUtilizacao(&listaP,&listSizeP); break;
            /*case 7: calcularCustoMobilidade();
            break;
            case 8: distribuirMeiosMobilidade();
            break;
            case 9: listagemUtilizacaoMeioMobilidade();
            break;
            case 10: armazenarPedidosUtilizacao();
            break;
            case 11: armazenarMeiosMobilidade();
            break;*/
        }
    } while (opcao != 0);

    return(0);
}
/*    FILE *f_MM;
    f_MM=fopen("MeioDeMobilidade.txt","a+");

    if (NULL != f_MM) {
        fseek (f_MM, 0, SEEK_END);
        size = ftell(f_MM);

        if (0 == size) {
            fprintf(f_MM, "Codigo       Tipo        Custo       Autonomia\n");
        }
		
        fprintf(f_MM, "%s       %s      %s      %s\n", mm[0], mm[1], mm[2], mm[3]);
    }

    fclose(f_MM);*/