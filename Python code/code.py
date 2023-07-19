import tkinter as tk
from tkinter import messagebox, simpledialog
import random

def load_words(filename):
    """Завантажує слова з файлу"""
    with open(filename, 'r') as file:
        words = file.read().splitlines()
    return words

def save_words(filename, words):
    """Записує слова у файл"""
    with open(filename, 'w') as file:
        file.write('\n'.join(words))

def save_scores(filename, scores):
    """Записує нік та бали у файл"""
    existing_scores = {}
    try:
        with open(filename, 'r') as file:
            for line in file:
                line = line.strip()
                if ':' in line:
                    name, score = line.split(':')
                    existing_scores[name.strip()] = int(score.strip())
    except FileNotFoundError:
        pass

    with open(filename, 'w') as file:
        for name, score in scores.items():
            if name in existing_scores:
                existing_scores[name] += score
            else:
                existing_scores[name] = score
        for name, score in existing_scores.items():
            file.write(f"{name}: {score}\n")


def get_random_word(words):
    """Вибирає випадкове слово зі списку"""
    return random.choice(words)

def update_display(word, guessed_letters):
    """Оновлює відображення слова з відгаданими буквами"""
    displayed_word = ''
    for letter in word:
        if letter.lower() in guessed_letters:
            displayed_word += letter + ' '
        else:
            displayed_word += '_ '
    return displayed_word.strip()

def guess_letter():
    """Обробляє спробу відгадати букву"""
    global score
    letter = letter_entry.get().lower()
    if len(letter) != 1 or not letter.isalpha():
        messagebox.showwarning("Помилка", "Введіть одну літеру.")
        return

    guessed_letters.append(letter)
    display_text.set(update_display(word_to_guess, guessed_letters))

    if letter.lower() not in word_to_guess:
        global attempts
        attempts -= 1
        attempts_label.config(text=f"Спроби: {attempts}")

        if attempts == 0:
            messagebox.showinfo("Кінець гри", f"Ви програли. Загадане слово: {word_to_guess}")
            save_scores('scores.txt', {player_name: score})
            reset_game()
            return

    if '_' not in display_text.get():
        messagebox.showinfo("Кінець гри", f"Ви виграли! Загадане слово: {word_to_guess}")
        score += 1
        save_scores('scores.txt', {player_name: score})
        reset_game()

    letter_entry.delete(0, tk.END)
    score_label.config(text=f"Гравець: {player_name} | Бали: {score}")

def add_word():
    """Додає нове слово до файлу words.txt"""
    word = simpledialog.askstring("Додати слово", "Введіть нове слово:")
    if word:
        word_list.append(word)
        save_words('words.txt', word_list)
        messagebox.showinfo("Додано", f"Слово '{word}' було додано до списку слів.")

def enter_name():
    """Вводить нік гравця та завантажує останній результат з файлу"""
    global player_name, score
    player_name = simpledialog.askstring("Введіть свій нік", "Як вас звати?")
    if not player_name:
        player_name = "Анонім"

    try:
        with open('scores.txt', 'r') as file:
            scores = {}
            for line in file:
                line = line.strip()
                if ':' in line:
                    name, score = line.split(':')
                    scores[name.strip()] = int(score.strip())
            if player_name in scores:
                score = scores[player_name]
            else:
                score = 0
    except FileNotFoundError:
        score = 0


def reset_game():
    """Скидає стан гри для нової гри"""
    global word_to_guess, guessed_letters, attempts, score
    word_to_guess = get_random_word(word_list)
    guessed_letters = []
    attempts = 6
    score = 0
    display_text.set(update_display(word_to_guess, guessed_letters))
    attempts_label.config(text=f"Спроби: {attempts}")
    score_label.config(text=f"Гравець: {player_name} | Бали: {score}")

def display_scores():
    """Відображає результати гравців з файлу"""
    try:
        with open('scores.txt', 'r') as file:
            scores = file.read()

        scores_window = tk.Toplevel(window)
        scores_window.title("Результати")
        scores_window.geometry(f"{window_width}x{window_height}")

        scores_text = tk.Text(scores_window, font=("Arial", int(window_height * 0.03)))
        scores_text.insert(tk.END, scores)
        scores_text.pack()

    except FileNotFoundError:
        messagebox.showinfo("Результати", "Немає збережених результатів.")


