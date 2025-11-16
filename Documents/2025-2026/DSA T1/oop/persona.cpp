#include<iostream>
using namespace std;

class Persona{
    public:
    string firstName;
    string lastName;
    int age;
    Persona(){}
    Persona(string fname, string lname, int a){
        firstName = fname;
        lastName = lname;
        age = a;
    }
    void printMe(){
        cout << firstName << " " << lastName << " " << age << endl;  
    }
};

int main(){
    Persona person1("Ange", "Mugisha", 20);
    Persona person2("Awet", "Ganza", 20);
    Persona person3("John", "UWASE", 18);
    Persona *person4 = new Persona("Mary", "Keza", 15);
    Persona person5;
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
