#include<iostream>
using namespace std;
//
//// Factorial
//int fact (int n) {
//
//    if(n<0)return -1;
//    if(n==0)return 1;
//
//    int smallerAnswer=fact(n-1);
//    return n*smallerAnswer;
//}
//
//int main(){
//    int num = 5;
//    cout<< fact(num) << endl;
//
//    return 0;
//}
//
//// Fibonacci
//int fibonacci (int num){
//    if (num == 0) return 0; // base case 1
//    if (num == 1) return 1; // base case 2
//    
//    int a = 0, b = 1, fib = 0;
//    for(int c = 2; c <= num; c++){
//        fib = a + b;
//        a = b;
//        b = fib;
//    }
//    return fib;
//}
//
//int main() {
//    int n;
//    cout << "Enter n: ";
//    cin >> n;
//    cout << "F(" << n << ") = " << fibonacci(n) << endl;
//    return 0;
//}

//fibonacci using recursive functions
int fibonacci(int m){
	if(m==0) return 0;
	if(m==1) return 1;
	
	return fibonacci(m-1) + fibonacci(m-2);
}

int main(){
	int a = 8;
	cout << "The factorial of a number of " << a << " is " << fibonacci(a) << endl;
	return 0;
}

//// Power of a number
//int power(int num, int p){
//    if(p == 0) return 1;
//    //Recursive whereby the main formula is x^n = x*x^n-1;
//    int smallOutput = power(num, p-1); 
//    //Calculation
//    return num * smallOutput;
//}
//
//int main(){
//    int n, pow;
//    cout<< "Provide any number and its power respectively: ";
//    cin>> n >> pow;
//    cout<< "The power of " << n << " = " << power(n,pow);
//    return 0;
//}
//
//// To calculate the number of zeros in a given number
//int countZ(int n){
//    //THE base case
//    if(n==0) return 1;
//
//    //recursion..
//    int smallN = countZ(n/10);
//
//    //THe calculation
//    int lastDigit = n%10;
//
//    //condition
//    if(lastDigit == 0) return smallN + 1;
//    return smallN;
//}
//
//int main(){
//    int num;
//    cout<< "Enter a random number to calculate the number of zeros it contains: ";
//    cin >> num;     
//    cout << "The number of zeros in " << num << " = " << countZ(num);
//    return 0;
//}
//
////(Logical errorr)
//
////Exercise 6
//int digitToString(int num, int n){
//    //the base case
//    if(n==0)return 0;
//    for()
//    int smallAns = 0*10+
//    //recursive statement and or function
//
//}
//
//int main(){
//    string numbers[] = {"123456"};
//
//    return 0;
//}
//
//
//
////convert the string of digits to integer. Hint: if "12345" is provided then the program would return 12345
////Hint: If we have "12345" then call the recursion on "1234",
////Then call the recursion on "123"
////Then call the recursion on "12"
////Then call the recursion on "1", now n=1. Then call the recursion on empty array.
////if n=0, then return 0;
//// The small answer is 0, then 0*10+1