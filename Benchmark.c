//ALUNOS: Marcelo Zschornack, Luiza Beltrame 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void criarArquivo(int tam, char letra);

int main(){
	int TAM, n=0, repeticoes;
	char c;
	
	printf("Tamanhos de arquivos: \n"); 
	printf("	1k/2k/4k/8k/16k/32k/64k/128k/256k/512k\n");
	printf("	1M/2M/4M/8M/16M/32M/64M/128M/256M/512M\n");
	printf("	1G/2G/4G/8G\n");
	
	printf("\n Digite o tamanho do arquivo(somente números): ");
	scanf("%d", &TAM);
	
	printf("\n Digite a ordem de grandeza(K, M ou G): ");
	scanf("\n%c", &c);
	c = toupper(c);
	
	printf("\n Digite o número de repetições: ");
	scanf("%d", &repeticoes);	
	
	while (n < repeticoes){
		criarArquivo(TAM, c);
		n++;
	}
	
	return 0;
}

void criarArquivo(int tam, char letra){
	int i, num=1;
	FILE *arq;
	clock_t inicio, fim; 
	double dif_time;
	
	if(letra == 'K')
		tam = tam*1024;
	else if(letra == 'M')
			tam = tam*1048576;
		 else if(letra == 'G')
				tam = tam*1073741824;
	
	inicio = clock()/(CLOCKS_PER_SEC/1000);
	arq = fopen("ARQUIVO", "w");
	
	for(i=1; i<=tam; i++){
		fprintf(arq, "%d", num);			
	}		
	
	fclose(arq);
	fim = clock()/(CLOCKS_PER_SEC/1000);
	dif_time = fim - inicio;
	
	printf("\nTempo de execução foi de %0.1f ms", dif_time);
	
	remove("Arquivo");
	
}
