#pragma once
#include <iostream>
#include <list>




class IUser { // interfata useri
public:
	virtual std::string getNume() const = 0;

};

class User : public IUser{ // clasa abstracta
public:

private:

	const std::string username;
	const std::string parola;
	const std::string email;
	const std::string nr_telefon;
	const std::string cnp;
};


enum SPECIALITATE {
	cardiologie,
	oftalmologie
};

class Medic : public User {
public:
	Medic();
	std::string getNume() const;
private:
	SPECIALITATE specialitate;
	int numar_unic_identificare; // pentru a face distinctia intre medic si pacient
	std::list<Programare> programari; // tr
};


class Pacient : public User{
public:
	
	Pacient();
private:
	std::string getNume() const;
	std::list<Programare> programari; // trcute / viitoare
};


typedef struct Data {
	int zi, luna, an;
	std::string ora;
};


class Programare {
public:
	//selectezi in interfata specialitatea -> afiseaza medicii de la specialitatea respectiva in data care este selectata
	//selectezi data si afiseaza in functie de specialitatea si data aleasa medicii disponibili in acea data.
	//selectezi motivul prezentarii(consultatie initiala, de control, de control + eliberare reteta, etc)
	//
	//!!DUPA ce modifici la specialitate sau data se modifica automat ce iti afiseaza(probabil request) in functie de alegeri
	// 
	Programare(std:: string medic, Data data);

private:
	std::string motivul;
	SPECIALITATE specialitate;
	bool valida;
	Data data;
	Medic* medic;
	Pacient* pacient;
};



class Utils {
	// clasa pentru implementarea modificarilor ppe stringuri, date,..... and so on 
	// va avea functii statice
};

class IRequest {
public:
	virtual void gestionare_request() = 0;
	virtual int trimite_raspuns() = 0;
};

class RequestLogin : public IRequest {
public:
	RequestLogin();
private:
	// .... 
	void gestionare_request();
};

class RequestRegister : public IRequest {
public:
	// ...
private:

};

class RequestSpecialitate : public IRequest {
public: 
	// ...
private:

};

// ... 







