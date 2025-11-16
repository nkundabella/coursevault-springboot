#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main() {
    // Word categories
    string animals[] = {"elephant", "tiger", "lion", "giraffe"};
    string teams[] = {"liverpool", "chelsea", "arsenal", "barcelona"};
    string districts[] = {"kigali", "nyarugenge", "gasabo", "kicukiro"};
    string films[] = {"inception", "avatar", "titanic", "interstellar"};
    string books[] = {"harrypotter", "lotr", "hobbit", "dune"};

    string playAgain = "yes";

    while(playAgain == "yes") {
        cout << "Select a category:\n";
        cout << "1. Animals\n2. Teams\n3. Districts\n4. Films\n5. Books\n";
        int choice;
        cin >> choice;

        string word = "";
        int wordIndex;

        // Randomly select a word
        srand(time(0));
        if(choice == 1) word = animals[rand() % 4];
        else if(choice == 2) word = teams[rand() % 4];
        else if(choice == 3) word = districts[rand() % 4];
        else if(choice == 4) word = films[rand() % 4];
        else if(choice == 5) word = books[rand() % 4];
        else {
            cout << "Invalid choice! Try again.\n";
            continue;
        }

        string guessed = "";       // Letters guessed by user
        string display = "";       // Word display with underscores
        int chances = 10;

        // Initialize display with underscores
        for(int i = 0; i < word.length(); i++)
            display += "_";

        bool won = false;

        while(chances > 0) {
            cout << "\nWord: " << display << endl;
            cout << "Chances left: " << chances << endl;
            cout << "Guess a letter (or type 'exit' to quit): ";
            string input;
            cin >> input;

            if(input == "exit") {
                cout << "Exiting game.\n";
                return 0;
            }

            char letter = input[0];

            // Check if letter is in the word
            bool found = false;
            for(int i = 0; i < word.length(); i++) {
                if(word[i] == letter) {
                    display[i] = letter;  // Reveal letter
                    found = true;
                }
            }

            if(!found) {
                chances--; // Wrong guess
            }

            // Check if word is completely guessed
            if(display == word) {
                won = true;
                break;
            }
        }

        if(won) cout << "Congratulations! You guessed the word: " << word << endl;
        else cout << "Out of chances! The word was: " << word << endl;

        cout << "Do you want to play again? (yes/no): ";
        cin >> playAgain;
    }

    cout << "Thanks for playing!\n";
    return 0;
}
