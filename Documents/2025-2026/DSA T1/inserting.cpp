#include <iostream>
using namespace std;

//Inserting an element into the array
// Removing an element from the array
int main(){
	
	int element = 17;
	int i = 3;
	int arr[] {53, 87, 67, 43, 54, 12, 98, 72, 23, 46};
	int len = 9; 
	int j=i; 
	
	while(j<len-1){
		arr[j] = arr[j+1];
		j++;
		len--;
	}
	
	for(int k=0;k<len-1;k++){
		cout << arr[k] <<endl;
	}
	
	return 0;
}