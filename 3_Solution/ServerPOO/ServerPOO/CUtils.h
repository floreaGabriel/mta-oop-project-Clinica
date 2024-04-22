#pragma once
#include <iostream>
#include <vector>

class CUtils
{
public:
	static std::vector<std::string> getData() { return m_data; }
	static std::vector<std::string> understandData(std::string, char);

private:
	static std::vector<std::string> m_data;

};

