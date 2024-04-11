//#pragma once
//
//#include <iostream>
//#include <sql.h>
//#include <sqlext.h>
//#include <sqltypes.h>
//#include <windows.h>
//
//#define SQL_RESULT_LEN 240
//#define SQL_RETURN_CODE_LEN 1000
//
//class DataBase
//{
//private:
//    SQLHANDLE sqlConnHandle;
//    SQLHANDLE sqlStmtHandle;
//    SQLHANDLE sqlEnvHandle;
//    SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
//public:
//    DataBase();
//    void CreateConnection();
//    void CloseConnection();
//    const char* GetQuery(SQLWCHAR* query, int& len);
//    ~DataBase();
//};