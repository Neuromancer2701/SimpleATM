
#include "ATMapi.h"
#include <fmt/format.h>
#include <iostream>
#include <cstdlib>
#include "database.h"   // user for making sure the database is setup correctly.

using fmt::format;  // wanted to use C++20 but format is not available yet in g++ just went with the lib that it is based off of.
using std::cout;
using std::for_each;\
using std::system;

int main()
{
    database db;
    auto DB_PATH = db.getPathName();
    auto command = format("rm {}",DB_PATH);
    if(system(command.c_str()) < 0)
    {
        cout << "Failed to clear old database\n";
    }

    command = format("sqlite3 {} < {}",DB_PATH,db.getPath()+"data.sqlite");
    if(system(command.c_str()) < 0)
    {
        cout << "Failed to load new database.\n";
    }

    BankAPI api;

    cout << "\nUser Test:\n";
    int validuser   = 123456;  // matches data in db
    int invaliduser = 13;      // not in db
    auto isValiduser   = api.ValidUser(validuser);
    auto isInvaliduser = api.ValidUser(invaliduser);

    string formatUser("User {} is {}.\n");
    cout << format(formatUser, validuser, isValiduser ? "Valid" : "Invalid");
    cout << format(formatUser, invaliduser, isInvaliduser ? "Valid" : "Invalid");


    cout << "\nPin Test:\n";
    int validpin   = 1234;
    int invalidpin = 999999;
    auto isValidpin   = api.ValidPin(validuser,  validpin);
    auto isInvalidpin = api.ValidPin(invaliduser,invalidpin);

    string formatPin("User {} pin is {}.\n");
    cout << format(formatPin, validuser, isValidpin ? "Valid" : "Invalid");
    cout << format(formatPin, invaliduser, isInvalidpin ? "Valid" : "Invalid");

    cout << "\nUser Accounts Test:\n";
    int user = 456;  // has 4 accounts
    auto accounts = api.UserAccounts(user);

    string formatAccounts("User {} has {} accounts.\n");
    cout << format(formatAccounts, user, accounts.size());
    for_each(begin(accounts), end(accounts),[&](auto account){cout << account << "\n";});


    cout << "\nUser Account Balance Test:\n";

    string formatAccountBalance("User {} has account: {} Balance: {}.\n");
    auto firstAccount = stoi(accounts[0]);
    cout << format(formatAccountBalance, user, firstAccount, api.AccountBalance(firstAccount));
    cout << format(formatAccountBalance, user, 73, api.AccountBalance(73));


    cout << "\nWithdraw Test:\n";
    cout << format(formatAccountBalance, user, firstAccount, api.AccountBalance(firstAccount));

    auto toomuch   = stoi(api.AccountBalance(firstAccount)) + 100;
    auto validWith = stoi(api.AccountBalance(firstAccount)) - 100;

    cout << format(formatAccountBalance, user, firstAccount, api.WithdrawBalance(firstAccount,toomuch));
    cout << format(formatAccountBalance, user, firstAccount, api.WithdrawBalance(firstAccount,validWith));
    cout << format(formatAccountBalance, user, firstAccount, api.AccountBalance(firstAccount));

    cout << "\nDeposit Test:\n";
    cout << format(formatAccountBalance, user, firstAccount, api.DepositBalance(firstAccount,100));
    cout << format(formatAccountBalance, user, firstAccount, api.AccountBalance(firstAccount));

    cout << format(formatAccountBalance, user, firstAccount, api.DepositBalance(firstAccount,10000));
    cout << format(formatAccountBalance, user, firstAccount, api.AccountBalance(firstAccount));

    return 0;
}
