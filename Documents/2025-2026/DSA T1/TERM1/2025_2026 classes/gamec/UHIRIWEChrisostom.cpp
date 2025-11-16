#include <bits/stdc++.h>

using namespace std;

void displayMenu(const map<string, vector<string>>& categories) {
    cout << "\nWord Guessing Game - Select a Category:\n";
    int index = 1;
    for (const auto& category : categories) {
        cout << index++ << ". " << category.first << endl;
    }
    cout << index << ". Exit\n";
}


string getUserChoice(const map<string, vector<string>>& categories) {
    int choice;
    string input;
    int maxChoice = categories.size() + 1;

    while (true) {
        cout << "\nEnter your choice (1-" << maxChoice << "): ";
        getline(cin, input);

        if (input == "exit" || input == "Exit") {
            return "";
        }

        try {
            choice = stoi(input);
            if (choice >= 1 && choice <= categories.size()) {
                auto it = categories.begin();
                advance(it, choice - 1);
                return it->first;
            } else if (choice == maxChoice) {
                return "";
            } else {
                cout << "Please enter a valid number or 'exit'.\n";
            }
        } catch (...) {
            cout << "Please enter a valid number or 'exit'.\n";
        }
    }
}


string displayWord(const string& word, const vector<char>& guessedLetters) {
    string display;
    for (char c : word) {
        if (find(guessedLetters.begin(), guessedLetters.end(), c) != guessedLetters.end()) {
            display += c;
        } else {
            display += '_';
        }
    }
    return display;
}


bool playGame(const string& category, const vector<string>& words) {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, words.size() - 1);
    string word = words[dis(gen)];
    transform(word.begin(), word.end(), word.begin(), ::tolower);

    cout << "[DEBUG] Selected word: " << word << endl;

    vector<char> guessedLetters;
    int maxGuesses = 6;
    int guessesLeft = maxGuesses;

    cout << "\nCategory: " << category << endl;
    cout << "The word has " << word.length() << " letters.\n";

    while (guessesLeft > 0) {
        cout << "\nGuesses left: " << guessesLeft << endl;
        cout << "Guessed letters: ";
        if (guessedLetters.empty()) {
            cout << "None";
        } else {
            for (char c : guessedLetters) {
                cout << c << " ";
            }
        }
        cout << "\nWord: " << displayWord(word, guessedLetters) << endl;

        string input;
        cout << "Enter a letter (or 'exit' to quit): ";
        getline(cin, input);

        if (input == "exit" || input == "Exit") {
            cout << "The word was: " << word << endl;
            return false;
        }

        if (input.empty() || input.length() != 1 || !isalpha(input[0])) {
            cout << "Please enter a single letter.\n";
            continue;
        }

        char guess = tolower(input[0]);

        if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            cout << "You already guessed that letter!\n";
            continue;
        }

        guessedLetters.push_back(guess);

        if (word.find(guess) != string::npos) {
            cout << "Good guess!\n";
        
            string currentDisplay = displayWord(word, guessedLetters);
            if (currentDisplay == word) {
                cout << "\nCongratulations! You guessed the word: " << word << endl;
                return true;
            }
        } else {
            cout << "Sorry, that letter is not in the word.\n";
            guessesLeft--;
        }

        if (guessesLeft == 0) {
            cout << "\nGame Over! The word was: " << word << endl;
            return false;
        }
    }
    return false;
}

int main() {
    
    map<string, vector<string>> categories = {
        {"Animals", {"elephant", "tiger", "giraffe", "kangaroo", "penguin"}},
        {"Books", {"potter", "hobbit", "dune", "pride", "catcher"}},
        {"Films", {"godfather", "inception", "titanic", "avatar", "jaws"}},
        {"Sports Teams", {"lakers", "celtics", "bulls", "warriors", "knicks"}}
    };

    while (true) {
        displayMenu(categories);
        string category = getUserChoice(categories);

        if (category.empty()) {
            cout << "Thanks for playing!\n";
            break;
        }

        playGame(category, categories[category]);

        string playAgain;
        cout << "\nWould you like to play again? (yes/no): ";
        getline(cin, playAgain);
        transform(playAgain.begin(), playAgain.end(), playAgain.begin(), ::tolower);
        if (playAgain != "yes") {
            cout << "Thanks for playing!\n";
            break;
        }
    }

    return 0;
}