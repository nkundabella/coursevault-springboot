//#include<iostream>
//using namespace std;
//
//int main(){
//
//string Fname, Lname, Fullname;
//cout<<"Enter your first name: ";
//getline(cin,Fname);
//cin>>Fname;
//cout<<"Enter your last name: ";
//cin>>Lname;
//Fullname = Fname+ " " +Lname;
//cout<<"Your Names Are "<<Fullname<<endl;
//
//return 0;
//} 

//#include<iostream>
//using namespace std;
//	namespace rca {
//		int num=80;
////		int value(){
////		return num;
////		}
//	}
//	namespace groupc{
//		int num=30;
//		void value(){
//			cout<<"The number of students is "<<num<<endl;
//		}
//	}
//	int num=240;
//	int main(){
//		int num=10;
//		cout<<"RCA: "<<rca::num<<endl;
//		
//		cout<<"Group C: "<<groupc::num<<endl;
//		groupc::value();
//		cout<<"Global: "<<::num<<endl;
//		cout<<"Local: " <<num<<endl;
//		
//		return 0;
//	}


#include<iostream>
using namespace std;
	  namespace userDefined {
	  	
	  int insideNamespace = 46;
	  int cout(){
	  	return insideNamespace;
	  	
	  }	
}

	int myGlobal = 85;
	int cout(){	
	
	int square = myGlobal * myGlobal;
    return square;  
	  
	}

int main(){
	
	int cout = 60;
	std::cout<<"The local variable cout in main is "<<cout<<""<<endl;
	std::cout<<"The variable in userDefined namespace is "<<userDefined::insideNamespace<<"."<<endl;
	std::cout<<"The output of cout() in userDefined is "<<userDefined::cout()<<"."<<endl;
	std::cout<<"The value of myGlobal is "<<::myGlobal<<"."<<endl;
	std::cout<<"The output of global cout() is "<<::cout()<<"."<<endl;
	
	return 0;
	
}