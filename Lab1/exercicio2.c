/**
 * @file exercicio2.c
 * @author Matheus Vinicius (mvr.nascimento@hotmail.com)
 * @brief Converter a text to uppercase end for lowercase
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <ctype.h>

int main(int argc, char const *argv[])
{
    char array[100];
    char lower[100];
    char upper[100];

    printf("Digite o texto:\n");

    scanf("%99[^\n]", array);
    printf("\n");

    printf("Texto original:\n\t\"%s\"\n", array);
    for(int i = 0; i < 100; i++) {
        lower[i] = tolower(array[i]);
        upper[i] = toupper(array[i]);
    }
    printf("Texto minusculo:\n\t\"%s\"\n", lower);
    printf("Texto maiusculo:\n\t\"%s\"\n", upper);

    return 0;
}
