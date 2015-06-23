//ALUNOS: Marcelo Zschornack, Luiza Beltrame 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

double escritaSequencial(int tam, char letra, int n);
double leituraSequencial(int tam, char letra, int n);
double escritaAleatoria(int tam, int n);
double leituraAleatoria(int tam, int n);

int pot(int i, int j);
double desvioPadrao(double media, int n);

double vetor[100];
float dif_timeT;

int main(){
	int i, escolha, TAM, repeticoes;
	char c;
	double media;
	
	printf("Teste de Benchmark\n");
	printf("\nDigite 1 para o teste de leitura sequencial");
	printf("\nDigite 2 para o teste de escrita sequencial");
	printf("\nDigite 3 para o teste de leitura aleatória");
	printf("\nDigite 4 para o teste de escrita aleatória");
	
	printf("\n\nOpção desejada: ");
	scanf("%d", &escolha);
	
	switch(escolha){
		case 1: 
			printf("\nDigite o tamanho do arquivo(somente números): ");
			scanf("%d", &TAM);
	
			printf("\nDigite a ordem de grandeza(K, M ou G): ");
			scanf("\n%c", &c);
			c = toupper(c);
			
			printf("\nDigite o número de repetições: ");
			scanf("%d", &repeticoes);
			
			media = leituraSequencial(TAM, c, repeticoes);
			printf("\nThroughput médio p/ leitura sequencial foi de %f MiB/s", media);
			printf("\nDesvio Padrão: %f", desvioPadrao(media, repeticoes));
			printf("\nTempo total de execução: %f s", dif_timeT/1000000);
			break;
		case 2: 
			printf("\nDigite o tamanho do arquivo(somente números): ");
			scanf("%d", &TAM);
	
			printf("\nDigite a ordem de grandeza(K, M ou G): ");
			scanf("\n%c", &c);
			c = toupper(c);
			
			printf("\nDigite o número de repetições: ");
			scanf("%d", &repeticoes);
			
			media = escritaSequencial(TAM, c, repeticoes);
			printf("\nThroughput médio p/ escrita sequencial foi de %f MiB/s", media);
			printf("\nDesvio Padrão: %f", desvioPadrao(media, repeticoes));
			printf("\nTempo total de execução: %f s", dif_timeT/1000000);
			break;
		case 3:
			printf("\nDigite o número de repetições: ");
			scanf("%d", &repeticoes);
			
			for(i=0; i<=5; i++){
				media = leituraAleatoria(i, repeticoes);
				printf("\nThroughput médio p/ leitura aleatória p/ blocos de %d Kb foi de %f MiB/s", pot(2,i), media);
				printf("\nDesvio Padrão: %f", desvioPadrao(media, repeticoes));
				printf("\nTempo total de execução: %f s", dif_timeT/1000000);
			} break;
		case 4: 
			printf("\nDigite o número de repetições: ");
			scanf("%d", &repeticoes);
		
			for(i=0; i<=5; i++){
				media = escritaAleatoria(i, repeticoes);
				printf("\nThroughput médio p/ escrita aleatória p/ blocos de %d Kb foi de %f MiB/s",  pot(2,i), media);
				printf("\nDesvio Padrão: %f", desvioPadrao(media, repeticoes));
				printf("\nTempo total de execução: %f s", dif_timeT/1000000);
			} break;
		
	}	
	
	return 0;
}

double escritaSequencial(int tam, char letra, int n){
	int i, j, num=1;
	FILE *arq;
	clock_t inicio, fim, inicioT, fimT; 
	double dif_time, media;
	
	inicioT = clock()/(CLOCKS_PER_SEC/1000000);
	
	media = 0;
	j = 0;
	
	if(letra == 'K')
		tam = tam*1024;
	else if(letra == 'M')
			tam = tam*1048576;
		 else if(letra == 'G')
				tam = tam*1073741824;
	
	while(j < n){
		inicio = clock()/(CLOCKS_PER_SEC/1000000);
		arq = fopen("ARQUIVO", "w");
	
		for(i=1; i<=tam; i++){
			fprintf(arq, "%d", num);			
		}		
	
		fclose(arq);
		fim = clock()/(CLOCKS_PER_SEC/1000000);
		dif_time = fim - inicio;
		vetor[j] = (tam/(dif_time/1000000))/1048576;
		media = media + dif_time;
		j++;
	}
	
	fimT = clock()/(CLOCKS_PER_SEC/1000000);
	dif_timeT = fimT - inicioT;
	
	return (tam/((media/n)/1000000))/1048576;
	
}

