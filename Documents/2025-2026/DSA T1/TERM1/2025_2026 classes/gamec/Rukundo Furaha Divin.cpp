#include <iostream>
#include <cctype>
#include <vector>
using namespace std;

void showGuessedChar(string word, string &guessed, char guessedChar){
    for (int i = 0; i < word.length(); i++){
        if (tolower(word[i]) == tolower(guessedChar)){
            guessed[i] = word[i];
        }
    }
    cout << guessed << endl;
}

string findWord(vector<string> arr, char guess, int arraySize){
    for(int i = 0; i < arraySize; i++){
        for (char c: arr[i]){
            if (tolower(c) == tolower(guess)){
                return arr[i];
            }
        }
    }
    return "";
}

vector <string> choices(int choice){
    vector <string> animals = {"Anteloppe","Lion","Giraffe","Elephant","Panda","Panther","Hippotamus","Penguin","Dog","Cat","Tiger","Horse"};
    vector <string> movies = {"PeakyBlinder","Avengers","Heretic","Nobody","Countdown","Vikings","Badboys","RRR","War"};
    vector <string> cars = {"BMW","Porsche","Ferrari","Lamborghini","RollsRoyce","Bentley","Honda","Toyota","MercedesBenz","Hyundai","Kia"};
    vector <string> country = {"Rwanda","Canada","UnitedKingdom","USA","Singapore","SouthKorea","DRC","Angola","Liberia","Libya","Tanzania","Kenya","Argentina","Portugal"};
    vector <string> players = {"Messi","Ronaldo","KDB","Pedri","Gavi","Fermin","Garcia","Balde","Kounde","Bellingham","Haaland","Doku","Donnaruma","Lewandowski","Yamal","Raphinha"}; 

    if(choice == 1) return animals;
    else if(choice == 2) return movies;
    else if(choice == 3) return cars;
    else if(choice == 4) return country;
    else if(choice == 5) return players;
    else {
        cout << "Invalid choice number" << endl;
        return {};
    }
}

int main(){
    int choice;
    cout << "Welcome to GuessChallenger" << endl;
    cout << "==========================" << endl;

    cout << "Where do you want to be challenged: " << endl;
    cout << "==================================" << endl;
    cout << "1. Animals" << endl;
    cout << "2. Movies" << endl;
    cout << "3. Cars" << endl;
    cout << "4. Countries" << endl;
    cout << "5. Footbal players" << endl;

    cout << "===================================" << endl;
    cout << "Choose Field: ";
    cin >> choice;

    vector <string> chosenField = choices(choice);
    if(chosenField.empty()) return 0;

    char guess;
    string word;
    string guessed;

    cout << "Guess a character to start: ";
    cin >> guess;
    word = findWord(chosenField, guess, chosenField.size());
    if(word.empty()){
        cout << "No word found with that letter!" << endl;
        return 0;
    }

    guessed = string(word.length(), '_');
    int trials = word.length();

    showGuessedChar(word, guessed, guess);
    trials--;

    while(trials > 0){
        cout << "Trials left: " << trials << endl;
        cout << "Guess a character: ";
        cin >> guess;

        showGuessedChar(word, guessed, guess);

        if(guessed == word){
            cout << "Congratulations! You guessed the word: " << word << endl;
            break;
        }

        trials--;
    }

    if(guessed != word){
        cout << "Trials ended. The word was: " << word << endl;
    }

    return 0;
}
