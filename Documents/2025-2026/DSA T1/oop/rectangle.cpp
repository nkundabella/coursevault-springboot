#include<iostream>
using namespace std;

struct Rectangle{
    double length;
    double width;

    Rectangle(){}
    Rectangle(double l, double w){
        length = l;
        width = w;
    }
    void area(double length, double width){
        double area = length * width;
    }
    void printMe(){
        cout<< "The area of this rectangle is " << area << endl;
    }
}rect1, rect2, rect3;

int main(){
    Rectangle rect1 = {123,456};
    Rectangle rect2 = {20,500};
    Rectangle rect3 = {75,321};
    Rectangle rect4(90,45);
    Rectangle rect5;
    rect5.length = 20;
    rect5.width = 30;

    rect1.printMe();
    rect2.printMe();
    rect3.printMe();
    rect4.printMe();
    rect5.printMe();

    return 0;
}