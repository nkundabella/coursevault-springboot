#include<iostream>
#include<cmath>
using namespace std;

//1. write a program with a function that prints the character array. 
//Hint: if abc is provided, the program prints abc. 
//Print the first character and call recursion on the small array. 
//If the character is '\0' return.
 
// void printCharacterArr(const char* str){
//     //the base cases will be when we reach at the end of the string.
//     if(str[0] == '\0'){
//         return;
//     }
//     // the recursive case will print the first char
//     cout << str[0];

//     //the calculations
//     printCharacterArr(str + 1);
// }

// int main(){
//     const char word[] = "abcd";
//     printCharacterArr(word);
//     cout<<endl;
//     return 0;
// }

//2. write a program with a function that prints the reserved character array.
//Hint: if abc is provided, the program prints cba. 
//Print the last character and call recursion on the small array. 
//If the character is '\0' return.

// void printReversedChar(const char* str){
//     // the base case
//     if(str[0] == '\0'){
//         return;
//     }
//     //the recursive call
//     printReversedChar(str + 1);

//     //then after that recursion, print the current char..
//     cout<< str[0];
// }

// int main(){
//     const char words[] = "abcdef";
//     printReversedChar(words);
//     cout<< " ";

//     return 0;
// }

//3. Remove a character in the array.
//Hint: if abacada is provided, by removing a the program print bcd 

// void removeChar(const char* rem, char imp){
//     //the base case
//     if(rem[0]=='\0') return;

//     //condition
//     if(rem[0]!=imp)cout << rem[0];

//     //recursion
//     removeChar(rem+1,imp);
// }

// int main(){
//     const char random[] = "abacadabacada";
//     char imposter = 'a';
//     removeChar(random,imposter);
//     cout << endl;

//     return 0;
// }

//4. Replace the character in the array.
//Hint: if abacada is provided, by replacing a with x the program print xbxcxdx

// void replaceChar(const char* st,char old, char fresh){
//     //base case
//     if(st[0]=='\0') return;

//     //conditions and necessary calculations
//     if(st[0] == old){
//         cout << fresh;
//     } else {
//         cout << st[0];
//     }
//     replaceChar(st+1,old,fresh);
// }

// int main(){
//     const char order[] = "abacadaabac";
//     int past = 'a';
//     int present = 'x';
//     replaceChar(order,past,present);
//     cout << endl;

//     return 0;
// }

//5. Find the length of character array.
// IF abcde i finds provided, the length should be 5
// int calculateLength(const char* st){
//     //base case
//     if(st[0]=='\0') return 0;

//     //recursive case
//     return 1+calculateLength(st+1);
// }

// int main(){
//     const char rando[] = "afnevinsitgn";
//     cout << "Length: " << calculateLength(rando);
// }

// 6. Convert the string of digits to integer.
// Hi nt: if "12345" is provided then the program would return 12345
// Hint: if we have "12345"
// Then call the recursion on "1234",
// Then call the recursion on "123",
// Then call the recursion on "12",
// Then call the recursion on "1", now n=1,
// Then call the recursion on empty array.
// if n=0, then return 0;
// The small answer is 0, then 0*10+1 as the last digit which is 1
// Then 1*10+2 as the last digit 
// Then 12*10+3
// Then 123*10+4
// Finally 1234*10+5

int stringToInt(const char* str) {
    // Base case: empty string
    if (str[0] == '\0') {
        return 0;
    }

    // Convert the rest first
    int smallAns = stringToInt(str + 1);

    // Current digit
    int digit = str[0] - '0';

    // Multiply smallAns by 10 and add current digit
    int len = 0;
    for (const char* s = str + 1; *s != '\0'; ++s) len++; // length of rest
    return digit * pow(10, len) + smallAns;
}

int main() {
    const char str[] = "1234567";
    cout << stringToInt(str) << endl;
    return 0;
}