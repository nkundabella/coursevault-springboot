#include <iostream>
#include <string>
using namespace std;

int main() {
    string secretWord = "potatoes";
    string guessedWord = "--------"; 
    int maxTries = 20;
    int tries = maxTries; 

    cout << "=== WORD GUESSING GAME ===" << endl;

    while (guessedWord != secretWord && tries > 0) {
        cout << "\nGuessed word : " << guessedWord << endl;
        cout << "Trials left : " << tries << endl;

        char guess;
        cout << "Enter a letter : ";
        cin >> guess;

        bool correct = false;
        for (int i = 0; i < secretWord.size(); i++) {
            if (secretWord[i] == guess && guessedWord[i] != guess) {
                guessedWord[i] = guess;
                correct = true;
            }
        }

        if (correct) {
            cout << "Good job! You guessed a correct letter!" << endl;
        } else {
            cout << "Incorrect guess" << endl;
        }

        tries--;

        if (guessedWord == secretWord) {
            cout << "\nCongratulations! You completed the word: " << secretWord << endl;
            break;
        }
    }

    if (guessedWord != secretWord) {
        cout << "\nYou lose. The word was: " << secretWord << endl;
    }

    return 0;
}
