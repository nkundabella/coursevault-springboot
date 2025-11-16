#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

int generateRandom(int size) {
    return rand() % size;
}

void game(string word) {
    int trials = 20;
    int wordLength = word.length();
    string guessed(wordLength, '_');
    string input;

    while (true) {
        while (trials > 0) {
            cout << "\nWord: " << guessed << endl;
        cout << "Enter a letter (or type 'exit' to quit): ";
            cin >> input;

            if (input == "exit") {
                cout << "Game exited!" << endl;
                return;
            }

            if (input.length() != 1) {
                cout << "Please enter only one letter." << endl;
                continue;
            }

            char letter = input[0];
            bool found = false;

            for (int i = 0; i < wordLength; i++) {
            if (word[i] == letter) {
                    guessed[i] = letter;
                    found = true;
                }
            }

            if (!found) {
                trials--;
                cout << "Wrong guess! Trials left: " << trials << endl;
            }

            if (guessed == word) {
                cout << "\nCongratulations! You guessed the word: " << word << endl;
                break;
            }
        }

        if (guessed != word) {
            cout << "\nYou ran out of trials! The word was: " << word << endl;
        }

        string choice;
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;

        if (choice != "y") {
            return;
        }

        trials = 20;
        guessed = string(wordLength, '_');
        int index = generateRandom(10);
    }
}

int main() {
    srand(time(0));

    string plants[10] = {"rose", "sunflower", "aloe vera", "bamboo", "tulip", "cactus", "lavender", "mango-tree", "fern", "oak-tree"};
    string animals[10] = {"lion", "elephant", "giraffe", "dolphin", "eagle", "kangaroo", "zebra", "panda", "crocodile", "gorilla"};
    string carBrands[10] = {"toyota", "bmw", "mercedes-benz", "honda", "ford", "audi", "nissan", "hyundai", "volkswagen", "tesla"};
    string clothingBrands[10] = {"nike", "adidas", "puma", "gucci", "zara", "h&m", "louis vuitton", "under armour", "levi's", "prada"};

    while (true) {
        cout << "Word Guess Game\n=================" << endl;
        cout << "Choose a category by typing its number: \n1. Plants\n2. Animals\n3. Car brands\n4. Clothing brands\n";

        int choice;
        cin >> choice;
        int index = 0;
        string word;

        switch(choice) {
            case 1:
                index = generateRandom(10);
                word = plants[index];
                break;
            case 2:
                index = generateRandom(10);
                word = animals[index];
                break;
            case 3:
                index = generateRandom(10);
                word = carBrands[index];
                break;
            case 4:
                index = generateRandom(10);
                word = clothingBrands[index];
                break;
            default:
                cout << "Invalid choice!" << endl;
                continue;
        }

        game(word);

        string playAgain;
        cout << "Do you want to choose a new category? (y/n): ";
        cin >> playAgain;
        if (playAgain != "y") {
            break;
        }
    }

    return 0;
}
