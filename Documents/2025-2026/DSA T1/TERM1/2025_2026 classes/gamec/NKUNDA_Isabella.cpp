#include <iostream>
#include <iomanip>
#include <string>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	
	char again = 'y';
	while (again == 'y' || again == 'Y') {
	
	cout << setw(20) << "Music Genres" 
	     << setw(25) << "Designer Brands"    
		 << setw(18) << "Subjects" 
		 << setw(19) << "Countries" 
		 << setw(14) << "Food" <<endl;
	
	string input;
		 
	cout << setw(41) << "Pick any category of preference: ";
	cin >>input;
	
	vector<string> options;
	
	if (input == "Music Genres") {
		
    	options = {"Jazz", "Reggae", "Grunge", "Trap", "PunkRock", "Blues", "Funk", "Bossa Nova"}; //*Gotta choose more unpredictable words and categories!
	
 	} else if (input == "Designer Brands") {
 		
 		options = {"Balenciaga", "BottegaVeneta", "AlexanderMcQueen", "VivienneWestwood", "ThomBrowne", "Givenchy", "SaintLaurent"};		
 		
	} else if (input == "Subjects") {
		
		options = {"Anthropology", "Criminology", "Neuroscience", "Astrophysics", "Linguistics", "Philosophy", "Archaeology"};	 	
 		
	} else if (input == "Countries") {
 		
 		options = {"Uzbekistan", "Johannesburg", "Bratislava", "Quebec", "Luxembourg", "Afghanistan", "Limpopo"};
 		
	} else if (input == "Food"){
		
		options = {"Wasabi", "Croissant", "Kimchi", "Tiramisu", "Caramel", "Backlava", "Ratatouille"};
		
	}
	
	 else {
	 	cout << setw(66) << "Invalid category! Please choose from those provided above." <<endl;
	 	continue;
	}

	//A modern random generator
	random_device r;
	mt19937 gen(r());                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          
	uniform_int_distribution<> dist(0, options.size() - 1); 
    string choice = options[dist(gen)]; 
    
    string hidden(choice.size(), '_');
    int attempts = choice.size() + 2;
    string guess;
    
    cout << "The Guesswork Begins! You have " << attempts << " trials." <<endl;

// Time for conditions
	while(attempts > 0 && hidden != choice){
		
		cout << "The random word is: " << hidden << " (Hint: The word has " << choice.size() << " letters.)" << "\nEnter a letter OR type 'Exit' to quit. ";
		cin >> guess;
		
		if(guess == "Exit" || guess == "exit") return 0;
		
		if(guess.size() != 1){
			cout << "Kindly enter only ONE letter!" <<endl;
			continue;
		}
		
		char letter = guess[0];
		bool found = false;
		
		for(size_t i=0;i<choice.size();i++){
			if(tolower(choice[i]) == letter) {
				hidden[i] = choice[i];
				found = true;
			}
		}
		
		if(!found){
			attempts--;
			cout << "Wrong guess. You have " << attempts << " chances left!" << endl;		
		}
	}
	
	if (hidden == choice) {
		cout << "Congratulations! You guessed it. The word is: " << choice << "." << endl;
	} else {
		cout << "You have run out of attempts! Better luck next time! The word was: " <<choice << "." <<endl;
	}
	
	cout << "\nDo you want to play again?(Y/n) ";
	cin >> again;
  }
	
  	cout << "Thanks for playing!" <<endl;
	return 0;
}