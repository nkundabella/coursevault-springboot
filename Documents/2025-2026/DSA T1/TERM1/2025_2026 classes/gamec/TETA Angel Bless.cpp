#include <iostream>
#include <string>
using namespace std;

int main() {
    string word = "JESUS";
    string hidden(word.size(), '_');
    int attempts = 10;
    char guess;
    bool completed = false;

    cout << "Welcome to Guess-the-Letter! \n";
    cout << "Guess the word: " << hidden << endl;

    while (attempts > 0 && !completed) {
        cout << "\nEnter a letter: ";
        cin >> guess;
        guess = toupper(guess);

        bool found = false;
        for (size_t i = 0; i < word.size(); i++) {
            if (word[i] == guess) {
                hidden[i] = word[i];      
                found = true;
            }
        }

        if (!found) {
            attempts--;
            cout << "Wrong!" << attempts <<"Trials left."<< endl;
        } else {
            cout << "Correct!" << endl;
        }


        cout << "Current word: " << hidden << endl;


        if (hidden == word) {
            completed = true;
            cout << "\nCongratulations! You guessed the word: " << word  << endl;
        }
    }

    if (!completed) {
        cout << "\nOut of attempts! The word was: " << word << endl;
    }

    return 0;
}
