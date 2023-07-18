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

void printGuesssedWord(char *word, int *status)
{
 printf("\n");
  for (int i = 0; i < strlen(word); i++)
    {
        if (status[i] == 1)
        {
            printf("%c ", word[i]);
        }
        else
        {
            printf("_ ");
        }
    }  
}

bool victoryStatus(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == 0)
            return false;
    }
    return true;
}

void drawMan(int lives)
{
    char *body[] = {" ", "  0", "  0\n  |", "  0\n /|", "  0\n /|\\", "  0\n /|\\\n /", "  0\n /|\\\n / \\"};
    int b = 7;
    if (lives > 0)
        printf("%s\n", body[b - lives]);
    b++;
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
    FILE *wordFile;
    wordFile = fopen("words.txt", "r");
    if (wordFile == NULL)
    {
        printf("No words found!\n");
        return;
    }
        printf("\nWords:\n");
    char word[256];
    while (fgets(word, sizeof(word), wordFile))
    {
        printf("%s", word);
    }
    fclose(wordFile);
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
            printf("Введіть слово, яке хочете додати до файлу: \n");
            file = fopen("words.txt", "a");
            if (file != NULL) {
                scanf("%s", wor);
                fprintf(file, "%s\n", wor);
            }
            fclose(file);
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
