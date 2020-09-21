
#include "database.h"
#include <string>
#include <sqlite3.h>
using std::lock_guard;

database::database():path("/opt/repos/SimpleATM/db/"),name("bank") // default database located int src tree
{

}

database::~database()
{

}

vector<map<string, string> > database::query(string query)
{
    vector<map<string, string> >  data;

    lock_guard<mutex>  guard(dbMutex);  // protect from multiple threads call this functions

    sqlite3* tempdb;
    if( sqlite3_open(getPathName().c_str(),&tempdb) != SQLITE_OK)
    {
        return data;  //failed to open database
    }

    char* errorMessage = nullptr;
    int returnCode = sqlite3_exec(tempdb, query.c_str(),database::vectorMapCallback,static_cast<void*>(&data), &errorMessage);
    if (returnCode != SQLITE_OK)
    {
        if(errorMessage)
        {
            //log error message
        }
        else
        {
            //log different failure
        }
    }
    sqlite3_close(tempdb);

    return data;
}

int database::vectorMapCallback(void *callbackParameter, int columns, char *columnText[], char *columnName[])
{
    vector<map<string, string> > *ptr;
    map<string, string> temp;

    ptr =  (vector<map<string, string> >*) callbackParameter;

    for(int i = 0; i < columns; ++i)
    {
        if(columnText[i] && columnName[i])
            temp[columnName[i]] = columnText[i];
    }

    if(!temp.empty())
    {
        ptr->emplace_back(move(temp));
    }

    return 0;
}

int database::update(string query)
{
    lock_guard<mutex>  guard(dbMutex);  // protect from multiple threads call this functions

    sqlite3* tempdb;
    if( sqlite3_open(getPathName().c_str(),&tempdb) != SQLITE_OK)
    {
        return -1;  //failed to open database
    }

    int returnCode = sqlite3_exec(tempdb, query.c_str(), nullptr, nullptr, nullptr);
    if (returnCode != SQLITE_OK)
    {
        return -1;
    }
    sqlite3_close(tempdb);

    return 0;
}
