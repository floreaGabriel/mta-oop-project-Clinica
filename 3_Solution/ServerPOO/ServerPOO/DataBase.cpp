#include "DataBase.h"

DataBase* DataBase::m_instance = nullptr;

DataBase::DataBase() {}

DataBase::~DataBase() {
    disconnect();
}



bool DataBase::connect()
{
    // Allocate environment handle
    if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle) != SQL_SUCCESS)
    {
        cerr << "Error allocating environment handle" << endl;
        return -1;
    }

    // Set the ODBC version environment attribute
    if (SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0) != SQL_SUCCESS)
    {
        cerr << "Error setting the ODBC version environment attribute" << endl;
        SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
        return -1;
    }

    // Allocate connection handle
    if (SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle) != SQL_SUCCESS)
    {
        cerr << "Error allocating connection handle" << endl;
        SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
        return -1;
    }

    // Connection string
    SQLWCHAR connectionStr[] = L"DRIVER={SQL SERVER};SERVER=localhost, 55555;DATABASE=LoginAccounts;Trusted_Connection=Yes;";
    // Connect to SQL Server
    std::cout << "waiting..\n";

    switch (SQLDriverConnect(sqlConnHandle, NULL, connectionStr, SQL_NTS, retconstring, SQL_RETURN_CODE_LEN, NULL, SQL_DRIVER_NOPROMPT))
    {
    case SQL_SUCCESS_WITH_INFO:
        break;
    case SQL_INVALID_HANDLE:
    case SQL_ERROR:
        cerr << "Error connecting to SQL Server" << endl;
        SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
        return -1;
    default:
        break;
    }
    std::cout << "Done waiting..\n";


}


bool DataBase::executeQuery(const std::wstring& query)
{
    // Allocate statement handle
    if (SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle) != SQL_SUCCESS)
    {
        cerr << "Error allocating statement handle" << endl;
        SQLDisconnect(sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
        return 0;
    }



    //// Define variables for the values to be inserted
    //string value1;
    //int value2;

    //cout << "Introdu valori: "; cin >> value1 >> value2;


    // Bind parameter values to the prepared statement
    //SQLWCHAR* sqlQuery = (SQLWCHAR*)L"INSERT INTO tabela (mere,pere) VALUES (?, ?)";
    SQLWCHAR* sqlQuery = (SQLWCHAR*)query.c_str();

    if (SQLPrepare(sqlStmtHandle, sqlQuery, SQL_NTS) != SQL_SUCCESS)
    {
        cerr << "Error preparing SQL statement" << endl;
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
        SQLDisconnect(sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
        return 0;
    }

    //// Bind parameter values to the prepared statement
    //if (SQLBindParameter(sqlStmtHandle, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, value1.length(), 0, (SQLPOINTER)value1.c_str(), 0, NULL) != SQL_SUCCESS ||
    //    SQLBindParameter(sqlStmtHandle, 2, SQL_PARAM_INPUT, SQL_C_LONG, SQL_INTEGER, 0, 0, &value2, 0, NULL) != SQL_SUCCESS)
    //{
    //    cerr << "Error binding parameter values" << endl;
    //    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    //    SQLDisconnect(sqlConnHandle);
    //    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    //    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
    //    return 0;
    //}

    if (SQLExecDirect(sqlStmtHandle, sqlQuery, SQL_NTS) != SQL_SUCCESS)
    {
        cerr << "Error executing SQL query" << endl;
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
        SQLDisconnect(sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
        SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
        return 0;
    }



    cout << "Values inserted successfully" << endl;

    return 1;

}


std::vector<std::wstring> DataBase::selectQuery(const std::wstring& query) {
   
    std::vector<std::wstring> results; // Vector pentru a stoca rezultatele
    
    // Verificați dacă există deja un handle de instrucțiune alocat
    if (SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle) != SQL_SUCCESS) {
        std::cerr << "Error allocating statement handle" << std::endl;
        return results;
    }

    // Convertiți interogarea într-un șir de caractere SQLWCHAR
    SQLWCHAR* sqlQuery = (SQLWCHAR*)query.c_str();

    // Executați interogarea SELECT
    if (SQLExecDirect(sqlStmtHandle, sqlQuery, SQL_NTS) != SQL_SUCCESS) {
        std::cerr << "Error executing SQL query" << std::endl;
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
        return results;
    }

    // Declarați o variabilă pentru a stoca rezultatul interogării SELECT
    SQLWCHAR result[1024];
    SQLLEN resultLen = 0;

    // Iterați prin toate rândurile obținute din interogare
    while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
        // Acest exemplu presupune că datele întoarse sunt în coloana 1
        SQLGetData(sqlStmtHandle, 1, SQL_C_WCHAR, result, sizeof(result), &resultLen);

        // Adăugați rezultatul la vectorul de rezultate
        results.push_back(std::wstring(result));
    }

    // Eliberați handle-ul de instrucțiune
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);

    // Returnați rezultatul sub formă de șir de caractere wide
    return results;
}



void DataBase::disconnect()
{
    // Free statement handle
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);

    // Disconnect from SQL Server
    SQLDisconnect(sqlConnHandle);

    // Free connection handle
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);

    // Free environment handle
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);

}