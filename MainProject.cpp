#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib> // For system("CLS")
#include <iomanip>
#include <regex>

using namespace std;

string formatCurrency(double amount) {
    stringstream ss;
    ss << fixed << setprecision(2) << amount;
    return "$" + ss.str();
}


bool isValidDateTime(const string& datetime) {
    regex pattern("\\d{4}-\\d{2}-\\d{2}-\\d{2}:\\d{2}");
    return regex_match(datetime, pattern);
}

class Purchase {
public:
    string item;
    double price;
    string time;

    Purchase(string item, double price, string time) : item(item), price(price), time(time) {}

    string toString() const {
        return item + "," + to_string(price) + "," + time;
    }

    static Purchase fromString(const string& line) {
        stringstream ss(line);
        string item, priceStr, time;
        getline(ss, item, ',');
        getline(ss, priceStr, ',');
        getline(ss, time);
        return Purchase(item, stod(priceStr), time);
    }
};

class FinanceAccount {
public:
    string accountID, password, name;
    double balance, savings;
    vector<Purchase> purchases;

    FinanceAccount(string accountID, string password, string name, double balance, double savings)
        : accountID(accountID), password(password), name(name), balance(balance), savings(savings) {}

    bool authenticate(const string& enteredPassword) const {
        return password == enteredPassword;
    }

    void updateBalance(double amount) {
        balance += amount;
        saveToFile("finance_data.txt");
    }

    void updateSavings(double amount) {
        savings += amount;
        saveToFile("finance_data.txt");
    }

    bool addPurchase(const string& item, double price, const string& time) {
        if (price <= balance) {
            purchases.push_back(Purchase(item, price, time));
            updateBalance(-price); // Deduct from balance
            saveToFile("finance_data.txt");
            return true;
        } else {
            cout << "Insufficient balance!\n";
            return false;
        }
    }

    bool deletePurchase(int index) {
        if (index >= 0 && index < purchases.size()) {
            double refund = purchases[index].price;
            purchases.erase(purchases.begin() + index);
            updateBalance(refund); // Refund the amount
            saveToFile("finance_data.txt");
            return true;
        } else {
            cout << "Invalid purchase index!\n";
            return false;
        }
    }

    void getExpense(string& name, string& sDate, string& eDate){
        double expense;
        int year, Syear, Eyear, month, Smonth, Emonth, day, Sday, Eday, hour, Shour, Ehour, min, Smin, Emin; 
        int tempi=0, count=0;
        char tempc;

        // for (int j=0; j<sDate.size(); j++){     //Breaks up purchase date to see if it falls in range
        //     if (sDate[j]=='-' || sDate[j]==':'){
        //         switch (count){
        //             case 0: Syear=static_cast<int>(tempi/10); break;
        //             case 1: Smonth=static_cast<int>(tempi/10); break;
        //             case 2: Sday=static_cast<int>(tempi/10); break;
        //             case 3: Shour=static_cast<int>(tempi/10); break;
        //             case 4: Smin=static_cast<int>(tempi/10); break;
        //         }
        //         count++;
        //         tempi=0;
        //     }
        //     else{
        //         tempc=sDate[j];
        //         tempi+=static_cast<int>(tempc-48);
        //         tempi=10*tempi;
        //     }
        // }
        // tempi=0;
        // count=0;
        // for (int j=0; j<eDate.size(); j++){     //Breaks up purchase date to see if it falls in range
        //     if (eDate[j]=='-' || eDate[j]==':'){
        //         switch (count){
        //             case 0: Eyear=static_cast<int>(tempi/10); break;
        //             case 1: Emonth=static_cast<int>(tempi/10); break;
        //             case 2: Eday=static_cast<int>(tempi/10); break;
        //             case 3: Ehour=static_cast<int>(tempi/10); break;
        //             case 4: Emin=static_cast<int>(tempi/10); break;
        //         }
        //         count++;
        //         tempi=0;
        //     }
        //     else{
        //         tempc=eDate[j];
        //         tempi+=static_cast<int>(tempc-48);
        //         tempi=10*tempi;
        //     }
        // }
        // tempi=0;
        // count=0;

        for (int i=0; i<purchases.size(); i++){
            if (purchases[i].item==name){
                if (sDate!="All"){
                    for (int j=0; j<purchases[i].time.size(); j++){     //Breaks up purchase date to see if it falls in range
                        if (purchases[i].time[j]=='-' || purchases[i].time[j]==':'){
                            switch (count){
                                case 0: year=static_cast<int>(tempi/10); break;
                                case 1: month=static_cast<int>(tempi/10); break;
                                case 2: day=static_cast<int>(tempi/10); break;
                                case 3: hour=static_cast<int>(tempi/10); break;
                                case 4: min=static_cast<int>(tempi/10); break;
                            }
                            count++;
                            tempi=0;
                        }
                        else{
                            tempc=purchases[i].time[j];
                            tempi+=static_cast<int>(tempc-48);
                            tempi=10*tempi;
                        }
                    }
                    if ((year>=Syear && year<=Eyear) && (month>=Smonth && month<=Emonth) && (day>=Sday && day<=Eday) && (hour>=Shour && hour<=Ehour) && (min>=Smin && min<=Emin)){
                        expense+=static_cast<double>(purchases[i].price);
                        cout<<"Add "<<purchases[i].price<<endl;
                    }
                }
                
                else if (sDate=="All"){
                    expense+=static_cast<double>(purchases[i].price);
                    cout<<"Add "<<purchases[i].price<<endl;
                }
            }
        }
        // cout<<"Date: "<<year<<" "<<month<<" "<<day<<" "<<hour<<" "<<min<<endl;
        cout<<"The expense for "<<name<<" is: "<<expense;
    }

