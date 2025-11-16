#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0)); // only once at start

    //categories
    string Animals[] = {"elephant","tiger","lion","crocodile","zebra","monkey"};
    string Artists[] = {"Mbonyi","Chriss Eazy","Meddy","Bruce Melodie","Element","Kevin Kade"};
    string Soccerplayers [] ={"Messi","Ronaldo","Kylian Mbappe","Yamal","Dembele","jude Bellingham"};

    char playAgain = 'y';  

    while (playAgain == 'y' || playAgain == 'Y') {
        //choice
        int choice;
        cout << "\nChoose a category\n";
        cout << "1. Animals\n2. Artists\n3. Soccer Players\n";
        cin >> choice;

        //words
        string word;
        if (choice == 1) {
            int index = rand() % 6;
            word = Animals[index];
        } else if (choice == 2) {
            int index = rand() % 6;
            word = Artists[index];
        } else if (choice == 3) {
            int index = rand() % 6;
            word = Soccerplayers[index];
        } else {
            cout << "Invalid choice." << endl;
            continue; // restart the loop if invalid choice
        }

        //make words lowercase
        for (int i = 0; i < word.length(); i++) {
            word[i] = tolower(word[i]);
        }

        //hidden word
        string hidden(word.length(), '_');

        //keep spaces visible
        for (int i = 0; i < word.length(); i++) {
            if (word[i] == ' ') hidden[i] = ' ';
        }

        int chances = 6;
        bool won = false;
        cout << "\nWord to guess: " << hidden << endl;

        //game loop
        while (chances > 0) {
            char guess;
            cout << "\nEnter a letter (or 0 to quit this game): ";
            cin >> guess;

            if (guess == '0') {
                cout << "Game exited." << endl;
                break;
            }

            guess = tolower(guess);
            bool correct = false;

            //check each letter
            for (int i = 0; i < word.length(); i++) {
                if (word[i] == guess && hidden[i] == '_') {
                    hidden[i] = guess;
                    correct = true;
                }
            }

            if (correct) {
                cout << "Correct! " << hidden << endl;
            } else {
                chances--;
                cout << "Wrong! Chances left: " << chances << endl;
                cout << "Word to guess: " << hidden << endl;
            }

            //win condition
            if (hidden == word) {
                won = true;
                cout << "\n🎉 You win! The word was: " << word << endl;
                break;
            }

            //lose condition
            if (hidden != word && chances == 0) {
                cout << "\n❌ You lose! The word was: " << word << endl;
            }
        }

        //ask if user wants to continue
        cout << "\nDo you want to play again? (y/n): ";
        cin >> playAgain;
    }

    cout << "\nThanks for playing Hangman! 👋\n";
    return 0;
}
