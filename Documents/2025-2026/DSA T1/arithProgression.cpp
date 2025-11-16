#include<iostream>
using namespace std;
int fun6(int n){
    int i,j,m = 0;
    for(i=0;i<n;i++){
        for(j=0;j<i;j++){
            m+=1;
        }
    }
    return m;
}

int main(){
    cout<< "N = 100, Number of instructions O(n^2) :: " << fun6(100);
    return 0;
}

//This series is an arithmetic progression.