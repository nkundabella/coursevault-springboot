#include <iostream>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}


string selectWord(const vector<string>& words) {
    int index = rand() % words.size();
    return words[index];
}


void displayWord(const string& word, const vector<char>& guessedLetters) {
    for (char c : word) {
        if (find(guessedLetters.begin(), guessedLetters.end(), tolower(c)) != guessedLetters.end()) {
            cout << c;
        } else {
            cout << "_";
        }
    }
    cout << endl;
}


bool isWordGuessed(const string& word, const vector<char>& guessedLetters) {
    for (char c : word) {
        if (find(guessedLetters.begin(), guessedLetters.end(), tolower(c)) == guessedLetters.end()) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    
    map<string, vector<string>> classes = {
        {"year2a", {"moise","divine","nikita","roger","darlen","tresor","alliance","derick","aloys","emmanuel",
                    "samuel","don durkheim","sandra","michael","duff","noah","noble","irakoze","zion","arlene",
                    "brian","herve","angelo","darius","christian","yanis"}},

        {"year2b", {"berard","belise","honorine","clare","winner","divine","bertrand","gold","shoulamite",
                    "arnaud","amani","angelique","prisca","louise","joshua","anna","esther","nora","christella",
                    "melissa","kelia","landra","aaron","sandrine","rugie","florence"}},

        {"year2c", {"happy","anitha","fanny","jordan","amandine","kennedy","geofrey","delice","bright",
                    "henriette","isaac","gloria","isabella","sasha","divin","tehila","barsime","bless",
                    "edourard","chrisostom","bonnette","sandra","paola","miguel"}}
    };

    string playAgain;

    do {
        cout << "=== WORD GUESSING GAME ===" << endl;
        cout << "Available Classes:\n";
        for (const auto& pair : classes) {
            cout << "- " << pair.first << endl;
        }

        string category;
        while (true) {
            cout << "\nChoose a class (e.g. Year2A): ";
            cin >> category;
            category = toLower(category);

            if (classes.find(category) != classes.end()) {
                break;
            } else {
                cout << "Invalid class. Try again." << endl;
            }
        }

        string word = selectWord(classes[category]);
        vector<char> guessedLetters;
        int attemptsLeft = 8;

        cout << "\nGuess the student name! You have " << attemptsLeft << " attempts." << endl;

        while (attemptsLeft > 0) {
            cout << "\nName: ";
            displayWord(word, guessedLetters);

            cout << "Enter a letter (or type 'exit' to quit): ";
            string input;
            cin >> input;

            if (toLower(input) == "exit") {
                cout << "Thanks for playing!" << endl;
                return 0;
            }

            if (input.length() != 1 || !isalpha(input[0])) {
                cout << "Please enter a single letter." << endl;
                continue;
            }

            char guess = tolower(input[0]);

            if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
                cout << "You already guessed that letter." << endl;
                continue;
            }

            guessedLetters.push_back(guess);

            if (word.find(guess) != string::npos) {
                cout << "Correct!" << endl;
            } else {
                attemptsLeft--;
                cout << "Wrong! Attempts left: " << attemptsLeft << endl;
            }

            if (isWordGuessed(word, guessedLetters)) {
                cout << "\n🎉 You guessed the student name: " << word << " 🎉" << endl;
                break;
            }
        }

        if (!isWordGuessed(word, guessedLetters)) {
            cout << "\nYou ran out of attempts. The name was: " << word << endl;
        }

        cout << "\nDo you want to play again? (yes/no): ";
        cin >> playAgain;
        playAgain = toLower(playAgain);

    } while (playAgain == "yes");

    cout << "Thanks for playing! " << endl;
    return 0;
}
