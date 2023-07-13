#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

typedef struct {

} User;

void ShowMenu()
{
    printf("\n-------- Вгадай слово --------\n");
    printf("1 - Нова гра\n");
    printf("2 - Правила\n");
    printf("3 - Інформація\n");
    printf("4 - Додати нове слово\n");
    printf("5 - Рахунок\n");
    printf("6 - Переглянути слова у файлі\n");
    printf("7 - Вийти\n");
    printf("-----------------------------\n");
}

void printGuesssedWord()
{

}

void drawMan()
{

}

void ShowScores()
{

}

void UpdateScore()
{

}

void ShowWords()
{

}

User AuthenticateUser()
{

}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, ".1251");

    int n;

    m:
    ShowMenu();

    switch (n)
    {
        case 1:
            //
            goto m;
            break;
        case 2:
            //
            goto m;
            break;
        case 3:
            //
            goto m;
            break;
        case 4:
            //
            goto m;
            break;
        case 5:
           //
            goto m;
            break;
        case 6:
            //
            goto m;
            break;
        case 7:
            exit(0);
            break;
    }
    return 0;
}
