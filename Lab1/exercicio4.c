/**
 * @file exercicio4.c
 * @author Matheus Vinicius (mvr.nascimento@hotmail.com)
 * @brief Converter a date format to another
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool bissexto(int a);
int mes(int m, int a);
bool validateDate(int d, int m, int y);


int main(int argc, char const *argv[])
{
    char *strMonths[] = {
        "janeiro", "fevereiro", "março", 
        "abril", "maio", "junho", 
        "julho", "agosto", "setembro", 
        "outubro", "novembro", "dezembro"
    };

    char inputDate[15];
    int day, month, year;
    printf("Digite a data que deseja converter (DD/MM/YYYY): ");
    scanf("%2d/%2d/%4d", &day, &month, &year);

    if(!validateDate(day, month, year)) {
        return 0;
    }

    printf("Data formatada:\n");
    printf("%02d de %s de %04d\n", day, strMonths[month - 1], year);
    
    return 0;
}

bool bissexto(int a)  {
	// if( a%400 == 0 || a%4 == 0)  {
	// 	return true;
	// }
	// return false;
    if(a % 100 == 0) {   // Test if the year ends with 00
        if(a % 400 == 0) {
            return true;
        } else {
            return false;
        }
    } else {
        if(a % 4 == 0) {
            return true;
        } else {
            return false;
        }
    }
}

int mes(int m, int a)  {
	int s = 0;
	switch(m) {
		case(12):
            s = 31;
            break;
		case(11):
            s = 30;
            break;
		case(10):
            s = 31;
            break;
		case(9):
            s = 30;
            break;
		case(8):
            s = 31;
            break;
		case(7):
            s = 31;
            break;
		case(6):
            s = 30;
            break;
		case(5):
            s = 31;
            break;
		case(4):
            s = 30;
            break;
		case(3):
            s = 31;
            break;
		case(2): 
			if(bissexto(a))  {
				s = 29;
			} else  {
				s = 28;
			}
            break;
		case(1):
            s = 31;
            break;
	}
	return s;	
}

bool validateDate(int d, int m, int y) {
    char *error;
    error = malloc(100);
    bool hasErrors = false;

    if(y < 1) {
        strcat(error, "Ano invalido\n");
        hasErrors = true;
    }
    if(m < 1 || m > 12) {
        strcat(error, "Mes invalido\n");
        hasErrors = true;
    }

    int lastDayOfMonth = mes(m, y);

    if(d < 1 || d > lastDayOfMonth) {
        strcat(error, "Dia invalido\n");
        hasErrors = true;
    }

    if(hasErrors) {
        printf("%s", error);
        return false;
    }
    return true;
}