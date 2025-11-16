#include<iostream>
using namespace std;

class Personb{
    string firstName;
    string lastName;
    int age;
    public:
    Personb(){}
    Personb(string fname, string lname, int age){
        firstName = fname;
        lastName = lname;
        age = age;
    }
    void printMe(){
        cout << firstName << " " << lastName << " " << age << endl; 
    }
}person1, person2;

int main(){
    person1 = {"Ange", "Mugisha", 20};
    person2 = {"Awet", "Ganza", 16};
    Personb person3;

    void setFirstName(string firstName){
        firstName = fname;
    }
    string getFirstName(){
        return firstName;
    }
    person3.firstName = "Isabella";
    person3.lastName = "Nkunda";
    person3.age = 17;

    person1.printMe();
    person2.printMe();
    person3.printMe();

    return 0;
}