#include <iostream>

using namespace std;

int main (){
	
	cout << "************************************" << endl;
	cout << "Welcome to the animal guessing game " << endl;
	cout << "************************************" << endl;
	
	string animal = "elephant";
	string dup = "_l_ph___";
	char mem ;
	int tries =0;
	
	while (dup!=animal){
		cout << "Guess the letter:" << endl;
		cout << dup << endl;
		cin >> mem;
		cout << dup << endl;
		if (animal.find(mem)!= string::npos){
			for (int i =0;i<animal.length();i++){
				if(animal[i]==mem && dup[i]=='_'){
					dup[i] = mem;
					cout << "You win !" << endl;
				}
			}
		}
		else {
			cout << "You lose !"<< endl;
			tries ++;
		}
	}
	cout << endl;
	cout << "Well done!"<<endl;
	cout << "The animal is " << dup << endl;
	cout << "You used lost " << tries << " tries" ;
	
	return 0;
}