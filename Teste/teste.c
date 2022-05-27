#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int aleatorio(int a,int b)  {
	return (a+rand()%(b-a+1));
}

int main() {
	int preco[15];
	int compra[2000];
	int venda[15];
	int clientes,i,j,maior,dmaior,menor,dmenor,v,pmaior,pmenor;
	float total,media; 
	
	srand((unsigned) time(NULL));
	clientes = aleatorio(1000,2000);
	
	for(j=0;j<15;j++)  {
		preco[j] = aleatorio(10,99);
		venda[j] = 0;
	}
	
	for(i=0;i<clientes;i++)  {
		v = aleatorio(0,14);
		compra[i] = v;
		venda[v]++;
	}
	
	total = 0;
	for(i=0;i<clientes;i++) {
		total = total + preco[compra[i]];
	}
	media = total/clientes;
	
	maior = -1;
	menor = 999999;
	for(i=0;i<15;i++)  {
		if(maior < venda[i]) {
			maior = venda[i];
		}
		if(menor > venda[i]) {
			menor = venda[i];
		}
	}
	
	for(j=0;j<15;j++) {
		if(venda[j] == maior)
			dmaior = j;
		if(venda[j] == menor)
			dmenor = j;
	}
	
	pmaior = preco[dmaior];
	pmenor = preco[dmenor];
	
	printf("Numero de clientes do dia:........ %d\n",clientes);
	printf("Valor total das vendas:........... %.0f\n",total);
	printf("Produto mais vendido:............. %d Preco:..... %d\n",dmaior,pmaior);
	printf("Produto menos vendido:............ %d Preco:..... %d\n",dmenor,pmenor);
	printf("O valor medio das vendas:......... %.0f\n",media);
	
	return 0;
}