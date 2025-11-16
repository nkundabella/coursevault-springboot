#include <iostream>
using namespace std;
#include <iomanip>

int main(){
	
	int a = 127;
	cout<<setw(20) << "RCA"<<endl; //a method to format output
	cout << setprecision(2) << "Fixed: "<<1234.56789 <<endl;
	cout <<setprecision(3) <<"Scientific: " <<1234.56789 <<endl;
	cout << "Hex: " << hex << a <<endl;
	cout << "Oct: " << oct << a <<endl;
	
	return 0;
}