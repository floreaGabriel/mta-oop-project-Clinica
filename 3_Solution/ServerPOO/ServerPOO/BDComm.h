#pragma once

#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

class BDComm
{
private:
    SQLHANDLE sqlConnHandle;
    SQLHANDLE sqlStmtHandle;
    SQLHANDLE sqlEnvHandle;
    SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
public:
    BDComm();
    void CreateConnection();
    void CloseConnection();
    const char* GetQuery(SQLWCHAR* query, int& len);
    ~BDComm();
};

