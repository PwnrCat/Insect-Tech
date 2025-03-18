#include <iostream>
#include <ctime>
#include "Finance.h"
#include "Finance.cpp"
using namespace std;

vector<Finance*> accountList={};

int main(){
    Finance account1("Jay","P4$$word");
    Finance account2("Jay 2","Pissword");
    accountList.push_back(&account1);
    accountList.push_back(&account2);

    cout<<account1.getName()<<" "<<account1.getPassword()<<endl;

    Finance accountGeneral("Jay","P4$$word");
    cout<<&account1<<endl;
    cout<<&account2<<endl;
    for (Finance* account:accountList){
        cout<<account<<endl;
    }
    // if (accountGeneral.getName()==)
    
    
    

    // accountGeneral.getBalance();
    // accountGeneral.withdraw("Pumpkin","groc",30,getNow());
    // accountGeneral.getLog();
    // account1.setBalance(accountGeneral.getBalance());
    // for (int i=0; i<accountGeneral.getLogSize(); i++){
    //         account1.withdraw(accountGeneral.logName[i]);
    // }
    return 0;
}