    void display() const {
        cout << "Account: " << name << " (ID: " << accountID << ")\n";
        cout << "Balance: " << formatCurrency(balance) << "\n";
        cout << "Savings: " << formatCurrency(savings) << "\n";
        cout << "Purchases:\n";
        for (size_t i = 0; i < purchases.size(); ++i) {
            cout << "  " << (i + 1) << ". " << purchases[i].item 
                 << ", " << formatCurrency(purchases[i].price) 
                 << ", " << purchases[i].time << "\n";
        }
    }

    void saveToFile(const string& filename) const {
        vector<FinanceAccount> accounts = loadFromFile(filename);
        ofstream file(filename);
        if (!file) {
            cerr << "Error opening file!\n";
            return;
        }

        bool found = false;
        for (auto& acc : accounts) {
            if (acc.accountID == accountID) {
                acc = *this;
                found = true;
            }
        }
        if (!found) accounts.push_back(*this);

        for (const auto& acc : accounts) {
            file << acc.accountID << "\n"
                 << acc.password << "\n"
                 << acc.name << "\n"
                 << acc.balance << "\n"
                 << acc.savings << "\n";

            file << acc.purchases.size() << "\n";
            for (const auto& p : acc.purchases) {
                file << p.toString() << "\n";
            }
        }
        file.close();
    }

    static vector<FinanceAccount> loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) return {};

        vector<FinanceAccount> accounts;
        string accountID, password, name, line;
        double balance, savings;
        int numPurchases;

        while (getline(file, accountID)) {
            getline(file, password);
            getline(file, name);
            file >> balance >> savings >> numPurchases;
            file.ignore();

            vector<Purchase> purchases;
            for (int i = 0; i < numPurchases; ++i) {
                getline(file, line);
                purchases.push_back(Purchase::fromString(line));
            }
            FinanceAccount acc(accountID, password, name, balance, savings);
            acc.purchases = purchases;
            accounts.push_back(acc);
        }
        return accounts;
    }
};


// long getNow(){
//     time_t timestamp;
//     time(&timestamp);
//     return timestamp;
// }
// long setTime(){
//     struct tm datetime;
//     time_t timestamp;
//     int year, month, day, hour, min;
//     cout<<"Enter Time (YYYY-MM-DD HH:MM): ";
//     cin>>year;
//     cin>>month;
//     cin>>day;
//     cin>>hour;
//     cin>>min;
  
//     datetime.tm_year = year - 1900; // Number of years since 1900
//     datetime.tm_mon = month - 1; // Number of months since January
//     datetime.tm_mday = day;
//     datetime.tm_hour = hour;
//     datetime.tm_min = min;
//     datetime.tm_sec = 0;
//     // Daylight Savings must be specified
//     // -1 uses the computer's timezone setting
//     datetime.tm_isdst = -1;
//     timestamp = mktime(&datetime);
  
