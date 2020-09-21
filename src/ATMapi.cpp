#include "ATMapi.h"
#include <fmt/format.h>

using fmt::format;  // wanted to use C++20 but format is not available yet in g++ just went with the lib that it is based off of.


string accountError = "InValid Account Number";
bool BankAPI::ValidUser(int userId)
{
    string query = format("SELECT * FROM PIN WHERE userid={};",userId);
    auto results = db.query(query);
    if(!results.empty())
    {
        for(auto&[key, value]:results[0])  //something odd going on this the compiler accessing map values so I just brute forced it.
        {
            if(!value.empty() && stoi(value) == userId)
            {
                return  true;
            }
        }
    }

    return false;
}

bool BankAPI::ValidPin(int userId, int Pin)
{
    string query = format("SELECT * FROM PIN WHERE userid={};",userId);
    auto results = db.query(query);
    if(!results.empty())
    {
        for(auto&[key, value]:results[0])  //something odd going on this the compiler accessing map values so I just brute forced it.
        {
            if(!value.empty() && stoi(value) == Pin)
            {
                return  true;
            }
        }
    }

    return false;
}

vector<string> BankAPI::UserAccounts(int userId)
{
    string query = format("SELECT accountId FROM ACCOUNTS WHERE userid={};",userId);
    vector<string> accounts;
    auto results = db.query(query);
    if(!results.empty())
    {
        for(const auto& result:results)
        {
            for(auto&[key, value]:result)
            {
                accounts.emplace_back(value);
            }
        }
    }

    return accounts;
}

string BankAPI::AccountBalance(int accountID)
{
    string query = format("SELECT money FROM BALANCE WHERE accountId={};",accountID);
    vector<string> accounts;
    auto results = db.query(query);
    if(!results.empty())
    {
        for(auto&[key, value]:results[0])
        {
            if(!value.empty())
            {
                return value;
            }
        }
    }

    return accountError;
}

string BankAPI::WithdrawBalance(int accountID, unsigned int amount)
{
    string balance = AccountBalance(accountID);

    if(balance != accountError)
    {
        auto money = stoi(balance);  ///  This could be replaced with a hard cap  e.g. 300$ daily limit.
        if( money > amount)
        {
            UpdateBalance(accountID, money - amount);
            return format("{}",money - amount);
        }
        return "Amount Not Available.";
    }

    return accountError;
}

string BankAPI::DepositBalance(int accountID, unsigned int amount)
{
    string balance = AccountBalance(accountID);

    if(balance != accountError)
    {
        auto money = stoi(balance);
        UpdateBalance(accountID, money + amount);
        return format("{}",money + amount);
    }

    return accountError;
}

void BankAPI::UpdateBalance(int accountID, unsigned int amount)
{
    string query = format("Update BALANCE set money={} WHERE accountId={};",amount, accountID);
    if(db.update(query) < 0)
    {
        //error log failed to update
    }
}

