#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    // Categories
    string fruits[]      = {"apple", "banana", "mango", "orange", "grape"};
    string animals[]     = {"elephant", "tiger", "lion", "giraffe", "zebra"};
    string countries[]   = {"rwanda", "kenya", "france", "brazil", "japan"};

    int fruitsCount = sizeof(fruits) / sizeof(fruits[0]);
    int animalsCount = sizeof(animals) / sizeof(animals[0]);
    int countriesCount = sizeof(countries) / sizeof(countries[0]);

    cout << "=== Word Guessing Game ===\n";
    cout << "Choose a category:\n";
    cout << "1. Fruits\n";
    cout << "2. Wild Animals\n";
    cout << "3. Countries\n";
    cout << "Enter choice (1-3): ";

    int choice;
    cin >> choice;

    
    srand(time(0));
    string secret;
    if (choice == 1) secret = fruits[rand() % fruitsCount];
    else if (choice == 2) secret = animals[rand() % animalsCount];
    else secret = countries[rand() % countriesCount];

    string guessed(secret.length(), '_');
    int attempts = secret.length() + 3;

    cout << "\nGuess the word (" << secret.length() << " letters)\n\n";

    while (attempts > 0 && guessed != secret) {
        cout << "Word: " << guessed << "\n";
        cout << "Attempts left: " << attempts << "\n";
        cout << "Enter a letter: ";

        char ch;
        cin >> ch;

        bool found = false;
        for (size_t i = 0; i < secret.size(); i++) {
            if (secret[i] == ch && guessed[i] == '_') {
                guessed[i] = ch;
                found = true;
            }
        }

        if (!found) {
            cout << "Wrong guess!\n";
            attempts--;
        } else {
            cout << "Good guess!\n";
        }
        cout << endl;
    }

    if (guessed == secret) {
        cout << "🎉 You guessed it! The word was: " << secret << endl;
    } else {
        cout << "😢 Out of attempts! The word was: " << secret << endl;
    }

    return 0;
}
