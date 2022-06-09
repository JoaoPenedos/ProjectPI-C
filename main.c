/**
 * @file main.c
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
#include "functions.c"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main() {
    int i, flag=0, opcao, success, listSizeM = 0, listSizeP = 0, lastCodM, lastCodP;
	char *endptr, buf[1024];
	tcelulaM *listaM;
	tcelulaP *listaP;

	system("cls");

    listaM=inicializarM();
    listaP=inicializarP();
	verificarDadosNosFicheiros(listaM,&listSizeM,&lastCodM,listaP,&listSizeP,&lastCodP);
    do {
        do {
            system("cls");

			printf("%c",201); for(i = 0; i < 103; i++) printf("%c",205); printf("%c\n",187);
            _printf_p("%1$c                                               MENU                                                    %1$c \n"
                      "%1$c   0 - Sair                                                                                            %1$c \n"
                      "%1$c   1 - Inserir Meio de Mobilidade                     4 - Inserir Pedido de Utilizacao                 %1$c \n"
                      "%1$c   2 - Listagem de todos os Meios de mobilidade       5 - Listagem de todos os Pedidos de utilizacao   %1$c \n"
                      "%1$c   3 - Remover Meio de mobilidade                     6 - Remover Pedidos de Utilizacao                %1$c \n",186);     
			printf("%c",204); for(i = 0; i < 103; i++) printf("%c",205);	printf("%c\n",185);
			_printf_p("%1$c   7 - Calculo do custo de utilizacao                                                                  %1$c \n"
                      "%1$c   8 - Distribuir meios de mobilidade                 9 - Lista da utilizacao de meios de mobilidade   %1$c \n",186);			
			printf("%c",200); for(i = 0; i < 103; i++) printf("%c",205); printf("%c\nOpcao: ",188);

			if (!fgets(buf, sizeof(buf), stdin)) {
				return 1;
			}
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
				// *endptr is neither end of string nor newline, so we didn't convert the *whole* input.
				success = 0;
			}
			else {
				success = 1;
			}
        }while(!success);

        switch(opcao) {
            case 0: printf("Goodbye!!\n\n"); 
					break;
            case 1: inserirMeioMobilidade(listaM,&listSizeM,&lastCodM); 
					break;
            case 2: listarMeioMobilidade(listaM,listSizeM); 
					break;
            case 3: removerMeioMobilidade(&listaM,&listSizeM,&listaP,&listSizeP);
					break;
            case 4: 
					if(listSizeM>0) {
						inserirPedidoUtilizacao(listaP,&listSizeP,&lastCodP,&listaM); 
					}
					else {
						printf("Nao existe nenhum meio de mobilidade disponivel para fazer o pedido");
						system("pause");
					}
					break;
            case 5: listarPedidoUtilizacao(listaP,listSizeP);
					break;
            case 6: removerPedidoUtilizacao(&listaP,&listSizeP,flag); 
					break;
            case 7: calcularCustoMobilidade(listaM,listaP);
            		break;
            case 8: distribuirMeiosMobilidade(listaM,listaP);
            		break;
            case 9: listagemUtilizacaoMeioMobilidade(listaM,listaP);
            		break;
        }
    }while(opcao != 0);

	armazenarNosFicheiros(listaM,listaP);
    free(listaM);
    free(listaP);

    return 0;
}