def clear_words_file():
    """Очищає файл words.txt"""
    try:
        with open('words.txt', 'w') as file:
            file.write('')
        messagebox.showinfo("Очищено", "Файл 'words.txt' успішно очищено.")
    except IOError:
        messagebox.showerror("Помилка", "Сталася помилка при очищенні файлу 'words.txt'.")

def clear_scores_file():
    """Очищає файл scores.txt"""
    try:
        with open('scores.txt', 'w') as file:
            file.write('')
        messagebox.showinfo("Очищено", "Файл 'scores.txt' успішно очищено.")
    except IOError:
        messagebox.showerror("Помилка", "Сталася помилка при очищенні файлу 'scores.txt'.")

def display_words():
    """Відображає записані слова з файлу words.txt"""
    try:
        with open('words.txt', 'r') as file:
            words = file.read()

        words_window = tk.Toplevel(window)
        words_window.title("Список слів")
        words_window.geometry(f"{window_width}x{window_height}")

        words_text = tk.Text(words_window, font=("Arial", int(window_height * 0.03)))
        words_text.insert(tk.END, words)
        words_text.pack()

    except FileNotFoundError:
        messagebox.showinfo("Список слів", "Немає записаних слів.")

# ...
# Завантажуємо слова з файлу
word_list = load_words('words.txt')

# Вибираємо випадкове слово для відгадування
word_to_guess = get_random_word(word_list)
guessed_letters = []

# Створюємо вікно
window = tk.Tk()
window.title("Відгадайте слово!")

# Задаємо розмір екрану
screen_width = window.winfo_screenwidth()
screen_height = window.winfo_screenheight()
window_width = int(screen_width * 0.6)
window_height = int(screen_height * 0.6)
window.geometry(f"{window_width}x{window_height}")

# Додаємо стиль для меню
window.option_add('*tearOff', False)  # Вимикаємо відділення пунктів меню

# Створюємо меню
menu = tk.Menu(window)
window.config(menu=menu)

# Додаємо пункти меню "Слова" та "Результати"
word_menu = tk.Menu(menu)
menu.add_cascade(label="Слова", menu=word_menu)
score_menu = tk.Menu(menu)
menu.add_cascade(label="Результати", menu=score_menu)


# Задаємо стиль для меню та пунктів меню
window.configure(menu=menu, background='lightgray')
menu.configure(background='lightgray')
word_menu.configure(background='lightgray')
score_menu.configure(background='lightgray')

# Додаємо команди до меню "Слова"
word_menu.add_command(label="Додати слово", command=add_word)
word_menu.add_command(label="Очистити words.txt", command=clear_words_file)
word_menu.add_command(label="Показати слова", command=display_words)

# Додаємо команди до меню "Результати"
score_menu.add_command(label="Показати результати", command=display_scores)
score_menu.add_command(label="Очистити scores.txt", command=clear_scores_file)

# Додаємо елементи у вікно
title_label = tk.Label(window, text="Відгадайте слово з 6 спроб:", font=("Arial", int(window_height * 0.03)))
title_label.pack(pady=int(window_height * 0.02))

display_text = tk.StringVar()
display_text.set(update_display(word_to_guess, guessed_letters))
display_label = tk.Label(window, textvariable=display_text, font=("Arial", int(window_height * 0.05)))
display_label.pack()

letter_label = tk.Label(window, text="Введіть букву:", font=("Arial", int(window_height * 0.03)))
letter_label.pack(pady=int(window_height * 0.02))

letter_entry = tk.Entry(window, font=("Arial", int(window_height * 0.03)))
letter_entry.pack()

guess_button = tk.Button(window, text="Відгадати", font=("Arial", int(window_height * 0.03)), command=guess_letter)
guess_button.pack(pady=int(window_height * 0.02))

attempts = 6
attempts_label = tk.Label(window, text=f"Спроби: {attempts}", font=("Arial", int(window_height * 0.03)))
attempts_label.pack()

# Вводимо нік гравця
player_name = None
score = 0
enter_name()

# Відображення результату гравця
score_label = tk.Label(window, text=f"Гравець: {player_name} | Бали: {score}", font=("Arial", int(window_height * 0.03)))
score_label.pack()

# Додаємо кнопку "Вихід"
exit_button = tk.Button(window, text="Вихід", font=("Arial", int(window_height * 0.03)), command=window.quit)
exit_button.pack(pady=int(window_height * 0.02))

# Запускаємо цикл головного вікна
window.mainloop()
