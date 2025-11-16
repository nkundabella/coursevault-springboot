#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
#include <set>
using namespace std;

// Function to replace multiple characters with '_'
string makePuzzle(string word, vector<char> &missingLetters) {
    int length = word.size();
    int missingCount = 1;

    if (length >= 5 && length <= 7) missingCount = 2;
    else if (length >= 8 && length <= 10) missingCount = 3;
    else if (length > 10) missingCount = 4;

    set<int> positions;
    while ((int)positions.size() < missingCount) {
        positions.insert(rand() % length);
    }

    for (int pos : positions) {
        missingLetters.push_back(word[pos]);
        word[pos] = '_';
    }

    return word;
}

int main() {
    srand(time(0));

    // Categories with 100 words each
    string animals[100] = {
        "tiger", "elephant", "zebra", "giraffe", "lion", "cheetah", "rhino", "hippo", "wolf", "bear",
        "fox", "deer", "leopard", "panther", "kangaroo", "monkey", "snake", "eagle", "panda", "dolphin",
        "shark", "horse", "cat", "dog", "rabbit", "bear", "owl", "falcon", "hawk", "parrot",
        "crocodile", "alligator", "turtle", "lizard", "chameleon", "gorilla", "chimpanzee", "orangutan", "koala", "wombat",
        "emu", "ostrich", "penguin", "seal", "walrus", "jaguar", "cougar", "lynx", "bobcat", "bison",
        "buffalo", "antelope", "gazelle", "impala", "deer", "moose", "elk", "reindeer", "camel", "llama",
        "alpaca", "hyena", "jackal", "coyote", "dingo", "badger", "otter", "beaver", "porcupine", "hedgehog",
        "squirrel", "raccoon", "opossum", "kangaroo", "wallaby", "lemur", "meerkat", "mongoose", "sloth", "armadillo",
        "anteater", "tapir", "boar", "pig", "sheep", "goat", "cow", "bull", "ram", "ewe",
        "chicken", "rooster", "turkey", "duck", "goose", "swan", "peacock", "flamingo", "stork", "heron"
    };

    string foods[100] = {
        "pizza", "burger", "pasta", "bread", "cheese", "sushi", "taco", "salad", "soup", "cake",
        "noodles", "sandwich", "curry", "icecream", "steak", "rice", "pancakes", "lasagna", "dumplings", "yogurt",
        "chicken", "fish", "shrimp", "lobster", "crab", "pork", "beef", "lamb", "sausage", "bacon",
        "egg", "omelette", "quiche", "fries", "chips", "mash", "corn", "beans", "peas", "carrot",
        "broccoli", "cauliflower", "spinach", "lettuce", "tomato", "cucumber", "onion", "garlic", "pepper", "mushroom",
        "potato", "yam", "squash", "zucchini", "eggplant", "avocado", "apple", "banana", "orange", "grape",
        "mango", "pineapple", "strawberry", "blueberry", "raspberry", "kiwi", "peach", "pear", "plum", "cherry",
        "watermelon", "melon", "lemon", "lime", "coconut", "bread", "bagel", "croissant", "muffin", "donut",
        "cookie", "brownie", "pie", "tart", "pudding", "custard", "jelly", "jam", "honey", "syrup",
        "chocolate", "candy", "caramel", "toffee", "popcorn", "pretzel", "cracker", "biscuit", "waffle", "scone"
    };

    // NOTE: (I keep your places, capitals, oceans same as before, omitted here for brevity)
    // just copy them in full like you had before

    char play_again;
    do {
        int choice;
        cout << "\nChoose a category:\n";
        cout << "1. Animals\n2. Food\n3. Places\n4. Capital Cities\n5. Oceans\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        string word;
        switch (choice) {
            case 1: word = animals[rand() % 100]; break;
            case 2: word = foods[rand() % 100]; break;
            case 3: word = "paris"; break;    // replace with places[rand()%100]
            case 4: word = "kigali"; break;   // replace with capitals[rand()%100]
            case 5: word = "atlantic"; break; // replace with oceans[rand()%100]
            default: cout << "Invalid choice!\n"; continue;
        }

        vector<char> missingLetters;
        string puzzle = makePuzzle(word, missingLetters);

        int attempts = 5;
        set<char> guessed;
        bool wordCompleted = false;

        cout << "\nGuess the missing letters in: " << puzzle << endl;

        while (attempts > 0 && !wordCompleted) {
            cout << "\nAttempts left: " << attempts;
            cout << "\nYour guess: ";
            char guess;
            cin >> guess;
            guess = tolower(guess);

            if (!isalpha(guess)) {
                cout << "Invalid input! Enter a letter." << endl;
                continue;
            }

            if (guessed.count(guess)) {
                cout << "You already guessed that letter!" << endl;
                continue;
            }

            guessed.insert(guess);

            bool correct = false;
            for (char m : missingLetters) {
                if (tolower(m) == guess) {
                    correct = true;
                    break;
                }
            }

            if (correct) {
                cout << "Correct guess!" << endl;
            } else {
                cout << "Wrong guess!" << endl;
                attempts--;
            }

            // Check if all missing letters are found
            wordCompleted = true;
            for (char m : missingLetters) {
                if (!guessed.count(tolower(m))) {
                    wordCompleted = false;
                    break;
                }
            }
        }

        if (wordCompleted) {
            cout << "\n🎉 Congratulations! You found all letters. The word was: " << word << endl;
        } else {
            cout << "\n❌ Out of attempts. The word was: " << word << endl;
        }

        cout << "\nDo you want to try another word? (y/n): ";
        cin >> play_again;
        play_again = tolower(play_again);

    } while (play_again == 'y');

    cout << "Thanks for playing!" << endl;
    return 0;
}
