#include "Application.h"


int main(int argc, char argv[])
{

	Application::getInstance().getServer()->start(12345);


	return 0;
}

//
//
//int TCPServer::sendImage(const char* imageName)
//{
//    FILE* file;
//    if (n % 2 == 0)
//        file = fopen("C:\\Users\\George\\Desktop\\Proiect POO\\OPP-Project\\3_Solution\\sigla.png", "rb");
//    else
//        file = fopen("C:\\Users\\George\\Desktop\\download.png", "rb");
//    n++;
//    if (!file) {
//        throw "Eroare la deschidere fisier";
//    }
//    fseek(file, 0, SEEK_END);
//    int imgDim = ftell(file);
//    fseek(file, 0, SEEK_SET);
//    char imgDimChar[50];
//    _itoa(imgDim, imgDimChar, 10);
//    int sentBytes = send(imgDimChar, strlen(imgDimChar));
//    char accBuffer[50];
//    int nrOfBytes = recv(accBuffer, 50);
//    uint8_t* buffer = (uint8_t*)malloc(40960 * sizeof(uint8_t));
//    int bytesRemained = imgDim;
//    int bytesthatHasBeenSent = 0;
//    for (int i = 1; i <= (imgDim / 40960) + 1; i++)
//    {
//        if (bytesRemained < 40960)
//        {
//            fread(buffer, 1, bytesRemained, file);
//            sentBytes = send((const char*)buffer, bytesRemained);
//            bytesthatHasBeenSent -= sentBytes;
//        }
//        else
//        {
//            fread(buffer, 1, 40960, file);
//            sentBytes = send((const char*)buffer, 40960);
//            bytesthatHasBeenSent -= sentBytes;
//        }
//        bytesRemained -= 40960;
//        std::cout << sentBytes << std::endl;
//        nrOfBytes = recv(accBuffer, 50);
//        memset(buffer, 40960, 0);
//    }
//    fclose(file);
//    std::cout << bytesthatHasBeenSent;
//}
