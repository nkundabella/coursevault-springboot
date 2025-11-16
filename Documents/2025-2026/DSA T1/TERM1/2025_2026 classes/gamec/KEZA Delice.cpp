#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
using namespace std;

string getMaskedWord(const string& word, const vector<char>& guessedLetters) {
    string maskedWord = "";
    for (char c : word) {
        if (find(guessedLetters.begin(), guessedLetters.end(), c) != guessedLetters.end()) {
            maskedWord += c;
        } else {
            maskedWord += "_";
        }
    }
    return maskedWord;
}

int main() {
    srand(time(0));

   
    vector<string> drinks = {"coke", "pepsi", "fanta", "sprite", "mirinda"};
    vector<string> cars = {"toyota", "bmw", "mercedes", "audi", "honda"};
    vector<string> phones = {"iphone", "samsung", "xiaomi", "tecno", "itel"};
    vector<string> animes = {"naruto", "onepiece", "bleach", "attackontitan", "deathnote"};
    vector<string> books = {"hamlet", "odyssey", "inferno", "frankenstein", "dune"};
    vector<string> brands = {"nike", "adidas", "puma", "gucci", "louisvuitton", "hm"};
    vector<string> songs = {"shapeofyou", "blindinglights", "believer", "perfect", "hallelujah"};
    vector<string> snacks = {"chips", "mandazi", "samosa", "popcorn", "chocolate"};
    vector<string> sports = {"soccer", "tennis", "cricket", "rugby", "hockey"};
    vector<string> sites = {"eiffel", "statueofliberty", "colosseum", "pyramids", "machupicchu"};

    bool playAgain = true;

    while (playAgain) {
        cout << "=============================\n";
        cout << "   WORD GUESSING GAME\n";
        cout << "=============================\n";
        cout << "Choose a category:\n";
        cout << "1. Drinks\n";
        cout << "2. Cars\n";
        cout << "3. Phones\n";
        cout << "4. Animes\n";
        cout << "5. Books\n";
        cout << "6. Brands\n";
        cout << "7. Songs\n";
        cout << "8. Snacks\n";
        cout << "9. Sports\n";
        cout << "10. Sites\n";
        cout << "Enter choice (1-10): ";

        int choice;
        cin >> choice;

        vector<string> selectedCategory;

        switch (choice) {
            case 1: selectedCategory = drinks; break;
            case 2: selectedCategory = cars; break;
            case 3: selectedCategory = phones; break;
            case 4: selectedCategory = animes; break;
            case 5: selectedCategory = books; break;
            case 6: selectedCategory = brands; break;
            case 7: selectedCategory = songs; break;
            case 8: selectedCategory = snacks; break;
            case 9: selectedCategory = sports; break;
            case 10: selectedCategory = sites; break;
            default:
                cout << "Invalid choice. Exiting...\n";
                return 0;
        }

        string word = selectedCategory[rand() % selectedCategory.size()];
        vector<char> guessedLetters;
        int chances = 6;

        cout << "\nA word has been chosen. Start guessing letters!\n";
        cout << "Type 'exit' anytime to quit.\n\n";

        while (chances > 0) {
            cout << "Word: " << getMaskedWord(word, guessedLetters) << endl;
            cout << "Chances left: " << chances << endl;
            cout << "Enter a letter: ";

            string input;
            cin >> input;

            if (input == "exit") {
                cout << "Exiting the game...\n";
                return 0;
            }

            char guess = tolower(static_cast<unsigned char>(input[0]));

            if (find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
                cout << "You already guessed that letter!\n";
                continue;
            }

            guessedLetters.push_back(guess);

            if (word.find(guess) != string::npos) {
                cout << "Good guess!\n";
            } else {
                cout << "Wrong guess!\n";
                chances--;
            }

            if (getMaskedWord(word, guessedLetters) == word) {
                cout << "\n🎉 Congratulations! You've guessed the word: " << word << "\n";
                break;
            }
        }

        if (chances == 0) {
            cout << "\n❌ You ran out of chances! The word has been: " << word << "\n";
        }

        cout << "\nDo you want to play again? (y/n): ";
        char again;
        cin >> again;
        playAgain = (again == 'y' || again == 'Y');
    }

    cout << "Thanks for playing the game!\n";
    return 0;
}
