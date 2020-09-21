#if !defined (DATABASE_H)
#define DATABASE_H

#include <sqlite3.h>
#include <string>
#include <mutex>
#include <memory>
#include <vector>
#include <map>

using std::mutex;
using std::string;
using std::shared_ptr;
using std::vector;
using std::map;


class database
{
public:
    database();

    vector<map<string, string> > query(string query);
    int update(string query);

    virtual ~database();

    string getPath(){return path;}
    string getPathName(){return path+name;}

private:
    string path;
    string name;
    mutex  dbMutex;

    static int vectorMapCallback(void *callbackParameter, int columns, char* columnText[], char* columnName[]);


};


#endif