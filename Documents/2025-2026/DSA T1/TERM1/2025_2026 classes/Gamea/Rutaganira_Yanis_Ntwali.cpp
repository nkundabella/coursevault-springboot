#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string vibeCheck(const string& mysteryWord, const string& trialWord, string& puzzleMask) {
    string chatter = "";
    for (int slot = 0; slot < 5; slot++) {
        if (trialWord[slot] == mysteryWord[slot]) {
            chatter += "[ " + string(1, trialWord[slot]) + " ] ";
            puzzleMask[slot] = mysteryWord[slot];
        } else if (mysteryWord.find(trialWord[slot]) != string::npos) {
            chatter += "( " + string(1, trialWord[slot]) + " ) ";
        } else {
            chatter += "  " + string(1, trialWord[slot]) + "   ";
        }
    }
    return chatter;
}

int main() {
    string hiddenSnack = "APPLE";
    string playerScribble;
    int lives = 6;
    string masky = "_____";

    cout << "Welcome to Word Jumble++!" << endl;
    cout << "You’ve got " << lives << " shots to crack the 5-letter riddle." << endl;

    while (lives > 0) {
        cout << "\nMystery so far: " << masky << endl;
        cout << "Your move (5 letters): ";
        cin >> playerScribble;

        transform(playerScribble.begin(), playerScribble.end(), playerScribble.begin(), ::toupper);

        if (playerScribble.length() != 5) {
            cout << "Nope, gotta be 5 letters." << endl;
            continue;
        }

        if (playerScribble == hiddenSnack) {
            cout << "Boom! You nailed it: " << hiddenSnack << endl;
            return 0;
        }

        cout << "Clues: " << vibeCheck(hiddenSnack, playerScribble, masky) << endl;
        lives--;
        cout << "Lives left: " << lives << endl;
    }

    cout << "\nOut of juice! The word was: " << hiddenSnack << endl;
    return 0;
}
