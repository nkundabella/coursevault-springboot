#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <map>

class WordGuessingGame {
private:
    std::map<std::string, std::vector<std::string>> categories;
    std::string secretWord;
    std::string displayWord;
    std::vector<char> guessedLetters;
    int maxWrongGuesses;
    int wrongGuesses;
    std::string currentCategory;

public:
    WordGuessingGame() : maxWrongGuesses(6), wrongGuesses(0) {
        // Initialize categories with words
        categories["animals"] = {"elephant", "tiger", "lion", "giraffe", "zebra", "monkey", "panda", "koala", "kangaroo", "cheetah"};
        categories["teams"] = {"manchester", "liverpool", "chelsea", "arsenal", "barcelona", "madrid", "bayern", "juventus", "psg", "dortmund"};
        categories["districts"] = {"manhattan", "brooklyn", "queens", "bronx", "statenisland", "downtown", "uptown", "midtown", "harlem", "soho"};
        categories["films"] = {"inception", "matrix", "avatar", "titanic", "interstellar", "gladiator", "casablanca", "godfather", "shawshank", "avatar"};
        categories["books"] = {"harrypotter", "lordoftherings", "hobbit", "dune", "foundation", "neuromancer", "snowcrash", "ender", "hitchhiker", "dune"};

        std::srand(std::time(0));
    }

    void showMenu() {
        std::cout << "=== WORD GUESSING GAME ===" << std::endl;
        std::cout << "Select a category:" << std::endl;
        std::cout << "1. Animals" << std::endl;
        std::cout << "2. Teams" << std::endl;
        std::cout << "3. Districts" << std::endl;
        std::cout << "4. Films" << std::endl;
        std::cout << "5. Books" << std::endl;
        std::cout << "Enter your choice (1-5): ";
    }

    std::string getCategory(int choice) {
        switch (choice) {
            case 1: return "animals";
            case 2: return "teams";
            case 3: return "districts";
            case 4: return "films";
            case 5: return "books";
            default: return "";
        }
    }

    void selectRandomWord(const std::string& category) {
        currentCategory = category;
        const std::vector<std::string>& words = categories[category];
        secretWord = words[std::rand() % words.size()];

        // Initialize display word with underscores
        displayWord = "";
        for (char c : secretWord) {
            displayWord += (c == ' ') ? ' ' : '_';
        }

        guessedLetters.clear();
        wrongGuesses = 0;
    }

    void showGameState() {
        std::cout << "\nCategory: " << currentCategory << std::endl;
        std::cout << "Word: " << displayWord << std::endl;
        std::cout << "Wrong guesses: " << wrongGuesses << "/" << maxWrongGuesses << std::endl;
        std::cout << "Guessed letters: ";
        for (char c : guessedLetters) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
    }

    void processGuess(char letter) {
        letter = std::tolower(letter);

        // Check if letter was already guessed
        for (char c : guessedLetters) {
            if (std::tolower(c) == letter) {
                std::cout << "You already guessed '" << letter << "'. Try another letter." << std::endl;
                return;
            }
        }

        guessedLetters.push_back(letter);
        bool found = false;

        // Update display word
        for (size_t i = 0; i < secretWord.length(); i++) {
            if (std::tolower(secretWord[i]) == letter) {
                displayWord[i] = secretWord[i];
                found = true;
            }
        }

        if (!found) {
            wrongGuesses++;
            std::cout << "Wrong guess! '" << letter << "' is not in the word." << std::endl;
        } else {
            std::cout << "Good guess! '" << letter << "' is in the word." << std::endl;
        }
    }

    bool isGameWon() {
        return displayWord == secretWord;
    }

    bool isGameLost() {
        return wrongGuesses >= maxWrongGuesses;
    }

    void playGame() {
        showMenu();
        int choice;
        std::cin >> choice;

        std::string category = getCategory(choice);
        if (category.empty()) {
            std::cout << "Invalid choice! Game over." << std::endl;
            return;
        }

        selectRandomWord(category);

        std::cout << "Game started! Try to guess the word." << std::endl;

        while (!isGameWon() && !isGameLost()) {
            showGameState();

            std::string input;
            std::cout << "Enter a letter (or 'exit' to quit): ";
            std::cin >> input;

            if (input == "exit") {
                std::cout << "Thanks for playing! The word was: " << secretWord << std::endl;
                return;
            }

            if (input.length() != 1 || !std::isalpha(input[0])) {
                std::cout << "Please enter a single letter!" << std::endl;
                continue;
            }

            char letter = input[0];
            processGuess(letter);
        }

        showGameState();

        if (isGameWon()) {
            std::cout << "Congratulations! You won!" << std::endl;
            std::cout << "You guessed the word: " << secretWord << std::endl;
        } else {
            std::cout << "Game Over! You lost!" << std::endl;
            std::cout << "The word was: " << secretWord << std::endl;
        }
    }

    bool askPlayAgain() {
        std::string choice;
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> choice;

        return (choice == "y" || choice == "Y" || choice == "yes" || choice == "YES");
    }
};

int main() {
    WordGuessingGame game;

    do {
        game.playGame();
    } while (game.askPlayAgain());

    std::cout << "Thanks for playing the Word Guessing Game!" << std::endl;

    return 0;
}
