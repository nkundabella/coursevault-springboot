#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype> 
using namespace std;

int main() {
    // Classmates for each classes in year two
    string Y2C[] = {"Kennedy", "Alain", "Fanny", "Sacha", "Bonnete"};
    string Y2C_Hints[] = {
        "Mac user kbx", 
        "Ati why share on the internet yet we have bluetooth😂😂", 
        "The crypto queen of class😏", 
        "Late comer wabigiz umwug kbx😂😂 ark mugihe aband bigir class meny we afatira dorm", 
        "Y2's Lady whistledown😂😂 usigay uri bedzz kuri swift kbx😏"
    };
    
    string Y2B[] = {"Christella", "Kelia", "Melissa", "Winner", "Joshua"};
    string Y2B_Hints[] = {
        "Always in C muri break😂😂 ark aside she's a three js babe😏", 
        "If it’s flat, she makes it 3D😏", 
        "Ati ndi umuhanga nte? na Informatics camp sinz uko nagezey😂", 
        "Deep voice, silent thinker — only the chosen hear him😏😏", 
        "King of the chessboard and smooth walker"
    };
    
    string Y2A[] = {"Brian", "Yanis", "Zion", "Navis"};
    string Y2A_Hints[] = {
        "Forensics yokwica😏 ark arifat akurira music and dance club🙄", 
        "Frontend s' ibye kbx nabyihorer😂😂 ark ati Backend yokwiciray nk' utu moves twa show😏", 
        "Blessed and busy talking to heaven ark hagati aho barabiz ni na chef😂", 
        "Brotherhood N' money ati ngew semi kbx niyo yange abakobw ntakirim😂😂"
    };

    srand(time(0)); //seed for random
    
    string again = "yes";

    while (again == "yes") {
        int gamer_choice;
        cout << "\n🎯 Guess the Classmate Game!\n";
        cout << "Choose a category:\n";
        cout << "1. Y2A\n2. Y2B\n3. Y2C\nEnter choice: ";
        cin >> gamer_choice;

        string* classmates;
        string* hints;
        int size;

        if (gamer_choice == 1) {
            classmates = Y2A;
            hints = Y2A_Hints;
            size = sizeof(Y2A) / sizeof(Y2A[0]);
        } else if (gamer_choice == 2) {
            classmates = Y2B;
            hints = Y2B_Hints;
            size = sizeof(Y2B) / sizeof(Y2B[0]);
        } else if (gamer_choice == 3) {
            classmates = Y2C;
            hints = Y2C_Hints;
            size = sizeof(Y2C) / sizeof(Y2C[0]);
        } else {
            cout << "Invalid choice! Exiting...\n";
            return 0;
        }

        int index = rand() % size; // pick random classmate
        string word = classmates[index];
        string guessed(word.length(), '_');
        string usedLetters = "";
        int chances = 6;
        char letter;

        cout << "\nHint: " << hints[index] << endl;

        // Real Game loop
        while (chances > 0 && guessed != word) {
            cout << "\nWord: ";
            for (int i = 0; i < guessed.length(); i++) cout << guessed[i] << " ";
            cout << "\nChances left: " << chances << endl;
            cout << "Used letters: " << usedLetters << endl;
            cout << "Enter a letter (or 0 to exit): ";
            cin >> letter;

            if (letter == '0') {
                cout << "Exiting game...\n";
                return 0;
            }

            // To lowercase for easy comparision
            letter = tolower(letter);

            if (usedLetters.find(letter) != string::npos) {
                cout << "⚠️ Already guessed '" << letter << "'\n";
                continue;
            }
            usedLetters += letter;

            bool correct = false;
            for (int i = 0; i < word.length(); i++) {
                if (tolower(word[i]) == letter) {
                    guessed[i] = word[i];
                    correct = true;
                }
            }

            if (correct) cout << "✅ Correct guess!\n";
            else {
                chances--;
                cout << "❌ Wrong guess!\n";
            }
        }

        // End of game
        if (guessed == word)
            cout << "\n🎉 You guessed it! The name is " << word << endl;
        else
            cout << "\n💀 You lost! The name was " << word << endl;

        cout << "Do you want to play again? (yes/no): ";
        cin >> again;
    }

    cout << "Thanks for playing!\n";
    return 0;
}
