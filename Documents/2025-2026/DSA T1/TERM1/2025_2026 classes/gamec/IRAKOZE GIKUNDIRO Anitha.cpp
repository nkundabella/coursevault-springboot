#include <iostream>
#include <string>
using namespace std;

int main() {
    string words[5] = {"pencil", "apple", "lion", "chair", "eagle"};
    string hints[5] = {"a school tool", "a fruit", "an animal", "a furniture", "a bird"};
cout<<"Welcome to Anitha's Guess the world game!!"<<endl;
    for (int w = 0; w < 5; w++) {
        string word = words[w];
        string hint = hints[w];
        string hidden(word.length(), '-');

        
        hidden[0] = word[0];
        hidden[word.length() / 2] = word[word.length() / 2];

        int wrong = 1;
        cout << "\nCan you guess the word: " << hidden << endl;

        while (hidden != word) {
            string guess;
            cout << "Enter your  guess: ";
            cin >> guess;

            bool anyCorrect = false;

   
            for (int i = 0; i < word.length() && i < guess.length(); i++) {
                if (guess[i] == word[i] && hidden[i] == '-') {
                    hidden[i] = word[i];
                    anyCorrect = true;
                }
            }

            if (!anyCorrect) {
                wrong++;
                cout << "Not true! " << endl;
                if (wrong == 3) {
                    cout << "Hint: It's " << hint << endl;
                }
            }

            cout << hidden << endl;

            if (hidden == word) {
                cout << "Good one! The word is: " << word << endl;
                break;
            }
        }
    }

    cout << "\nGame Over! You tried all 5 words." << endl;
    return 0;
}

