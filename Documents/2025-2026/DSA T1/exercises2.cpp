// Use sqrt and pow to calculate the hypotenuse of a right triangle

#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

//int main (){
//	int a, b, hyp;
//	cout << "Enter the base and height: " <<endl;
//	cin>>a>>b;
//	hyp = sqrt(pow(a,2) + pow(b,2));
//	cout << "The hypotenuse of this right triangle is: " << hyp <<endl;
//
//	return 0;
//}

//Print all integer pairs(a,b) greater than 1 and  less than 100 that can satisfy hypotenuse rule. 
//Hypotenuse should be also integer. 
//Display the number of pairs found. 
//Treat (3,4) and (4,3) as one pair.

//int main() {
//	int x, y;
//	float hyp;
//	int i=0;
//	
//	for(x=2;x<100;x++){
//		for(y=x;y<100;y++){	
//			hyp = sqrt(pow(x,2) + pow(y,2));	
//			if(hyp == int(hyp)){	
//			cout << "(" << x << ", " << y << ")" <<endl;
//			i++; 
//			}		
//		}
//			
//	}
//	
//	cout << setw(15) << "Found " << i << " number of pairs." <<endl;
//	 
//	return 0;
//}

//Find the roots of quadratic function if the values of a, b and c are provided.

int main () {
	float r1, r2, a, b, c;
	cout << "Enter values for a, b and c respectively here below!" <<endl;
	cin >> a >> b >> c;
	double det = sqrt(pow(b,2) - 4 * (a*c));
	
	if(det>0){
		r1 = (-(b) + sqrt(pow(b,2) - 4 * (a*c))) / 2 * a;
		r2 = (-(b) - sqrt(pow(b,2) - 4 * (a*c))) / 2 * a;
		cout << "The roots are: " << r1 << " and " << r2 <<endl;
	} else {
		cout << "No roots!" <<endl;
	}
	
	return 0;
}
