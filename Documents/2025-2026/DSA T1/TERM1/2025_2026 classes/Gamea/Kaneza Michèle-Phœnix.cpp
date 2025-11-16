#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    vector<pair<string, string>> words = {
        {"carrot", "It's a vegetable"},
        {"banana", "It's a fruit"},
        {"tiger", "It's an animal"},
        {"guitar", "It's a musical instrument"}
    };

    srand(time(0));
    int randomIndex = rand() % words.size();
    string word = words[randomIndex].first;
    string hint = words[randomIndex].second;

    string display(word.length(), '-');
    display[0] = word[0];
    display[word.length() - 1] = word[word.length() - 1];

    int wrongGuesses = 0;
    const int maxWrong = 3;

    cout << "Guess the word: " << display << endl;

    while (display != word) {
        cout << "Enter a letter: ";
        char guess;
        cin >> guess;

        bool correct = false;
        for (size_t i = 0; i < word.length(); i++) {
            if (word[i] == guess && display[i] == '-') {
                display[i] = guess;
                correct = true;
            }
        }

        if (correct) {
            cout << "Good job! " << display << endl;
        } else {
            wrongGuesses++;
            cout << "Wrong guess! " << display << endl;

            if (wrongGuesses >= maxWrong) {
                cout << "Hint: " << hint << endl;
            }
        }
    }

    cout << "Congratulations! You guessed the word: " << word << endl;
    return 0;
}
