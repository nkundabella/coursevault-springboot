#include<iostream>
#include<ctime>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

int main(){
	srand(time(0));
	
	vector<string> countries = {"rwanda", "japan", "canada", "uganda"};
	vector<string> foods = {"pizza", "chips", "salad", "chicken"};
	vector<string> sports = {"football", "golf", "hockey", "rugby"};
	vector<string> clothes = {"shirts", "skirts", "pants", "dress"};
	vector<string> continents = {"africa", "europe", "asia", "northamerica"};
	
	bool playAgain = true;
	while(playAgain){
		cout <<"======WELCOME TO THE GUESSING GAME======"<<endl;
		cout <<"Choose category: "<<endl;
		cout <<"1.Country"<<endl;
		cout <<"2.Food"<<endl;
		cout <<"3.Sports"<<endl;
		cout <<"4.Clothes"<<endl;
		cout <<"5.Continents"<<endl;
		cout <<"Enter choice: "<<endl;
		
		int choice;
		cin >>choice;
		
	vector<string> chosenCategory;
	    if(choice ==1) chosenCategory = countries;
	    else if(choice ==2) chosenCategory = foods;
	    else if(choice ==3) chosenCategory = sports;
	    else if(choice ==4) chosenCategory = clothes;
	    else chosenCategory = continents;
	    
	string word = chosenCategory[rand() % chosenCategory.size()];
	    string display = word;
	    for(int i=1;i<word.size()-1;i++){
	    	display[i] = '_';
		}
	    int chances = 6;
	    bool wordGuessed = false;
	    
	while(chances > 0 &&!wordGuessed){
		cout <<"Word: "<<display<<endl;
		cout <<"Chances left: "<<chances<<endl;
		cout <<"Guess a letter(type 0 to exit game): "<<endl;
		
		char guess;
		cin >>guess;
		
		if(guess =='0'){
			cout <<"Exiting game..."<<endl;
			return 0;
		}
		
		bool correct = false;
		
		for(int i=0;i<word.size();i++){
			if(word[i] == guess){
				display[i] = guess;
				correct = true;
			}
		}
		
		if(!correct){
			chances--;
			 cout <<"Wrong guess!!"<<endl;
		}
			else{
				cout <<"Good guess!!"<<endl;
			}
		
		if(display == word)	{
			wordGuessed = true;
			
		}
		}
		
		if(wordGuessed){
			cout <<"You won! The word was: "<<word<<endl;
		}
		else{
			cout <<"You lost! The word was: "<<word<<endl;
		}
		
		cout <<"Play again? (1=yes, 0=no): "<<endl;
		int again;
		cin >> again;
		
		playAgain = (again == 1);
		
	}
		cout <<"Thanks for playing" <<endl;
		return 0;
	}   
		
	

