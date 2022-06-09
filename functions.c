/**
 * @file functions.c
 * @author João Penedos
 * @brief
 * @version 1.1
 * 
 * @copyright Copyright (c) 2022 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

#include "header.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif


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
void lerM(mMobilidade *m, int lastCodM) {
    char input[100];

	snprintf((*m).codigo,sizeof((*m).codigo),"M_%d",lastCodM);

	while(1) {
		printf("Diga o tipo do meio de mobilidade que pertende adicionar\n");
		printf("Tipos aceites (Trotinete, Bicicleta, Carro, Carrinha): ");
		if(fgets((*m).tipoMM, sizeof((*m).tipoMM), stdin)) {
			(*m).tipoMM[strcspn((*m).tipoMM, "\n")] = 0;
			if((strcmp(strlwr((*m).tipoMM),"trotinete")==0) || 
			   (strcmp(strlwr((*m).tipoMM),"bicicleta")==0) || 
			   (strcmp(strlwr((*m).tipoMM),"carrinha")==0) ||
			   (strcmp(strlwr((*m).tipoMM),"carro")==0)) {
				break;
			}
		}
		printf("Tipos inserido (%s) nao e compativel com os tipos aceites (Trotinete, Bicicleta, Carro, Carrinha)\n",strlwr((*m).tipoMM));
	}

    printf("Diga o custo: ");
	fgets(input, sizeof(input), stdin);
	(*m).custo = strtof(input, NULL);

    printf("Diga a autonomia: ");
	fgets(input, sizeof(input), stdin);
	(*m).autonomia = strtol(input, NULL, 0);
}
//#####################################################################################################
void lerP(pUtilizacao *p, int lastCodP, tcelulaM **m) {
	tcelulaM *aux;
    char input[100];
    int nineDigitString, success = 0;

    (*p).ordem = lastCodP;

    do {
    	printf("NIF: ");
    	fgets(input, sizeof(input), stdin);
    	nineDigitString = sscanf(input, "%d", &(*p).nif);
		if(nineDigitString != 1) {
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

	do {
		printf("Diga a distancia: ");
		fgets(input, sizeof(input), stdin);
		(*p).distancia = strtol(input, NULL, 0);
		if((*p).distancia <= (*aux).itemMM.autonomia) {
			success = 1;
		}
		else {
			printf("\nA distancia inserida (%d) e superior a autonomia do veiculo escolhido (%d)\n\n",(*p).distancia,(*aux).itemMM.autonomia);
			success = 0;
		}
	}while(success!=1);
}
//#####################################################################################################
void imprimirM(mMobilidade m) {
	printf("%-12s%-15s%-15.2f%d\n",m.codigo,m.tipoMM,m.custo,m.autonomia);
}
//#####################################################################################################
void imprimirP(pUtilizacao p) {
	printf("%-14d%-15d%-13s%-11d%d\n",p.ordem,p.nif,p.codTipoMM,p.tempo,p.distancia);
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
void inserirMeioMobilidade(tcelulaM *m, int *sizeM, int *lastCodM) {
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
        (*sizeM)++;
		(*lastCodM)++;
		lerM(&aux,(*lastCodM));
		while((*m).prox!=NULL) {
			m=(*m).prox;
		}
		(*m).itemMM=aux;
		(*m).prox=ap;
	}
}
//#####################################################################################################
void inserirPedidoUtilizacao(tcelulaP *p, int *sizeP, int *lastCodP, tcelulaM **m) {
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
        (*sizeP)++;
		(*lastCodP)++;
		lerP(&aux,(*lastCodP),m);
		while((*p).prox!=NULL) {
			p=(*p).prox;
		}
		(*p).itemPU=aux;
		(*p).prox=ap;
	}
}
//#####################################################################################################
void listarMeioMobilidade(tcelulaM *m, int sizeM) {
	system("cls");
	puts("Dados disponiveis: ");
	if((*m).prox==NULL)	{
		puts("Nenhum");
	}
	else {
        printf("A lista de pedidos de utilizacao contem %d pedidos",sizeM);
		printf("\n\n%-12s%-15s%-15s%s\n","Codigo","Tipo","Custo","Autonomia");
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
		printf("\n\n%-29s%s\n%-14s%-15s%-13s%-11s%s\n","Numero de","Codigo","Ordem","NIF","Tipo MM","Tempo","Distancia");
		while((*p).prox != NULL) {
			imprimirP((*p).itemPU);
			p=(*p).prox;
		}
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
void removerPedidoUtilizacao(tcelulaP **p, int *sizeP, int nOrdem) {
	tcelulaP *y, *atras, *frente, *aux;
	char elemRetirar[40];
	int intElemRetirar;
	
	system("cls");
	y=(*p);
	
	if(((*y).prox)==NULL) { 
		printf("A lista nao tem dados"); 
	}
	else {
		if(nOrdem==0) {
			printf("Diga o codigo cujo meio de mobilidade quer retirar?\n");
			if(fgets(elemRetirar, sizeof(elemRetirar), stdin)) {
				elemRetirar[strcspn(elemRetirar, "\n")] = 0;
				intElemRetirar = strtol(elemRetirar, NULL, 0);
			}
		}
		else {
			intElemRetirar = nOrdem;
		}
		
		if(intElemRetirar == (*(*p)).itemPU.ordem) {
			system("cls");
			printf("O elemento foi retirado\n");
			printf("\n\n%-29s%s\n%-14s%-15s%-13s%-11s%s\n","Numero de","Codigo","Ordem","NIF","Tipo MM","Tempo","Distancia");
			imprimirP((*(*p)).itemPU);
			(*p)=(*(*p)).prox;
            (*sizeP)--;
			free(y);
		}
		else {
			aux=(*p);
			while((intElemRetirar != (*aux).itemPU.ordem) && ((*(*aux).prox).prox!=NULL)) {
				atras=aux;
				aux=(*aux).prox;
				frente=(*aux).prox;
			}
			
			if(intElemRetirar == (*aux).itemPU.ordem) {
				(*atras).prox=frente;
				printf("O elemento foi retirado\n");
				printf("\n\n%-29s%s\n%-14s%-15s%-13s%-11s%s\n","Numero de","Codigo","Ordem","NIF","Tipo MM","Tempo","Distancia");
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
void removerMeioMobilidade(tcelulaM **m, int *sizeM, tcelulaP **p, int *sizeP) {
	tcelulaM *y, *atras, *frente, *aux;
	tcelulaP *atrasP, *frenteP,  *auxP;
	char elemRetirar[40];
	
	system("cls");
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
			printf("\n\n%-12s%-15s%-15s%s\n","Codigo","Tipo","Custo","Autonomia");
			imprimirM((*(*m)).itemMM);
			system("pause");
			auxP=(*p);
			while((*auxP).prox != NULL) {
				while((strcmp((*auxP).itemPU.codTipoMM,elemRetirar)!=0) && (*(*auxP).prox).prox != NULL) {
					atrasP=auxP;
					auxP=(*auxP).prox;
					frenteP=(*auxP).prox;
				}	
				if(strcmp((*auxP).itemPU.codTipoMM,elemRetirar)==0) {
					frenteP=(*auxP).prox;
					removerPedidoUtilizacao(p,sizeP,(*auxP).itemPU.ordem);
					auxP=frenteP;
				}
				else {
					break;
				}
			}
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
				printf("\n\n%-12s%-15s%-15s%s\n","Codigo","Tipo","Custo","Autonomia");
				imprimirM((*aux).itemMM);
				system("pause");

				auxP=(*p);
				while((*auxP).prox != NULL) {
					while((strcmp((*auxP).itemPU.codTipoMM,elemRetirar)!=0) && (*(*auxP).prox).prox != NULL) {
						atrasP=auxP;
						auxP=(*auxP).prox;
						frenteP=(*auxP).prox;
					}	
					if(strcmp((*auxP).itemPU.codTipoMM,elemRetirar)==0) {
						removerPedidoUtilizacao(p,sizeP,(*auxP).itemPU.ordem);
						auxP=frenteP;
					}
					else {
						break;
					}
				}
                (*sizeM)--;
				free(aux);
				free((*auxP).prox);
			}
			else {
				system("cls"); 
				printf("O elemento com o codigo %s nao existe na lista", elemRetirar);
			}
		}
	}
}
//#####################################################################################################
void calcularCustoMobilidade(tcelulaM *m,tcelulaP *p) {
	char elemCalcular[40];
	int intElemCalcular;

	system("cls");
	printf("Diga o numero de ordem que quer calcular?\n");
	if(fgets(elemCalcular, sizeof(elemCalcular), stdin)) {
		elemCalcular[strcspn(elemCalcular, "\n")] = 0;
		intElemCalcular = strtol(elemCalcular, NULL, 0);
	}

	if((*p).prox==NULL)	{
		puts("Nenhum");
	}
	else {
		while((intElemCalcular != (*p).itemPU.ordem) && ((*p).prox != NULL)) {
			p=(*p).prox;
		}
		if(intElemCalcular == ((*p).itemPU.ordem)) {
			printf("\n\n%-29s%s\n%-14s%-15s%-13s%-11s%s\n","Numero de","Codigo","Ordem","NIF","Tipo MM","Tempo","Distancia");
			imprimirP((*p).itemPU);
			while(strcmp((*p).itemPU.codTipoMM,(*m).itemMM.codigo)!=0 && ((*m).prox != NULL)) {
				m=(*m).prox;
			}
			if(strcmp((*p).itemPU.codTipoMM,(*m).itemMM.codigo)==0) {
				printf("\n\n%-12s%-15s%-15s%s\n","Codigo","Tipo","Custo","Autonomia");
				imprimirM((*m).itemMM);
				printf("\nO pedido de ordem n.(%d) tera um custo de (%g)",(*p).itemPU.ordem,((*p).itemPU.tempo) * ((*m).itemMM.custo));
			}
		}
		else {
			printf("\nNao existe nenhum pedido de ordem n.(%s)!!",elemCalcular);			
		}
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
void distribuirMeiosMobilidade(tcelulaM *m, tcelulaP *p) {
	tcelulaP *auxP;
	int flag=0;

	if(((*p).prox==NULL) && ((*m).prox==NULL))	{
		puts("Nenhum");
	}
	else {
		auxP=p;
		while((*m).prox != NULL) {
				printf("\n");
				imprimirM((*m).itemMM);
			while(((*p).prox != NULL)) {
				// TempoInicial = TempoFinal;
				// TempoFinal = TempoFinal + (*p).itemPU.tempo;
				// AutonomiaInicial = AutonomiaFinal;
				// if((AutonomiaInicial - (*p).itemPU.distancia)<0) {
				// 	AutonomiaFinal = 0;
				// }
				// else {
				// 	AutonomiaFinal = AutonomiaInicial - (*p).itemPU.distancia;
				// }
				if(strcmp((*p).itemPU.codTipoMM,(*m).itemMM.codigo)==0) {
					imprimirP((*p).itemPU);
					flag=1;
				}
				p=(*p).prox;
				//printf("%-15d%-15d%-15d%-15d%-15d%d\n",(*p).itemPU.ordem,(*p).itemPU.nif,TempoInicial,TempoFinal,AutonomiaInicial,AutonomiaFinal);
			}
			if(flag!=1) {
				printf("\tNenhum pedido\n");
			}
			flag=0;
			p=auxP;
			m=(*m).prox;
		}
	}
	system("pause");
}
//#####################################################################################################
void listagemUtilizacaoMeioMobilidade(tcelulaM *m, tcelulaP *p){
	char elemDeterminar[40];
	int TempoInicial=0, TempoFinal=0, AutonomiaInicial=0, AutonomiaFinal=0;

	system("cls");
	printf("Diga o codigo do Meio de Mobilidade que pertende calcular?\n");
	if(fgets(elemDeterminar, sizeof(elemDeterminar), stdin)) {
		elemDeterminar[strcspn(elemDeterminar, "\n")] = 0;
	}

	if(((*p).prox==NULL) && ((*m).prox==NULL))	{
		puts("Nenhum");
	}
	else {
		while((strcmp(elemDeterminar,(*m).itemMM.codigo)!=0) && ((*m).prox != NULL)) {
			m=(*m).prox;
		}
		if(strcmp(elemDeterminar,(*m).itemMM.codigo)==0) {
			printf("\n\n%-12s%-15s%-15s%s\n","Codigo","Tipo","Custo","Autonomia");
			imprimirM((*m).itemMM);
			printf("\n%-15s%-15s%-15s%-15s%-15s%-15s%s\n","n Ordem","NIF","Tempo Inicio","Tempo Fi.","Auto. Ini.","Auto. Fi.","Dist. Nece.");
			AutonomiaFinal = (*m).itemMM.autonomia;
			while(((*p).prox != NULL)) {
				if(strcmp((*p).itemPU.codTipoMM,(*m).itemMM.codigo)==0) {
					TempoInicial = TempoFinal;
					TempoFinal = TempoFinal + (*p).itemPU.tempo;
					AutonomiaInicial = AutonomiaFinal;
					if((AutonomiaInicial - (*p).itemPU.distancia)<0) {
						AutonomiaFinal = 0;
					}
					else {
						AutonomiaFinal = AutonomiaInicial - (*p).itemPU.distancia;
					}
					printf("%-15d%-15d%-15d%-15d%-15d%-15d%d\n",(*p).itemPU.ordem,(*p).itemPU.nif,TempoInicial,TempoFinal,AutonomiaInicial,AutonomiaFinal,(*p).itemPU.distancia);
				}
				p=(*p).prox;
			}
		}
		else {
			printf("\nNao existe nenhum meio de mobilidade com o codigo (%s)!!",elemDeterminar);			
		}
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
void verificarDadosNosFicheiros(tcelulaM *m, int *listSizeM, int *lastCodM, tcelulaP *p, int *listSizeP, int *lastCodP) {
	tcelulaM *apM;
	tcelulaP *apP;
	mMobilidade auxM;
	pUtilizacao auxP;
	FILE *f_MM;
	FILE *f_PU;
	int success = 0;

	f_MM=fopen("MeioDeMobilidade.txt","r");
	f_PU=fopen("PedidosDeUtilizacao.txt","r");
	
    if((f_MM != NULL) && (f_PU != NULL)) {
		fscanf(f_MM, "%*s %*s %*s %*s");
		do {
			if(fscanf(f_MM, "%s %s %f %d", auxM.codigo, auxM.tipoMM, &auxM.custo, &auxM.autonomia) == 4) {
				apM=(tcelulaM *)malloc(sizeof(tcelulaM));
				inicializarM(&(*apM).itemMM);
				(*apM).prox=NULL;

				while((*m).prox!=NULL) {
					m = (*m).prox;
				}
				(*m).itemMM=auxM;
				(*m).prox=apM;
				(*listSizeM)++;
				sscanf((*m).itemMM.codigo,"%*[^0123456789]%d", &(*lastCodM));
				success = 0;
			}
			else{
				success = 1;
			}
		}while(success == 0);

		fscanf(f_PU, "%*s %*s %*s");
		fscanf(f_PU, "%*s %*s %*s %*s %*s %*s");
		do {
			if(fscanf(f_PU, "%d %d %s %d %d", &auxP.ordem, &auxP.nif, auxP.codTipoMM, &auxP.tempo, &auxP.distancia) == 5) {
				apP=(tcelulaP *)malloc(sizeof(tcelulaP));
				inicializarP(&(*apP).itemPU);
				(*apP).prox=NULL;

				while((*p).prox!=NULL) {
					p = (*p).prox;
				}
				(*p).itemPU=auxP;
				(*p).prox=apP;
				(*listSizeP)++;
				(*lastCodP)=(*p).itemPU.ordem;
				success = 0;
			}
			else{
				success = 1;
			}
		}while(success == 0);
	}

	if(((*listSizeM) > 0) && ((*listSizeP) > 0)) {
		printf("Lista de (Meios de Mobilidade) foi carregada com sucesso - Lista contem (%d) dados!!\n",(*listSizeM));
		printf("Lista de (Pedidos de utilizacao) foi carregada com sucesso - Lista contem (%d) dados!!\n",(*listSizeP));
	}
	else if((*listSizeM) > 0) {
		printf("Lista de (Meios de Mobilidade) foi carregada com sucesso - Lista contem (%d) dados!!\n",(*listSizeM));
		printf("A lista (Pedidos de utilizacao) encontra-se vazia!!\n");
	}
	else if((*listSizeP) > 0) {
		printf("A lista (Meios de Mobilidade) encontra-se vazia!!\n");
		printf("Lista de (Pedidos de utilizacao) foi carregada com sucesso - Lista contem (%d) dados!!\n",(*listSizeP));
	}
	else {
		printf("A lista (Meios de Mobilidade) e (Pedidos de utilizacao) encontra-se vazia!!\n");
	}
	Sleep(3000);

    fclose(f_MM);
    fclose(f_PU);
}
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