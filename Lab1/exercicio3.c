/**
 * @file exercicio3.c
 * @author Matheus Vinicius (mvr.nascimento@hotmail.com)
 * @brief Calculate salary of workers and classify them
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct
{
    char name[20];
    float faturamento;
    int class;
} Vendedor;

int aleatorio(int a,int b);
float calculateCommission(float value);

int main(int argc, char const *argv[])
{
    char *categories[] = {
        "R$ 500,00 a R$ 599,00",
        "R$ 600,00 a R$ 699,00",
        "R$ 700,00 a R$ 799,00",
        "R$ 800,00 a R$ 899,00",
        "R$ 900,00 a R$ 999,00",
        "R$ 1000,00 a R$ 1199,00",
        "R$ 1200,00 a R$ 1299,00",
        "R$ 1300,00 ou mais"
    };
    int faixas[] = {0, 0, 0, 0, 0, 0, 0, 0};

    Vendedor vendedores[20];
    srand(time(NULL));

    for(int i = 0; i < 20; i++) {
        sprintf(vendedores[i].name, "Vendedor %d", (i + 1));
        vendedores[i].faturamento = aleatorio(2000, 10000);
    }

    for(int i = 0; i < 20; i++) {
        char *name = vendedores[i].name;
        float fat = vendedores[i].faturamento;

        printf("Funcionario: %15s | Faturamento: %06.2f\n", name, fat);
        int class = (((int)calculateCommission(fat) / 100) - 5);
        
        
        if(class < 5) {
            faixas[class]++;
        } else if(class >= 5 && class < 7) {
            faixas[5]++;
        } else if(class == 7) {
            faixas[6]++;
        } else if(class >= 8) {
            faixas[7]++;
        }
    }

    printf("\n\nEstatisticas\n");

    for(int i = 0; i < 8; i++) {
        printf("%d trabalhadores ganharam %s por semana\n", faixas[i], categories[i]);
    }

    return 0;
}

int aleatorio(int a,int b)  {
	return (a+rand()%(b-a+1));
}

float calculateCommission(float value) {
    return (500 + value*0.09);
}