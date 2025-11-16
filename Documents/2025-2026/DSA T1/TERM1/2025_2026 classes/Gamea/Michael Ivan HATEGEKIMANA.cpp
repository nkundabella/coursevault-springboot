#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
using namespace std;

class WordGuessingGame {
private:
    vector<vector<string>> categories;
    vector<string> categoryNames;
    string currentWord;
    string guessedWord;
    vector<char> guessedLetters;
    int maxAttempts;
    int remainingAttempts;
    
public:
    WordGuessingGame() {
        
        categoryNames = {"Animals", "Teams", "Districts", "Films", "Books"};
        categories.push_back({"elephant", "tiger", "lion", "giraffe", "zebra", "monkey", "dolphin", "penguin", "kangaroo", "rhinoceros"});
        categories.push_back({"barcelona", "madrid", "manchester", "liverpool", "arsenal", "chelsea", "juventus", "milan", "bayern", "paris"});
        categories.push_back({"manhattan", "brooklyn", "queens", "bronx", "westminster", "kensington", "chelsea", "camden", "greenwich", "hackney"});
        categories.push_back({"titanic", "avatar", "inception", "gladiator", "matrix", "godfather", "casablanca", "shawshank", "pulpfiction", "goodfellas"});
        categories.push_back({"hamlet", "macbeth", "othello", "gatsby", "mockingbird", "catcher", "pride", "prejudice", "wuthering", "heights"});
        
        maxAttempts = 6;
        srand(time(0));
    }
    
    void displayCategories() {
        cout << "\n=== WORD GUESSING GAME ===" << endl;
        cout << "Choose a category:" << endl;
        for (int i = 0; i < categoryNames.size(); i++) {
            cout << i + 1 << ". " << categoryNames[i] << endl;
        }
        cout << "Enter your choice (1-" << categoryNames.size() << "): ";
    }
    
    bool selectCategory() {
        int choice;
        cin >> choice;
        
        if (choice < 1 || choice > categoryNames.size()) {
            cout << "Invalid choice! Please try again." << endl;
            return false;
        }
        
        vector<string>& selectedCategory = categories[choice - 1];
        int randomIndex = rand() % selectedCategory.size();
        currentWord = selectedCategory[randomIndex];
        
        guessedWord = string(currentWord.length(), '_');
        guessedLetters.clear();
        remainingAttempts = maxAttempts;
        
        cout << "\nCategory selected: " << categoryNames[choice - 1] << endl;
        cout << "Word length: " << currentWord.length() << " letters" << endl;
        cout << "You have " << maxAttempts << " wrong guesses allowed." << endl;
        
        return true;
    }
    
    void displayGameState() {
        cout << "\n" << string(40, '=') << endl;
        cout << "Word: ";
        for (char c : guessedWord) {
            cout << c << " ";
        }
        cout << endl;
        
        cout << "Remaining attempts: " << remainingAttempts << endl;
        
        if (!guessedLetters.empty()) {
            cout << "Guessed letters: ";
            for (char c : guessedLetters) {
                cout << c << " ";
            }
            cout << endl;
        }
        cout << string(40, '=') << endl;
    }
    
    bool isLetterAlreadyGuessed(char letter) {
        return find(guessedLetters.begin(), guessedLetters.end(), letter) != guessedLetters.end();
    }
    
    bool makeGuess(char letter) {
        letter = tolower(letter);
        
        if (isLetterAlreadyGuessed(letter)) {
            cout << "You already guessed '" << letter << "'! Try a different letter." << endl;
            return false;
        }
        
        guessedLetters.push_back(letter);
        
        bool found = false;
        for (int i = 0; i < currentWord.length(); i++) {
            if (currentWord[i] == letter) {
                guessedWord[i] = letter;
                found = true;
            }
        }
        
        if (found) {
            cout << "Good guess! '" << letter << "' is in the word." << endl;
        } else {
            remainingAttempts--;
            cout << "Sorry! '" << letter << "' is not in the word." << endl;
        }
        
        return true;
    }
    
    bool isWordComplete() {
        return guessedWord == currentWord;
    }
    
    bool isGameOver() {
        return remainingAttempts <= 0 || isWordComplete();
    }
    
    void displayResult() {
        cout << "\n" << string(50, '=') << endl;
        if (isWordComplete()) {
            cout << "🎉 CONGRATULATIONS! YOU WON! 🎉" << endl;
            cout << "You guessed the word: " << currentWord << endl;
        } else {
            cout << "💀 GAME OVER! YOU LOST! 💀" << endl;
            cout << "The word was: " << currentWord << endl;
        }
        cout << string(50, '=') << endl;
    }
    
    void playGame() {
        while (true) {
            displayCategories();
            
            if (!selectCategory()) {
                continue;
            }
            
            while (!isGameOver()) {
                displayGameState();
                
                cout << "\nEnter a letter (or 'exit' to quit): ";
                string input;
                cin >> input;
                
                if (input == "exit" || input == "EXIT") {
                    cout << "Thanks for playing! Goodbye!" << endl;
                    return;
                }
                
                if (input.length() != 1 || !isalpha(input[0])) {
                    cout << "Please enter a single letter!" << endl;
                    continue;
                }
                
                makeGuess(input[0]);
            }
            
            displayGameState();
            displayResult();
            
            cout << "\nDo you want to play again? (y/n): ";
            char playAgain;
            cin >> playAgain;
            
            if (tolower(playAgain) != 'y') {
                cout << "Thanks for playing! Goodbye!" << endl;
                break;
            }
        }
    }
};

int main() {
    WordGuessingGame game;
    game.playGame();
    
    return 0;
}
