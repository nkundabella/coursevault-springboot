#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>

using namespace std;

vector<string> getCategoryWords(const string& category) {
    if (category == "animals") {
        return {"elephant", "giraffe", "kangaroo", "penguin", "dolphin", "tiger", "lion", "zebra"};
    } else if (category == "countries") {
        return {"canada", "brazil", "japan", "australia", "germany", "india", "france", "mexico"};
    } else if (category == "fruits") {
        return {"apple", "banana", "strawberry", "pineapple", "mango", "kiwi", "orange", "grape"};
    }
    return {};
}

int main() {

    srand(static_cast<unsigned int>(time(0)));
    
    cout << "Welcome to the Word Guessing Game!" << endl;
    cout << "Available categories: animals, countries, fruits" << endl;
    
    
    string category;
    vector<string> words;
    while (true) {
        cout << "Choose a category (animals, countries, fruits): ";
        cin >> category;
        transform(category.begin(), category.end(), category.begin(), ::tolower);
        words = getCategoryWords(category);
        if (!words.empty()) {
            break;
        }
        cout << "Invalid category. Please choose from animals, countries, or fruits." << endl;
    }
    

    string word = words[rand() % words.size()];
    set<char> word_letters(word.begin(), word.end());
    set<char> guessed_letters;
    string display(word.length(), '_');
    int chances = 15;
    
    cout << "\nYou have selected '" << category << "'. The word has " << word.length() << " letters." << endl;
    cout << display << endl;
    
    while (chances > 0 && display != word) {
        cout << "\nGuess a letter: ";
        string guess;
        cin >> guess;
        
        if (guess.length() != 1 || !isalpha(guess[0])) {
            cout << "Invalid input. Please enter a single letter." << endl;
            continue;
        }
        
        char guess_char = tolower(guess[0]);
        if (guessed_letters.find(guess_char) != guessed_letters.end()) {
            cout << "You already guessed that letter. Try another." << endl;
            continue;
        }
        
        guessed_letters.insert(guess_char);
        
        if (word_letters.find(guess_char) != word_letters.end()) {
            cout << "Correct!" << endl;
            for (size_t i = 0; i < word.length(); ++i) {
                if (word[i] == guess_char) {
                    display[i] = guess_char;
                }
            }
        } else {
            cout << "Incorrect!" << endl;
            --chances;
            cout << "Chances left: " << chances << endl;
        }
        
        cout << display << endl;
    }
    
    if (display == word) {
        cout << "\nCongratulations! You guessed the word correctly." << endl;
    } else {
        cout << "\nGame over! The word was '" << word << "'." << endl;
    }
    
    return 0;
}