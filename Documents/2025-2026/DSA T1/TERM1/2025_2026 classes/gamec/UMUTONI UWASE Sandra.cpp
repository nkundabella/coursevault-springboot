#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>
#include <cctype>
#include <limits>

using namespace std;

struct Word {
    string word;
    string hint;
};

vector<Word> loadWords() {
    vector<Word> v;
    v.reserve(6);

    Word tmp;
    tmp.word = "giraffe";   tmp.hint = "A tall animal with spots";        v.push_back(tmp);
    tmp.word = "banana";    tmp.hint = "A yellow fruit monkeys love";     v.push_back(tmp);
    tmp.word = "school";    tmp.hint = "A place full of learning";        v.push_back(tmp);
    tmp.word = "laptop";    tmp.hint = "A portable computer device";      v.push_back(tmp);
    tmp.word = "astronaut"; tmp.hint = "Someone who goes to space";       v.push_back(tmp);
    tmp.word = "puzzle";    tmp.hint = "Something you solve with logic";  v.push_back(tmp);

    return v;
}

void revealRandomLetter(string &hidden, const string &word, set<char> &revealed) {
    vector<size_t> indices;
    for (size_t i = 0; i < word.size(); ++i) {
        if (hidden[i] == '_') indices.push_back(i);
    }
    if (!indices.empty()) {
        size_t r = indices[rand() % indices.size()];
        hidden[r] = word[r];
        revealed.insert(word[r]);
        cout << "\n?? Surprise! A letter has been revealed: " << word[r] << endl;
    }
}

void playGame(const Word &w) {
    string word = w.word;
    string hidden(word.size(), '_');
    if (!word.empty()) hidden[0] = word[0]; 

    set<char> guessed;
    set<char> revealed;
    if (!word.empty()) revealed.insert(word[0]);

    int maxGuesses = 12;
    int attempts = 0;
    int wrongGuesses = 0;
    int score = 0;

    cout << "\n?? Hint: " << w.hint << endl;
    cout << "Word length: " << word.size() << " | Max guesses: " << maxGuesses << endl;

    while (attempts < maxGuesses && hidden != word) {
        cout << "\nCurrent word: " << hidden << endl;

        cout << "Available letters: ";
        for (char c = 'a'; c <= 'z'; ++c) {
            if (guessed.find(c) == guessed.end() && revealed.find(c) == revealed.end()) cout << c << " ";
        }
        cout << endl;

        cout << "Enter guess #" << (attempts + 1) << ": ";
        char guess;
        if (!(cin >> guess)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, try again.\n";
            continue;
        }

        guess = static_cast<char>(tolower(static_cast<unsigned char>(guess)));

        if (!isalpha(static_cast<unsigned char>(guess))) {
            cout << "Please enter a letter (a-z).\n";
            continue;
        }

        if (guessed.find(guess) != guessed.end()) {
            cout << "?? You've already guessed that letter!" << endl;
            continue;
        }

        guessed.insert(guess);

        bool correct = false;
        for (size_t i = 0; i < word.size(); ++i) {
            if (word[i] == guess && hidden[i] == '_') {
                hidden[i] = guess;
                correct = true;
                score += 10; 
            }
        }

        if (correct) {
            cout << "? Nice! Letter found!" << endl;
        } else {
            cout << "? Oops! Wrong guess." << endl;
            score -= 2; 
            ++wrongGuesses;
            if (wrongGuesses > 0 && wrongGuesses % 3 == 0)
                revealRandomLetter(hidden, word, revealed);
        }

        ++attempts;
    }

    if (hidden == word) {
        cout << "\n?? Congratulations! You guessed the word: " << word << endl;
        score += (maxGuesses - wrongGuesses); 
    } else {
        cout << "\n?? Game Over! The word was: " << word << endl;
    }

    cout << "?? Your score: " << score << endl;
}

int main() {
    srand(static_cast<unsigned>(time(0))); 
    vector<Word> words = loadWords();

    char again;
    do {
        int index = rand() % words.size();
        playGame(words[index]);

        cout << "\nPlay again? (y/n): ";
        cin >> again;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } while (again == 'y' || again == 'Y');

    system("pause"); 
    return 0;
}

