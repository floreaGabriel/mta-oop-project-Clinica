#define _CRT_SECURE_NO_WARNINGS
#include "BDComm.h"
#include <iostream>
#include <cstring>

#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

using namespace std;

BDComm::BDComm()
{
    return;
}

void BDComm::CreateConnection()
{
    sqlConnHandle = NULL;
    sqlStmtHandle = NULL;
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
        CloseConnection();
    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        CloseConnection();
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
        CloseConnection();
    cout << "Attempting connection to SQL Server...";
    cout << "\n";
    //connect to SQL Server  
    //I am using a trusted connection and port 14808
    //it does not matter if you are using default or named instance
    //just make sure you define the server name and the port
    //You have the option to use a username/password instead of a trusted connection
    //but is more secure to use a trusted connection
    switch (SQLDriverConnect(sqlConnHandle, NULL, (SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 55555;DATABASE=LoginAccounts;Trusted=true;",
        SQL_NTS, retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT)) {
    case SQL_SUCCESS:
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;
    case SQL_SUCCESS_WITH_INFO:
        cout << "Successfully connected to SQL Server";
        cout << "\n";
        break;
    case SQL_INVALID_HANDLE:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        CloseConnection();
    case SQL_ERROR:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        CloseConnection();
    default:
        break;
    }
    //if there is a problem connecting then exit application
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
        CloseConnection();
    //output
    //cout << "\n";
    //cout << "Executing T-SQL query...";
    //cout << "\n";
    //if there is a problem executing the query then exit application
    //else display query result
    //if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT FirstName from Students", SQL_NTS)) {
    //    cout << "Error querying SQL Server";
    //    cout << "\n";
    //    CloseConnection();
    //}
    //else {
    //    //declare output variable and pointer
    //    SQLCHAR sqlVersion[SQL_RESULT_LEN];
    //    SQLLEN ptrSqlVersion;
    //    while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
    //        SQLGetData(sqlStmtHandle, 1, SQL_CHAR, sqlVersion, SQL_RESULT_LEN, &ptrSqlVersion);
    //        //display query result
    //        cout << "\nQuery Result:\n\n";
    //        cout << sqlVersion << endl;
    //    }
    //}
}

void BDComm::CloseConnection()
{
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    SQLDisconnect(sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}

const char* BDComm::GetQuery(SQLWCHAR* query, int& len)
{
    if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM Accounts", SQL_NTS)) {
        cout << "Error querying SQL Server";
        cout << "\n";
        CloseConnection();
        return nullptr; // Întoarce nullptr în caz de eroare
    }
    else {
        SQLCHAR sqlVersion[SQL_RESULT_LEN];
        std::string buffer;
        SQLLEN ptrSqlVersion;
        while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
            SQLGetData(sqlStmtHandle, 1, SQL_CHAR, sqlVersion, SQL_RESULT_LEN, &ptrSqlVersion);
            strcat((char*)buffer.c_str(), reinterpret_cast<const char*>(sqlVersion));
        }
    }
}

BDComm::~BDComm()
{
    CloseConnection();
}
