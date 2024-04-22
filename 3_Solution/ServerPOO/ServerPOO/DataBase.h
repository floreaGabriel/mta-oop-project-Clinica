#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include <vector>

using namespace std;

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

	bool connect(/*const std::string& server, const std::string& user, const std::string& password*/);
	void disconnect();
	bool executeQuery(const std::string& query);
	std::vector<std::vector<std::string>> select(const std::string& query);

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
