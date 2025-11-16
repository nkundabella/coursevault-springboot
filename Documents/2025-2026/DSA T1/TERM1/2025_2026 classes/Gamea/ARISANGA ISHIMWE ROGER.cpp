#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// Function to display word with guessed letters
string getMaskedWord(const string &word, const vector<char> &guessed) {
    string masked = "";
    for (char c : word) {
        if (find(guessed.begin(), guessed.end(), c) != guessed.end())
            masked += c;
        else
            masked += "_";
    }
    return masked;
}

int main() {
    srand(time(0)); // seed random

    // Categories and words
    vector<string> categories = {"Animals", "Teams", "Districts", "Films", "Books"};
    vector<vector<string>> words = {
        {"elephant", "giraffe", "lion", "zebra", "tiger"},          // Animals
        {"arsenal", "chelsea", "barcelona", "bayern", "juventus"},  // Teams
        {"kigali", "gicumbi", "rusizi", "nyanza", "musanze"},       // Districts
        {"avatar", "inception", "titanic", "jaws", "gladiator"},    // Films
        {"hamlet", "inferno", "dracula", "odyssey", "iliad"}        // Books
    };

    char playAgain;
    do {
        // Display categories
        cout << "Select a category:\n";
        for (int i = 0; i < categories.size(); i++) {
            cout << i + 1 << ". " << categories[i] << endl;
        }

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > categories.size()) {
            cout << "Invalid choice. Exiting game.\n";
            return 0;
        }

        // Select random word
        string word = words[choice - 1][rand() % words[choice - 1].size()];

        vector<char> guessed;
        int chances = 6; // max wrong guesses allowed
        bool won = false;

        cout << "\nWord Guessing Game Started! Type 'exit' anytime to quit.\n";

        while (chances > 0) {
            string masked = getMaskedWord(word, guessed);
            cout << "\nWord: " << masked << endl;
            cout << "Chances left: " << chances << endl;
            cout << "Enter a letter: ";

            string input;
            cin >> input;

            // Exit option
            if (input == "exit") {
                cout << "Exiting game...\n";
                return 0;
            }

            // Validate single letter
            if (input.size() != 1 || !isalpha(input[0])) {
                cout << "Please enter a single valid letter.\n";
                continue;
            }

            char letter = tolower(input[0]);

            // Check if already guessed
            if (find(guessed.begin(), guessed.end(), letter) != guessed.end()) {
                cout << "You already guessed that letter.\n";
                continue;
            }

            guessed.push_back(letter);

            // Check if letter is in word
            if (word.find(letter) != string::npos) {
                cout << "Good guess!\n";
            } else {
                cout << "Wrong guess!\n";
                chances--;
            }

            // Check if word is fully guessed
            if (getMaskedWord(word, guessed) == word) {
                won = true;
                break;
            }
        }

        if (won) {
            cout << "\nCongratulations! You guessed the word: " << word << endl;
        } else {
            cout << "\nGame Over! The word was: " << word << endl;
        }

        // Ask to play again
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing! Goodbye.\n";
    return 0;
}
