#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

// Helper function to get current date and time
string currentDateTime() {
    time_t now = time(0);
    char buf[80];
    struct tm tstruct;
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return "[" + string(buf) + "]";
}

// Helper function to generate a simulated Transaction ID
string generateTxnID() {
    return "TXN" + to_string(rand() % 900000 + 100000);
}

class BankAccount {
private:
    string accountHolder;
    int pin;
    double balance;
    vector<string> history;

    double dailyLimit = 20000;
    double withdrawnToday = 0;
    double minBalance = 500;
    bool isLocked = false;

public:
    BankAccount(string name, int p, double initial_balance) {
        accountHolder = name;
        pin = p;
        balance = initial_balance;
        history.push_back(currentDateTime() + " Account opened | Initial Balance: $" + to_string(balance));
    }

    bool authenticate() {
        if (isLocked) {
            cout << "\n[SECURITY ALERT] Account is locked. Contact bank support.\n";
            return false;
        }

        int attempts = 0;
        while (attempts < 3) {
            int enteredPin;
            cout << "Enter PIN to access account: ";
            cin >> enteredPin;

            if (enteredPin == pin) return true;

            attempts++;
            cout << "[!] Incorrect PIN. Attempts left: " << 3 - attempts << endl;
        }

        isLocked = true;
        cout << "\n[SECURITY ALERT] Account locked due to multiple failed attempts!\n";
        return false;
    }

    void showAccountDetails() {
        cout << "\n--- Account Details ---\n";
        cout << "Account Holder : " << accountHolder << endl;
        cout << "Account Type   : Savings\n";
        cout << "Daily Limit    : $" << dailyLimit << endl;
        cout << "Minimum Bal.   : $" << minBalance << endl;
        showBalance();
    }

    void showBalance() {
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "\n[ERROR] Invalid deposit amount!\n";
            return;
        }
        balance += amount;
        string txnID = generateTxnID();
        history.push_back(currentDateTime() + " " + txnID + " Deposited $" + to_string(amount));
        
        cout << "\n--------------------------------------------------" << endl;
        cout << "[SUCCESS] $" << fixed << setprecision(2) << amount << " has been deposited." << endl;
        cout << "Transaction ID: " << txnID << endl;
        cout << "--------------------------------------------------" << endl;
        showBalance();
    }

    void withdraw(double amount, int method) {
        if (amount <= 0 || amount > balance) {
            cout << "\n[ERROR] Invalid amount or insufficient balance!\n";
            return;
        }

        if (withdrawnToday + amount > dailyLimit) {
            cout << "\n[ERROR] Daily withdrawal limit ($" << dailyLimit << ") exceeded!\n";
            return;
        }

        balance -= amount;
        withdrawnToday += amount;

        string methodType;
        string notification;

        switch(method) {
            case 1:
                methodType = "ATM";
                notification = "NOTIFICATION: Money withdrawn via ATM. Please collect your cash.";
                break;
            case 2:
                methodType = "Bank Counter";
                notification = "NOTIFICATION: Cash withdrawal processed at the bank counter.";
                break;
            case 3:
                methodType = "Cheque";
                notification = "NOTIFICATION: Self-Cheque has been cleared for cash withdrawal.";
                break;
            case 4:
                methodType = "Debit Card POS";
                notification = "NOTIFICATION: Money withdrawn via Debit Card (POS Cashback).\nIf it was not you, contact your bank immediately!";
                break;
            default:
                methodType = "Unknown";
                notification = "Withdrawal detected.";
        }

        string txnID = generateTxnID();
        history.push_back(currentDateTime() + " " + txnID + " Withdrawn $" + to_string(amount) + " via " + methodType);

        cout << "\n--------------------------------------------------" << endl;
        cout << notification << endl;
        cout << "Transaction ID: " << txnID << endl;
        cout << "--------------------------------------------------" << endl;

        if (balance < minBalance) {
            balance -= 50;
            history.push_back(currentDateTime() + " SERVICE CHARGE: $50.00 (Balance below minimum)");
            cout << "[WARNING] Balance fell below minimum. $50.00 service charge applied.\n";
        }

        cout << "[SUCCESS] Withdrawal completed.\n";
        showBalance();
    }

    void addInterest() {
        double interest = balance * 0.04;
        balance += interest;
        history.push_back(currentDateTime() + " Interest Credited: $" + to_string(interest));
        cout << "\n[SUCCESS] 4% Annual Interest credited: $" << fixed << setprecision(2) << interest << endl;
        showBalance();
    }

    void changePIN() {
        int oldPin, newPin;
        cout << "\nEnter old PIN: ";
        cin >> oldPin;

        if (oldPin != pin) {
            cout << "[ERROR] Incorrect PIN!\n";
            return;
        }

        cout << "Enter new 4-digit PIN: ";
        cin >> newPin;
        pin = newPin;

        history.push_back(currentDateTime() + " PIN Changed Successfully");
        cout << "[SUCCESS] PIN updated successfully.\n";
    }

    void showHistory() {
        cout << "\n--- Full Transaction History ---\n";
        for (const string& h : history)
            cout << h << endl;
    }

    void miniStatement() {
        cout << "\n--- Mini Statement (Last 5 Transactions) ---\n";
        int start = max(0, (int)history.size() - 5);
        for (int i = start; i < history.size(); i++)
            cout << history[i] << endl;
    }
};

int main() {
    srand(time(0)); // Seed for random Transaction IDs
    BankAccount account("Mukesh Sahni", 99, 1000.00);

    cout << "\n==========================================";
    cout << "\n   ADVANCED BANK MANAGEMENT SYSTEM";
    cout << "\n==========================================\n";

    if (!account.authenticate()) return 0;

    int choice;
    do {
        cout << "\n--- MAIN MENU ---";
        cout << "\n1. Account Details";
        cout << "\n2. Check Balance";
        cout << "\n3. Deposit Money";
        cout << "\n4. Withdraw Money";
        cout << "\n5. Transaction History";
        cout << "\n6. Mini Statement";
        cout << "\n7. Add Interest";
        cout << "\n8. Change PIN";
        cout << "\n9. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        double amt;
        int method;

        switch (choice) {
            case 1: account.showAccountDetails(); break;
            case 2: account.showBalance(); break;
            case 3:
                cout << "Enter deposit amount: $"; cin >> amt;
                account.deposit(amt);
                break;
            case 4:
                cout << "\nSelect Withdrawal Method:";
                cout << "\n1. ATM Withdrawal";
                cout << "\n2. Bank Branch Cash Counter";
                cout << "\n3. Cheque Withdrawal (Self-Cheque)";
                cout << "\n4. Debit Card Cash Withdrawal (POS)";
                cout << "\nSelect Method (1-4): ";
                cin >> method;
                if (method < 1 || method > 4) {
                    cout << "[ERROR] Invalid method selection!\n";
                    break;
                }
                cout << "Enter withdrawal amount: $"; cin >> amt;
                account.withdraw(amt, method);
                break;
            case 5: account.showHistory(); break;
            case 6: account.miniStatement(); break;
            case 7: account.addInterest(); break;
            case 8: account.changePIN(); break;
            case 9: cout << "Thank you for using our banking services. Goodbye!\n"; break;
            default: cout << "Invalid choice! Please select from 1-9.\n";
        }

    } while (choice != 9);

    return 0;
}
