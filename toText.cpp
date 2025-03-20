#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib> // For system("CLS")

using namespace std;

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

    void addPurchase(const string& item, double price, const string& time) {
        purchases.push_back(Purchase(item, price, time));
        saveToFile("finance_data.txt"); // Save changes
    }

    void deletePurchase(int index) {
        if (index >= 0 && index < purchases.size()) {
            purchases.erase(purchases.begin() + index);
            saveToFile("finance_data.txt"); // Save changes
        } else {
            cout << "Invalid purchase index!\n";
        }
    }

    void display() const {
        cout << "Account: " << name << " (ID: " << accountID << ")\n";
        cout << "Balance: $" << balance << "\n";
        cout << "Savings: $" << savings << "\n";
        cout << "Purchases:\n";
        for (const auto& p : purchases) {
            cout << "  - " << p.item << ", $" << p.price << ", " << p.time << "\n";
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
            string accountID, password, name;
            double balance, savings;

            cout << "Enter Account ID: ";
            getline(cin, accountID);
            cout << "Enter Password: ";
            getline(cin, password);
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter Initial Savings: ";
            cin >> savings;
            cin.ignore();

            vector<FinanceAccount> accounts = FinanceAccount::loadFromFile(filename);
            for (const auto& acc : accounts) {
                if (acc.accountID == accountID) {
                    cout << "Account ID already exists!\n";
                    system("PAUSE");
                    continue;
                }
            }

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
                    cout << "\n1. View Account\n2. Add Purchase\n3. Delete Purchase\n4. Logout\n";
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
                        cout << "Enter Time (YYYY-MM-DD HH:MM): ";
                        getline(cin, time);

                        currentAccount.addPurchase(item, price, time);
                        cout << "Purchase added!\n";
                        system("PAUSE");
                    } else if (action == 3) {
                        system("CLS");
                        currentAccount.display();
                        int index;
                        cout << "Enter the index of the purchase to delete: ";
                        cin >> index;
                        cin.ignore();
                        currentAccount.deletePurchase(index - 1); // Adjust for 0-based index
                        cout << "Purchase deleted!\n";
                        system("PAUSE");
                    } else if (action == 4) {
                        cout << "Logging out...\n";
                        system("PAUSE");
                        break;
                    } else {
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
