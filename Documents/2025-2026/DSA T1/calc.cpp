#include <iostream>
#include <gtkmm.h>
#include <string>
using namespace std;

double calc(double n1, double n2, char s){
    switch(s){
        case '+': return n1 + n2;
        case '-': return n1 - n2;
        case '*': return n1 * n2;
        case '/': if(n2!=0){
            return n1/n2;
        } else {
            cout<<"Math Error"<<endl;
            return 0;
        } default:
        cout<<"Invalid Operator"<<endl;
        return 0;
    }
}

int main(){
    double a, b;
    char s; //the operation sign

    cin>>a;
    cin>>s;
    cin>>b;

    double result = calc(a,b,s);
    cout<<result<<endl;
    return 0;
}