#ifndef CUTILS_H
#define CUTILS_H

#include <iostream>
#include <vector>


class CUtils
{
private:
    static std::vector<std::string> m_data;


public:
    CUtils();
    static std::vector<std::string> getData() { return m_data; }
    static std::vector<std::string> understandData(std::string, char);
};

#endif // CUTILS_H
