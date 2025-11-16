/*Include libraries – for input/output, strings, vectors, random numbers.

Define constants – words list and max_guesses.

Write display function – show guessed word and remaining guesses.

Write input function – get a letter from the player.

Write update function – reveal correct letters in the guessed word.

Write win-check function – compare guessed word with secret word.

Write main game function –

Select random word.

Initialize guessed word and remaining guesses.

Loop: display → input → update/check → decrease guesses if wrong.

End: display result (win/loss).*/

Write main() – call the game function to start.
#include <iostream>     // For input/output operations (cin, cout)
#include <string>       // For using the string class
#include <vector>       // For using the vector container
#include <ctime>        // For time(), used to seed the random number generator
#include <cstdlib>      // For rand() and srand()

using namespace std;

// A constant vector storing all possible secret words for the game
const vector<string> words = {
    "apple", "banana", "cherry", "date", "elderberry",
    "fig", "grape", "kiwi", "lemon", "mango"
};

// Maximum number of incorrect guesses allowed
const int max_guesses = 6;

// Function to display the current game state
// secret_word and guessed_word are passed by const reference for efficiency
// num_guesses_left is passed by value
void display_game(const string& secret_word, const string& guessed_word, int num_guesses_left) {
    cout << "\nSecret word: " << guessed_word << endl;   // Display the guessed word so far
    cout << "Guesses left: " << num_guesses_left << endl; // Display remaining guesses
}

// Function to get a letter guess from the player
char get_guess() {
    char guess;
    cout << "Guess a letter: ";
    cin >> guess; // Wait for user input
    return guess; // Return the guessed letter
}

// Function to update the guessed_word if the guessed letter exists in the secret_word
// guessed_word is passed by reference so the function can modify it directly
void update_guessed_word(string& guessed_word, const string& secret_word, char guess) {
    // Loop through each character in the secret word
    for (int i = 0; i < secret_word.length(); i++) {
        if (secret_word[i] == guess) {
            guessed_word[i] = guess; // Reveal the correct letter in guessed_word
        }
    }
}

// Function to check if the player has guessed the entire word
bool check_win(const string& secret_word, const string& guessed_word) {
    return secret_word == guessed_word; // Returns true if guessed_word matches secret_word
}

// Main function to play the Hangman game
void play_hangman() {
    srand(time(NULL)); // Seed the random number generator with current time

    // Randomly select a secret word from the list
    string secret_word = words[rand() % words.size()];

    // Create a guessed word with underscores, same length as secret_word
    string guessed_word(secret_word.length(), '_');

    // Initialize the number of guesses left
    int num_guesses_left = max_guesses;

    // Game loop: continue while the player hasn't guessed the word and has guesses left
    while (!check_win(secret_word, guessed_word) && num_guesses_left > 0) {
        display_game(secret_word, guessed_word, num_guesses_left); // Show current game state

        char guess = get_guess(); // Get a letter from the player

        // Check if the guessed letter exists in the secret word
        if (secret_word.find(guess) != string::npos) {
            update_guessed_word(guessed_word, secret_word, guess); // Update guessed_word if correct
        } else {
            num_guesses_left--; // Reduce guesses left if wrong
        }
    }

    // Display final game state
    display_game(secret_word, guessed_word, num_guesses_left);

    // Check if player won or lost
    if (check_win(secret_word, guessed_word)) {
        cout << "Congratulations! You won!" << endl;
    } else {
        cout << "Sorry, you lost. The secret word was " << secret_word << "." << endl;
    }
}

// Program entry point
int main() {
    play_hangman(); // Start the game
    return 0;       // Exit program
}
