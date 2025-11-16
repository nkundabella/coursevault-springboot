#include <iostream>
using namespace std;

//int addition(int n1, int n2){
//	return n1 + n2;
//}

template<typename q>
q addition(q a, q b){
	return a + b;
}
int main(){
	int x, y;
	float n1 = 4.5, n2 = 76;
	cout << "Enter two numbers: " << endl;
	cin >> x >> y;
	
	
	cout << "The sum is = " << addition<int>(x,y) << endl;
	cout << "The sum is = " << addition<float>(n1,n2) << endl;
	return 0;
}