//     return timestamp;
// }


int main() {
    string filename = "finance_data.txt";

    int choice;
    while (true) {
        system("CLS"); // Clear screen
        cout << "\n1. Create Account\n2. Login\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            system("CLS");
            string accountID;
            
            // Check ID first
            cout << "Enter Account ID: ";
            getline(cin, accountID);
            
            vector<FinanceAccount> accounts = FinanceAccount::loadFromFile(filename);
            bool idExists = false;
            for (const auto& acc : accounts) {
                if (acc.accountID == accountID) {
                    cout << "Account ID already exists!\n";
                    system("PAUSE");
                    idExists = true;
                    break;
                }
            }
            
            if (idExists) {
                continue;
            }
            
            // If ID is available, proceed with rest of account creation
            string password, name;
            double balance, savings;
            
            cout << "Enter Password: ";
            getline(cin, password);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Initial Savings: ";
            cin >> savings;
            cin.ignore();

            FinanceAccount newAccount(accountID, password, name, balance, savings);
            newAccount.saveToFile(filename);
            cout << "Account created successfully!\n";
            system("PAUSE");

        } else if (choice == 2) {
            system("CLS");
            string accountID, password;
            cout << "Enter Account ID: ";
            getline(cin, accountID);
            cout << "Enter Password: ";
            getline(cin, password);

            vector<FinanceAccount> accounts = FinanceAccount::loadFromFile(filename);
            bool found = false;
            FinanceAccount currentAccount("", "", "", 0, 0);

            for (const auto& acc : accounts) {
                if (acc.accountID == accountID && acc.authenticate(password)) {
                    currentAccount = acc;
                    found = true;
                    break;
                }
            }

            if (found) {
                cout << "Login successful!\n";
                system("PAUSE");

                int action;
                while (true) {
                    system("CLS");
                    cout << "\n1. View Account\n2. Add Purchase\n3. Delete Purchase\n4. Get Expense\n5. Logout\n";
                    cout << "Enter choice: ";
                    cin >> action;
                    cin.ignore();

                    if (action == 1) {
                        system("CLS");
                        currentAccount.display();
                        system("PAUSE");
                    } else if (action == 2) {
                        system("CLS");
                        string item, time;
                        double price;

                        cout << "Enter Item Name: ";
                        getline(cin, item);
                        cout << "Enter Price: ";
                        cin >> price;
                        cin.ignore();
                        cout << "Enter Time (YYYY-MM-DD-HH:MM): ";
                        getline(cin, time);
                        // if (time=="Current"){
                        //     time=getNow();
                        // }
                        // else if (time=="Custom"){
                        //     time=setTime();
                        // }

                        if (!isValidDateTime(time)) {
                            cout << "Invalid date/time format! Use YYYY-MM-DD HH:MM\n";
                            system("PAUSE");
                            continue;
                        }

                        if (currentAccount.addPurchase(item, price, time)) {
                            cout << "Purchase added!\n";
                        }
                        system("PAUSE");
                    } else if (action == 3) {
                        system("CLS");
                        currentAccount.display();
                        int index;
                        cout << "Enter the index of the purchase to delete: ";
                        cin >> index;
                        cin.ignore();
                        if (currentAccount.deletePurchase(index - 1)) {
                            cout << "Purchase deleted!\n";
                        }
                        system("PAUSE");
                    } else if (action == 4) {
                        system("CLS");
                        currentAccount.display();
                        string name, startDate, endDate;
                        cout << "Enter the name of a purchase: ";
                        cin >> name;
                        cout<<" Enter date range of purchase ('All' for no date range): ";
                        cin>>startDate;
                        cin>>endDate;
                        cin.ignore();
                        currentAccount.getExpense(name, startDate, endDate);
                        system("PAUSE");
                    } else if (action == 5) {
                        cout << "Logging out...\n";
                        system("PAUSE");
                        break;
                    }  else {
                        cout << "Invalid choice!\n";
                        system("PAUSE");
                    }
                }
            } else {
                cout << "Invalid Account ID or Password!\n";
                system("PAUSE");
            }
        } else if (choice == 3) {
            cout << "Exiting program...\n";
            system("PAUSE");
            break;
        } else {
            cout << "Invalid choice!\n";
            system("PAUSE");
        }
    }
    return 0;
}

