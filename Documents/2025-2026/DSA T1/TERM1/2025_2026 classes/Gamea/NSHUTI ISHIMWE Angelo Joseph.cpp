#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

string randomWord(const string words[], int size) {
    int nber = rand() % size;
    return words[nber];
}

void displayWord(const string& word, const char guessed[], int guessedCount) {
    for (int i = 0; i < word.length(); i++) {
        bool found = false;
        for (int j = 0; j < guessedCount; j++) {
            if (guessed[j] == word[i]) {
                found = true;
                break;
            }
        }
        cout << (found ? word[i] : '_') << " ";
    }
    cout << endl;
}

bool guessedWord(const string& word, const char guessed[], int guessedCount) {
    for (int i = 0; i < word.length(); i++) {
        bool found = false;
        for (int j = 0; j < guessedCount; j++) {
            if (guessed[j] == word[i]) {
                found = true;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}

int main() {
    string players[]  = {"cristiano", "dybala", "olmo", "messi", "rashford"};
    string teams[]    = {"arsenal", "realmadrid", "juventus", "roma", "dortmund"};
    string movies[]   = {"baywatch", "gladiator", "encharted", "wolfpack", "wildflower"};
    string foods[]    = {"burger", "pizza", "sandwich", "noodles", "chicken"};
    string cars[]     = {"bmw", "mercedes", "bugatti", "lamborghini", "challenger"};

    bool play = true;

    while (play) {
        cout << "**** WORD GUESS GAME ****" << endl;
        cout << "Select the category: " << endl;
        cout << "1. Players" << endl;
        cout << "2. Football teams" << endl;
        cout << "3. Movies" << endl;
        cout << "4. Foods" << endl;
        cout << "5. Cars" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        string word;
        switch (choice) {
            case 1:
                word = randomWord(players, 5);
                break;
            case 2:
                word = randomWord(teams, 5);
                break;
            case 3:
                word = randomWord(movies, 5);
                break;
            case 4:
                word = randomWord(foods, 5);
                break;
            case 5:
                word = randomWord(cars, 5);
                break;
            default:
                cout << "INVALID INPUT. DEFAULT IS PLAYERS" << endl;
                word = randomWord(players, 5);
        }

        char guessed[26];
        int guessedCount = 0;
        int chances = 5;
        string input;

        cout << "\nThe game begins! Take a guess..." << endl;

        while (chances > 0) {
            displayWord(word, guessed, guessedCount);
            cout << "Chances left: " << chances << endl;
            cout << "Enter a letter(Type 'exit' to exit.): ";
            cin >> input;

            if (input == "exit") {
                cout << "Game ended." << endl;
                return 0;
            } else if (input.length() != 1 || !isalpha(input[0])) {
                cout << "Enter a valid letter!" << endl;
                continue;
            }

            char guess = tolower(input[0]);

            bool alreadyGuessed = false;
            for (int i = 0; i < guessedCount; i++) {
                if (guessed[i] == guess) {
                    alreadyGuessed = true;
                    break;
                }
            }

            if (alreadyGuessed) {
                cout << "You already guessed that letter. Try again." << endl;
                continue;
            }

            guessed[guessedCount++] = guess;

            if (word.find(guess) == string::npos) {
                cout << "Bad guess. Try again." << endl;
                chances--;
            } else if (guessedWord(word, guessed, guessedCount)) {
                cout << "Congratulations! You guessed the word: " << word << endl;
                break;
            }
        }

        if (!guessedWord(word, guessed, guessedCount)) {
            cout << "Your chances are over. The word was: " << word << endl;
        }

        cout << "Do you want to play again? (Y/N): ";
        char playAgain;
        cin >> playAgain;
        play = (playAgain == 'y' || playAgain == 'Y');
    }

    cout << "Goodbye!!" << endl;
    return 0;
}
