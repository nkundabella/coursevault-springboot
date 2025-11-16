#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


void playGame(string category[], int size) {
    srand(time(0));
    string word = category[rand() % size];
    string guessed(word.size(), '_');
    int chances = 6;

    cout << "\nYou have " << chances << " chances to guess the word!" << endl;

    while (chances > 0 && guessed != word) {
        cout << "\nWord: " << guessed << endl;
        cout << "Enter a letter (or type 'exit' to quit): ";
        string input;
        cin >> input;

        if (input == "exit") {
            cout << "Game exited.\n";
            return;
        }

        char letter = input[0];
        bool found = false;


        for (int i = 0; i < word.size(); i++) {
            if (word[i] == letter) {
                guessed[i] = letter;
                found = true;
            }
        }

        if (!found) {
            chances--;
            cout << "Wrong! Chances left: " << chances << endl;
        }
    }

    if (guessed == word) {
        cout << "\n🎉 Congratulations! You guessed the word: " << word << endl;
    } else {
        cout << "\n❌ You lost! The word was: " << word << endl;
    }
}

int main() {
    string animals[] = {"elephant", "tiger", "giraffe", "lion", "zebra"};
    string teams[]   = {"arsenal", "chelsea", "barcelona", "juventus", "bayern"};
    string films[]   = {"avatar", "inception", "gladiator", "frozen", "batman"};

    char playAgain = 'y';

    while (playAgain == 'y') {
        int choice;
        cout << "\n--- Word Guessing Game ---" << endl;
        cout << "Choose a category:\n1. Animals\n2. Teams\n3. Films\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) playGame(animals, 5);
        else if (choice == 2) playGame(teams, 5);
        else if (choice == 3) playGame(films, 5);
        else cout << "Invalid choice!" << endl;

        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "Thanks for playing!\n";
    return 0;
}
