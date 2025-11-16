#include <iostream>
#include <cstdlib>
#include <string>
#include <cctype>
using namespace std;

void game(int n, char choice, string &sol){
    string list[10] = { "banana","aeroplane", "thing", "walking", "hunger", "twelve", "what","elephant", "refectory","chair"};

    string word = list[n];

    for(int i = 0; i < word.length(); i++){
        if(choice == word[i]){
            sol[i] = word[i];
        } else if(sol[i] == '\0' || sol[i] == '_'){
            sol[i] = '_';
        }
        cout << sol[i];
    }
    cout << endl;
}

bool complete(string &sol){
    for(char c : sol){
        if(c == '_') return false;
    }
    return true;
}
int main(){
    char yn;

    do { // i thought that maybe this might be a good idea to use do while insetead of while
    cout << "Welcome to the guessing game. You have limited trials." << endl;

    int random = rand() % 10;
    string list[10] = { "banana","aeroplane", "thing", "walking", "hunger", "twelve", "what","elephant", "refectory","chair"};

    int trials = static_cast<int>(list[random].length() * 1.5);
    string sol(list[random].length(), '_');
    char choice;

    switch(random+1){
        case 1: 
            cout << "this is something you eat, yellow, and good source of energy" << endl;
            break;
        case 2: 
            cout << "you have seen it fly, what other thing that flies other than bird, maybe you should sound British" << endl;
            break;
        case 3: 
            cout << "someething is what, something contains what" << endl;
            break;
        case 4: 
            cout << "if you would run in slow motion, what would you be doing normally" << endl;
            break;
        case 5: 
            cout << "some people say that nothing is sweeter than this, especially a student" << endl;
            break;    
        case 6: 
            cout << "tell me this number, how many months does a year have" << endl;
            break;
        case 7: 
            cout << "what has a name and you never call it ?" << endl;
            break;
        case 8: 
            cout << "tell me a big animal with a long trunk" << endl;
            break;
        case 9: 
            cout << "wshere do you go for the food" << endl;
            break;
        case 10: 
            cout << "what do you sit on in class" << endl;
            break;
        }

    while(trials > 0){
        cin >> choice;
        choice = tolower(choice);

        game(random, choice, sol);
        trials--;
        cout << "Remaining trials: " << trials << endl;

        if(complete(sol)){
            cout << "Congratulations! You guessed the word!" << endl;
            break;
        }

        if(trials == 0){
            cout << "Out of trials! The word was: " << list[random] << endl;
        }
    }

    cout << "Want to play again? (y yes, n no): ";
    cin >> yn;
    yn = tolower(yn);

    } while(yn == 'y');

    return 0;
}
