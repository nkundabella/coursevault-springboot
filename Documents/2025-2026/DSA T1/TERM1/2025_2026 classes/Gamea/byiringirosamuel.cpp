#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

void displayWord(const std::string& word, const std::string& guessed) {
    for (char c : word) {
        if (guessed.find(c) != std::string::npos)
            std::cout << c;
        else
            std::cout << "_";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<std::string> teams = {
        "arsenal", "astonvilla", "bournemouth", "brentford", "chelsea", "crystalpalace", "everton", "fulham", "liverpool", "luten",
        "manchesterunited", "manchestercity", "newcastle", "nottinghamforest", "sheffieldunited", "tottenham", "westham", "wolves",
        "leedsunited", "burnley", "sunderland", "realmadrid"
    };

    std::srand(std::time(nullptr));

    char playAgain = 'y';
    while (playAgain == 'y' || playAgain == 'Y') {
        int index = std::rand() % teams.size();
        std::string word = teams[index];
        std::string guessedLetters = "";
        int chances = 6;
        std::string input;

        std::cout << "Guess the football club! Type 'exit' to quit.\n";

        while (chances > 0) {
            displayWord(word, guessedLetters);
            std::cout << "Chances left: " << chances << "\nEnter a letter: ";
            std::cin >> input;

            if (input == "exit") {
                std::cout << "Exiting the game.\n";
                return 0;
            }

            if (input.length() != 1) {
                std::cout << "Please enter only a single letter.\n";
                continue;
            }

            char letter = input[0];

            if (word.find(letter) != std::string::npos) {
                if (guessedLetters.find(letter) == std::string::npos)
                    guessedLetters += letter;
            } else {
                chances--;
            }

            bool complete = true;
            for (char c : word) {
                if (guessedLetters.find(c) == std::string::npos) {
                    complete = false;
                    break;
                }
            }

            if (complete) {
                std::cout << "Congratulations! You guessed the team: " << word << std::endl;
                break;
            }
        }

        if (chances == 0) {
            std::cout << "Out of chances! The team was: " << word << std::endl;
        }

        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}