double leituraSequencial(int tam, char letra, int n){
	int i, j, num=1;
	FILE *arq;	
	clock_t inicio, fim, inicioT, fimT;
	double dif_time, media;
	
	inicioT = clock()/(CLOCKS_PER_SEC/1000000);
	
	media = 0;
	j = 0;
	
	if(letra == 'K')
		tam = tam*1024;
	else if(letra == 'M')
			tam = tam*1048576;
		 else if(letra == 'G')
				tam = tam*1073741824;
	
	arq = fopen("ARQUIVO", "w");
	
	for(i=1; i<=tam; i++){
		fprintf(arq, "%d", num);			
	}		
	
	fclose(arq);
				
	while(j < n){
		inicio = clock()/(CLOCKS_PER_SEC/1000000);
		arq = fopen("ARQUIVO", "r");
	
		while(!feof(arq)){
			fscanf(arq, "%d", &num);
		}
	
		fclose(arq);
		fim = clock()/(CLOCKS_PER_SEC/1000000);
		dif_time = fim - inicio;
		vetor[j] = (tam/(dif_time/1000000))/1048576;
		media = media + dif_time;
		j++;	
	}
	
	fimT = clock()/(CLOCKS_PER_SEC/1000000);
	dif_timeT = fimT - inicioT;
	
	return (tam/((media/n)/1000000))/1048576;
}

double escritaAleatoria(int tam, int n){
	int i, j, num=1;
	FILE *arq;
	clock_t inicio, fim, inicioT, fimT;
	double dif_time, media;
	
	inicioT = clock()/(CLOCKS_PER_SEC/1000000);
	
	j = 0;
	media = 0;
	tam = 1024*(pot(2,tam));
	
	while(j < n){
		arq = fopen("ARQUIVO", "w");
			//cria um arquivo de 4Mb para teste 
		for(i=1; i<=4194304; i++){
			fprintf(arq, "%d", num);			
		}	
		fclose(arq);
	
		inicio = clock()/(CLOCKS_PER_SEC/1000000);
	
		arq = fopen("ARQUIVO", "a");
		rewind(arq);
		fseek(arq, rand()%4194303, SEEK_SET);
		for(i=1; i<=tam; i++){
			fprintf(arq, "%d", num);
		}
		fclose(arq);
		fim = clock()/(CLOCKS_PER_SEC/1000000);
		dif_time = fim - inicio;
		vetor[j] = (tam/(dif_time/1000000))/1048576;
		media = media + dif_time;
		j++;
	}
	fimT = clock()/(CLOCKS_PER_SEC/1000000);
	dif_timeT = fimT - inicioT;
	
	return (tam/((media/n)/1000000))/1048576;
}

double leituraAleatoria(int tam, int n){
	int i, j, num=1;
	FILE *arq;
	clock_t inicio, fim, inicioT, fimT;
	double dif_time, media;
	
	inicioT = clock()/(CLOCKS_PER_SEC/1000000);
	
	j = 0;
	media = 0;
	tam = 1024*(pot(2,tam));
	
	while(j < n){
		arq = fopen("ARQUIVO", "w");
			//cria um arquivo de 4Mb para teste 
		for(i=1; i<=4194304; i++){
			fprintf(arq, "%d", num);			
		}	
		fclose(arq);
	
		inicio = clock()/(CLOCKS_PER_SEC/1000000);
	
		arq = fopen("ARQUIVO", "a");
		rewind(arq);
		fseek(arq, rand()%4194304, SEEK_SET);
		for(i=1; i<=tam; i++){
			fscanf(arq, "%d", &num);
		}
		fclose(arq);
		fim = clock()/(CLOCKS_PER_SEC/1000000);
		dif_time = fim - inicio;
		vetor[j] = (tam/(dif_time/1000000))/1048576;
		media = media + dif_time;
		j++;
	}
	fimT = clock()/(CLOCKS_PER_SEC/1000000);
	dif_timeT = fimT - inicioT;
	
	return (tam/((media/n)/1000000))/1048576;
}

int pot(int i, int j){
	int a, prov=1;
	
	if(j==0)
		return 1;
	else
		for(a=1; a<=j; a++){
			prov = prov * i;
		} return prov;	
	
}

double desvioPadrao(double media, int n){
	int i; 
	double result=0;
	
	for(i=0; i<n; i++){
		result = result + (vetor[i]-media)*(vetor[i]-media);	
	}
	
	result = result/(n-1);
	
	return pow(result, 0.5);
}
