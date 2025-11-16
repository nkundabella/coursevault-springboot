#include <bits/stdc++.h>
using namespace std;



int main() {
    string animals[] = {"dog", "cat", "monkey", "goat", "lion","crocodile","fish","elephant","tiger","giraffe","zebra","turtle","rabbit","bear","wolf","cheetah"};
    int len0 = sizeof(animals) / sizeof(animals[0]);
    string films[] = {"Inception", "Avatar", "Titanic", "The Matrix", "Interstellar","6 Undegrounds","The Dark Knight","The Shawshank Redemption","Pulp Fiction","Forrest Gump","The Godfather","Gladiator","The Avengers","Jurassic Park","The Lion King","Frozen","Nobody"};
    int len1 = sizeof(films) / sizeof(films[0]);
    string colors[] = {"red", "blue", "green", "yellow", "purple","orange","black","white","pink","brown","gray","cyan","magenta","teal","lime","indigo","violet","gold","silver","beige","maroon","navy","olive","coral","turquoise"};
    int len2 = sizeof(colors) / sizeof(colors[0]);
    string fcs[]= {"Real Madrid", "Barcelona", "Manchester United", "Bayern Munich", "Juventus","APR FC","Manchester City","Chelsea","Liverpool","Arsenal","PSG","AC Milan","Inter Milan","Atletico Madrid","Tottenham Hotspur","Borussia Dortmund","Napoli","Roma","Lazio","Sevilla"};
    int len3 = sizeof(fcs) / sizeof(fcs[0]);
    string books[] = {"1984", "To Kill a Mockingbird", "The Great Gatsby", "Mind Hacker", "Secret behind money"};
    int len4 = sizeof(books) / sizeof(books[0]);
    string districts[]= {"Nyarugenge","Kicukiro","Gasabo","Rulindo","Musanze","Burera","Gakenke","Musanze","Nyabihu","Rubavu","Rusizi","Nyamasheke","Karongi","Rutsiro","Ngororero","Nyamagabe","Huye","Nyanza","Gisagara","Muhanga","Kamonyi","Bugesera","Rwamagana","Kayonza","Kayonza","Kirehe","Ngoma"};
    int len5 = sizeof(districts) / sizeof(districts[0]);
    cout << "::::::::::::::::::::Guess What:::::::::::::::::::::::::::::" << endl << endl;
    cout << "@@@@@@@@@@@@@@@Guess Category`````````````" << endl;
    cout << "1. Animals" << endl;
    cout << "2. Films" << endl;
    cout << "3. Colors" << endl;
    cout << "4. Football Clubs" << endl;
    cout << "5. Books" << endl;
    cout << "6. Districts of Rwanda" << endl;
    cout << "Choose a category by entering the corresponding number (1-6) or (exit): ";
    string category;
    cin >> category;
    if (category == "exit") {
        cout << "Exiting the game. Goodbye!" << endl;
        return 0;
    } else {
        int cat = stoi(category);
        if (cat < 1 || cat > 6) {
            cout << "Invalid category number. Please restart the game and choose a valid category." << endl;
            return 0;
        }
        string selectedWord;
        switch (cat) {
            case 1:
                selectedWord = animals[rand() % len0];
                break;
            case 2:
                selectedWord = films[rand() % len1];
                break;
            case 3:
                selectedWord = colors[rand() % len2];
                break;
            case 4:
                selectedWord = fcs[rand() % len3];
                break;
            case 5:
                selectedWord = books[rand() % len4];
                break;
            case 6:
                selectedWord = districts[rand() % len5];
                break;
        }
        string guessedWord(selectedWord.length(), '_');
        int attempts = 6;
        set<char> guessedLetters;// I wanna to assure people and the government that the ecomony is now on youuuuuooooo!!!

        while (attempts > 0 && guessedWord != selectedWord) {
            cout << "\nCurrent word: " << guessedWord << endl;
            cout << "Attempts left: " << attempts << endl;
            cout << "Guessed letters: ";
            for (char c : guessedLetters) cout << c << ' ';
            cout << endl;

            cout << "Enter a letter to guess or type 'exit' to quit: ";
            string input;
            cin >> input;
            
            if (input == "exit") {
                cout << "Exiting the game. Goodbye!" << endl;
                return 0;
            }

            if (input.length() != 1 || !isalpha(input[0])) {
                cout << "Please enter a single valid letter." << endl;
                continue;
            }

            char guess = tolower(input[0]);
            if (guessedLetters.count(guess)) {
                cout << "You've already guessed that letter. Try again." << endl;
                continue;
            }

            guessedLetters.insert(guess);
            bool correctGuess = false;

            for (size_t i = 0; i < selectedWord.length(); ++i) {
                if (tolower(selectedWord[i]) == guess) {
                    guessedWord[i] = selectedWord[i];
                    correctGuess = true;
                }
            }

            if (!correctGuess) {
                attempts--;
                cout << "Wrong guess!" << endl;
            } else {
                cout << "Good guess!" << endl;
    }
}        if (guessedWord == selectedWord) {
            cout << "\nCongratulations! You've guessed the word: " << selectedWord << endl;
        } else {
            cout << "\nOut of attempts! The correct word was: " << selectedWord << endl;
        }
    }
    return 0;


}