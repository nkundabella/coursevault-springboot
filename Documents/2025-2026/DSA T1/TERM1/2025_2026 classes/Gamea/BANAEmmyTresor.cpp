#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <cctype>

using namespace std;

string getRandomWord(const vector<string>& words) {
    if (words.empty()) {
        return "";
    }
    unsigned seed = chrono::high_resolution_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(0, words.size() - 1);
    return words[distribution(generator)];
}

void displayWord(const string& word, const string& guessedLetters) {
    for (char c : word) {
        if (c == ' ') {
            cout << " ";
        } else if (guessedLetters.find(c) != string::npos) {
            cout << c;
        } else {
            cout << "_";
        }
    }
    cout << endl;
}

bool isWordGuessed(const string& word, const string& guessedLetters) {
    for (char c : word) {
        if (c != ' ' && guessedLetters.find(c) == string::npos) {
            return false;
        }
    }
    return true;
}

void playGame() {
    vector<string> words = {"elephant", "tiger", "giraffe", "penguin", "kangaroo"};

    string wordToGuess = getRandomWord(words);
    if (wordToGuess.empty()) {
        cout << "Error: No words available." << endl;
        return;
    }

    string guessedLetters = "";
    int remainingChances = 8;

    cout << "Welcome to the Word Guessing Game!" << endl;
    cout << "You have " << remainingChances << " chances to guess the word." << endl;
    cout << "To exit at any time, type 'exit'." << endl;

    while (remainingChances > 0 && !isWordGuessed(wordToGuess, guessedLetters)) {
        cout << "\nGuessed word: ";
        displayWord(wordToGuess, guessedLetters);
        cout << "Remaining chances: " << remainingChances << endl;
        cout << "Guessed letters: " << guessedLetters << endl;

        char guess;
        string input;
        cout << "Enter a letter or 'exit': ";
        cin >> input;

        if (input == "exit") {
            cout << "Exiting the game. Goodbye!" << endl;
            return;
        }

        if (input.length() != 1 || !isalpha(input[0])) {
            cout << "Invalid input. Please enter a single letter." << endl;
            continue;
        }
        
        guess = tolower(input[0]);

        if (guessedLetters.find(guess) != string::npos) {
            cout << "You've already guessed that letter. Try another one." << endl;
            continue;
        }

        guessedLetters += guess;

        if (wordToGuess.find(guess) == string::npos) {
            cout << "Incorrect guess!" << endl;
            remainingChances--;
        } else {
            cout << "Correct guess!" << endl;
        }
    }

    cout << "\n--- Game Over ---" << endl;
    cout << "The word was: " << wordToGuess << endl;
    if (isWordGuessed(wordToGuess, guessedLetters)) {
        cout << "Congratulations! You won." << endl;
    } else {
        cout << "You lost. Better luck next time!" << endl;
    }
}

int main() {
    char playAgain;
    do {
        playGame();
        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
    } while (tolower(playAgain) == 'y');

    cout << "Thank you for playing!" << endl;
    return 0;
}