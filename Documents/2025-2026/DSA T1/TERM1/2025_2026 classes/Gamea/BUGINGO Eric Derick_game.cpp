#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

int chances = 5;
vector<char> guessedLetters;

vector<string> words = {
    // C++ OOP keywords
    "class", "public", "private", "protected",
    "virtual", "override", "friend", "this",
    "namespace", "template", "typename", "using",
    "new", "delete", "operator", "explicit",
    "mutable", "inline", "static", "const",
    "throw", "try", "catch", "final"
};

string mutateWord(const string &word) {
    string mutated = word;
    for (size_t i = 0; i < mutated.size(); i++) {
        int randomInt = rand() % 100;
        if (randomInt % 2 == 0) {
            mutated[i] = '_';
        }
    }
    return mutated;
}

string getRandomWord() {
    int index = rand() % words.size();
    return words[index];
}

string updateMutatedString(char guessedChar, string mutatedString, const string &originalWord) {
    for (size_t i = 0; i < mutatedString.size(); i++) {
        if (mutatedString[i] == '_' && originalWord[i] == guessedChar) {
            mutatedString[i] = guessedChar;
        }
    }
    return mutatedString;
}

int main() {
    srand((unsigned) time(0));

    string word = getRandomWord();
    string mutation = mutateWord(word);

    cout << "Word guess game to help you revise cpp object oriented Programming" << endl;
    cout << "Guess the word: " << mutation << endl;

    while (chances > 0) {
        cout << "\nCurrent word: " << mutation << endl;
        cout << "Enter a letter (or 'quit' to exit): ";
        
        string input;
        getline(cin, input);

        if (input == "quit") break;
        if (input.empty()) continue;

        char guessedChar = input[0];
        if (guessedChar < 'a' || guessedChar > 'z') continue;

        if (find(guessedLetters.begin(), guessedLetters.end(), guessedChar) != guessedLetters.end()) {
            mutation = updateMutatedString(guessedChar, mutation, word);
        } else {
            guessedLetters.push_back(guessedChar);
            if (word.find(guessedChar) != string::npos) {
                mutation = updateMutatedString(guessedChar, mutation, word);
            } else {
                chances--;
                cout << "Wrong guess! Remaining chances: " << chances << endl;
            }
        }

        if (word == mutation) {
            cout << "Word guessed successfully: " << word << endl;
            chances++;
            break;
        }
    }

    if (word != mutation) {
        cout << "Game over! The word was: " << word << endl;
    }

    return 0;
}
