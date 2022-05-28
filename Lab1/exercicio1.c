/**
 * @file exercicio1.c
 * @author Matheus Vinicius (mvr.nascimento@hotmail.com)
 * @brief Calculate distance and consume of a car
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>

float calculateDistance(int time, int vel);
float calculateConsume(float distance, float consume);

int main(int argc, char const *argv[])
{
    int time;
    float velMedia, conMedio;
    // Get informations
    for(int i = 0; i < 30; i++) {
        printf("\n");
    }

    // Consumo medio
    printf("Digite o consumo medio do automovel (km/L): ");
    scanf("%f", &conMedio);

    // Tempo gasto
    printf("Digite o tempo gasto na viagem (em minutos): ");
    scanf("%d", &time);

    printf("Digite a velocidade media do automovel (km/h): ");
    scanf("%f", &velMedia);

    float distance = calculateDistance(time, velMedia);
    float consume = calculateConsume(distance, conMedio);


    printf("\nA distancia percorrida foi de %.2fkm com um consumo de %.2fL\n", distance, consume);
    return 0;
}


float calculateDistance(int time, int vel) {
    return ((time / (float)60) * vel);
}

float calculateConsume(float distance, float consume) {
    return distance / consume;
}