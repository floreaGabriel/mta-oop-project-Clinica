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


std::string extractNumePrenumeCnp(std::string specializare, std::string data, int id)
{

    std::string string_cautare = "SELECT d.Nume, d.Prenume, d.CNP FROM ProgramDoctori pd INNER JOIN Doctors d ON pd.IDDoctor = d.ID WHERE d.Specializare = '" + specializare + "' AND pd.Data = '" + data + "' AND pd.IDDoctor = " + to_string(id);

    std::vector<std::vector<std::wstring>> select_result =
        DataBase::getInstance().selectQuery2(
            std::wstring(string_cautare.begin(), string_cautare.end())
        );

    std::string de_trimis;

    // Verifică dacă există cel puțin un rând în rezultatele selectate
    if (select_result.empty()) { throw Exception("Nu exista niciun rand in tabela selectata!\n", 104); }
    // Verifică dacă primul rând conține cel puțin un element
    if (select_result[0].empty()) { throw Exception("Primul rand din tabela selectat nu contine niciun cuvant!\n", 104); }
    // Iterează prin elementele primului rând și construiește șirul de trimis
    for (const auto& it : select_result[0])
    {
        de_trimis += std::string(it.begin(), it.end());
        de_trimis += "#";
    }
            
        

    return de_trimis;
    
}

void RequestProgramare::manage_request()
{

    std::string string_cautare = "SELECT pd.* FROM ProgramDoctori pd INNER JOIN Doctors d on pd.IDDoctor = d.ID where d.Specializare = '"+m_specializare+"' and pd.Data = '"+m_data+"'";

    std::vector<std::vector<std::wstring>> select_result =
        DataBase::getInstance().selectQuery2(
        std::wstring(string_cautare.begin(), string_cautare.end())
        );

    if (select_result.empty()) { 
        throw Exception("Query-ul de SELECT de la programare nu a selectat nimic!\n", 104); 
    
    }
    // de continuat de trimis raspuns milea si de adaugat error handling!!!
    // 4#nume#prenume#cnp#......ore
    for (const auto& row : select_result)
    {
        std::string date = extractNumePrenumeCnp(m_specializare, m_data, atoi(std::string(row[0].begin(), row[0].end()).c_str()));
        std::string creare_raspuns = "4#" + date;
        int i = 0;
        for (auto it = row.begin() ; it != row.end(); ++it)
        {
            if (i == 0 || i == 1) { i++; continue; } // sa imi sara peste primul element
            creare_raspuns += std::string(it->begin(),it->end());
            if(std::next(it) != row.end())
                creare_raspuns += "#";
        }
        m_to_send.push_back(creare_raspuns);
    }

    if (!m_to_send.empty())
    {
        m_answear = (char*)malloc(2 * sizeof(char));
        memcpy(m_answear, "4", 2);
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
