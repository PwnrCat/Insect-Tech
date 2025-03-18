#ifndef FINANCE_H
#define FINANCE_H
#include <iostream>
#include <ctime>
#include <vector>
using namespace std;
class Finance{
    public:
        Finance();
        Finance(string newName, string newPassword);

        string getName();
        static int getID();
        int getPersonalID();
        string getPassword();
        double getBalance();
        double getSavingBalance();
        long getNow();

        void isNew(bool isNew);
        void setName(string newName);
        static void setID(int newID);
        void setPersonalID(int newPersonalID);
        void setPassword(string newPassword);
        void setBalance(double newBalance);
        void setSavingBalance(double newSavings);
        long setTime(int year, int month, int day, int hour, int min, int sec);

        void withdraw(string name, string type, double amount, long time);
        void deposit(string name, string type, double amount, long time);
        void getExpenseType(string type);

        int getLogSize();
        void getLogList();
        void getLog();
        template <typename T>
        void setLog(int index, int type, T newData);
        void deleteLog(int index);
        void clearLog();

    protected:
        bool newAccount;
        string name;
        static int ID;
        int personalID;
        string password;
        double balance;
        double savingBalance;
        vector<string> logName;
        vector<string> logType;
        vector<double> logAmount;
        vector<long> logTime;
        int logSize;
};
#endif