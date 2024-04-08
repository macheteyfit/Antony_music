#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Структура для хранения информации о песне
struct Song {
    string title;
    string author;
    string lyrics;
};

// Функция для добавления текста песни
void addSong(vector<Song>& cartoteka) {
    Song newSong;
    cout << "Введите название песни: ";
    getline(cin >> ws, newSong.title);
    cout << "Введите имя автора: ";
    getline(cin >> ws, newSong.author);
    cout << "Введите текст песни (для окончания введите пустую строку):\n";
    string line;
    while (getline(cin, line) && !line.empty()) {
        newSong.lyrics += line + "\n";
    }
    cartoteka.push_back(newSong);
    cout << "Песня успешно добавлена!\n";
}

// Функция для отображения информации о песне
void displaySong(const Song& song) {
    cout << "Название: " << song.title << endl;
    cout << "Автор: " << song.author << endl;
    cout << "Текст:\n" << song.lyrics << endl;
}

// Функция для удаления песни
void deleteSong(vector<Song>& cartoteka, const string& title) {
    auto it = find_if(cartoteka.begin(), cartoteka.end(), [&](const Song& s) {
        return s.title == title;
        });
    if (it != cartoteka.end()) {
        cartoteka.erase(it);
        cout << "Песня успешно удалена!\n";
    }
    else {
        cout << "Песня с указанным названием не найдена.\n";
    }
}

// Функция для поиска песен по автору
void searchByAuthor(const vector<Song>& cartoteka, const string& author) {
    bool found = false;
    for (const auto& song : cartoteka) {
        if (song.author == author) {
            displaySong(song);
            found = true;
        }
    }
    if (!found) {
        cout << "Песен данного автора не найдено.\n";
    }
}

// Функция для поиска песен, содержащих заданное слово
void searchByWord(const vector<Song>& cartoteka, const string& word) {
    bool found = false;
    for (const auto& song : cartoteka) {
        if (song.lyrics.find(word) != string::npos) {
            displaySong(song);
            found = true;
        }
    }
    if (!found) {
        cout << "Песен с данным словом не найдено.\n";
    }
}

// Функция для сохранения каталога песен в файл
void saveCartoteka(const vector<Song>& cartoteka, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& song : cartoteka) {
            file << "Название: " << song.title << endl;
            file << "Автор: " << song.author << endl;
            file << "Текст:\n" << song.lyrics << endl;
            file << endl;
        }
        cout << "Каталог сохранен в файле: " << filename << endl;
    }
    else {
        cout << "Ошибка сохранения каталога в файл.\n";
    }
}

int main() {
    vector<Song> cartoteka;
    string filename = "cartoteka.txt"; // Имя файла для сохранения каталога

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Добавить текст песни\n";
        cout << "2. Удалить текст песни\n";
        cout << "3. Отобразить текст песни\n";
        cout << "4. Сохранить каталог в файл\n";
        cout << "5. Поиск песен по автору\n";
        cout << "6. Поиск песен по слову\n";
        cout << "7. Выйти\n";
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore(); // очистка буфера ввода

        switch (choice) {
        case 1:
            addSong(cartoteka);
            break;
        case 2: {
            string title;
            cout << "Введите название песни для удаления: ";
            getline(cin >> ws, title);
            deleteSong(cartoteka, title);
            break;
        }
        case 3: {
            string title;
            cout << "Введите название песни для отображения: ";
            getline(cin >> ws, title);
            auto it = find_if(cartoteka.begin(), cartoteka.end(), [&](const Song& s) {
                return s.title == title;
                });
            if (it != cartoteka.end()) {
                displaySong(*it);
            }
            else {
                cout << "Песня с указанным названием не найдена.\n";
            }
            break;
        }
        case 4:
            saveCartoteka(cartoteka, filename);
            break;
        case 5: {
            string author;
            cout << "Введите имя автора для поиска: ";
            getline(cin >> ws, author);
            searchByAuthor(cartoteka, author);
            break;
        }
        case 6: {
            string word;
            cout << "Введите слово для поиска: ";
            getline(cin >> ws, word);
            searchByWord(cartoteka, word);
            break;
        }
        case 7:
            cout << "До свидания!\n";
            break;
        default:
            cout << "Некорректный ввод. Попробуйте снова.\n";
        }
    } while (choice != 7);

    return 0;
}
