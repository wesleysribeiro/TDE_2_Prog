 /************************
* Desenvolvido por:		*
*	Lucas Lavratti		*
*	Wesley Ribeiro		*
************************/

						/* Realiza diversos calculos envolvendo vetores*/
						
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "CalculusGA.h"


FILE *fp;

typedef struct{
	float x[5], y[5], z[5];
	float result;
	time_t timeraw;

} LOG;


int Create_Log(){ 
	fp = fopen("log.txt", "r+b");
	if(fp == NULL)
		fp = fopen("log.txt", "w+b");
    if(fp == NULL){
		getchar();
		return 0; // Nao foi possivel criar
	}
	else
		return 1; // Foi possivel criar
}

int New_Log_Entry(float *x, float *y, float *z, float resultado){
	int traw;
	Create_Log();
	int i;
	LOG a;
	a.result = resultado;
	printf("a.result = %f\n", a.result);
	for(i = 0; i<3; i++){
		a.x[i] = x[i];
		a.y[i] = y[i];
		a.z[i] = z[i];
	}
	traw = time(NULL);
	a.timeraw = traw;
    fseek(fp, 0, SEEK_END);
	fwrite(&a, sizeof(a), 1, fp);
    fflush(fp);
	return 1;
}


int Remove_Log(){
	
}

void Show_Log(){
	Create_Log();
	LOG a;
	fseek(fp, 0, SEEK_SET);	
    while(fread(&a, sizeof(a), 1, fp) == 1){
	    puts("---------------------");
	    printf("%s", ctime(&a.timeraw));
	    printf("Resultado: %f\n", a.result);
    }
}


