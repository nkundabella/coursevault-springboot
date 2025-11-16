#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

string getRandomWord(const vector<string>& words) {
    int index = rand() % words.size();
    return words[index];
}

void displayWord(const string& word, const vector<bool>& guessed) {
    for (size_t i = 0; i < word.size(); i++) {
        if (guessed[i]) cout << word[i];
        else cout << "_";
    }
    cout << endl;
}

int main() {
    srand(time(0));

    vector<string> animals = {"elephant", "lion", "tiger", "giraffe", "zebra"};
    vector<string> teams = {"arsenal", "chelsea", "lakers", "patriots", "warriors"};
    vector<string> districts = {"gasabo", "nyarugenge", "kicukiro", "rubavu", "musanze"};
    vector<string> films = {"inception", "avatar", "gladiator", "frozen", "titanic"};
    vector<string> books = {"hamlet", "odyssey", "inferno", "foundation", "dune"};

    bool playAgain = true;

    while (playAgain) {
        cout << "\n=== WORD GUESSING GAME ===" << endl;
        cout << "Choose a category:\n";
        cout << "1. Animals\n2. Teams\n3. Districts\n4. Films\n5. Books\n";
        int choice;
        cin >> choice;

        vector<string> category;
        switch (choice) {
            case 1: category = animals; break;
            case 2: category = teams; break;
            case 3: category = districts; break;
            case 4: category = films; break;
            case 5: category = books; break;
            default: cout << "Invalid choice. Exiting...\n"; return 0;
        }

        string word = getRandomWord(category);
        vector<bool> guessed(word.size(), false);
        int chances = 6; 
        bool won = false;

        cout << "\nA word has been chosen. Start guessing!" << endl;

        while (chances > 0) {
            displayWord(word, guessed);
            cout << "Chances left: " << chances << endl;
            cout << "Enter a letter (or type 'exit' to quit): ";
            string input;
            cin >> input;

            if (input == "exit") {
                cout << "Exiting game. Goodbye!" << endl;
                return 0;
            }

            char letter = tolower(input[0]);
            bool found = false;

            for (size_t i = 0; i < word.size(); i++) {
                if (word[i] == letter && !guessed[i]) {
                    guessed[i] = true;
                    found = true;
                }
            }

            if (!found) {
                cout << "Wrong guess!" << endl;
                chances--;
            }

            if (all_of(guessed.begin(), guessed.end(), [](bool g){ return g; })) {
                won = true;
                break;
            }
        }

        if (won) {
            cout << "Congratulations! You guessed the word: " << word << endl;
        } else {
            cout << "Out of chances! The word was: " << word << endl;
        }

        cout << "Do you want to play again? (y/n): ";
        char ans;
        cin >> ans;
        playAgain = (ans == 'y' || ans == 'Y');
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}
