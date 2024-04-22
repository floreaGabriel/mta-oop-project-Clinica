#include "DataBase.h"

DataBase* DataBase::m_instance = nullptr;

DataBase::DataBase() {
    sqlConnHandle = NULL;
    sqlStmtHandle = NULL;
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
        disconnect();
    if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        disconnect();
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
        disconnect();
    cout << "Attempting connection to SQL Server...";
    cout << "\n";
}

DataBase::~DataBase() {
    disconnect();
}


bool DataBase::connect(/*const std::string& server, const std::string& user, const std::string& password*/) {
    // Conectare la bază de date
    /*SQLWCHAR serverName[256], userName[256], passWord[256];
    strcpy((char*)serverName, server.c_str());
    strcpy((char*)userName, user.c_str());
    strcpy((char*)passWord, password.c_str());

    if (SQLConnect(hDbc, serverName, SQL_NTS, userName, SQL_NTS, passWord, SQL_NTS) != SQL_SUCCESS)
        return false;

    return true;*/
    
    

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
        disconnect();
    case SQL_ERROR:
        cout << "Could not connect to SQL Server";
        cout << "\n";
        disconnect();
    default:
        break;
    }
    //if there is a problem connecting then exit application
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
    {
        disconnect();
        return false;
    }

    return true;
}

void DataBase::disconnect() {
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    SQLDisconnect(sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
}

bool DataBase::executeQuery(const std::string& query) {
    //SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    //return SQLExecDirect(hStmt, (SQLWCHAR*)query.c_str(), SQL_NTS) == SQL_SUCCESS;
    SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle);

    // Verificarea dacă s-a făcut cu succes alocarea unui handle pentru instrucțiunea SQL
    if (sqlStmtHandle == SQL_NULL_HSTMT) {
        std::cerr << "Error: Failed to allocate statement handle\n";
        return false;
    }

    // Executarea instrucțiunii SQL
    SQLRETURN ret = SQLExecDirectW(sqlStmtHandle, (SQLWCHAR*)query.c_str(), SQL_NTS);

    // Verificarea rezultatului execuției instrucțiunii SQL
    if (ret != SQL_SUCCESS) {
        // Afișarea erorii
        SQLWCHAR sqlstate[6];
        SQLWCHAR message[SQL_MAX_MESSAGE_LENGTH];
        SQLINTEGER native_error;
        SQLSMALLINT message_length;

        SQLGetDiagRec(SQL_HANDLE_STMT, sqlStmtHandle, 1, sqlstate, &native_error, message, sizeof(message), &message_length);
        std::cerr << "Error: SQLExecDirect failed (" << ret << "): " << message << std::endl;

        // Eliberarea handle-ului de instrucțiune SQL
        SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);

        return false;
    }

    // Eliberarea handle-ului de instrucțiune SQL
    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);

    return true;
}

std::vector<std::vector<std::string>> DataBase::select(const std::string& query) {
    std::vector<std::vector<std::string>> result;

    if (executeQuery(query)) {
        // Procesare rezultate
        while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
            std::vector<std::string> row;
            SQLCHAR data[256];

            for (int i = 1; ; ++i) {
                SQLGetData(sqlStmtHandle, i, SQL_CHAR, data, sizeof(data), NULL);
                if (SQL_SUCCEEDED(SQLFetch(sqlStmtHandle))) {
                    row.push_back((char*)data);
                }
                else {
                    break;
                }
            }

            result.push_back(row);
        }
    }

    SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
    return result; // functia imi returneaza query-ul pe care i l am dat eu ca parametru si mi l pune in result
}