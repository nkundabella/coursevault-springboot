#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

string getRandomWord(const vector<string>& category) {
    int index = rand() % category.size();
    return category[index];
}

void showHangman(int chancesLeft) {
    vector<string> stages = {
        "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n",
        "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n"
    };
    cout << stages[chancesLeft] << endl;
}

int main() {
    srand(time(0));
    int wins = 0, losses = 0;
    bool playAgain = true;

    vector<string> mythCreatures = {"phoenix", "kraken", "leviathan", "banshee", "kitsune"};
    vector<string> sciFiTech     = {"warpdrive", "nanobots", "cyberdome", "quantumchip", "neuralink"};
    vector<string> planets       = {"kepler22b", "proxima", "europa", "titan", "trappist1e"};
    vector<string> hackers       = {"zerocool", "acidburn", "cypherpunk", "darkphantom", "rootkit"};
    vector<string> mysteries     = {"bermudatriangle", "el-dorado", "atlantis", "stonehenge", "nazcalines"};

    while (playAgain) {
        cout << "\n=== WORD GUESSING GAME ===\n";
        cout << "Choose a category:\n1. Mythical Creatures\n2. Sci-Fi Tech\n3. Planets\n4. Hackers\n5. Mysteries\n";
        int choice;
        cin >> choice;

        string word;
        if (choice == 1) word = getRandomWord(mythCreatures);
        else if (choice == 2) word = getRandomWord(sciFiTech);
        else if (choice == 3) word = getRandomWord(planets);
        else if (choice == 4) word = getRandomWord(hackers);
        else word = getRandomWord(mysteries);

        string hidden(word.size(), '_');
        int chances = 6; 

        cout << "You have " << chances << " chances. Guess one letter at a time.\n";

        while (chances >= 0 && hidden != word) {
            cout << "\nWord: " << hidden << endl;
            showHangman(chances);

            cout << "Guess a letter: ";
            char letter;
            cin >> letter;

            bool found = false;
            for (int i = 0; i < (int)word.size(); i++) {
                if (word[i] == letter) {
                    hidden[i] = letter;
                    found = true;
                }
            }

            if (found) {
                cout << "Correct!\n";
            } else {
                chances--;
                cout << "Wrong! Chances left: " << chances << endl;
            }
        }

        if (hidden == word) {
            cout << "\nYuhuuuu ?? You guessed it! The word was: " << word << endl;
            wins++;
        } else {
            cout << "\nYou failed ?? The word was: " << word << endl;
            losses++;
        }

        cout << "Score -> Wins: " << wins << " | Losses: " << losses << endl;
        cout << "Play again? (y/n): ";
        char ans;
        cin >> ans;
        playAgain = (ans == 'y' || ans == 'Y');
    }

    cout << "\nTHANK YOU FOR PLAYING!\nFINAL SCORE -> Wins: " << wins << " | Losses: " << losses << endl;
    return 0;
}
