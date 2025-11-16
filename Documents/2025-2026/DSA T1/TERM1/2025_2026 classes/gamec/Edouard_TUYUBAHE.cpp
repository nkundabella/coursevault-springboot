#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <cctype>

using namespace std;

void showCategories(const map<string, vector<string>>& wordLists) {
    cout << "\n=== Word Guess Challenge ===\n";
    int num = 1;
    for (const auto& pair : wordLists) {
        cout << num++ << ") " << pair.first << "\n";
    }
    cout << num << ") Quit Game\n";
}

string selectCategory(const map<string, vector<string>>& wordLists) {
    int selection;
    string userInput;
    int totalOptions = wordLists.size() + 1;

    while (true) {
        cout << "\nPick a number (1-" << totalOptions << ") or type 'quit': ";
        getline(cin, userInput);

        if (userInput == "quit" || userInput == "Quit") {
            return "";
        }

        try {
            selection = stoi(userInput);
            if (selection >= 1 && selection <= wordLists.size()) {
                auto iter = wordLists.begin();
                advance(iter, selection - 1);
                return iter->first;
            } else if (selection == totalOptions) {
                return "";
            } else {
                cout << "Invalid choice. Enter a number between 1 and " << totalOptions << " or 'quit'.\n";
            }
        } catch (...) {
            cout << "Please provide a valid number or 'quit'.\n";
        }
    }
}

string revealWord(const string& target, const vector<char>& guesses) {
    string result = "";
    for (char letter : target) {
        if (find(guesses.begin(), guesses.end(), letter) != guesses.end()) {
            result += letter;
        } else {
            result += '-';
        }
    }
    return result;
}

bool runRound(const string& topic, const vector<string>& wordPool) {
    srand(static_cast<unsigned>(time(0)));
    string chosenWord = wordPool[rand() % wordPool.size()];
    transform(chosenWord.begin(), chosenWord.end(), chosenWord.begin(), ::tolower);

    cout << "[DEBUG] Chosen word: " << chosenWord << endl;

    vector<char> lettersGuessed;
    int attemptsLeft = 6;

    cout << "\nTopic: " << topic << "\n";
    cout << "Word length: " << chosenWord.length() << " letters.\n";

    while (attemptsLeft > 0) {
        cout << "\nAttempts remaining: " << attemptsLeft << "\n";
        cout << "Letters tried: ";
        if (lettersGuessed.empty()) {
            cout << "None";
        } else {
            for (char letter : lettersGuessed) {
                cout << letter << " ";
            }
        }
        cout << "\nCurrent word: " << revealWord(chosenWord, lettersGuessed) << "\n";

        string userGuess;
        cout << "Guess a letter (or type 'quit' to stop): ";
        getline(cin, userGuess);

        if (userGuess == "quit" || userGuess == "Quit") {
            cout << "The word was: " << chosenWord << "\n";
            return false;
        }

        if (userGuess.length() != 1 || !isalpha(userGuess[0])) {
            cout << "Enter exactly one letter.\n";
            continue;
        }

        char letter = tolower(userGuess[0]);

        if (find(lettersGuessed.begin(), lettersGuessed.end(), letter) != lettersGuessed.end()) {
            cout << "That letter was already tried!\n";
            continue;
        }

        lettersGuessed.push_back(letter);

        if (chosenWord.find(letter) != string::npos) {
            cout << "Nice! That letter is in the word.\n";
            if (revealWord(chosenWord, lettersGuessed) == chosenWord) {
                cout << "\nYou won! The word was: " << chosenWord << "\n";
                return true;
            }
        } else {
            cout << "Oops, that letter isn't in the word.\n";
            attemptsLeft--;
        }

        if (attemptsLeft == 0) {
            cout << "\nOut of attempts! The word was: " << chosenWord << "\n";
            return false;
        }
    }
    return false;
}

int main() {
    map<string, vector<string>> wordLists = {
        {"Wildlife", {"lion", "zebra", "rhino", "cheetah", "koala"}},
        {"Novels", {"gatsby", "ulysses", "mockingbird", "frankenstein", "orwell"}},
        {"Movies", {"matrix", "gladiator", "starwars", "jumanji", "rocky"}},
        {"Teams", {"yankees", "redsox", "packers", "giants", "eagles"}}
    };

    while (true) {
        showCategories(wordLists);
        string selectedTopic = selectCategory(wordLists);

        if (selectedTopic.empty()) {
            cout << "Goodbye!\n";
            break;
        }

        runRound(selectedTopic, wordLists[selectedTopic]);

        string continueGame;
        cout << "\nPlay another round? (y/n): ";
        getline(cin, continueGame);
        transform(continueGame.begin(), continueGame.end(), continueGame.begin(), ::tolower);
        if (continueGame != "y") {
            cout << "Thanks for playing!\n";
            break;
        }
    }

    return 0;
}