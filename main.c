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

/*NUMEROS DAS ESCOLHAS NOS MENUS*/
#define PRODUTOS 1
#define DISTANCIAS 2
#define MOSTRA_LOG 3

#define PRODUTO_ESCALAR 1
#define PRODUTO_VETORIAL 2
#define PRODUTO_MISTO 3

#define DIST_DOIS_PONTOS 1
#define DIST_PONTO_RETA 2
#define DIST_DUAS_RETAS 3
#define DIST_RETA_PLANO 4
#define DIST_PONTO_PLANO 5
#define MAGIA_NEGRA 32

FILE *fLog;

/* 
 *	Codigo n funfa no linux corretamente,
 *	Abaixo um pedaco de portabilidade
 *	Mude novamente para fflush(stdin) no windows
 */

void clean_stdin(void) {
    
    int c;
    
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);

}

float preLog[MAGIA_NEGRA];

int abreLog() {
	
    fLog = fopen("historico.log", "w+t");

    if(fLog == NULL)	/* Não foi possivel ler ou o arquivo não existe */
        fLog = fopen("historico.log", "w+t");

    if(fLog == NULL)
        return 0; // Não foi possível criar o arquivo
    else 
	    return 1; // Foi possivel criar
}


int novaEntrada(int argc, float *argv){
	
	int i;
	
	if(!abreLog())	
		return 0;
	
	fprintf(fLog, "%ld;",time(NULL));	
	fprintf(fLog, "%d;",argc);		
	
	for (i = 0 ; i < argc; i++){
		fprintf(fLog, "%f;",*(argv+i));	
		//printf(" LOG> %f \n",*(argv+i));
	}
	
	printf("\n <LOG OK> \n");
	
	fflush(fLog);	
	return 1;

}

/* TODO
int Remove_Log() {
}
/**/

/*
void Show_Log() {
	abreLog();
    LOG a;
    fseek(fLog, 0, SEEK_SET); 
    while(fread(&a, sizeof(a), 1, fLog) == 1) {    	
        puts("---------------------");
        printf("%s", ctime(&a.timeraw));
        printf("Operacao: %s\n", a.operation == 1? "Produto Escalar" : "Sei la viu");
        printf("Resultado: %f\n", a.result);        
    }
}
/**/
void menuProdutos() {
	
    int auxMenu = 0;
    float resultado = 0;
    float *x, *y, *z;

    printf("1 - \t Produto Escalar\n"
           "2 - \t Produto Vetorial\n"
           "3 - \t Produto Misto\n"
           "Outro -  Retonar ao menu principal\n"
           "Digite o numero correspondente a opcao desejada: ");

    scanf(" %1d\n", &auxMenu);
	
	preLog[1] = auxMenu;
	
    if (auxMenu >= PRODUTO_ESCALAR && auxMenu <= PRODUTO_MISTO) {
        /* Evita repeti??o de printf e scanf em cada case */
        x = calloc(2, sizeof(float));
        y = calloc(2, sizeof(float));
        z = calloc(2, sizeof(float));

        printf("Digite as coordenadas (x, y, z) do primeiro vetor: ");
        scanf("%f%f%f", x, y, z);        
        preLog[2] = *x; 
        preLog[3] = *y;
        preLog[4] = *z;
        

        printf("Digite as coordenadas (x, y, z) do segundo vetor: ");
        scanf("%f%f%f", x+1, y+1, z+1);
		preLog[5] = *(x+1); 
        preLog[6] = *(y+1);
        preLog[7] = *(z+1);
        /* O Produto Misto Necessita de 3 vetores para realizar os calculos */
        if (auxMenu == PRODUTO_MISTO) {
            			
			x = realloc(x, 3 * sizeof(float));
            y = realloc(y, 3 * sizeof(float));
            z = realloc(z, 3 * sizeof(float));
                        
			printf("Digite as coordenadas (x, y ,z) do terceiro vetor: ");
            scanf("%f%f%f", x+2, y+2, z+2);
            preLog[8] = *(x+2); 
        	preLog[9] = *(y+2);
        	preLog[10] = *(z+2);

        }

    }
	
    switch (auxMenu) {

	    case PRODUTO_ESCALAR:
	        resultado = prod_escalar(x, y, z);
	        preLog[8] = resultado;
	        printf("Produto escalar = %.9f\n", resultado);
			novaEntrada(9, preLog);
	        break;
	
	    case PRODUTO_VETORIAL:
	        prod_vet(x, y, z);
	        preLog[8] = *(x+2);
	        preLog[9] = *(y+2);
	        preLog[10] = *(z+2);
	        printf("Produto vetorial = (%f, %f, %f)\n", x[2], y[2], z[2]);
	       	novaEntrada(11, preLog);
	        break;
	
	    case PRODUTO_MISTO:
	    	resultado = prod_misto(x, y, z);
	    	preLog[11] = resultado;
	        printf("Produto misto = %f\n", resultado);
	        novaEntrada(12, preLog);
	        break;

    }

}

