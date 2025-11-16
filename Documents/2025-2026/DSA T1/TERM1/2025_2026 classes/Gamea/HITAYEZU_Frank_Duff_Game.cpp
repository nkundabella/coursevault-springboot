#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>
#include <set>
using namespace std;

int main(){
    srand(time(0));
    int numCategories = 3;
    string categories[numCategories] {"Animals","Teams","Cities"};
    int numWords = 3;
    string words[numCategories][numWords] = {
        {"Tiger","Penguin","Boar"},
        {"Lakers","Warriors","Spurs"},
        {"Texas","Tokyo","Beijing"}
    };
    string playAgain;

    cout << "============================================" << endl;
    cout << "   Welcome to the Word Guessing Game " << endl;
    cout << "============================================" << endl << endl;

    do {
        int choice;

        do {
            cout<<"Choose a category to continue:"<<endl;
            cout<<"  1. Animals"<<endl;
            cout<<"  2. Teams"<<endl;
            cout<<"  3. Cities"<<endl;
            cout<<endl<<"Enter your choice (1-3): ";

            cin>>choice;

            if(cin.fail()){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout<<"\nInvalid input! Please enter a number between 1 and 3.\n\n";
                choice = -1;
            } else if(choice < 1 || choice > numCategories){
                cout<<"\nInvalid choice! Please enter 1, 2 or 3.\n\n";
            }

        } while(choice < 1 || choice > numCategories);

        choice--;
        int index = rand() % numWords;
        string chosenWord = words[choice][index];

        for(char &c : chosenWord){
            c = tolower(c);
        }

        string hiddenWord(chosenWord.length(), '_');
        set<char> guessedLetters;
        int chances = 6;

        cout<<"\nYou chose: "<<categories[choice]<<endl;
        cout<<"Your word has "<<chosenWord.length()<<" letters."<<endl;
        cout<<"You have 6 chances to guess it!"<<endl<<endl;
        cout<<"Guess the word: "<<hiddenWord<<endl<<endl;

        while(chances > 0 && hiddenWord != chosenWord){
            string input;
            cout<<"Enter a letter to continue or type 'exit' to quit: ";
            cin>>input;
            cout<<endl;

            if(input == "exit" ||input == "Exit" || input== "EXIT"){
                cout<<"Game exited. Thanks for playing!"<<endl;
                return 0;
            }

            if(input.length() != 1 || !isalpha(input[0])){
                cout<<"Invalid input! Please enter a single letter.\n\n";
                continue;
            }

            char guess = tolower(input[0]);

            if(guessedLetters.count(guess)){
                cout<<"You already guessed '"<<guess<<"'. Try a different letter.\n\n";
                continue;
            }
            guessedLetters.insert(guess);

            bool correct = false;
            for(int i=0;i<chosenWord.length();i++){
                if(chosenWord[i]==guess){
                    hiddenWord[i] = guess;
                    correct = true;
                }
            }

            if(!correct){
                chances--;
                cout<<"Wrong guess! Chances left: "<< chances<<endl;
                cout<<"Don't give up yet!\n\n";
            } else {
                cout<<"Good guess!\n\n";
            }

            cout<<"Current word: "<<hiddenWord<<endl<<endl;
        }

        if(hiddenWord == chosenWord){
            cout<<"Congrats, you guessed the word! It was: "<<chosenWord<<endl<<endl;
        } else {
            cout<<"You lost! The word was: "<<chosenWord<<endl<<endl;
        }

        do {
            cout<<"Do you want to play again? (y/n): ";
            cin>>playAgain;
            for(char &c : playAgain) c = tolower(c);

            if(playAgain != "y" && playAgain != "yes" && playAgain != "n" && playAgain != "no"){
                cout<<"Invalid input! Please type y/n.\n\n";
            }
        } while(playAgain != "y" && playAgain != "yes" && playAgain != "n" && playAgain != "no");

        cout<<endl;

    } while(playAgain == "yes" || playAgain == "y");

    cout<<"Thanks for playing the game, hope you enjoyed!"<<endl<<endl;

    return 0;
}
