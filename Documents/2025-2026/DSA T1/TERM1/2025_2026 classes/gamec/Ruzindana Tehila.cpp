#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <limits>

using namespace std;

// Function to check if a character exists in a string
bool charInString(char c, const string& s) {
    return s.find(c) != string::npos;
}

// Function to display the masked word
void displayWord(const string& word, const string& guessedLetters) {
    for (char c : word) {
        if (charInString(c, guessedLetters)) {
            cout << c << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

// Main game function
void playGame() {
    // Word categories
    map<string, vector<string>> categories = {
        {"Countries", {"rwanda", "kenya", "uganda", "tanzania", "burundi"}},
        {"Presidents", {"biden", "macron", "putin", "obama", "kagame"}},
        {"Electronic Devices", {"laptop", "smartphone", "tablet", "keyboard", "monitor"}},
        {"Capital Cities", {"kigali", "nairobi", "kampala", "dodoma", "bujumbura"}}
    };

    // Category selection
    string categoryName;
    cout << "Available categories: ";
    for (const auto& pair : categories) {
        cout << pair.first << ", ";
    }
    cout << endl;
    cout << "Select a category: ";
    getline(cin, categoryName);

    // Validate category
    if (categories.find(categoryName) == categories.end()) {
        cout << "Invalid category selected. Exiting." << endl;
        return;
    }

    // Random word selection
    vector<string> wordList = categories[categoryName];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, wordList.size() - 1);
    string secretWord = wordList[distrib(gen)];

    string guessedLetters = "";
    int remainingGuesses = 6;
    bool wordGuessed = false;

    cout << "The word has " << secretWord.length() << " letters. Let's play!" << endl;

    while (remainingGuesses > 0 && !wordGuessed) {
        cout << "---------------------------" << endl;
        cout << "Remaining guesses: " << remainingGuesses << endl;
        cout << "Guessed letters: " << guessedLetters << endl;

        displayWord(secretWord, guessedLetters);

        cout << "Guess a letter or type 'exit' to quit: ";
        string guess;
        getline(cin, guess);

        if (guess == "exit") {
            cout << "Exiting the game. Goodbye!" << endl;
            return;
        }

        if (guess.length() != 1 || !isalpha(guess[0])) {
            cout << "Invalid input. Please enter a single letter." << endl;
            continue;
        }

        char guessedChar = tolower(guess[0]);

        if (charInString(guessedChar, guessedLetters)) {
            cout << "You already guessed that letter. Try again." << endl;
            continue;
        }

        guessedLetters += guessedChar;

        if (charInString(guessedChar, secretWord)) {
            cout << "Correct guess!" << endl;
        } else {
            cout << "Wrong guess." << endl;
            remainingGuesses--;
        }

        // Check for win condition
        wordGuessed = true;
        for (char c : secretWord) {
            if (!charInString(c, guessedLetters)) {
                wordGuessed = false;
                break;
            }
        }
    }

    // Game end
    cout << "---------------------------" << endl;
    if (wordGuessed) {
        cout << "Congratulations! You guessed the word: " << secretWord << endl;
    } else {
        cout << "You ran out of guesses. The word was: " << secretWord << endl;
    }
}

int main() {
    string playAgain;
    do {
        playGame();
        cout << "Do you want to play again? (yes/no): ";
        getline(cin, playAgain);
    } while (playAgain == "yes");

    cout << "Thanks for playing!" << endl;

    return 0;
}