int main() {
	int menu, menu_sec, i, decisao;
	float *x, *y, *z, dist, modulo, mod_diretor, d[2], resultado = 0;
    float ptr_x = NULL, ptr_y = NULL; ptr_z = NULL;
	do{
		i = 0;
		/* Menu Primário*/
		printf("1 - \t Produtos entre vetores\n");
		printf("2 - \t Distancias\n");
		printf("3 - \t Sair do programa\n");
		printf("4 - \t Mostrar log\n");
		printf("Digite o numero correspondente a opcao desejada: ");
		scanf("%1d", &menu);
		switch (menu){
			case 1:
				printf("1 - \t Produto Escalar\n");
				printf("2 - \t Produto Vetorial\n");
				printf("3 - \t Produto Misto\n");
				printf("4 - \t Retonar ao menu principal\n");
				printf("Digite o numero correspondente a opcao desejada: ");
				scanf(" %1d", &menu_sec);
				if (menu_sec >=1 && menu_sec <4){		                           /* Evita repetição de printf e scanf em cada case */
                    x = calloc(2, sizeof(float));
                    y = calloc(2, sizeof(float));
                    z = calloc(2, sizeof(float));
                    ptr_x = x;
                    ptr_y = y;
                    ptr_z = z;
					printf("Digite as coordenadas (x, y, z) do primeiro vetor: ");
					scanf("%f%f%f", &x[0], &y[0], &z[0]);
					printf("Digite as coordenadas (x, y, z) do segundo vetor: ");
					scanf("%f%f%f", &x[1], &y[1], &z[1]);
					if (menu_sec == 3){											/* Necessita de três vetores para realizar os calculos */
                        x = realloc(ptr_x, 3 * sizeof(float));
                        y = realloc(ptr_y, 3 * sizeof(float));
                        z = realloc(ptr_z, 3 * sizeof(float));
						printf("Digite as coordenadas (x, y ,z) do terceiro vetor: ");
						scanf("%f%f%f", &x[2], &y[2], &z[2]);
					}
				}
				switch (menu_sec){
					case 1:
						/* Calculo do produto escalar*/
						resultado = prod_escalar(x , y, z);
						printf("Produto escalar = %.9f\n", resultado);
						New_Log_Entry(x, y, z, resultado);
						break;
					case 2:
						/* Calculo do Produto Vetorial */
						prod_vet(x, y, z);
						printf("Produto vetorial = (%f, %f, %f)\n", x[2], y[2], z[2]);
						break;
					case 3:
						/* Calculo do Produto Misto */
						printf("Produto misto = %f\n", prod_misto(x, y, z));
						break;
					case 4:
						break;
					default:
						printf("Opcao invalida!\a\n");
				}
				break;
			case 2:
				/* Menu secundario */
				printf("1 - \t Distancia entre dois pontos\n");
				printf("2 - \t Distancia entre ponto e reta\n");	
				printf("3 - \t Distancia entre duas retas\n");	
				printf("4 - \t Distancia entre reta e plano\n");
				printf("5 - \t Distancia entre ponto e plano\n");
				printf("6 - \t Retornar ao menu principal\n");
				printf("Informe o numero correspondente a opcao desejada: ");
				scanf("%d", &menu_sec);
				switch(menu_sec){
					case 1:
						printf("Informe as coordenadas (x,y,z) do primeiro ponto: ");
						scanf("%f%f%f", &x[0], &y[0], &z[0]);
						printf("Informe as coordenads (x,y,z) do segundo ponto: ");
						scanf("%f%f%f", &x[1], &y[1], &z[1]);
						 /*Calcula a distancia entre dois pontos*/
						resultado = dist_pontos(x, y, z);
						break;
					case 2:
						printf("Informe as coordenadas (x, y, z) do vetor diretor: ");			/* Calcula a distancia entre um ponto e uma reta */
						scanf("%f%f%f", &x[0], &y[0], &z[0]);
						printf("Informe as coordenadas (x,y,z) do ponto desejado: ");
						scanf("%f%f%f", &x[1], &y[1], &z[1]);
						printf("Informe as coordenads (x,y,z) de um ponto pertencente a reta: ");
						scanf("%f%f%f", &x[2], &y[2], &z[2]);
						printf("A distancia entre o ponto e a reta eh: %f\n", dist_ponto_reta(x, y, z));
						break;
					case 3:
						printf("Informe as coordenadas (x, y, z) do vetor diretor da reta r: "); /* Calcula a distancia entre duas retas */
						scanf("%f%f%f", &x[0], &y[0], &z[0]);
						printf("Informe as coordenadas (x, y, z) do vetor diretor da reta s: ");
						scanf("%f%f%f", &x[1], &y[1], &z[1]);		
						if (x[0]/x[1] == y[0]/y[1] && y[0]/y[1] == z[0]/z[1]){         /* Verifica se as retas são paralelas */
							printf("Informe as coordenadas (x,y,z) do ponto  a reta s: ");
							scanf("%f%f%f", &x[1], &y[1], &z[1]);
							printf("Informe as coordenads (x,y,z) de um ponto  a reta r: ");
							scanf("%f%f%f", &x[2], &y[2], &z[2]);
							printf("A distancia entre as reta eh: %f\n", dist_retas(x, y, z));
						}
						else{
							printf("Informe as coordenadas (x, y, z) de um ponto da reta r: ");    /* Caso sejam reversas */
							scanf("%f%f%f", &x[2], &y[2], &z[2]);
							printf("Informe as coordenadas (x, y, z) de um ponto da reta s: ");
							scanf("%f%f%f", &x[3], &y[3], &z[3]);	
							printf("A distancia entre as duas retas eh: %f\n", dist_retas_reversas(x, y, z));
						}
						break;
					case 4:
						printf("Digite as coordenadas (x, y, z) do vetor diretor do plano e o termo 'd': "); /* Calcula a distancia entre uma reta e um plano */
						scanf("%f%f%f%f", &x[0], &y[0], &z[0], &d[0]);
						printf("Informe um ponto da reta (x, y, z): ");
						scanf("%f%f%f", &x[1], &y[1], &z[1]);
						printf("A distancia entre a reta e o plano eh: %f\n", dist_reta_plano(x, y , z, d));
						break;
					case 5:
						printf("Digite as coordenadas (x, y, z) do vetor diretor do plano e o termo 'd': "); /* Calcula a distancia entre um ponto e um plano */
						scanf("%f%f%f%f", &x[0], &y[0], &z[0], &d[0]);
						printf("Digite as coordenadas (x, y, z) do ponto: ");
						scanf("%f%f%f", &x[1], &y[1], &z[1]);
						printf("A distancia entre o ponto e o plano eh: %f\n", dist_ponto_plano(x, y, z, d));
						break;
					case 6:
						break;
					default:
						printf("Opcao invalida!\a\n");
				}
				break;
			case 3:
				continue;
			case 4:
				Show_Log();
				break;
			default:
				printf("Opcao invalida\a\n");
		}
		printf("Deseja continuar? (1 - Sim) (0 - Nao)\n");
		scanf("%d", &i);
		if (i == 1) {
			printf("Retornando ao meu principal... pressione enter para continuar\n");
			getchar();
		}
		system("clear || cls"); /* Limpa a tela do programa no windows e linux*/
	} while (i == 1);
	fclose(fp);
	return 0;
}
