#include <iostream>
#include <cstdlib>
#include <ctime> 
#include <cctype> 

using namespace std;

void displayWord(const string& word, bool Guessed[]) {
    for (int i = 0; i < word.length(); i++) {
        if (Guessed[i])
            cout << word[i];
        else
            cout << "_";
    }
    cout << endl;
}

int main() {
    srand(time(0));

    string animals[] = {"elephant", "tiger", "giraffe", "kangaroo", "zebra"};
    string teams[] = {"warriors", "lakers", "arsenal", "barcelona", "celtics"};
    string districts[] = {"kigali", "nyarugenge", "gasabo", "ruhanga", "huye"};
    string films[] = {"inception", "avatar", "titanic", "gladiator", "matrix"};
    string books[] = {"hobbit", "dune", "it", "lotr", "gatsby"};

    int animalsSize = sizeof(animals)/sizeof(animals[0]);
    int teamsSize = sizeof(teams)/sizeof(teams[0]);
    int districtsSize = sizeof(districts)/sizeof(districts[0]);
    int filmsSize = sizeof(films)/sizeof(films[0]);
    int booksSize = sizeof(books)/sizeof(books[0]);

    bool keepPlaying = true;

    while (keepPlaying) {
        cout << "Select a category:\n";
        cout << "1. Animals\n2. Teams\n3. Districts\n4. Films\n5. Books\n";
        int choice;
        cin >> choice;

        string word;
        switch (choice) {
            case 1: word = animals[rand() % animalsSize]; break;
            case 2: word = teams[rand() % teamsSize]; break;
            case 3: word = districts[rand() % districtsSize]; break;
            case 4: word = films[rand() % filmsSize]; break;
            case 5: word = books[rand() % booksSize]; break;
            default: 
                cout << "Invalid choice. Defaulting to Animals.\n";
                word = animals[rand() % animalsSize];
        }

        bool Guessed[word.length()];
        for (int i = 0; i < word.length(); i++)
            Guessed[i] = false;

        int chances = 10;
        bool wordGuessed = false;

        cout << "Guess the word! Type a letter or 'exit' to quit.\n";

        while (chances > 0 && !wordGuessed) {
            displayWord(word, Guessed);
            cout << "Chances left: " << chances << "\nEnter a letter: ";
            string input;
            cin >> input;

            if (input == "exit") {
                cout << "Exiting game.\nThank you for trying.";
                return 0;
            }

            if (input.length() != 1 || !isalpha(input[0])) {
                cout << "Please enter a single letter.\n";
                continue;
            }

            char guess = tolower(input[0]);
            bool correct = false;
            for (int i = 0; i < word.length(); i++) {
                if (word[i] == guess && !Guessed[i]) {
                    Guessed[i] = true;
                    correct = true;
                }
            }

            if (!correct) {
                cout << "Wrong guess!\n";
                chances--;
            }

            wordGuessed = true;
            for (int i = 0; i < word.length(); i++) {
                if (!Guessed[i]) {
                    wordGuessed = false;
                    break;
                }
            }
        }

        if (wordGuessed) {
            cout << "Congratulations! You Guessed the word: " << word << endl;
        } else {
            cout << "Out of chances! The word was: " << word << endl;
        }

        cout << "Do you want to play again? (y/n): ";
        char again;
        cin >> again;
        keepPlaying = (again == 'y' || again == 'Y');
    }

    cout << "Thanks for playing!\n";
    return 0;
}
