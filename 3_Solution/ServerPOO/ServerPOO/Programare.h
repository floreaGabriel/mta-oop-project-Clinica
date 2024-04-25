#pragma once

#include <iostream>


// 4#NumePacient#PrenumePacient#CNPPacient#NumeDoctor#CNPDoctor#Telefon#Email#Specialitate#Data#Ora#Motiv

class Programare
{
private: 
	std::string m_CNP_Doctor;
	std::string m_numeDoctor;
	std::string m_prenumeDoctor;
	std::string m_numePacient;
	std::string m_prenumePacient;
	std::string m_CNP_Pacient;
	std::string m_telefon;
	std::string m_email;
	std::string m_specialitate;
	std::string m_data;
	std::string m_ora;
	std::string m_motiv;

public:
	Programare() {
		m_CNP_Doctor = nullptr;
		m_CNP_Doctor = nullptr;
		m_numeDoctor = nullptr;
		m_numePacient = nullptr;
		m_prenumePacient = nullptr;
		m_CNP_Pacient = nullptr;
		m_telefon = nullptr;
		m_email = nullptr;
		m_specialitate = nullptr;
		m_data = nullptr;
		m_ora = nullptr;
		m_motiv = nullptr;
	};
	
	~Programare() {}

	void afisareDetalii() const;

	std::string PrenumeDoctor() { return m_numePacient; }
	std::string NumePacient() { return m_numePacient; }
	std::string NumeDoctor() { return m_numeDoctor; }
	std::string CNPDoctor() { return m_CNP_Doctor; }
	std::string CNPPacient() { return m_CNP_Pacient; }
	std::string PrenumePacient() { return m_prenumePacient; }
	std::string Telefon() { return m_telefon; }
	std::string Email() { return m_email; }
	std::string Specialitate() { return m_specialitate; }
	std::string Data() { return m_data; }
	std::string Ora() { return m_ora; }
	std::string Motiv() { return m_motiv; }

};

class Builder {
public:
	Builder& setNumePacient(const std::string& nume) {
		m_programare.NumePacient() = nume;
		return *this;
	}

	Builder& setPrenumePacient(const std::string& prenume) {
		m_programare.PrenumePacient() = prenume;
		return *this;
	}

	Builder& setNumeDoctor(const std::string& nume) {
		m_programare.NumeDoctor() = nume;
		return *this;
	}

	Builder& setCNPPacient(const std::string& cnp) {
		m_programare.CNPPacient() = cnp;
		return *this;
	}

	Builder& setCNPDoctor(const std::string& cnp) {
		m_programare.CNPDoctor() = cnp;
		return *this;
	}

	Builder& setTelefon(const std::string& telefon) {
		m_programare.Telefon() = telefon;
		return *this;
	}

	Builder& setData(const std::string& newData) {
		m_programare.Data() = newData;
		return *this;
	}

	Builder& setOra(const std::string& newOra) {
		m_programare.Ora() = newOra;
		return *this;
	}

	Builder& setSpecialitate(const std::string& specialitate) {
		m_programare.Specialitate() = specialitate;
		return *this;
	}

	Builder& setEmail(const std::string& email) {
		m_programare.Email() = email;
		return *this;
	}

	Programare build() const {
		return m_programare;
	}

private:
	Programare m_programare;
};
