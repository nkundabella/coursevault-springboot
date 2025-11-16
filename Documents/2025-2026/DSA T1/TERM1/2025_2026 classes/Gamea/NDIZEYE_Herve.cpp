#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;

string getWord(const string &category) {
    map<string, vector<string>> words = {
        {"animals", {"elephant", "tiger", "giraffe", "zebra", "lion"}},
        {"teams", {"arsenal", "barcelona", "chelsea", "juventus", "lakers"}},
        {"districts", {"nyarugenge", "gasabo", "kicukiro", "musanze", "huye"}},
        {"films", {"inception", "avatar", "titanic", "gladiator", "interstellar"}},
        {"books", {"hamlet", "odyssey", "iliad", "inferno", "frankenstein"}}
    };
    return words[category][rand() % words[category].size()];
}

bool Game() {
    cout << "Categories: animals, teams, districts, films, books\n";
    string category;
    cout << "Choose a category: ";
    cin >> category;
    string word = getWord(category);
    string guessed(word.size(), '_');
    int chances = word.size() + 3;
    while (chances > 0 && guessed != word) {
        cout << guessed << " (" << chances << " chances left)\n";
        string input;
        cout << "Enter a letter or type exit: ";
        cin >> input;
        if (input == "exit") return false;
        if (input.size() != 1) continue;
        char letter = input[0];
        bool found = false;
        for (int i = 0; i < word.size(); i++) {
            if (word[i] == letter) {
                guessed[i] = letter;
                found = true;
            }
        }
        if (!found) chances--;
    }
    if (guessed == word) cout << "You win! The word was " << word << endl;
    else cout << "You lose! The word was " << word << endl;
    return true;
}

int main() {
    srand(time(0));
    while (true) {
        if (!Game()) break;
        string choice;
        cout << "Play once again? (y/n): ";
        cin >> choice;
        if (choice != "y") break;
    }
    return 0;
}
