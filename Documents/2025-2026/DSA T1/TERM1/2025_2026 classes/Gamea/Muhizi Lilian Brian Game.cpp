#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include <ctime>

using namespace std;

string makeLower(string str) {
    for (char &c : str) {
        c = tolower(c);
    }
    return str;
}

string showWord(const string &word, const vector<char> &foundLetters) {
    string result;
    for (char c : word) {
        if (find(foundLetters.begin(), foundLetters.end(), tolower(c)) != foundLetters.end()) {
            result += c;
        } else {
            result += '_';
        }
    }
    return result;
}

void startGame() {
    // Single unique word list (about 30)
    vector<string> words = {
        "zephyr", "quokka", "serendipity", "polymath", "glyph", 
        "nebula", "xenon", "onyx", "runestone", "fjord",
        "labyrinth", "cipher", "tundra", "oracle", "ember",
        "alchemy", "cascade", "horizon", "mirage", "puzzle",
        "eclipse", "aurora", "quasar", "cyclone", "sphinx",
        "vortex", "nimbus", "phantom", "zenith", "mosaic"
    };

    srand(time(0));
    string secretWord = words[rand() % words.size()];
    string secretWordLower = makeLower(secretWord);
    
    int totalTries = 6;
    int triesLeft = totalTries;
    vector<char> correctLetters;
    vector<char> wrongLetters;
    bool solved = false;
    
    cout << "\nGame on! The word has " << secretWord.length() << " letters.\n";
    cout << "You get " << triesLeft << " tries to figure it out.\n";
    
    while (triesLeft > 0 && !solved) {
        cout << "\nWord: " << showWord(secretWord, correctLetters) << endl;
        cout << "Wrong guesses: ";
        for (char c : wrongLetters) cout << c << " ";
        cout << "\nTries remaining: " << triesLeft << endl;
        
        string input;
        cout << "Guess a letter (or type 'exit' to stop): ";
        cin >> input;
        
        if (makeLower(input) == "exit") {
            cout << "Thanks for playing! The word was: " << secretWord << endl;
            return;
        }
        
        if (input.length() != 1 || !isalpha(input[0])) {
            cout << "Just one letter please.\n";
            continue;
        }
        
        char letterGuess = tolower(input[0]);
        
        if (find(correctLetters.begin(), correctLetters.end(), letterGuess) != correctLetters.end() ||
            find(wrongLetters.begin(), wrongLetters.end(), letterGuess) != wrongLetters.end()) {
            cout << "You already tried that letter.\n";
            continue;
        }
        
        if (secretWordLower.find(letterGuess) != string::npos) {
            cout << "Nice guess!\n";
            correctLetters.push_back(letterGuess);
            
            solved = true;
            for (char c : secretWordLower) {
                if (find(correctLetters.begin(), correctLetters.end(), c) == correctLetters.end()) {
                    solved = false;
                    break;
                }
            }
        } else {
            cout << "Nope, that letter's not there.\n";
            wrongLetters.push_back(letterGuess);
            triesLeft--;
        }
    }
    
    cout << "\n";
    if (solved) {
        cout << "You got it! The word was: " << secretWord << endl;
    } else {
        cout << "Better luck next time! The word was: " << secretWord << endl;
    }
}

int main() {
    cout << "Welcome to Word Guess!\n\n";
    
    bool keepPlaying = true;
    while (keepPlaying) {
        startGame();
        
        string answer;
        cout << "\nWant to play again? (yes/no): ";
        cin >> answer;
        
        if (makeLower(answer) != "yes" && makeLower(answer) != "y") {
            keepPlaying = false;
        }
        cout << "\n";
    }
    
    cout << "Thanks for playing! See you next time!\n";
    return 0;
}