void menuDistancias() {

    float d[1] = {0};
    float resultado = 0;
    float *x, *y, *z;

    x = calloc(3, sizeof(float));
    y = calloc(3, sizeof(float));
    z = calloc(3, sizeof(float));


    printf("1 - \t Distancia entre dois pontos\n"
           "2 - \t Distancia entre ponto e reta\n"
           "3 - \t Distancia entre duas retas\n"
           "4 - \t Distancia entre reta e plano\n"
           "5 - \t Distancia entre ponto e plano\n"
           "Outro -  Retornar ao menu principal\n"
           "Informe o numero correspondente a opcao desejada: ");
    
	clean_stdin();

    switch(getchar()-48) {
	
	    case DIST_DOIS_PONTOS:
	        preLog[1] = DIST_DOIS_PONTOS;
	        
	        printf("Informe as coordenadas (x,y,z) do primeiro ponto: ");
	        scanf("%f%f%f", &x[0], &y[0], &z[0]);
			preLog[2] = *x; 
        	preLog[3] = *y;
        	preLog[4] = *z;

	        printf("Informe as coordenads (x,y,z) do segundo ponto: ");
	        scanf("%f%f%f", &x[1], &y[1], &z[1]);
		    preLog[5] = *(x+1); 
        	preLog[6] = *(y+1);
        	preLog[7] = *(z+1);

	        resultado = dist_pontos(x, y, z);
			preLog[8] = resultado;
			novaEntrada(9, preLog);

			printf("A distancia entre o ponto e o ponto eh: %f\n", resultado);
	
	        break;
	
	    case DIST_PONTO_RETA:
	        printf("Informe as coordenadas (x, y, z) do vetor diretor: ");
	        scanf("%f%f%f", &x[0], &y[0], &z[0]);
			preLog[2] = *x; 
        	preLog[3] = *y;
        	preLog[4] = *z;

	        printf("Informe as coordenadas (x,y,z) do ponto desejado: ");
	        scanf("%f%f%f", &x[1], &y[1], &z[1]);
		    preLog[5] = *(x+1); 
        	preLog[6] = *(y+1);
        	preLog[7] = *(z+1);
								
	        printf("Informe as coordenads (x,y,z) de um ponto pertencente a reta: ");
	        scanf("%f%f%f", &x[2], &y[2], &z[2]);
		    preLog[8] = *(x+2); 
        	preLog[9] = *(y+2);
        	preLog[10] = *(z+2);

			resultado = dist_ponto_reta(x, y, z);
			preLog[11] = resultado;
			novaEntrada(12, preLog);

	        printf("A distancia entre o ponto e a reta eh: %f\n", resultado);
	
	        break;
	
	    case DIST_DUAS_RETAS:
	        printf("Informe as coordenadas (x, y, z) do vetor diretor da reta r: ");
	        scanf("%f%f%f", &x[0], &y[0], &z[0]);
			preLog[2] = *x; 
        	preLog[3] = *y;
        	preLog[4] = *z;
	        printf("Informe as coordenadas (x, y, z) do vetor diretor da reta s: ");
	        scanf("%f%f%f", &x[1], &y[1], &z[1]);
		    preLog[5] = *(x+1); 
        	preLog[6] = *(y+1);
        	preLog[7] = *(z+1);
								
	        if (x[0]/x[1] == y[0]/y[1] && y[0]/y[1] == z[0]/z[1]) {
	            printf("Informe as coordenadas (x,y,z) do ponto  a reta s: ");
	            scanf("%f%f%f", &x[1], &y[1], &z[1]);
			    preLog[8] = *(x+2); 
    	    	preLog[9] = *(y+2);
        		preLog[10] = *(z+2);
								
	            printf("Informe as coordenads (x,y,z) de um ponto  a reta r: ");
	            scanf("%f%f%f", &x[2], &y[2], &z[2]);
			    preLog[11] = *(x+3); 
	        	preLog[12] = *(y+3);
    	    	preLog[13] = *(z+3);
								
				resultado = dist_retas(x, y, z);
				preLog[14] = resultado;
				novaEntrada(15, preLog);

	            printf("A distancia entre as reta eh: %f\n", resultado);
	
	        } else {
	            printf("Informe as coordenadas (x, y, z) de um ponto da reta r: ");
	            scanf("%f%f%f", &x[2], &y[2], &z[2]);
				preLog[8] = *(x+2); 
    	    	preLog[9] = *(y+2);
        		preLog[10] = *(z+2);

	            printf("Informe as coordenadas (x, y, z) de um ponto da reta s: ");
	            scanf("%f%f%f", &x[3], &y[3], &z[3]);
				preLog[11] = *(x+3); 
	        	preLog[12] = *(y+3);
    	    	preLog[13] = *(z+3);

				resultado = dist_retas_reversas(x, y, z);
				preLog[14] = resultado;
				novaEntrada(15, preLog);


	            printf("A distancia entre as duas retas eh: %f\n", resultado);
	
	        }
	        
	        break;
	
	    case DIST_RETA_PLANO:
	        printf("Digite as coordenadas (x, y, z) do vetor diretor do plano e o termo 'd': ");
	        scanf("%f%f%f%f", &x[0], &y[0], &z[0], &d);
			preLog[2] = *x; 
        	preLog[3] = *y;
        	preLog[4] = *z;

	        printf("Informe um ponto da reta (x, y, z): ");
	        scanf("%f%f%f", &x[1], &y[1], &z[1]);
			preLog[5] = *(x+1); 
        	preLog[6] = *(y+1);
        	preLog[7] = *(z+1);

			resultado = dist_reta_plano(x, y, z, d);
			preLog[8] = resultado;
			novaEntrada(9, preLog);

	        printf("A distancia entre a reta e o plano eh: %f\n", resultado);
	
	        break;
	
	    case DIST_PONTO_PLANO:
	        printf("Digite as coordenadas (x, y, z) do vetor diretor do plano e o termo 'd': ");
	        scanf("%f%f%f%f", &x[0], &y[0], &z[0], &d);
			preLog[2] = *x; 
        	preLog[3] = *y;
        	preLog[4] = *z;
        	preLog[5] = *d;

	        printf("Digite as coordenadas (x, y, z) do ponto: ");
	        scanf("%f%f%f", &x[1], &y[1], &z[1]);
			preLog[6] = *(x+1); 
        	preLog[7] = *(y+1);
        	preLog[8] = *(z+1);

        	resultado = dist_ponto_plano(x, y, z, d);
        	preLog[9] = resultado;
        	novaEntrada(10, preLog);

	        printf("A distancia entre o ponto e o plano eh: %f\n", resultado);
	
	        break;
	        
    }

}

int main(int argc, char *argv[]) {
	
    while (1) {
        /* Menu Prim?rio*/
        printf("1 - \t Produtos entre vetores\n"
               "2 - \t Distancias\n"
               "3 - \t Mostrar log\n"
               "Outro -  Sair do programa\n"
               "Digite o numero correspondente a opcao desejada: ");
        clean_stdin();
        switch (getchar()-48) {
        	
	        case PRODUTOS:
	        	preLog[0] = PRODUTOS;
	            menuProdutos();
	            break;
	
	        case DISTANCIAS:
	        	preLog[0] = DISTANCIAS;
	            menuDistancias();
	            break;
	
	        case MOSTRA_LOG:
	            //Show_Log();
	            break;
	    }

        printf("Deseja continuar? (1 - Sim) (Outro - Nao)\n");
        clean_stdin();
        if (getchar() != '1')
            return 0;

        printf("Retornando ao meu principal... \n");
        system("pause");
        system("cls");


    }
    /* Remover? vide sugest?o*/
    fclose(fLog);
    return 0;
    
}
