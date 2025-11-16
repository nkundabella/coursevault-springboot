#include <iostream>
#include <map>      // stores key-value pairs in sorted order by key
#include <vector>   // allows storing multiple elements dynamically
#include <string>   // enables using strings and functions like length()
#include <cstdlib>  // includes functions for memory allocation, process control, conversions, etc.
#include <ctime>    // allows working with date and time
#include <set>      // stores unique values, useful for guessed letters
#include <algorithm>// allows functions like transform for lowercase conversion
using namespace std;

// Function that runs one round of the game
void playGame(map<string, vector<string>> &categories) {
    // Show the available categories to the player
    cout << "\nAvailable categories: ";
    for (auto &c : categories) {
        cout << c.first << " ";
    }
    cout << endl;

    // Ask the player to choose one category
    string category;
    cout << "Choose a category: ";
    cin >> category;

    // If the category does not exist, quit this round
    if (categories.find(category) == categories.end()) {
        cout << "Invalid category!" << endl;
        return;
    }

    // Pick a random word from the chosen category
    string word = categories[category][rand() % categories[category].size()];

    // Make a lowercase copy so guesses can be case-insensitive
    string lowerWord = word;
    transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);

    // Create a "hidden" version of the word (underscores for letters, spaces left as spaces)
    string display(word.size(), '_');
    for (int i = 0; i < word.size(); i++) {
        if (word[i] == ' ')
            display[i] = ' ';
    }

    set<char> guessed; // keeps track of already guessed letters
    int chances = 7;   // number of chances before losing

    cout << "\nWord to guess: " << display << endl;

    // Main game loop
    while (chances > 0) {
        cout << "\nEnter a letter (or type exit to quit): ";
        string input;
        cin >> input;

        // Allow the player to quit early
        if (input == "exit") {
            cout << "Game exited." << endl;
            return;
        }

        // Only allow single alphabet characters
        if (input.size() != 1 || !isalpha(input[0])) {
            cout << "Please enter a single letter." << endl;
            continue;
        }

        char guess = tolower(input[0]);

        // If the letter was already guessed, tell the player
        if (guessed.count(guess)) {
            cout << "You already guessed that letter." << endl;
            continue;
        }

        guessed.insert(guess); // record this guess

        // Check if the guess is in the word
        bool correct = false;
        for (int i = 0; i < word.size(); i++) {
            if (lowerWord[i] == guess) {
                display[i] = word[i]; // reveal the actual letter (preserves case)
                correct = true;
            }
        }

        // Feedback for the player
        if (correct) {
            cout << "Correct!" << endl;
        } else {
            chances--;
            cout << "Wrong! Chances left: " << chances << endl;
        }

        // Show the current state of the word
        cout << "Word: " << display << endl;

        // Check if the player has guessed the full word
        if (display == word) {
            cout << "\nCongratulations! You guessed the word: " << word << endl;
            return;
        }
    }

    // If we reach here, the player ran out of chances
    cout << "\nYou lost! The word was: " << word << endl;
}

int main() {
    srand(time(0)); // Seed random generator once at the start of the program

    // Categories with words
    map<string, vector<string>> categories = {
        {"animals", {"Elephant", "Giraffe", "Tiger", "Kangaroo"}},
        {"teams", {"Arsenal", "Chelsea", "Real Madrid", "Man U"}},
        {"districts", {"Gasabo", "Nyanza", "Kamonyi", "Nyamagabe"}},
        {"films", {"Kuch Kuch Hota Hai", "Endgame", "Koi Mil Gaya", "We Are Family"}},
        {"books", {"Behind the Crown", "The Concubine", "Him in the Shadow", "Odyssey"}}
    };

    // Loop to let the player replay multiple times
    while (true) {
        playGame(categories);
        cout << "\nPlay again? (yes/no): ";
        string choice;
        cin >> choice;
        if (choice != "yes") {
            cout << "Thanks for playing!" << endl;
            break;
        }
    }
    return 0;
}