/**
 * @file header.h
 * @author João Penedos
 * @brief
 * @version 1.1
 * 
 * @copyright Copyright (c) 2022 
 */

#ifndef _HEADER
#define _HEADER


typedef struct {
	char codigo[50];
	char tipoMM[50];
	float custo;
	int autonomia;
}mMobilidade;

typedef struct {
    int ordem;
    int nif;
	char codTipoMM[50];
    int tempo;
    int distancia;
}pUtilizacao;

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


void iniM(mMobilidade *meio);
void iniP(pUtilizacao *pedido);

void lerM(mMobilidade *m, int lastCodM);
void lerP(pUtilizacao *p, int lastCodP, tcelulaM **m);

void imprimirM(mMobilidade m);
void imprimirP(pUtilizacao p);

void putInFileM(mMobilidade m, FILE *f_MM);
void putInFileP(pUtilizacao p, FILE *f_PU);

tcelulaM *inicializarM();
tcelulaP *inicializarP();

void inserirMeioMobilidade(tcelulaM *m, int *sizeM, int *lastCodM);
void inserirPedidoUtilizacao(tcelulaP *p, int *sizeP, int *lastCodP, tcelulaM **m);

void listarMeioMobilidade(tcelulaM *m, int sizeM);
void listarPedidoUtilizacao(tcelulaP *p, int sizeP);

void removerPedidoUtilizacao(tcelulaP **p, int *sizeP, int nOrdem);
void removerMeioMobilidade(tcelulaM **m, int *sizeM, tcelulaP **p, int *sizeP);

void calcularCustoMobilidade(tcelulaM *m,tcelulaP *p);
void distribuirMeiosMobilidade(tcelulaM *m, tcelulaP *p);
void listagemUtilizacaoMeioMobilidade(tcelulaM *m, tcelulaP *p);

void verificarDadosNosFicheiros(tcelulaM *m, int *listSizeM, int *lastCodM, tcelulaP *p, int *listSizeP, int *lastCodP);
void armazenarNosFicheiros(tcelulaM *m, tcelulaP *p);


#endif