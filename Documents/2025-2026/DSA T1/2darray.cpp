#include<iostream>
using namespace std;

// int main() {

//     int a = 15;
//     int b = 20;
//     int *c = &b;
//     *c = 15;
//     cout << a << " " << b << endl;

//     return 0;
// }

// int main(){
//     int x=10, y=20, z=5,t=2,s=7;
//     int h = x*y/z%s*t-s*x/t+y/x*t;

//     cout << h << endl;

//     return 0;
// }

// int main() {
//     int x=15;
//     int y=23;
//     cout << "x,y:" << x << " and " << y << endl;
//     cout << "x,y" << ++x << "and " << y++ << endl;
//     cout << "x=" << --x << " and y= " << y-- << endl;
//     ++x;
//     y++;
//     cout << "x=" << x << "and y=" << y << endl;
//     --x;
//     y--;
//     cout << "x=" << x << " and y=" << y << endl;

//     return 0;
// }

// int main(){
//     int a=50;
//     int *ptr=&a;
//     cout<<(*ptr)++<<endl;
//     cout<<a<<endl;
//     int *q=ptr;
//     (*q)++;
//     cout<<(*ptr)++<<endl;
//     cout<<*q<<endl;
//     cout<<a<<endl;

//     return 0;
// }

// int main(){
//     int arr[] = {10,20,30,40,50};
//     cout<< "The array is: ";
//     for(auto i: arr){
//         cout << i << " ";
//     }
//     cout << endl;
//     cout << "The first element of the array is: " << arr[0] << endl;
//     cout << "The first element of the array using pointers is: " << *arr <<endl;
//     for(int i=0;i<5;i++){
//         cout<<*(arr+i) << " ";
//     }

//     return 0;
// }

// factorial function

int sum(int n) {
    if(n==1){
        return 1;
    }
    int smallAnswer = sum(n-1);
    return n + smallAnswer;

}

int main() {
    int number;
    cout << "Enter any number to figure out its factorial: ";
    cin >> number;
    cout << number << "! = " << sum(number) << endl;
}

// int main() {
//     float score = 15.5;
//     float p = 7.5;
//     float *ptr = &score;
//     (*ptr)++;
//     *ptr = p;
//     cout << *ptr << " " << score << " " << p;
    
//     return 0;
// }

// int show(int c, int d){
//     int A[c][d] = {80,75,76,54,72,55,70,65,85,35,59};

//     for(int i=0;i<3;i++){
//         for(int j=0;j<4;j++){
//             cout << A[i][j] << " ";
//         }
//         cout << endl;
//     }
//     return 0;

   
// }

// int main() {
//     int b[][5] = {{0}};
//     show(5,5);

//     return 0;
// }