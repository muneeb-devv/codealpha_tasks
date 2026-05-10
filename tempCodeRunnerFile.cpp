#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

// ========== Transaction Class ==========
class Transaction {

public:
    string type;
    double amount;
    string date;
};

// ========== Bank Account Class ==========
class BankAccount {

private:
    string pin;

public:
    string name;
    string accNo;
    double balance = 0;

    vector<Transaction> history;

    // Get Current Date
    string getDate() {

        time_t now = time(0);

        return ctime(&now);
    }

    // Create Account
    void createAccount() {

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Create PIN: ";
        cin >> pin;

        accNo = "PK" + to_string(rand() % 10000);

        cout << "\nAccount Created Successfully!\n";
        cout << "Account Number: " << accNo << endl;
    }

    // Verify PIN
    bool checkPin() {

        string p;

        cout << "Enter PIN: ";
        cin >> p;

        if (p == pin)
            return true;

        cout << "Wrong PIN!\n";

        return false;
    }

    // Add Transaction
    void addTransaction(string type, double amount) {

        Transaction t;

        t.type = type;
        t.amount = amount;
        t.date = getDate();

        history.push_back(t);
    }

    // Deposit
    void deposit() {

        double amount;

        cout << "Enter Amount: ";
        cin >> amount;

        balance += amount;

        addTransaction("Deposit", amount);

        cout << "Money Deposited!\n";
    }

    // Withdraw
    void withdraw() {

        double amount;

        cout << "Enter Amount: ";
        cin >> amount;

        if (amount > balance) {

            cout << "Insufficient Balance!\n";
            return;
        }

        balance -= amount;

        addTransaction("Withdraw", amount);

        cout << "Money Withdrawn!\n";
    }

    // Show Balance
    void showBalance() {

        cout << "\nCurrent Balance: Rs." << balance << endl;
    }

    // Show History
    void showHistory() {

        cout << "\n===== Transaction History =====\n";

        for (int i = 0; i < history.size(); i++) {

            cout << i + 1 << ". "
                 << history[i].type
                 << " | Rs." << history[i].amount
                 << " | " << history[i].date;
        }
    }

    // Save Data
    void saveFile() {

        ofstream file("bank.txt");

        file << name << endl;
        file << accNo << endl;
        file << balance << endl;
        file << pin << endl;

        file.close();
    }

    // Load Data
    void loadFile() {

        ifstream file("bank.txt");

        if (!file)
            return;

        getline(file, name);
        getline(file, accNo);

        file >> balance;

        file.ignore();

        getline(file, pin);

        file.close();
    }
};

// ========== Main Function ==========
int main() {

    srand(time(0));

    // Welcome Message
    cout << "======== Welcome to Banking System ========" << endl;

    BankAccount user;

    int choice;

    user.loadFile();

    // If no account exists
    if (user.name.empty()) {

        user.createAccount();

        user.saveFile();
    }

    while (true) {

        cout << "\n===== BANK MENU =====\n";

        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Balance\n";
        cout << "4. History\n";
        cout << "5. Exit\n";

        cout << "Choose: ";
        cin >> choice;

        // PIN Check
        if (choice >= 1 && choice <= 4) {

            if (!user.checkPin())
                continue;
        }

        switch (choice) {

        case 1:

            user.deposit();

            user.saveFile();

            break;

        case 2:

            user.withdraw();

            user.saveFile();

            break;

        case 3:

            user.showBalance();

            break;

        case 4:

            user.showHistory();

            break;

        case 5:

            cout << "\nThank You For Using Banking System!\n";

            return 0;

        default:

            cout << "Invalid Option!\n";
        }
    }
}