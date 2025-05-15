#pragma once
#include "mysql/jdbc.h"
#include "DataBaseConnection.h"
#include "Arinc429.h"

class DataBaseConnection {
public:
	DataBaseConnection();

	~DataBaseConnection();

	int InsertArinc429Data(std::map<std::string, Arinc429>& data);

	int TempInsert(std::map<std::string, Arinc429>& data, int target, bool mark);

private:
	sql::mysql::MySQL_Driver* driver;
	sql::Connection* con;
	sql::Statement* statement;
};