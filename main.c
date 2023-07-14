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
    char username[30];
    int score;
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
    FILE *scoreFile;
    scoreFile = fopen("scores.txt", "r");
    if (scoreFile == NULL)
    {
        printf("Помилка відкриття файлу!\n");
        return;
    }
    printf("\Рекорди:\n");
    char line[256];
    while (fgets(line, sizeof(line), scoreFile))
    {
        printf("%s", line);
    }

    fclose(scoreFile);
}

void UpdateScore(User user)
{
    FILE *scoreFile;
    scoreFile = fopen("scores.txt", "a");
    if (scoreFile == NULL)
    {
        printf("Помилка відкриття файлу!\n");
        return;
    }

    fprintf(scoreFile, "Ім'я: %s, Рекорд: %d\n", user.username, user.score);
    fclose(scoreFile);
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

    ShowMenu();

    switch (n)
    {
        case 1:
            //
            break;
        case 2:
            system("cls");
            printf("Комп’ютер генерує випадкове слово та відображає шифр слова.\n");
            printf("Якщо ви вгадали літеру, на екрані буде відображатися шифр слова з цією літерою\n");
            printf("Якщо ви вгадаєте ціле слово, ви виграєте гру\nGood Luck!");
            break;
        case 3:
            system("cls");
            printf("'Вгадай слово' - це інтелектуальна гра, створена у розважальному форматі. \n");
            printf("Водночас цей жанр вимагає від гравця використання логіки та інтуїції. \n");
            printf("Тема є досить важливою, оскільки вона покращує важливі якості та навички в простому для гри форматі.");
            break;
        case 4:
            //
            break;
        case 5:
           //
            break;
        case 6:
            //
            break;
        case 7:
            exit(0);
            break;
    }
    return 0;
}
