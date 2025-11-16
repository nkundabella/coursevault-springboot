#include <iostream>
using namespace std;

bool containsChar(string word, char c) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == c)
            return true;
    }
    return false;
}

void updateDisplay(string word, string &display, char guess) {
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == guess)
            display[i] = guess;
    }
}

int main() {
    string word;
    cout<<"Enter the word to be guessed (no spaces): ";
    cin>>word;

    for (int i=0; i<50; i++) cout<<endl;

    string display(word.length(), '_');
    int chancesLeft = 6;
    string guess;

    cout<<"Start guessing the word: "<<display<<endl;

    while (chancesLeft > 0) {
        cout<<"Enter a letter / type 'exit' to quit): ";
        cin>>guess;

        if (guess == "exit") {
            return 0;
        }

        char letter = guess[0];

        if (containsChar(word, letter)) {
            updateDisplay(word, display, letter);
            cout<<"Correct! "<<display<<endl;
        } else {
            chancesLeft--;
            cout<<"Wrong! Chances left: "<<chancesLeft<<endl;
        }

        if (display == word) {
            cout<<"Congratulations! "<<word<<endl;
            break;
        }
    }

    if (display != word)
        cout <<"You ran out of chances! The word was: "<<word<<endl;

    return 0;
}
