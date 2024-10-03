#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>
#include <math.h>
#include "ExercicioPilhaHanoi.h"

// Função para desenhar as torres
void desenharTorres(TpPilha p) {
    clrscr(); // Limpa a tela
    gotoxy(10, 1); printf("Torre A");
    gotoxy(30, 1); printf("Torre B");
    gotoxy(50, 1); printf("Torre C");

    // Desenha os discos nas torres
    for (int i = MAX_DISCOS - 1; i >= 0; i--) {
        for (int j = 0; j < 3; j++) { // Para cada torre
            gotoxy(10 + j * 20, 2 + (MAX_DISCOS - 1 - i)); // Ajusta a posição na linha
            if (i <= p.topo[j]) { // Se há um disco nesta posição
                int disco = pop(p,j); // Obtém o valor do disco
                	if(vazia(p,j))
                	{
                		printf("|");
                	}
                	else
                	{
                		printf("%2d ", disco); // Exibe o valor do disco
                	}
                                    
            } else {
                printf("|"); // Espaço vazio (sem disco)
            }
        }
    }
    
    gotoxy(1, 2 + MAX_DISCOS); // Move o cursor para baixo
}

void mostrarPilhas(TpPilha p)
{
    gotoxy(10, 1); 
	printf("Torre 0");
    gotoxy(30, 1);
	printf("Torre 1");
    gotoxy(50, 1); 
	printf("Torre 2");
	TpPilha aux;  // Pilha auxiliar
    incializar(aux,3);
     for (int i =0; i <MAX_DISCOS; i++)
     {
     	for (int j = 0; j < 3; j++) // para andar nas torres
     	{
	    	while (!vazia(p, j)) 
			{
	        	push(aux,j, pop(p, j));
	    	}
     		gotoxy(10 + j * 20, 2 + (MAX_DISCOS - 1 - i)); // Ajusta a posição na linha
     		if(!vazia(aux,j))
     		{
     			int disco = pop(aux,j); // Obtém o valor do disco
     			printf("%2d ", disco);
     		}
     		else
     		{
     			printf("|"); // mostra estra espaço vazio 
     		}
		 }
     }
 
}
char menu(void) {
    printf("\nEscolha uma opcao:\n");
    printf("[1] - Inicializar hastes\n");
    printf("[2] - Mover Discos\n");
    printf("[3] - Movimento Automatico\n");
    printf("[4] - Imprimir Pilhas\n");
    printf("[5] - Sair\n");
    printf("Opcao: ");
    return getche();  // Captura a opcao do usuario
}
void moverDisco(TpPilha &p)
{
	int dist,orig;
	int auxP;
	gotoxy(1,12); // manda pra depois das hastes
	printf("Torre Origem: ");
	scanf("%d",&orig);
	if(orig>=0 && orig<=2)
	{
		if(!vazia(p,orig))
		{
			printf("Torre distino: ");
			scanf("%d",&dist);
			// deveria ver se as hastes existem né
			if(dist>= 0 && dist <=2)
			{
				auxP=p.pilha[p.topo[orig]]; // faça uma copia do valor para verificar e só depois remover
				if(!vazia(p,dist))
				{
					if(auxP<p.pilha[p.topo[dist]])
					{
						push(p,dist,auxP);// adiciona no distino
						pop(p,orig); // remove o elem da origem
						printf("Mudanca feita!\n");
					}
					else
					{
						printf("Elemento e maior do que o anterior\n");
					}
				}
				else
				{
					push(p,dist,auxP);// adiciona no distino
					pop(p,orig); // remove o elem da origem
					printf("Mudanca feita!\n");
				}	
				}
			else
			{
				printf("TORRE NAO EXISTE");
			}

		}
		else
		{
			printf("\nHaste Vazia!!\n");
		}
	}
	else
	{
			printf("TORRE NAO EXISTE");
	}
	
}
void moverEntreTorres(TpPilha &p, int origem, int destino) {
    if (vazia(p, origem) && !vazia(p, destino)) {
        //destino para origem
        push(p, origem, pop(p, destino));
    } else if (!vazia(p, origem) && vazia(p, destino)) {
        // origem destino
        push(p, destino, pop(p, origem));
    } else if (elemTopo(p, origem) > elemTopo(p, destino)) {
        //destino para origem
        push(p, origem, pop(p, destino));
    } else {
        // origem para destino
        push(p, destino, pop(p, origem));
    }
}
void AutomaticoG(TpPilha &p, int qntdDisco) {
    int origem = 0, aux = 1, destino = 2;  
    int movimentos = pow(2, qntdDisco) - 1; 
    
    // Se o número de discos for par, troca a torre auxiliar e destino
    if (qntdDisco % 2 == 0) {
        int temp = destino;
        destino = aux;
        aux = temp;
    }

    // Loop para realizar os movimentos automaticamente
    for (int i = 1; i <= movimentos; i++) {
    	clrscr();
        mostrarPilhas(p);  // Mostra a torres

        if (i % 3 == 1) {
            // Movimento entre origem e destino
            moverEntreTorres(p, origem, destino);
        } else if (i % 3 == 2) {
            // Movimento entre origem e auxiliar
            moverEntreTorres(p, origem, aux);
        } else if (i % 3 == 0) {
            // Movimento entre auxiliar e destino
            moverEntreTorres(p, aux, destino);
        }

        Sleep(500); 
    }
	clrscr();
    mostrarPilhas(p);
    gotoxy(1,12);
    printf("Resolvido automaticamente!\n");
}

int main(void) {
    TpPilha pilha;
    int op, np, elem;
	int qntdDisco;
    do {
        system("cls");  // Limpa a tela
        op = menu();    // Exibe o menu

        switch (op) 
		{
            case '1':
            	
            	printf("\nQuantidade de Discos\n(min: 3 | max: 10): ");
            	scanf("%d",&qntdDisco);
            	if(qntdDisco >=3 && qntdDisco<=10)
            	{
            		incializar(pilha,qntdDisco);
					for(int i=qntdDisco; i>0 ;i--)
					{
						push(pilha,0,i);
					}
			        printf("\nPilhas inicializadas!\n");
            	}
            	else
            	{
            		printf("Valor Invalido!!\n");
            	}
				
				//desenharTorres(pilha);
		        getche();
		                break;

            case '2':
            	int  den;
            	do
            	{
					clrscr();
	            	mostrarPilhas(pilha);
	                moverDisco(pilha);
            		printf("Novo Movimento?\nAperte ENTER | ESC parar");
            		mostrarPilhas(pilha);
            		den=getch();
				}while(den!=27);
				
		        getche();
		                break;

            case '3':
		               AutomaticoG(pilha,qntdDisco);
		               getche();
		                break;

            case '4':
            	clrscr();
				mostrarPilhas(pilha);
				getch();
                break;
			case '5':
				printf("\nSaindo...\n");
                break;
             
        }
    } while (op != '5');

    return 0;
}

