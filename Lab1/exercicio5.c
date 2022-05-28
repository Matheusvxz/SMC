#include <stdio.h>

int values[] = {6, 7, 8, 9, 8, 7, 8, 9, 8, 9, 7, 8, 9, 5, 9, 8, 7, 8, 7, 8, 6, 7, 8, 9, 3, 9,
8, 7, 8, 7, 7, 8, 9, 8, 9, 8, 9, 7, 8, 9, 6, 7, 8, 7, 8, 7, 9, 8, 9, 2, 7, 8,
9, 8, 9, 8, 9, 7, 5, 3, 5, 6, 7, 2, 5, 3, 9, 4, 6, 4, 7, 8, 9, 6, 8, 7, 8, 9,
7, 8, 7, 4, 4, 2, 5, 3, 8, 7, 5, 6, 4, 5, 6, 1, 6, 5, 7, 8, 7};

// int values[] = {2,2,2,3,3};

float mean(int *num, int length);
void makeHistogram(int *num, int length);
void printData(int *num, int length);

int main(int argc, char const *argv[])
{

    int size = sizeof values / sizeof values[0];

    printData(values, size);

    printf("\nMedia dos valores: %.2f\n\n", mean(values, size));
    makeHistogram(values, size);

    return 0;
}

float mean(int *num, int length) {
    int accu = 0;
    
    for(int i = 0; i < length; i++) {
        accu += *(num + i);
    }
    
    return (float)(accu / length);
}

void makeHistogram(int *num, int length) {
    printf("\tHistograma\n\n");

    int matriz[10][2];
    for(int i = 0; i < 10; i++) {
        matriz[i][0] = i;
        matriz[i][1] = 0;
    }

    for(int i = 0; i < length; i++) {
        matriz[*(num + i)][1]++;
    }

    // printf("O numero %d apareceu %d vezes.\n", matriz[3][0], matriz[3][1]);
    for(int i = 0; i < 10; i++) {
        printf("O numero %d apareceu %d vezes.\n", matriz[i][0], matriz[i][1]);
    };
}

void printData(int *num, int length) {
    int divs = 3;
    printf("Conjunto de dados:\n   [");


    for(int i = 0; i < length; i++) {
        if(i % (length / 3) == 0 && i != 0) {
            printf("\n");
        }
        if(i == length - 1) {
            printf(" %d", *num);
        } else {
            printf(" %d,", *(num + i));
        }
    }
    printf(" ]\n");
}