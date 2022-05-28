#include <stdio.h>
#include <string.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char firstName[30];
    char surName[50];
    Date birthdate;
    char role[30];
    float baseSalary;
} Employee;

void paymentRaise(Employee *emp, float raise);
void showInfo(Employee emp);

int main(int argc, char const *argv[])
{
    /* code */
    Date birthday = {20, 2, 1979};
    Employee emp = {"Jose", "da Silva Braga", birthday, "Desenvolvedor", 3534.0};

    showInfo(emp);
    paymentRaise(&emp, 0.1);
    showInfo(emp);
    return 0;
}

void paymentRaise(Employee *emp, float raise) {
    emp->baseSalary = emp->baseSalary * (1.0 + raise);
}

void showInfo(Employee emp) {
    
    printf("\033[0m╔════════════════════════════════════════════════════════════════════════╗\n");
    printf("\033[0m║                          \033[2mFICHA DO FUNCIONÁRIO\033[0m                          ║\n");
    printf("\033[0m║                                                                        ║\n");

    printf("\033[0m║  Nome: ");
    printf("\033[31m%s", emp.firstName);
    for(int i = 0; i < 30 - strlen(emp.firstName); i++) {
        printf(" ");
    }
    printf("\033[0m  Data de nascimento: \033[31m%02d/%02d/%04d", emp.birthdate.day, emp.birthdate.month, emp.birthdate.year);
    printf("\033[0m  ║\n");

    printf("\033[0m║  Sobrenome: ");
    printf("\033[31m%s", emp.surName);
    for(int i = 0; i < 59 - strlen(emp.surName); i++) {
        printf(" ");
    }
    printf("\033[0m║\n");

    printf("\033[0m║  Cargo: ");
    printf("\033[31m%s", emp.role);
    for(int i = 0; i < 30 - strlen(emp.role); i++) {
        printf(" ");
    }
    printf("\033[0m  Salário base: ");
    char number[10];
    sprintf(number, "%d", (int)emp.baseSalary);
    printf("\033[31mR$%04.2f", emp.baseSalary);
    for(int i = 0; i < 10 - strlen(number); i++) {
        printf(" ");
    }
    printf("\033[0m  ║\n");

    printf("\033[0m║                                                                        ║\n");
    printf("\033[0m╚════════════════════════════════════════════════════════════════════════╝\n");
    // printf("\033[31mred text\n");
}