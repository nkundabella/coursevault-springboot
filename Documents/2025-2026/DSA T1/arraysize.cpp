#include <iostream>
// #include <array>
using namespace std;

// int calculateSize(int arr[], int j) {
//     int count = 0;
//     for(int i=0;i<j;arr++){
//         arr[i];
//         count++;
//     }
//     return count;
// }

// int main() {
//     int array1[] = {0,1,2,3,4};
//     int size = sizeof(array1)/ sizeof(array1[0]);
//     cout << "The size of this array is " << calculateSize(array1, size) << "." << endl;
//     return 0;
// }

//Using auto
// int main() {
//     int count = 0;
//     int arr[]={3,4,5,32,2,5,423,23,56};
//     cout << "The array is: ";
//     for(auto i: arr) {
//         cout << i << " ";
//         count++;
//     } 
//     cout << endl;
//     cout << "The length of the given array is: " << count << endl;

//     return 0;
// }

//using begin
#include <iostream>
#include <array>
using namespace std;
    int main(){
    int array1[]={0,1,2,3,4,5,4,3,6,34,2,5};
    int c;
    // cout<<"The array is: ";
    cout<< "The length of the Array is: "<<end(array1)-begin(array1);
    return 0;
    }

//using sizeof()
// #include <iostream>
// #include <array>
// using namespace std;

// int main() {
//     int arr[] = {23,5,345,34};
//     int size = sizeof(arr)/sizeof(arr[0]);
//     cout << "The length of the array is: " << size << endl;

//     return 0;
// }