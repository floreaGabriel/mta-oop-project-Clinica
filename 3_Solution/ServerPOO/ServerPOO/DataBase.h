#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include <vector>

using namespace std;

#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000

class DataBase
{
public:

	static DataBase& getInstance()
	{
		if (m_instance == nullptr)
			m_instance = new DataBase();
		return *m_instance;
	}

	bool connect();
	void disconnect();
	bool executeQuery(const wstring& query);
	std::vector<std::wstring> selectQuery(const std::wstring& query);

	SQLHANDLE getSTMT() { return sqlStmtHandle; }
	SQLHANDLE getconn() { return sqlConnHandle; }
	SQLHANDLE getEnv() { return sqlEnvHandle; }
private:


	DataBase();
	~DataBase();
	DataBase(const DataBase&) = delete;
	DataBase(DataBase&&) = delete;
	DataBase& operator = (const DataBase&) = delete;
	DataBase&& operator = (DataBase&&) = delete;

	static DataBase* m_instance;

	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
};
