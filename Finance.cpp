#include <iostream>
#include <ctime>
#include <vector>
#include "Finance.h"
using namespace std;

int Finance::ID=0;

Finance::Finance(){
    name="No name";
    password="No Password";
    balance=0;
}
Finance::Finance(string newName, string newPassword){
    name=newName;
    password=newPassword;
    ID++;
    personalID=ID;
}

string Finance::getName(){
    return name;
}
int Finance::getID(){
    return ID;
}
int Finance::getPersonalID(){
    return personalID;
}
string Finance::getPassword(){
    return password;
}
double Finance::getBalance(){
    cout<<"Current balance: $"<<balance<<endl;
    return balance;
}
double Finance::getSavingBalance(){
    return savingBalance;
}
long getNow(){
    time_t timestamp;
    time(&timestamp);
  
    // Display the date and time represented by the timestamp
    return timestamp;
}


void Finance::isNew(bool isNew){

}
void Finance::setName(string newName){
    name=newName;
}
void Finance::setID(int newID){
    ID=newID;
}
void Finance::setPersonalID(int newPersonalID){
    personalID=newPersonalID;
}
void Finance::setPassword(string newPassword){
    password=newPassword;
}
void Finance::setBalance(double newBalance){
    balance=newBalance;
}
void Finance::setSavingBalance(double newSavings){
    savingBalance=newSavings;
}
long setTime(int year, int month, int day, int hour, int min, int sec){
  struct tm datetime;
  time_t timestamp;

  datetime.tm_year = year - 1900; // Number of years since 1900
  datetime.tm_mon = month - 1; // Number of months since January
  datetime.tm_mday = day;
  datetime.tm_hour = hour;
  datetime.tm_min = min;
  datetime.tm_sec = sec;
  // Daylight Savings must be specified
  // -1 uses the computer's timezone setting
  datetime.tm_isdst = -1;

  timestamp = mktime(&datetime);

  return timestamp;
}


void Finance::withdraw(string name, string type, double amount, long time){
    logName.push_back(name);
    logType.push_back(type);
    logAmount.push_back(amount);
    logTime.push_back(time);
    balance-=amount;
}
void Finance::deposit(string name, string type, double amount, long const time){
    logName.push_back(name);
    logType.push_back(type);
    logAmount.push_back(amount);
    logTime.push_back(time);
    balance+=amount;
}
void Finance::getExpenseType(string type){
    double amount;
    bool found=false;
    for (int i=0; i<logType.size(); i++){
        if (type==logType[i]){
            amount+=logAmount[i];
            found=true;
        }
    }
    if (found==false){
        cout<<"Type "<<type<<" not found"<<endl;
    }
    else{
        cout<<"Expenses for "<<type<<" $"<<amount<<endl;
    }
}

int Finance::getLogSize(){
    return logSize;
}
void Finance::getLogList(){
    if (logName.empty()==true){
        cout<<"No logs"<<endl;
    }
    // cout<<"Log size: "<<logName.size()<<endl;
    for (int i=0; i<logName.size(); i++){
        cout<<i<<" "<<logName[i]<<" "<<logType[i]<<" $"<<logAmount[i]<<'\t'<<ctime(&logTime[i])<<endl;
    }
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
}
void Finance::getLog(){

}
template <typename T>
void Finance::setLog(int index, int type, T newData){
    switch (type){
        case 0: logName[index]=newData; break;
        case 1: logType[index]=newData; break;
        case 2: balance-=newData-logAmount[index]; logAmount[index]=newData; break;
        case 3: logTime[index]=newData; break;
    }
}
void Finance::deleteLog(int index){
    balance+=logAmount[index];
    logName.erase(logName.begin()+index);
    logType.erase(logType.begin()+index);
    logAmount.erase(logAmount.begin()+index);
    // logTime[index].erase();
}
void Finance::clearLog(){
    for (int i: logAmount){
        balance+=i;
    }
    logName.clear();
    logType.clear();
    logAmount.clear();
    // logTime.clear();
}