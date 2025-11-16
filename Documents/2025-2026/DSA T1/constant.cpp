#include <iostream>
using namespace std;

#define PI 3.14
const int nbrOfDistricts = 30;

int main() {
    double radius;
    cout<<"Enter radius: "<<endl;
    cin>>radius;
    double area = PI * (radius * radius);
    cout <<"Area of a circle = "area".";

    cout<<"The number of districts is: "nbrOfDistricts"."<<endl;

    return 0;
}