#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

#define FILE_ERROR_MESSAGE "Помилка завантаження файлу!\n"

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
        printf(FILE_ERROR_MESSAGE);
        return;
    }
    printf("\nРекорди:\n");
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
        printf(FILE_ERROR_MESSAGE);
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
        printf(FILE_ERROR_MESSAGE);
        return;
    }
        printf("\nСлова:\n");
    char word[256];
    while (fgets(word, sizeof(word), wordFile))
    {
        printf("%s", word);
    }
    fclose(wordFile);
}

User AuthenticateUser()
{
    User user;

    printf("Enter username: ");
    scanf("%s", user.username);

    return user;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, ".1251");
    srand(time(NULL));

    FILE *file;
    if ((file = fopen("words.txt", "r")) == NULL)
    {
        printf(FILE_ERROR_MESSAGE);
        return 0;
    }
    char words[256][256];
    int j = 0;

    while (fgets(words[j], 256, file) != NULL)
    {
        sscanf(words[j], "%s", words[j]);
        j++;
    }
    fclose(file);
    printf("Кількість зчитаних з файлу слів: %d", j);
    
    int key;
    int option;
    char newWord[30];
    
    User user; 
    bool exitGame = false;
    while (!exitGame)
    {
        ShowMenu();
        scanf("%i", &option);

    switch (option) 
    {
        case 1:

            while (key != 27) {
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
                key = getch();
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
                scanf("%s", newWord);
                fprintf(file, "%s\n", newWord);
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
