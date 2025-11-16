#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

void displayWord(const string& word, const set<char>& guessedLetters) {
    string display;
    for (char letter : word) {
        if (guessedLetters.count(letter)) {
            display += letter;
            display += ' ';
        } else if (letter == ' ') {
            display += "  ";
        } else {
            display += "_ ";
        }
    }
    cout << "Word: " << display << endl;
}

void playGame() {
    vector<string> animals = {"elephant", "giraffe", "leopard", "chimpanzee", "kangaroo", "hippopotamus"};
    vector<string> teams = {"warriors", "lakers", "celtics", "raptors", "mavericks", "rockets"};
    vector<string> districts = {"manhattan", "brooklyn", "queens", "bronx", "staten island"};
    vector<string> films = {"inception", "gladiator", "matrix", "avengers", "titanic", "interstellar"};
    vector<string> books = {"shogun", "dune", "enders game", "hitchhikers guide", "foundation"};

    vector<string> selectedCategory;
    string choice;

    cout << "Welcome to the Word Guessing Game!" << endl;
    cout << "Please select a category to begin:" << endl;
    cout << "- animals" << endl;
    cout << "- teams" << endl;
    cout << "- districts" << endl;
    cout << "- films" << endl;
    cout << "- books" << endl;

    while (true) {
        cout << "\nEnter your choice: ";
        cin >> choice;
        transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

        if (choice == "animals") {
            selectedCategory = animals;
            break;
        } else if (choice == "teams") {
            selectedCategory = teams;
            break;
        } else if (choice == "districts") {
            selectedCategory = districts;
            break;
        } else if (choice == "films") {
            selectedCategory = films;
            break;
        } else if (choice == "books") {
            selectedCategory = books;
            break;
        } else {
            cout << "Invalid category. Please choose from the list." << endl;
        }
    }

    srand(time(0));
    int randomIndex = rand() % selectedCategory.size();
    string wordToGuess = selectedCategory[randomIndex];

    set<char> guessedLetters;
    set<char> incorrectLetters;
    int incorrectGuesses = 0;
    const int maxIncorrectGuesses = 6;
    bool wordGuessed = false;

    while (incorrectGuesses < maxIncorrectGuesses) {
        cout << "\nGuess the word!" << endl;
        displayWord(wordToGuess, guessedLetters);
        cout << "Chances left: " << maxIncorrectGuesses - incorrectGuesses << endl;
        cout << "Incorrect guesses: ";
        for (char letter : incorrectLetters) {
            cout << letter << " ";
        }
        cout << endl;

        wordGuessed = true;
        for (char letter : wordToGuess) {
            if (isalpha(letter) && guessedLetters.count(letter) == 0) {
                wordGuessed = false;
                break;
            }
        }
        if (wordGuessed) {
            cout << "\nCongratulations! You won!" << endl;
            return;
        }

        string guessStr;
        cout << "Enter a letter (or type 'exit' to quit): ";
        cin >> guessStr;

        if (guessStr == "exit") {
            cout << "Thanks for playing! Goodbye." << endl;
            return;
        }

        if (guessStr.length() != 1 || !isalpha(guessStr[0])) {
            cout << "Invalid input. Please enter a single letter." << endl;
            continue;
        }
        char guess = tolower(guessStr[0]);

        if (guessedLetters.count(guess) || incorrectLetters.count(guess)) {
            cout << "You already guessed that letter." << endl;
        } else if (wordToGuess.find(guess) != string::npos) {
            guessedLetters.insert(guess);
            cout << "Good guess! '" << (char)toupper(guess) << "' is in the word." << endl;
        } else {
            incorrectLetters.insert(guess);
            incorrectGuesses++;
            cout << "Sorry, '" << (char)toupper(guess) << "' is not in the word." << endl;
        }
    }

    cout << "\nGame Over! You've run out of chances." << endl;
    cout << "The word was: " << wordToGuess << endl;
}

int main() {
    char playAgain;
    do {
        playGame();
        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
        playAgain = tolower(playAgain);
    } while (playAgain == 'y');

    cout << "Thanks for playing! Goodbye." << endl;
    return 0;
}
