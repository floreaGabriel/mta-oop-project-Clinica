#include "IRequest.h"
#include "CUtils.h"
#include "RequestRegNormalUser.h"
#include "RequestDoctorUser.h"
#include "RequestLoginNormalUser.h"
#include "RequestLoginDoctor.h"
#include "RequestProgramare.h"
#include "Exception.h"

IRequest* IRequest::Factory::requestSelector(std::string data)
{
	int magicByte = stoi(CUtils::understandData(data, '#')[0]);

	switch (magicByte)
	{
	case 0:
		// 0#username#nume#prenume#email#parola#telefon#CNP
		return new RequestRegNormalUser(data);
	case 1:
		// 1#username#nume#prenume#email#parola#telefon#CNP#specializare
		return new RequestDoctorUser(data);
	case 2: 
		// 2#useranme#parola
		return new RequestLoginNormalUser(data);
	case 3:
		// 3#username#paraola
		return new RequestLoginDoctor(data);
	case 4: 
		// primesc -> 4#specializare#data(20/03/2004)
		// trimit -> 4#numeDoctor#prenumeDoctor#15_campuri_pentru_ore(0 unde e null si 1 unde e programat)
		return new RequestProgramare(data);
	
		
	// case 5:
		//5#CNP_Doctor#CNP_Pacient#data(20/03/2004)#ora(09:30-10:00)#motiv -> 
		// LA FINAL : #numePacient#prenumePacient sau #username
		//putem sa punem asta in casuta din ProgramDoctori in loc sa scrie PROGRAMAT sa scrie numele
		//sau username ceva ca trebuie sa stie cine are programare atunci, imi spui cand te intorci
		//mileanu :3
	default:
		throw Exception("Nu s-a putut selecta un Request din datele trimise de client!\n", 11);
	}
}
