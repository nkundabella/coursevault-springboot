#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <limits>
using namespace std;

 void printWord(string display) {
    for(char c: display) {
        cout << c << " ";
    }
    cout <<endl;
 }

int main () {
    int chances = 10;
    char inputLetter = 0;
    srand(time(0));
    string words[] = { "xylophone","juxtapose","quizzical","zephyr","mnemonic",
    "rhythm","sphinx","cryptic","jazzy","vortex","gizmo","fjord","awkward","lymph",
    "glyph","nymph","sphinxlike","pneumonia","pshaw","queue","bleach","brew"
    };

    int size = sizeof(words)/sizeof(words[0]);
    string word = words[ rand() % size];
    string display(word.size(),'_');
    bool isGameOver = false;
    cout<<"****LETTER GUESSING GAME******"<<endl;

    while(!isGameOver) {
     cout<<"``````````````````````\n";
     cout<<"\n Word: ";
     printWord(display);
     cout <<"Chances left: " << chances << endl;
     cout<<"Enter you guess letter (a to z): ";
     cin>>inputLetter;
     cin.get();
     inputLetter = tolower(inputLetter);
        
     bool correctGuess = false;
     for (int i = 0 ; i < word.size() ; i++) {
        if(word[i] == inputLetter && display[i]== '_') {
            display[i] = inputLetter;
            correctGuess = true;
        }
     }
     if(!correctGuess) {
        chances--;
        cout<<"Wrong Guess!" <<endl;
        cout<<"``````````````````````\n";

     }else {
        cout<<"Good Guess!" <<endl;
        cout<<"``````````````````````\n";

     }

     if(display == word) {
        cout<<"\n Congratulations! You've guessed the word: "<< word << endl;
        isGameOver=true;
     }
     if(chances<=0) {
        cout<<"\n Oh no! You've exhausted you're chances.";
        cout<<"The word was: "<<word<<endl;
        isGameOver=true;
     }
    }
    cout<<"******************************";
    return 0;
}