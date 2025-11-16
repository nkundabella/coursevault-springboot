#include<iostream>
using namespace std;

class Personc{
    public:
    string firstName;
    string lastName;
    int age;

    Personc(){}
    //A new method of construction
    Personc(int age, string fname, string lname): age(a), firstName(fname), lastName(l){}
    Personc(int age, string fname,string lname) : age(a), firstName(fname){
        lastName = lname;
    }

    void printMe(){
        cout << firstName << " " << lastName << " " << age << endl;  
    }
};

int main(){
    Personc person1("Ange", "Mugisha", 20);
    Personc person2("Awet", "Ganza", 20);
    Personc person3("John", "UWASE", 18);
    Personc *person4 = new Person("Mary", "Keza", 15);
    Personc person5;
    person5.firstName = "Isabella";
    person5.lastName = "Nkunda";
    person5.age = 16;
    person5.printMe();
    person1.printMe();
    person2.printMe();
    person3.printMe();
    person4 -> printMe();
    
    return 0;
}