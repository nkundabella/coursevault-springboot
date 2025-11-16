// #include <iostream>
// #include <iomanip>
// #include <string>

// using namespace std;

// int main() {
	
// 	int op, n1, n2, res;
	
// 	string choice;
// 	cout << "Choose the operation of your choice.\n MENU \n"
// 	<< setw(10) << "1. Add" <<endl
// 	<< "2. Subtract" <<endl
// 	<< setw(10) << "3. Multiply" <<endl
// 	<< setw(10) << "4. Divide" <<endl
// 	<< setw(10) << "5. Modulus" <<endl;
	
// 	cout << "Enter your choice: ";
// 	cin >> op;
// 	cout << "Enter two numbers: ";
// 	cin >> n1 >> n2;
	
// 	switch (op) {
// 		case 1 : res = n1 + n2; break;
// 		case 2 : res = n1 - n2; break;
// 		case 3 : res = n1 * n2; break;
// 		case 4 : res = n1 / n2; break;
// 		case 5 : res = n1 % n2; break;
// 		default : cout << "Invalid number."; break;
// 	}
	
// 	cout << "Result: " << res << endl;
	
// 	cout << "\nContinue? (Y/n) ";
// 	cin >> choice;
	
// 	if (choice == "n" || choice == "N"){
// 		return 0;
// 	}
// }

// Number 2 & Number 3
// #include<iostream>
// using namespace std;

// int main(){
// 	int n1, n2, sum;
// 	cout<< "Enter two numbers: " <<endl;
// 	cin>> n1 >> n2;
// 	sum = n1+n2;
// 	cout << "The sum of " << n1 << " and " << n2 << " is : " << sum << endl;
// }

//Number 4
// #include<iostream>
// using namespace std;

// int main(){
// 	int n1, n2;
// 	cout<< "Input 1st number: " << endl;
// 	cin>> n1;
// 	cout<< "Input 2nd number: " << endl;
// 	cin>> n2;
// 	cout<< "After swapping the 1st number is : " << n2 << endl;
// 	cout << "After swapping the 2nd number is : " << n1 << endl;

// 	return 0;
// }

//Number 5
// #include<iostream>
// #include<cmath>
// using namespace std;

// int main() {
// 	double Pi = M_PI;
// 	double radius, vol;

// 	cout<< "Enter the radius of this sphere: " <<endl;
// 	cin>>radius;
// 	vol = (4/3) * Pi * radius;
// 	cout<< "The volume = " << vol << "." <<endl;
// 	return 0;
// }

//Number 6
// #include<iostream>
// using namespace std;

// int main(){
//     int sum = 0;
//     for(int i=0;i<100;i++){
//         if(i%2==0){
//             sum+=i;
//         }
//     }
//     cout<< "The sum of all even numbers less than 100 is " << sum << endl;
//     return 0;
// }

//Number 7
// #include<iostream>
// using namespace std;

// int main(){
//     int prod = 1;
//     for(int i=1;i<20;i++){
//         if(i%2!=0){
//             prod*=i;
//         }
//     }
//     cout<< "The product of all odd numbers between 1 and 20 is " << prod << endl;
//     return 0;
// }

//Number 8
// #include<iostream>
// using namespace std;

// bool isPrime(int number){
//     int prod = 1;
//     int i;
//     if(number<=1){
//         return false;
//     } else {
//         for(i=2;i*i<=number;i++){
//             if(number%i==0){
//                 return false;
//             } 
//         }
//             return true;
//         }
//     }

// int main(){
//     int prod = 1;
//     for(int j=2;j<100;j++){
//         if(isPrime(j)){
//             prod*=j;
//         }
//     }
//     cout<< "The product of all prime numbers between 1 and 100 is " << prod << endl;
//     return 0;
// }

//Number 9
// #include<iostream>
// #include<cmath>
// #include<iomanip>
// using namespace std;

// int main(){
//     int x,y;
//     int count=0;
//     for(x=2;x<100;x++){
//         for(y=x;y<100;y++){
//             int hyp = x*x + y*y;
//             int hyp2= sqrt(hyp);
//             if(hyp2*hyp2 == hyp){
//                 cout << "(" << x << ", " << y << ")" << endl;
//                 count++;
//             }
//         }
//     }

//     cout<< "We have found " << count << " pairs!" <<endl;
//     return 0;
// }

//Number 10
#include<iostream>
#include<array>
using namespace std;

int main(){
    
    array<int,6>, aur = {34,54,32,12,43,76};
    cout << aur.at(2) << endl;
    return 0;
}