
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
int main(){
srand(time(0));
string planets[]={"mercury","venus","earth","mars","jupiter","saturn","uranus","neptune","pluto","kepler"};
string superheroes[]={"hulk","batman","superman","aquaman","spiderman","thor","wonderwoman","ironman","flash","goku"};
string random[]={"umbrella","spoon","drone","carpet","headset","pen","book","pencil","watch","sunglasses"};
string instruments[]={"violin","guitar","drums","clarinet","banjo","harp","saxophone","flute","tuba","trumpet"};
string destinations[]={"paris","venice","dubai","cairo","kigali","rome","london","nairobi","sydney","bujumbura"};
string villains[] = {"joker","thanos","voldemort","magneto","greenGoblin","lexLuthor","cersei","sauron","darkseid","harleyquinn"};
bool playAgain=true;
while(playAgain){
    int choice;
    string secret;
    cout  <<"======WORD GUESSING GAME======"<<endl;
    cout  <<"Choose a category:"<<endl;
    cout  << "1.Planets"<<endl;
    cout  << "2.Superheroes"<<endl;
    cout  <<"3.Random objects"<<endl;
    cout  <<"4.Musical instruments"<<endl;
    cout  <<"5.Destinations"<<endl;
    cout <<"6.Villains"<<endl;
    cout  <<"Enter you choice 1-6: "<<endl;
    cin>>choice;

    switch(choice){
    case 1:
    secret=planets[rand()%10];
    break;
    case 2:
    secret=superheroes[rand()%10];
    break;
    case 3:
    secret=random[rand()%10];
    break;
    case 4:
    secret=instruments[rand()%10];
    break;
    case 5:
    secret=destinations[rand()%10];
    break;
    case 6:
    secret=villains[rand()%10];
    break;

    default:
    cout<<"Invalid choice try again!"<<endl;
    break;
    }

    string word(secret.size(),'_');
    int chance=8;
    bool win=false;
    while(chance>0 &&!win){
    string input;
    cout<<"A word has been chosen"<<endl;
    cout<<"Word: "<<word<<endl;
    cout<<"Chances left:"<<chance<<endl;
    cout<<"guess a letter(or exit to quit the game): "<<endl;
    cin>>input;

    if(input=="exit"){
        cout <<"You have  exited the game"<<endl;
        return 0;
    }
    bool correct=false;
    for(int i=0;i<secret.size();i++){
        if(secret[i] == input[0]){
            word[i]=input[0];
            correct=true;
        }
    }
    if (correct){
        cout<<"You guessed the correct word!!"<<endl;
    }
    else{
        cout<<"Wrong guess"<<endl;
        chance--;
    }
    if(word==secret){
        win=true;
    }
    }
    if(win){
        cout<<"Congzz!!! You won the word is: "<<word<<endl;
    }
    else{
        cout<<"oops!! You lost the word was: "<<secret<<endl;
    }
    cout<<"Do you want to play again? (y/n)"<<endl;
    char play;
    cin >>play;
    if(play!='y'&& play!='Y'){
        playAgain=false;
    }
    }
    cout<<"Thanks for playing"<<endl;


}
