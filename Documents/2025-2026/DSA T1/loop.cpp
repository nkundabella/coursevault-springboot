#include <iostream>
using namespace std;

// int main(){

//     int count = 0;
//     for(int i=0;i<1000000;i++){
//         for(int j=0;j<1000000;j++){
//             count++;
//         }
//     }
//     cout << "Number of steps: " << count << endl; 
//     return 0;
// }

int fun1(int n){
    int m=0;
    for(int i=0;i<n;i++){
     m+=1;
    }
    return m;
}

int main(){
    cout << "N = 100, Number of instructions 0(n) :: " << fun1(100);
    return 0;
}
