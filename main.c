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
    srand(time(NULL));

    int s;
    int n;
    char wor[30];
    
    User user; // Declare a User structure to store authenticated user
    bool exitGame = false;
    while (!exitGame)
    {
        ShowMenu();
        scanf("%i", &n);

    switch (n) 
    {
        case 1:

            while (s != 27) {
                char alreadyUsedLetters[100] = "";
                char *totalWord = words[rand() % j];
                int *wordStatus = (int *) malloc(strlen(totalWord) * sizeof(int));
                memset(wordStatus, 0, sizeof(int) * strlen(totalWord));
                char c;
                int lives = 6;
                bool guessed = true;
                int score = 0;

                while (lives > 0) {
                    for (int i = 0; i < strlen(totalWord); i++) {
                        if (c == totalWord[i]) {
                            wordStatus[i] = 1;
                            guessed = true;
                        }
                    }

                    if (!guessed) {
                        lives--;
                    }
                    drawMan(lives + 1);
                    printGuesssedWord(totalWord, wordStatus);
                    if (victoryStatus(wordStatus, strlen(totalWord))) {
                        printf("\nПЕРЕМОГА! :)\nЗагадане слово: %s \n", totalWord);
                        score += 10;
                        break;
                    }

                    printf("\nКількісь спроб: %d\n", lives);
                    if (lives > 0) {
                        printf("Введіть букву: ");
                        c = getchar();
                        scanf("%c", &c);

                        if (strchr(alreadyUsedLetters, c)) {
                            printf("Ви вже вводили цю букву! Спробуйте ще раз: ");
                            c = getchar();
                            scanf("%c", &c);
                        }

                        if (!strchr(alreadyUsedLetters, c))
                            alreadyUsedLetters[strlen(alreadyUsedLetters)] = c;
                    }

                    system("cls");
                    guessed = false;
                }

                if (lives == 0) {
                    printf("\nВИ ПРОГРАЛИ! :( \nЗагадане слово: %s\n", totalWord);
                }
                printf("Ваша оцінка: %d\n", score);
                user.score = score; // Update the score for the authenticated user
                UpdateScore(user); // Update the score for the authenticated user
                c = 0;
                alreadyUsedLetters[0] = '\0';
                printf("Для продовження натисніть будь-яку клавішу, або ESC для виходу...\n");
                s = getch();
            }
            return 0;
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
           system("cls");
            ShowScores();
            break;
        case 6:
            system("cls");
            ShowWords();
            break;
        case 7:
            exit(0);
            break;
    }
    }
    return 0;
}
