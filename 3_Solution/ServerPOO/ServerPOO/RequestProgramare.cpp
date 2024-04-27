#include "RequestProgramare.h"
#include "CUtils.h"
#include "DataBase.h"
#include "Exception.h"

#include <iostream>


RequestProgramare::RequestProgramare(std::string data)
{
    std::vector<std::string> splitted_data = CUtils::understandData(data, '#');
    this->m_specializare = splitted_data[1];
    this->m_data = splitted_data[2]; // 20/03/2004 
}




void RequestProgramare::manage_request()
{

    std::string string_cautare = "SELECT d.Nume, d.Prenume, d.CNP,  p.IntervalOrar FROM Doctors d LEFT JOIN Programari p ON d.ID = p.IDDoctor AND p.Data = '"+ m_data +"' WHERE d.Specializare = '"+ m_specializare +"'; ";

    std::vector<std::vector<std::wstring>> select_result =
        DataBase::getInstance().selectQuery2(
        std::wstring(string_cautare.begin(), string_cautare.end())
        );

    if (select_result.empty()) { 
        throw Exception("Query-ul de SELECT de la programare nu a selectat nimic!\n", 104); 
    
    }
    // de continuat de trimis raspuns milea si de adaugat error handling!!!
    // 4#nume#prenume#cnp#......ore
    m_to_send = CUtils::selectDataForProgramari(select_result, m_specializare, m_data);

    if (!m_to_send.empty())
    {
        std::string buffer_final = "4$";
        auto it = m_to_send.begin();
        auto end = m_to_send.end();
        for (it; it != end - 1; ++it)
        {
            buffer_final += *it;
            buffer_final += "$";
        }
        buffer_final += *it;
        m_answear = (char*)malloc((buffer_final.size() + 1) * sizeof(char));
        memcpy(m_answear, buffer_final.c_str(), buffer_final.size() + 1);
    }
    else
    {
        m_answear = (char*)malloc(4 * sizeof(char));
        memcpy(m_answear, "NOK", 4);
    }
    // std::cout << "S-au gasit " << select_result.size() << " doctori disponibili!\n";
    
}

char* RequestProgramare::manage_answear()
{
    return m_answear;
}
