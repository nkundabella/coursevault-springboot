#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    srand(time(0));

    
    string animals[] = {"elephant", "leopard", "panda"};
    string teams[]   = {"real", "chelsea", "barcelona"};
    string films[]   = {"pushpa", "titanic", "straw"};

    int choice;
    cout << "Choose a category:\n";
    cout << "1. Animals\n2. Teams\n3. Films\n";
    cin >> choice;

    string word;
    if (choice == 1) word = animals[rand() % 3];
    else if (choice == 2) word = teams[rand() % 3];
    else word = films[rand() % 3];

    string hidden(word.size(), '_');
    int attempts = 6;
    char guess;
    string input;

    cout << "\nWord to guess: " << hidden << endl;

    while (attempts > 0 && hidden != word) {
        cout << "Guess a letter (or type exit to exit): ";
        cin >> input;

        if (input == "exit") {
            cout << "Good bye...\n";
            return 0;
        }

        guess = input[0];
        bool correct = false;

        for (int i = 0; i < word.size(); i++) {
            if (word[i] == guess) {
                hidden[i] = guess;
                correct = true;
            }
        }

        if (correct) {
            cout << "Correct! " << hidden << endl;
        } else {
            attempts--;
            cout << "Wrong! Attempts left: " << attempts << endl;
        }
    }

    if (hidden == word) {
        cout << "You win! The Word was: " << word << endl;
    } else {
        cout << "You lose! The Word was: " << word << endl;
    }

    return 0;
}

