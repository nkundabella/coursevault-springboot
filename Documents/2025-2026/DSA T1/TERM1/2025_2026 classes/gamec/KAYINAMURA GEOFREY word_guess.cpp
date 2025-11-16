#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;


string maskWord(const string& word, const vector<char>& guessed) {
    string masked = "";
    for (char c : word) {
        if (find(guessed.begin(), guessed.end(), c) != guessed.end()) {
            masked += c;
        } else {
            masked += '_';
        }
    }
    return masked;
}

int main() {
    srand(time(0));


    vector<string> categories = {"Animals", "Teams", "Districts", "Films", "Books"};

    vector<vector<string>> words = {
        {"elephant", "tiger", "giraffe", "kangaroo", "zebra"},
        {"mancity", "barca", "bayern", "chelsea", "arsenal"},
        {"rulindo", "nyarugenge", "musanze", "rubavu", "huye"},
        {"inception", "avatar", "titanic", "gladiator", "jumanji"},
        {"hamlet", "odyssey", "inferno", "twilight", "dune"}
    };

    char playAgain = 'y';

    while (playAgain == 'y' || playAgain == 'Y') {

        cout << "Choose a category:\n";
        for (int i = 0; i < categories.size(); i++) {
            cout << i + 1 << ". " << categories[i] << endl;
        }

        int choice;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice < 1 || choice > categories.size()) {
            cout << "Invalid category!\n";
            continue;
        }


        string word = words[choice - 1][rand() % words[choice - 1].size()];

        vector<char> guessed;
        int attempts = 6;
        bool won = false;

        cout << "\nGame Started! You have " << attempts << " attempts.\n";

        while (attempts > 0) {
            string masked = maskWord(word, guessed);
            cout << "Word: " << masked << endl;


            if (masked == word) {
                cout << " Congratulations! You guessed the word: " << word << endl;
                won = true;
                break;
            }

            string guess;
            cout << "Enter a letter (or type 'exit' to quit): ";
            cin >> guess;

            if (guess == "exit") {
                cout << "Exiting game...\n";
                return 0;
            }

            if (guess.size() != 1 || !isalpha(guess[0])) {
                cout << "Invalid input! Enter a single letter.\n";
                continue;
            }

            char letter = tolower(guess[0]);


            if (find(guessed.begin(), guessed.end(), letter) != guessed.end()) {
                cout << "You already guessed '" << letter << "'. Try another.\n";
                continue;
            }

            guessed.push_back(letter);

            if (word.find(letter) == string::npos) {
                attempts--;
                cout << "Wrong guess! Attempts left: " << attempts << endl;
            } else {
                cout << "Good guess!\n";
            }
        }

        if (!won) {
            cout << " You lost! The word was: " << word << endl;
        }

        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "Thanks for playing! \n";
    return 0;
}

