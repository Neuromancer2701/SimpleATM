# SimpleATM

This program uses two libraries: Sqlite3 which can be installed via Apt  
and Fmt library which is a submodule in lib.
this can be build via (mkdir build; cd build; cmake ..) and installed with sudo make install.

The current path to the database and data.sqlite data file is hardcoded to  
/opt/repos/SimpleATM/db/  so update this to the appropriate location when checking out the repository.


To build this project from commandline:
mkdir build  
cd build  
cmake ..  

This should build the library and the test executable.
running the ./tests should produce the following results:

User Test:  
User 123456 is Valid.  
User 13 is Invalid.  
Pin Test:  
User 123456 pin is Valid.  
User 13 pin is Invalid.  
User Accounts Test:  
User 456 has 4 accounts.  
6  
7  
8  
9  
User Account Balance Test:  
User 456 has account: 6 Balance: 750000.  
User 456 has account: 73 Balance: InValid Account Number.  
Withdraw Test:  
User 456 has account: 6 Balance: 750000.  
User 456 has account: 6 Balance: Amount Not Available..  
User 456 has account: 6 Balance: 100.  
User 456 has account: 6 Balance: 100.  
Deposit Test:  
User 456 has account: 6 Balance: 200.  
User 456 has account: 6 Balance: 200.  
User 456 has account: 6 Balance: 10200.  
User 456 has account: 6 Balance: 10200.  



  
