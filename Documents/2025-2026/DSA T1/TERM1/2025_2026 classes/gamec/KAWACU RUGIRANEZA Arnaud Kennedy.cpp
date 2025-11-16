#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// Get random word from category
string getRandomWord(const vector<string>& words) {
    int idx = rand() % words.size();
    return words[idx];
}

// Display current guessed word
void displayWord(const string& word, const vector<char>& guessed) {
    for (char c : word) {
        if (find(guessed.begin(), guessed.end(), c) != guessed.end()) {
            cout << c << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

// Check if word is fully guessed
bool isWordGuessed(const string& word, const vector<char>& guessed) {
    for (char c : word) {
        if (find(guessed.begin(), guessed.end(), c) == guessed.end())
            return false;
    }
    return true;
}

int main() {
    srand(time(0));
    bool playAgain = true;

    vector<string> animals = {"elephant", "lion", "giraffe", "tiger", "zebra"};
    vector<string> teams = {"arsenal", "chelsea", "barcelona", "bayern", "juventus"};
    vector<string> films = {"inception", "avatar", "gladiator", "titanic", "joker"};
    vector<string> books = {"hamlet", "odyssey", "inferno", "dracula", "frankenstein"};

    while (playAgain) {
        cout << "Choose a category:\n";
        cout << "1. Animals\n";
        cout << "2. Teams\n";
        cout << "3. Films\n";
        cout << "4. Books\n";
        int choice;
        cin >> choice;

        vector<string> category;
        if (choice == 1) category = animals;
        else if (choice == 2) category = teams;
        else if (choice == 3) category = films;
        else if (choice == 4) category = books;
        else {
            cout << "Invalid choice! Exiting.\n";
            break;
        }

        string word = getRandomWord(category);
        vector<char> guessed;
        int attempts = 6;

        cout << "\nThe game has chosen a word. Start guessing letters!\n";
        while (attempts > 0) {
            displayWord(word, guessed);
            cout << "Attempts left: " << attempts << endl;
            cout << "Enter a letter (or type 'exit' to quit): ";
            string input;
            cin >> input;

            if (input == "exit") {
                cout << "Exiting game...\n";
                return 0;
            }

            char letter = tolower(input[0]);

            if (find(guessed.begin(), guessed.end(), letter) != guessed.end()) {
                cout << "You already guessed that letter!\n";
                continue;
            }

            guessed.push_back(letter);

            if (word.find(letter) != string::npos) {
                cout << "Good guess!\n";
            } else {
                cout << "Wrong guess!\n";
                attempts--;
            }

            if (isWordGuessed(word, guessed)) {
                cout << "Congratulations! You guessed the word: " << word << endl;
                break;
            }
        }

        if (!isWordGuessed(word, guessed)) {
            cout << "Out of attempts! The word was: " << word << endl;
        }

        cout << "Do you want to play again? (y/n): ";
        char again;
        cin >> again;
        playAgain = (again == 'y' || again == 'Y');
    }

    cout << "Thanks for playing!\n";
    return 0;
}