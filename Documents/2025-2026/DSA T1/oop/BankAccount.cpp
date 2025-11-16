#include<iostream>
using namespace std;

class BankAccount {
    private:
    int accountNumber;
    int balance;

    public:
    BankAccount(){} // default constructor

    BankAccount(int a, int b){
        accountNumber = a;
        balance = b;
    }

    int deposit(int depMon){
        if(depMon > 0){
            balance += depMon;
            cout << "You have deposited " << depMon << " FRW into your account. Your new balance is " << balance << " FRW." << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }
    //Withdraw money
    int withdraw(int drawMon){
        if(drawMon <= balance && drawMon > 0){
            balance -= drawMon;
            cout << "You have withdrawn " << drawMon << " FRW from your account. Your new balance is " << balance << " FRW." << endl;
        } else {
            cout << "You don't have enough balance in your bank account." << endl;
        }
    }

    void setAccountNumber(int accNum){
        accountNumber = accNum;
    }

    int getAccountNumber(){
        return accountNumber;
    }

    void setBalance(int bal){
        balance = bal;
    }
    int getBalance(){
        return balance;
    }
};

int main(){
    BankAccount b1;
    b1.setAccountNumber(200);
    b1.setBalance(1500);

    cout << "Account Number 1: " << b1.getAccountNumber() << endl;
    cout << "Balance 1: " << b1.getBalance() << endl;
    b1.deposit(320);
    b1.withdraw(15);

    cout << endl;
    
    BankAccount b2(300, 4500); // using the parametized constructors
    cout << "AccountNumber b2: " << b2.getAccountNumber() << endl;
    cout << "Balance b2: " << b2.getBalance() << endl;  
    return 0;
}