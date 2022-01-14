#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

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
struct m {
	mMobilidade itemMM;
	struct m *prox;
};
typedef struct m tcelulaM;
//-------------------------------------------------------
struct p {
	pUtilizacao itemPU;
	struct p *prox;
};
typedef struct p tcelulaP;
//#####################################################################################################
//#####################################################################################################
void iniM(mMobilidade *meio) {
	strcpy((*meio).codigo,"--");
	strcpy((*meio).tipoMM,"--");
	(*meio).custo=0;
	(*meio).autonomia=0;
}
//#####################################################################################################
void iniP(pUtilizacao *pedido) {
	(*pedido).ordem=0;
	(*pedido).nif=0;
	strcpy((*pedido).codTipoMM,"--");
	(*pedido).tempo=0;
	(*pedido).distancia=0;
}
//#####################################################################################################
void lerM(mMobilidade *m,int quantM) {
    char input[100];
    int nineDigitString = 0;
	char *endptr_f, *endptr_i;

	snprintf((*m).codigo,sizeof((*m).codigo),"M_%d",quantM);
    printf("Diga o tipo do meio de mobilidade que pertende adicionar: ");
	if(fgets((*m).tipoMM, sizeof((*m).tipoMM), stdin)) {
		(*m).tipoMM[strcspn((*m).tipoMM, "\n")] = 0;	
	}

    printf("Diga o custo: ");
	fgets (input, sizeof(input), stdin);
	(*m).custo = strtof(input, NULL);

    printf("Diga a autonomia: ");
	fgets(input, sizeof(input), stdin);
	(*m).autonomia = strtol(input, NULL, 0);
}
//#####################################################################################################
void lerP(pUtilizacao *p, int quantP, tcelulaM **m) {
	tcelulaM *aux;
    char input[100];
    int nineDigitString, success = 0;
	char *endptr_f, *endptr_i;

    (*p).ordem = quantP;

    do {
    	printf("NIF: ");
    	fgets(input, sizeof(input), stdin);
    	nineDigitString = sscanf(input, "%d", &(*p).nif);
		if(nineDigitString != 1){
        	printf("Numero de NIF invalido, apenas sao aceites numeros.\n");
		}
		else if (( (*p).nif < 100000000 ) || ( (*p).nif > 999999999 )) {
        	printf("Numero de NIF invalido, Nif tem que possuir 9 digitos.\n");
		}
		else {
			success = 1;
		}
	}while(!success);

	do {
		aux = (*m);
		printf("Diga o codigo do tipo de meio de mobilidade: ");
		if(fgets((*p).codTipoMM, sizeof((*p).codTipoMM), stdin)) {
			(*p).codTipoMM[strcspn((*p).codTipoMM, "\n")] = 0;
		}
	
		while((*aux).prox != NULL) {
			if(strcmp((*p).codTipoMM,(*aux).itemMM.codigo)==0) {
				success = 1;
				break;
			}
			else {
				aux=(*aux).prox;
				success = 0;
			}
		}
		if(success == 0) {
			printf("\nO codigo inserido (%s) nao estava presente na lista\n\n",(*p).codTipoMM);
		}
	}while(success!=1);

    printf("Diga o tempo: ");
	fgets(input, sizeof(input), stdin);
	(*p).tempo = strtol(input, NULL, 0);
	/*if (*endptr_f != '\n' || input[0] == '\n' || endptr_f == input)	{
		printf("ERROR: \"%s\" is an invalid float!\n", input);
	}*/

    printf("Diga a distancia: ");
	fgets(input, sizeof(input), stdin);
	(*p).distancia = strtol(input, NULL, 0);
	/*if (*endptr_f != '\n' || input[0] == '\n' || endptr_f == input)	{
		printf("ERROR: \"%s\" is an invalid float!\n", input);
	}*/
}
//#####################################################################################################
void imprimirM(mMobilidade m) {
	printf("\n\nCodigo-(%s)\nTipoMM-(%s)\nCusto-(%.2f)\nAutonomia-(%d)\n",m.codigo,m.tipoMM,m.custo,m.autonomia);
}
//#####################################################################################################
void imprimirP(pUtilizacao p) {
	printf("\n\nN de Ordem-(%d)\nNif-(%d)\nCod TipoMM-(%s)\nTempo-(%d)\nDistancia-(%d)\n",p.ordem,p.nif,p.codTipoMM,p.tempo,p.distancia);
}
//#####################################################################################################
void putInFileM(mMobilidade m, FILE *f_MM) {
	fprintf(f_MM,"%-12s%-15s%-15.2f%d\n",m.codigo,m.tipoMM,m.custo,m.autonomia);
}
//#####################################################################################################
void putInFileP(pUtilizacao p, FILE *f_PU) {
	fprintf(f_PU,"%-14d%-15d%-13s%-11d%d\n",p.ordem,p.nif,p.codTipoMM,p.tempo,p.distancia);
}
//#####################################################################################################
tcelulaM *inicializarM() {
	tcelulaM * ap;
	ap = (tcelulaM *) malloc( sizeof(tcelulaM));
	
	if(ap==NULL) {
		system("cls");
		printf("E impossivel criar a lista\n\n");
		system("pause");
		return(NULL);
	}
	else {
		iniM(&(*ap).itemMM);
		(*ap).prox=NULL;
		return(ap);
	}
}
//#####################################################################################################
tcelulaP *inicializarP() {
	tcelulaP * ap;
	ap = (tcelulaP *) malloc( sizeof(tcelulaP));
	
	if(ap==NULL) {
		system("cls");
		printf("E impossivel criar a lista\n\n");
		system("pause");
		return(NULL);
	}
	else {
		iniP(&(*ap).itemPU);
		(*ap).prox=NULL;
		return(ap);
	}
}
//#####################################################################################################
void inserirMeioMobilidade(tcelulaM *m, int *sizeM, int quantM) {
    tcelulaM *ap;
	mMobilidade aux;
	ap=(tcelulaM *)malloc(sizeof(tcelulaM));
	
	system("cls");
	if(ap==NULL) { 
		printf("Nao existe mais espaço em memoria. E impossivel inserir\n\n");
		system("pause");
	}
	else {
        inicializarM(&(*ap).itemMM);
        (*ap).prox=NULL;
		
		system("cls");
		lerM(&aux,quantM);
        (*sizeM)++;
		while((*m).prox!=NULL){
			m=(*m).prox;
		}
		(*m).itemMM=aux;
		(*m).prox=ap;
	}
}
//#####################################################################################################
void inserirPedidoUtilizacao(tcelulaP *p, int *sizeP, int quantP,tcelulaM **m) {
    tcelulaP *ap;
	pUtilizacao aux;
	ap=(tcelulaP *)malloc(sizeof(tcelulaP));
	
	system("cls");
	if(ap==NULL) { 
		printf("Nao existe mais espaço em memoria. E impossivel inserir\n\n");
		system("pause");
	}
	else {
        inicializarP(&(*ap).itemPU);
        (*ap).prox=NULL;
		
		system("cls");
		lerP(&aux,quantP,m);
        (*sizeP)++;
		while((*p).prox!=NULL){
			p=(*p).prox;
		}
		(*p).itemPU=aux;
		(*p).prox=ap;
	}
}
//#####################################################################################################
void listarMeioMobilidade(tcelulaM *m, int sizeM) {
	int flag = 1;

	system("cls");
	puts("Dados disponiveis: ");
	if((*m).prox==NULL)	{
		puts("Nenhum");
	}
	else {
        printf("A lista de pedidos de utilizacao contem %d pedidos",sizeM);
		while((*m).prox != NULL) {
			imprimirM((*m).itemMM);
			m=(*m).prox;
		}
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
void listarPedidoUtilizacao(tcelulaP *p, int sizeP) {
	system("cls");
	puts("Dados disponiveis: ");
	if((*p).prox==NULL) {
		puts("Nenhum");
	}
	else {
        printf("A lista de pedidos de utilizacao contem %d pedidos",sizeP);
		while((*p).prox != NULL) {
			imprimirP((*p).itemPU);
			p=(*p).prox;
		}
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
void removerMeioMobilidade(tcelulaM **m, int *sizeM) {
	tcelulaM *y, *atras, *frente, *aux;
	char elemRetirar[40];
	
	system ("cls");
	y=(*m);
	
	if(((*y).prox)==NULL) { 
		printf("A lista nao tem dados"); 
	}
	else {
		printf("Diga o codigo cujo meio de mobilidade quer retirar?\n");
		if(fgets(elemRetirar, sizeof(elemRetirar), stdin)) {
			elemRetirar[strcspn(elemRetirar, "\n")] = 0;	
		}
		
		if(strcmp(elemRetirar,(*(*m)).itemMM.codigo)==0) {
			system ("cls");
			printf("O elemento foi retirado\n");
			imprimirM((*(*m)).itemMM);
			(*m)=(*(*m)).prox;
            (*sizeM)--;
			free(y);
		}
		else {
			aux=(*m);
			while((strcmp(elemRetirar,(*aux).itemMM.codigo)!=0) && ((*(*aux).prox).prox!=NULL)) {
				atras=aux;
				aux=(*aux).prox;
				frente=(*aux).prox;
			}
			
			if(strcmp(elemRetirar,(*aux).itemMM.codigo)==0) {
				(*atras).prox=frente;
				printf("O elemento foi retirado\n");
				imprimirM((*aux).itemMM);
                (*sizeM)--;
				free(aux);
			}
			else {
				system("cls"); 
				printf("O elemento com o codigo %s nao existe na lista", elemRetirar);
			}
		}
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
void removerPedidoUtilizacao(tcelulaP **p, int *sizeP) {
	tcelulaP *y, *atras, *frente, *aux;
	char elemRetirar[40];
	int intElemRetirar;
	
	system ("cls");
	y=(*p);
	
	if(((*y).prox)==NULL) { 
		printf("A lista nao tem dados"); 
	}
	else {
		printf("Diga o codigo cujo meio de mobilidade quer retirar?\n");
		if(fgets(elemRetirar, sizeof(elemRetirar), stdin)) {
			elemRetirar[strcspn(elemRetirar, "\n")] = 0;
			intElemRetirar = strtol(elemRetirar, NULL, 0);
		}
		
		if(intElemRetirar == (*(*p)).itemPU.ordem) {
			system("cls");
			printf("O elemento foi retirado\n");
			imprimirP((*(*p)).itemPU);
			(*p)=(*(*p)).prox;
            (*sizeP)--;
			free(y);
		}
		else {
			aux=(*p);
			while((intElemRetirar == (*(*p)).itemPU.ordem) && ((*(*aux).prox).prox!=NULL)) {
				atras=aux;
				aux=(*aux).prox;
				frente=(*aux).prox;
			}
			
			if(intElemRetirar == (*(*p)).itemPU.ordem) {
				(*atras).prox=frente;
				printf("O elemento foi retirado\n");
				imprimirP((*aux).itemPU);
                (*sizeP)--;
				free(aux);
			}
			else {
				system("cls"); 
				printf("O elemento com o codigo %s nao existe na lista", elemRetirar);
			}
		}
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
//#####################################################################################################
void armazenarNosFicheiros(tcelulaM *m, tcelulaP *p) {
	FILE *f_MM;
	FILE *f_PU;

	f_MM=fopen("MeioDeMobilidade.txt","w");// (a) se for para ler o conteudo e carregar numa string
	f_PU=fopen("PedidosDeUtilizacao.txt","w");// (a) se for para ler o conteudo e carregar numa string

	fprintf(f_MM,"%-12s%-15s%-15s%s\n","Codigo","Tipo","Custo","Autonomia");
	fprintf(f_PU,"%-29s%s\n%-14s%-15s%-13s%-11s%s\n","Numero de","Codigo","Ordem","NIF","Tipo MM","Tempo","Distancia");
	/*fseek(f_MM, 0, SEEK_END);
	size = ftell(f_MM);
	if (0 == size)*/

    if((f_MM != NULL) && (f_PU != NULL)) {
		if((*m).prox==NULL) {
			puts("Nenhum dado para colocar na lista de (Meios de Mobilidade)");
		}
		else {
			while((*m).prox != NULL) {
				putInFileM((*m).itemMM,f_MM);
				m=(*m).prox;
			}
			printf("Lista de (Meios de Mobilidade) foi carregada no ficheiro (MeioDeMobilade.txt) com sucesso!!\n");
		}

		if((*p).prox==NULL) {
			puts("Nenhum dado para colocar na lista de (Pedidos de Utilizacao)");
		}
		else {
			while((*p).prox != NULL) {
				putInFileP((*p).itemPU,f_PU);
				p=(*p).prox;
			}
			printf("Lista de (Pedidos de Utilizacao) foi carregada no ficheiro (PedidosDeUtilizacao.txt) com sucesso!!\n\n");
		}
	}

    fclose(f_MM);
    fclose(f_PU);
}
//#####################################################################################################
//#####################################################################################################
main() {
    int opcao, success, listSizeM = 0, listSizeP = 0, quantM = 1, quantP = 1;
	char buf[1024];
	tcelulaM *listaM;
	tcelulaP *listaP;

    listaM=inicializarM();
    listaP=inicializarP();
    do {
        do {
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
                   "-------------------------------------------------------------------------------------------------------------- \n"
                   "Opcao: ");
				if (!fgets(buf, sizeof(buf), stdin)) {
					// reading input failed:
					return 1;
				}
				char *endptr;
				errno = 0; // reset error number
				opcao = strtol(buf, &endptr, 10);
				if (errno == ERANGE) {
					printf("Desculpe, o numero inserido e muito grande ou demasiado pequeno.\n\n");
					system("pause");
					success = 0;
				}
				else if ((opcao > 9) || (opcao < 0)) {
					printf("Por favor insira um numero entre 0 e 9.\n\n");
					system("pause");
					success = 0;
				}
				else if (endptr == buf)	{
					// no character was read.
					success = 0;
				}
				else if ((*endptr) && (*endptr != '\n')) {
					// *endptr is neither end of string nor newline,
					// so we didn't convert the *whole* input.
					success = 0;
				}
				else {
					success = 1;
				}
        }while(!success);

        switch(opcao) {
            case 0: printf("Goodbye!!\n\n"); 
			break;
            case 1: inserirMeioMobilidade(listaM,&listSizeM,quantM); 
					quantM++; 
					break;
            case 2: listarMeioMobilidade(listaM,listSizeM); 
					break;
            case 3: removerMeioMobilidade(&listaM,&listSizeM); 
					break;
            case 4: 
					if(listSizeM>0) {
						inserirPedidoUtilizacao(listaP,&listSizeP,quantP,&listaM); 
						quantP++; 
					}
					else {
						printf("Nao existe nenhum meio de mobilidade disponivel para fazer o pedido");
						system("pause");
					}
					break;
            case 5: listarPedidoUtilizacao(listaP,listSizeP);
					break;
            case 6: removerPedidoUtilizacao(&listaP,&listSizeP); 
					break;
            /*case 7: calcularCustoMobilidade();
            		break;
            case 8: distribuirMeiosMobilidade();
            		break;
            case 9: listagemUtilizacaoMeioMobilidade();
            		break;*/
        }
    }while(opcao != 0);

	armazenarNosFicheiros(listaM,listaP);
    free(listaM);
    free(listaP);

    return(0);
}