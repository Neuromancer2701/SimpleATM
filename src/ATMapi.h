#ifndef SIMPLE_ATM_LIBRARY_H
#define SIMPLE_ATM_LIBRARY_H

#include <vector>
#include <string>
#include "database.h"

using std::string;
using std::vector;

class BankAPI
{
public:
    bool ValidUser(int userId);             //  See if this User ID is valid  result from card reader should be tested  with this function
    bool ValidPin(int userId, int Pin);     //  pass validated User ID and user input pin number

    vector<string> UserAccounts(int userId);  // returns a list a account numbers for specified user
    string AccountBalance(int accountID);     // returns the current balance of account

    // additional functions could be added for calculating number of 20s, 10s, or 5s in a specific  withdrawal
    // Current cap on withdrawal is the account balance but an addition function could be added to add a daily cap e.g. 300$
    string WithdrawBalance(int accountID, unsigned amount);  // user can only withdraw positive amount. will return error if amount not available returns new balance
    string DepositBalance(int accountID, unsigned amount);   // user can only add positive amount, returns new balance

private:
    database db;
    void UpdateBalance(int accountID, unsigned amount);
};


#endif //SIMPLE_ATM_LIBRARY_H
