#ifndef FINANCE_H
#define FINANCE_H
#include <iostream>
#include <vector>
using namespace std;
class Finance{
    public:
        Finance();      //
        Finance(string newName, string newPassword, double newBalance);

        string getName();
        int getID();
        string getPassword();
        double getBalance();
        double getSavingBalance();
        double getMonthlySavings();
        double getMonthlyExpenses();
        double getSalary();
        double getRent();
        double getGrocery();
        double getTransport();
        double getPersonal();

        void isNew(bool isNew);
        void setName(string newName);
        void setID(int newID);
        void setPassword(string newPassword);
        void setBalance(double newBalance);
        void setSavingBalance(double newSavings);
        void setMonthlySavings(double salary, double other);
        void setMonthlyExpenses(double rent, double grocery, double transport, double personal, double other);
        void setSalary(double newSalary);
        void setRent(double newRent);       
        void setGrocery(double newGrocery);
        void setTransport(double newTransport);
        void setPersonal(double newPersonal);
        void setOtherSavings(double* savingList);
        void setOtherExpenses(double* spendingList);

        void withdraw(string name, double amount);
        void deposit(string name, double amount);
        void calcSalary(double wage, double workHours);
        void getLog();

    private:
        bool newAccount;
        string name;
        int ID;
        string password;
        double balance;
        double savingBalance;
        double monthlySavings;
        double monthlyExpenses;
        double salary;
        double rent;
        // double grocery;
        // double transport;
        // double personal;
        // double otherSavings;
        // double otherExpenses;
        vector<string> logName;
        vector<string> logType;
        vector<double> logAmount;
        vector<int> logTime;
};
#endif