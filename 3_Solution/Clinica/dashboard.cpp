#include "dashboard.h"
#include "ui_dashboard.h"
#include <QThread>

#include"clientconnection.h"


dashBoard::dashBoard(QWidget *parent,IUser* usser)
    : QDialog(parent)
    , ui(new Ui::dashBoard) , client_pacient(usser) , pagina_shop(1)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/alexm/Desktop/poo proiect/oop proiect clinica/poze/sigla-transparenta.png");
    ui->lblpageHomePoza->setPixmap(pix.scaled(300,300,Qt::KeepAspectRatio));
    QPixmap pixprog("C:/Users/alexm/Desktop/poo proiect/oop proiect clinica/poze/screenprog.png");
    ui->lblpageHomePoza_programare->setPixmap(pixprog.scaled(300,300,Qt::KeepAspectRatio));
    QPixmap pixshop("C:/Users/alexm/Desktop/poo proiect/oop proiect clinica/poze/screenshop.png");
    ui->lblpageHomePoza_Shop->setPixmap(pixshop.scaled(300,300,Qt::KeepAspectRatio));
    QPixmap pixafectiuni("C:/Users/alexm/Desktop/poo proiect/oop proiect clinica/poze/screenafectiuni.png");
    ui->lblpageHomePoza_Afectiuni->setPixmap(pixafectiuni.scaled(300,300,Qt::KeepAspectRatio));


    this->ui->StackedWidgetAplicatie->setCurrentWidget(this->ui->pageHome);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(myFunction_timer()));


    ui->dataProgramare->setDisplayFormat("dd/MM/yyyy");
    ui->btnSearchDoctori->setIcon(QIcon("C:/Users/alexm/Desktop/poo proiect/oop proiect clinica/poze/search-alb.png"));
    ui->btnSearchAfectiune->setIcon(QIcon("C:/Users/alexm/Desktop/poo proiect/oop proiect clinica/poze/search-alb.png"));

    ui->comboSpecializare->addItem("Oftalmolog");
    ui->comboSpecializare->addItem("Dentist");
    ui->comboSpecializare->addItem("Cardiolog");
    ui->comboSpecializare->addItem("Hematolog");
    ui->comboSpecializare->addItem("Pediatru");
    ui->comboSpecializare->addItem("Psihiatru");
    ui->comboSpecializare->addItem("Ginecolog");

    ui->comboMotiv->addItem("Consultatie initiala.");
    ui->comboMotiv->addItem("Consultatie de control.");
    ui->comboMotiv->addItem("Consultatie de control + Eliberare reteta.");


    if(this->client_pacient == dynamic_cast<Doctor*>(client_pacient))
    {
        //este un doctor
        removeButtonAndResize(this->ui->btnSchedule);
    }

    setFixedSize(size());
}

dashBoard::~dashBoard()
{
    delete ui;
}


void dashBoard::removeButtonAndResize(QPushButton* buttonToRemove)
{
    QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(ui->horizontalLayout);

    if (!layout) {
        qWarning("Layout not found!");
        return;
    }

    // Remove the button from the layout
    layout->removeWidget(buttonToRemove);
    buttonToRemove->setParent(nullptr);
    buttonToRemove->hide();

    int remainingButtons = layout->count();
    int newWidth = 1000 / remainingButtons;

    for (int i = 0; i < remainingButtons; ++i) {
        QWidget* widget = layout->itemAt(i)->widget();
        if (QPushButton* button = qobject_cast<QPushButton*>(widget)) {
            button->setFixedSize(newWidth, 50);
        }
    }
}


void delayFunction() {
    qDebug() << "Începe întârzierea...";
    QThread::msleep(3000);
    qDebug() << "Sfârșitul întârzierii.";
}



void dashBoard::reset_layout_programari() {
    // Verifică dacă widget-ul pageProgramari are un layout setat
    QLayout *layout = ui->pageProgramari->layout();
    if (layout) {
        // Șterge toate widget-urile din layout-ul actual al pageProgramari
        QLayoutItem* child;
        while ((child = layout->takeAt(0)) != nullptr) {
            // Șterge widget-ul din layout
            delete child->widget();
            // Șterge item-ul din layout
            delete child;
        }
        // Eliberează memoria ocupată de layout
        delete layout;
        // Setează layout-ul pageProgramari la nullptr pentru a evita referințele nule
        ui->pageProgramari->setLayout(nullptr);
    }
}



void dashBoard::on_btnHome_clicked()
{
    //home
    this->ui->StackedWidgetAplicatie->currentWidget()->close();

    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageHome);
    this->ui->pageHome->show();
}


void dashBoard::on_btnSchedule_clicked()
{
    //schedule
    reset_layout_programari();

    this->ui->StackedWidgetAplicatie->currentWidget()->close();

    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageSchedule);
    this->ui->pageSchedule->show();
}



void dashBoard::on_btnShop_2_clicked()
{
    //search afectiuni
    this->ui->StackedWidgetAplicatie->currentWidget()->close();

    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageSearch);
    this->ui->pageSearch->show();
    this->ui->lineEditTextSearchAfectiune->clear();
    reset_layout_afectiuni();
}


void dashBoard::on_btnAcoount_clicked()
{
    //account
    this->ui->StackedWidgetAplicatie->currentWidget()->close();
    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageAccount);
    this->ui->pageAccount->show();
}





//--------------------------------------------------------------------------------------------------------
//SCHEDULE:




QString convert_nulls_to_interval(int nr)
{
    switch (nr) {
    case 0:
        return "08:30-09:00";
    case 1:
        return "09:00-09:30";
    case 2:
        return "09:30-10:00";
    case 3:
        return "10:00-10:30";
    case 4:
        return "10:30-11:00";
    case 5:
        return "11:00-11:30";
    case 6:
        return "11:30-12:00";
    case 7:
        return "12:00-12:30";
    case 8:
        return "12:30-13:00";
    case 9:
        return "13:00-13:30";
    case 10:
        return "15:00-15:30";
    case 11:
        return "15:30-16:00";
    case 12:
        return "16:00-16:30";
    case 13:
        return "16:30-17:00";
    case 14:
        return "17:00-17:30";
    case 15:
        return "17:30-18:00";
    default:
        return "";
    }
}


int convert_hour_to_pozition(std::string hour)
{
    if(hour=="08:30-09:00")
        return 0;
    if(hour=="09:00-09:30")
        return 1;
    if(hour=="09:30-10:00")
        return 2;
    if(hour=="10:00-10:30")
        return 3;
    if(hour=="10:30-11:00")
        return 4;
    if(hour=="11:00-11:30")
        return 5;
    if(hour=="11:30-12:00")
        return 6;
    if(hour=="12:00-12:30")
        return 7;
    if(hour=="12:30-13:00")
        return 8;
    if(hour=="13:00-13:30")
        return 9;
    if(hour=="15:00-15:30")
        return 10;
    if(hour=="15:30-16:00")
        return 11;
    if(hour=="16:00-16:30")
        return 12;
    if(hour=="16:30-17:00")
        return 13;
    if(hour=="17:00-17:30")
        return 14;
    if(hour=="17:30-18:00")
        return 15;

    return 1001;

    // Tratează cazul în care nr nu se potrivește cu niciunul dintre cazurile de mai sus
}


bool dashBoard::exista_doctor_in_vector(std::string nume,std::string prenume,std::string CNP)
{
    for (size_t i = 0; i < disp_prog_vect.size(); ++i) {
        Disponibilitate_Programari* ptr = disp_prog_vect[i];
        if(ptr->getNume()==nume && ptr->getPrenume()==prenume && ptr->getCNP()==CNP)
            return true;
        //free(ptr);
    }
    return false;
}


void dashBoard::modify_hour_doctor(std::string nume,std::string prenume,std::string CNP,std::string hour)
{
    for (size_t i = 0; i < disp_prog_vect.size(); ++i) {
        Disponibilitate_Programari* ptr = disp_prog_vect[i];

        if(ptr->getNume()==nume && ptr->getPrenume()==prenume && ptr->getCNP()==CNP)
        {
            ptr->setIntervalOcupat(convert_hour_to_pozition(hour));
            return;
        }
        //free(ptr);
    }
}


void dashBoard::creaza_vector_disp_prog(char* tot_stringul){

        std::vector<std::string> splitted_data_dolar = CUtils::understandData(tot_stringul, '$');


        // Verificăm dacă există cel puțin două elemente în vector
        if (splitted_data_dolar.size() >= 2) {
            // Obținem iteratorul către al doilea element
            auto it = splitted_data_dolar.begin() + 1;

            // Parcurgem vectorul începând de la al doilea element
            for (; it != splitted_data_dolar.end(); ++it) {
                // Utilizați *it pentru a accesa fiecare element
                std::string& element = *it;
                std::vector<std::string> splitted_data_diez = CUtils::understandData(element, '#');
                if(exista_doctor_in_vector(splitted_data_diez[0],splitted_data_diez[1],splitted_data_diez[2])==true)
                {
                    //doctorul exista si modific ora respectiva ca fiind programata
                    modify_hour_doctor(splitted_data_diez[0],splitted_data_diez[1],splitted_data_diez[2],splitted_data_diez[3]);
                }else {
                    //creez doctorul respectiv si ii adaug si ora
                    Disponibilitate_Programari* disp_prog = new Disponibilitate_Programari(splitted_data_diez[0],splitted_data_diez[1],splitted_data_diez[2]);
                    this->disp_prog_vect.push_back(disp_prog);
                    if(splitted_data_diez[3]!="NULL")
                        modify_hour_doctor(splitted_data_diez[0],splitted_data_diez[1],splitted_data_diez[2],splitted_data_diez[3]);
                }
            }
        }
}


void dashBoard::ButtonOraProgramareClicked()
{
        QByteArray byteNumePac = (QString::fromStdString(this->client_pacient->getNume())).toUtf8();
        QByteArray bytePrenumePac = (QString::fromStdString(this->client_pacient->getPrenume())).toUtf8();
        QByteArray byteCNPPac = (QString::fromStdString(this->client_pacient->getCNP())).toUtf8();

        QPushButton *button = qobject_cast<QPushButton*>(sender());
        QByteArray byteNumeDoctor = (button->property("NumeDoctor").toString()).toUtf8();
        QByteArray bytePrenumeDoctor =( button->property("PrenumeDoctor").toString()).toUtf8();
        QByteArray byteCNPDoctor = (button->property("CNPDoctor").toString()).toUtf8();

        QByteArray byteData = (this->ui->dataProgramare->text()).toUtf8();
        QByteArray byteOra = (button->text()).toUtf8();
        QByteArray byteMotiv = (this->ui->comboMotiv->currentText()).toUtf8();

        const char* dataNumePac = byteNumePac.constData();
        const char* dataPrenumePac = bytePrenumePac.constData();
        const char* dataCNPPac = byteCNPPac.constData();
        const char* dataNumeDoctor = byteNumeDoctor.constData();
        const char* dataPrenumeDoctor = bytePrenumeDoctor.constData();
        const char* dataCNPDoctor = byteCNPDoctor.constData();
        const char* dataData = byteData.constData();
        const char* dataOra = byteOra.constData();
        const char* dataMotiv = byteMotiv.constData();

        char* buffer;
        buffer = (char*)malloc(10 + sizeof(dataCNPPac)+sizeof(dataCNPDoctor)+
                                 sizeof(dataData)+sizeof(dataOra)+sizeof(dataMotiv));
        // buffer = (char*)malloc(10 + sizeof(dataNumePac)+sizeof(dataPrenumePac)+sizeof(dataCNPPac)+
        //                          sizeof(dataNumeDoctor)+sizeof(dataPrenumeDoctor)+sizeof(dataCNPDoctor)+
        //                          sizeof(dataData)+sizeof(dataOra)+sizeof(dataMotiv));
        strcpy(buffer,"5#");
        strcat(buffer,dataCNPPac);
        strcat(buffer,"#");
        strcat(buffer,dataCNPDoctor);
        strcat(buffer,"#");
        strcat(buffer,dataData);
        strcat(buffer,"#");
        strcat(buffer,dataOra);
        strcat(buffer,"#");
        strcat(buffer,dataMotiv);

        if (ClientConnection::getInstance().sendData(buffer)) {
            // Message sent successfully
            qDebug() << "Message sent: " << buffer;
            // insertCreds()
        }
        //free(buffer);

        char responseBuffer[1024];
        if(ClientConnection::getInstance().receiveData(responseBuffer, sizeof(responseBuffer)))
        {
            qDebug() << "Mesaj primit: " << responseBuffer;
            if (strcmp(responseBuffer, "OK") == 0) {
                // Handle successful response from server
                qDebug() << "ok\n";

            }
            else if (strcmp(responseBuffer, "NOK") == 0) {
                // Handle error response from server
                qDebug() << "NOK\n";
            }
        } else {
            // Handle receive error
        }
        on_btnSchedule_clicked();
}


void dashBoard::print_widget_programari()
{
    // Creează un layout grid
    QGridLayout *layout = new QGridLayout(this->ui->pageProgramari);

    // Setează alinierea layout-ului pe partea de sus
    layout->setAlignment(Qt::AlignTop);

    // Iterează prin fiecare obiect Disponibilitate_Programari din vector
    for (int i = 0; i < disp_prog_vect.size(); ++i) {
        Disponibilitate_Programari* disp_prog = disp_prog_vect[i];

        // Creează label-urile pentru nume și prenume
        QLabel *numeLabel = new QLabel(QString::fromStdString(disp_prog->getNume()), this);
        QLabel *prenumeLabel = new QLabel(QString::fromStdString(disp_prog->getPrenume()), this);

        // Adaugă label-urile în layout
        layout->addWidget(numeLabel, i * 3, 0); // Afișează numele pe o linie nouă pentru fiecare obiect
        layout->addWidget(prenumeLabel, i * 3, 1); // Afișează prenumele pe aceeași linie cu numele

        // Iterează prin fiecare interval orar și creează butoane pentru fiecare
        std::vector<std::string> intervale = disp_prog->getIntervale_Vect();
        int row = i * 3 + 1; // Prima linie disponibilă pentru butoane
        int col = 0; // Coloana în care se adaugă butoanele
        for (int j = 0; j < intervale.size(); ++j) {
            if(intervale[j]=="NULL")
            {
                QPushButton *button = new QPushButton(convert_nulls_to_interval(j), this);
                button->setMinimumSize(45, 30); // Setează dimensiunea minimă a butonului
                layout->addWidget(button, row, col); // Adaugă butonul la poziția corespunzătoare

                button->setProperty("NumeDoctor", numeLabel->text());
                button->setProperty("PrenumeDoctor", prenumeLabel->text());
                button->setProperty("CNPDoctor",QString::fromStdString(disp_prog->getCNP()));

                connect(button, &QPushButton::clicked, this, &dashBoard::ButtonOraProgramareClicked);

                // Verifică dacă trebuie să trecem la următoarea linie
                if ((col+1) % 8 == 0) {
                    row++; // Trecem la următoarea linie
                    col = 0; // Resetăm coloana la începutul liniei
                } else {
                    col++; // Trecem la următoarea coloană
                }
            }
        }
    }

    // Setează layout-ul pe widget-ul pageProgramari
    this->ui->pageProgramari->setLayout(layout);

    for (auto& disp_prog : disp_prog_vect) {
        delete disp_prog; // Dezalocă memoria pentru obiect
    }
    disp_prog_vect.clear();
}


void dashBoard::on_btnSearchDoctori_clicked()
{
        reset_layout_programari();

        QString specializare,data;
        specializare = this->ui->comboSpecializare->currentText();
        data = this->ui->dataProgramare->text();

        QByteArray byteSpecializare = specializare.toUtf8();
        QByteArray byteData = data.toUtf8();

        const char* dataSpecializare = byteSpecializare.constData();
        const char* dataData = byteData.constData();

        char* buff = (char*) malloc(5 + sizeof(dataData) + sizeof(dataSpecializare));

        strcpy(buff,"4");
        strcat(buff,"#");
        strcat(buff,dataSpecializare);
        strcat(buff,"#");
        strcat(buff,dataData);


        if (ClientConnection::getInstance().sendData(buff)) {
            // Message sent successfully
            qDebug() << "Message sent: " << buff;
            // insertCreds()
        }

        //std::string responseBuffer;
        char responseBuffer[10000];
        if(ClientConnection::getInstance().receiveData(responseBuffer, sizeof(responseBuffer)))
        {
            qDebug() << "Mesaj primit: " << responseBuffer;
            if (strcmp(responseBuffer,"NOK")==0) {
                qDebug() << "nu exista\n";
            }
            else if(responseBuffer[0]=='4')
            {
                // Procesează mesajul de disponibilitate a programărilor
                this->creaza_vector_disp_prog(responseBuffer);
                this->print_widget_programari();
            }
            else {
                // Handle other types of messages from server
            }
        } else {
            // Handle receive error
        }
}


//--------------------------------------------------------------------------------------------------------
//SHOP:

void dashBoard::reset_layout_shop() {
    // Verifică dacă widget-ul pageProgramari are un layout setat
    QLayout *layout = ui->pageShopMedicamente->layout();
    if (layout) {
        // Șterge toate widget-urile din layout-ul actual al pageProgramari
        QLayoutItem* child;
        while ((child = layout->takeAt(0)) != nullptr) {
            // Șterge widget-ul din layout
            delete child->widget();
            // Șterge item-ul din layout
            delete child;
        }
        // Eliberează memoria ocupată de layout
        delete layout;
        // Setează layout-ul pageProgramari la nullptr pentru a evita referințele nule
        ui->pageShopMedicamente->setLayout(nullptr);
    }
}



void dashBoard::on_btnBackToShopFromMedicament_clicked()
{
    this->ui->btnBack->show();
    this->ui->pushButton_2->show();
    if(previous_page==22) //vine din shop;
    {
        this->ui->StackedWidgetMedicamente->currentWidget()->close();
        this->ui->StackedWidgetMedicamente->setCurrentWidget(ui->pageShopMedicamente);
    } else if(previous_page==23) //vine din afectiune
    {
        //this->ui->StackedWidgetMedicamente->close();
        this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageAfectiune);

    }
}


uint8_t* dashBoard::primire_poza(int &NrOfBytes){
    uint8_t* poza;
    NrOfBytes = 0;

    char dim_poza[50];
    if (ClientConnection::getInstance().receiveData(dim_poza, sizeof(dim_poza))) {
        std::vector<std::string> splitted_response = CUtils::understandData(dim_poza, '#');
        //dimensiunea pozei
        NrOfBytes = std::stoi(splitted_response[1]);

        // Allocați memoria pentru poza
        poza = (uint8_t*)malloc(NrOfBytes);
        memset(poza, 0, NrOfBytes);

        // Primirea pozei de la server în bucăți
        int bytesPrimiti = 0;
        while (bytesPrimiti < NrOfBytes) {
            ClientConnection::getInstance().sendData("ACCEPT");
            int bytesDePrimit = std::min(40960, NrOfBytes - bytesPrimiti);
            if (ClientConnection::getInstance().receiveData((char*)(poza + bytesPrimiti), bytesDePrimit)) {
                bytesPrimiti += bytesDePrimit;
            } else {
                // Handle receive error
                break;
            }
        }
    }
    return poza;
}

void dashBoard::ButtonInformatiiMedicament(const std::string& numeMedicament)
{
    //this->ui->lblNumeMedicament->setText(QString::fromStdString(numeMedicament));
    char* buffer = (char*)malloc(sizeof(numeMedicament)+2);
    strcpy(buffer,"8#");
    strcat(buffer,numeMedicament.c_str());

    if (ClientConnection::getInstance().sendData(buffer)) {
        // Message sent successfully
        qDebug() << "Message sent: " << buffer;
    }

    char responseBuffer[500];
    if (ClientConnection::getInstance().receiveData(responseBuffer, sizeof(responseBuffer)))
    {

        qDebug() << "Mesaj primit: " << responseBuffer;
        std::vector<std::string> splitted_response = CUtils::understandData(responseBuffer, '#');

        this->ui->lblNumeMedicament->setText(QString::fromStdString(splitted_response[1]));
        this->ui->lblProviderMedicament->setText(QString::fromStdString(splitted_response[2]));
        this->ui->lblInformatiiMedicament->setText(QString::fromStdString(splitted_response[3]));
        this->ui->lblPretMedicament->setText(QString::fromStdString(splitted_response[4]));
        this->ui->lblPrescriptie->setText(QString::fromStdString(splitted_response[5]));
        this->ui->lblStoc->setText(QString::fromStdString(splitted_response[6]));

        char* buffer_to_send = (char*)malloc(sizeof(numeMedicament) + 3);
        strcpy(buffer_to_send, "7#");
        strcat(buffer_to_send, numeMedicament.c_str());
        ClientConnection::getInstance().sendData(buffer_to_send);


        int NrOfBytes = 0;
        uint8_t* poza=primire_poza(NrOfBytes);

        QPixmap buttonIcon = QPixmap("C:/Users/alexm/Desktop/poo proiect/oop proiect clinica/poze/add-shop.png").scaled(this->ui->btnAddShopMedicament->size(), Qt::KeepAspectRatio);
        this->ui->btnAddShopMedicament->setIcon(buttonIcon);
        this->ui->btnAddShopMedicament->setIconSize(buttonIcon.size());


        QImage image;
        image.loadFromData(poza, NrOfBytes);
        QPixmap pix = QPixmap::fromImage(image);
        ui->pozaMedicament->setPixmap(pix.scaled(450,300,Qt::KeepAspectRatio));

        Medicament_shop* medicament_shop = findMedicamentByName(numeMedicament);
        if (medicament_shop == nullptr)
        {
            medicament_shop = new Medicament_shop(numeMedicament,splitted_response[4],pix);
        }
        connect(this->ui->btnAddShopMedicament, &QPushButton::clicked, this, std::bind(&dashBoard::ButtonAddCosMedicament, this, medicament_shop));
    }



    this->ui->StackedWidgetMedicamente->currentWidget()->close();
    this->ui->btnBack->hide();
    this->ui->pushButton_2->hide();
    this->previous_page=22;
    this->ui->StackedWidgetMedicamente->setCurrentWidget(ui->pageMedicament);
}


void dashBoard::ButtonAddCosMedicament(Medicament_shop* medicament)
{
    this->CosCumparaturi[medicament]++;
    qDebug() << this->CosCumparaturi[medicament]<<"\n";
}


Medicament_shop* dashBoard::findMedicamentByName(const std::string& name)
{
    for (const auto& pair : this->CosCumparaturi) {
        Medicament_shop* medicament = pair.first;
        if (medicament->returnNume() == name) {
            return medicament;
        }
    }
    return nullptr; // Returnează nullptr dacă medicamentul nu este găsit
}

void dashBoard::Actualizare_shop(){
    char pagina[3];
    itoa(this->pagina_shop,pagina,10);
    char* buff;
    buff = (char*)malloc(sizeof(char) * 4);
    strcpy(buff, "6#");
    strcat(buff,pagina);


    if (ClientConnection::getInstance().sendData(buff)) {
        // Message sent successfully
        qDebug() << "Message sent: " << buff;
    }

    char responseBuffer[500];
    if (ClientConnection::getInstance().receiveData(responseBuffer, sizeof(responseBuffer))) {
        qDebug() << "Mesaj primit: " << responseBuffer;
        if (strcmp(responseBuffer, "NOK") == 0) {
            qDebug() << "nu exista\n";
        } else if (responseBuffer[0] == '6') {
            QGridLayout* mainLayout = new QGridLayout(ui->pageShopMedicamente);
            mainLayout->setSpacing(5); // Setează spațiul între widget-uri în layout
            int row = 0;
            int col = 0;

            // Folosește funcția understandData din CUtils pentru a separa șirul responseBuffer în funcție de caracterul '$'
            std::vector<std::string> splitted_response = CUtils::understandData(responseBuffer, '$');

            if (splitted_response.size() >= 2) {
                // Obținem un iterator către al doilea element din vector
                auto it = std::next(splitted_response.begin(), 1);

                //QPixmap buttonIcon("C:/Users/alexm/Desktop/poo proiect/oop proiect clinica/poze/add-shop.jpg");

                // Parcurgem vectorul de la al doilea element
                for (; it != splitted_response.end(); ++it) {
                    const std::string& medicament = *it;
                    // Folosește funcția understandData din CUtils pentru a separa informațiile despre medicament în funcție de caracterul '#'
                    std::vector<std::string> info_medicament = CUtils::understandData(medicament, '#');

                    // Extrage informațiile despre medicament (nume, preț, poză)
                    std::string numeMedicament = info_medicament[0];
                    std::string pretMedicament = info_medicament[1];

                    // Trimiterea numelii medicamentului la server pentru a obține poza
                    char* buffer_to_send = (char*)malloc(sizeof(numeMedicament) + 3);
                    strcpy(buffer_to_send, "7#");
                    strcat(buffer_to_send, numeMedicament.c_str());
                    ClientConnection::getInstance().sendData(buffer_to_send);

                    // Recepționarea pozei de la server

                    int NrOfBytes = 0;
                    uint8_t* poza = primire_poza(NrOfBytes);

                    // Creează un widget pentru medicament
                    //QWidget* widgetMedicament = new QWidget();
                    //QVBoxLayout* layout = new QVBoxLayout(widgetMedicament);

                    // Creează un chenar pentru a încadra poza și prețul medicamentului
                    QFrame* frame = new QFrame();
                    frame->setFrameShape(QFrame::Box);
                    frame->setLineWidth(2);
                    QVBoxLayout* frameLayout = new QVBoxLayout(frame);

                    // Adaugă poza medicamentului în chenar
                    QImage image;
                    image.loadFromData(poza, NrOfBytes);

                    QLabel* labelPoza = new QLabel();
                    QPixmap pix = QPixmap::fromImage(image);
                    labelPoza->setPixmap(pix.scaled(300,220));
                    //QPixmap pixmap = QPixmap::fromImage(image).scaled(100, 100, Qt::KeepAspectRatio);
                    frameLayout->addWidget(labelPoza);

                    // Creează un widget pentru numele medicamentului
                    QLabel* labelNume = new QLabel(QString::fromUtf8(numeMedicament.c_str()));
                    labelNume->setAlignment(Qt::AlignCenter);
                    labelNume->setFont(QFont("Arial", 12, QFont::Bold)); // Setează fontul și dimensiunea textului pentru nume
                    frameLayout->addWidget(labelNume);


                    // Adaugă layout-ul pentru preț și buton în layout-ul orizontal
                    QHBoxLayout* horizontalLayout = new QHBoxLayout();


                    // Adaugă prețul medicamentului în stânga jos
                    QLabel* labelPret = new QLabel(QString::fromUtf8(pretMedicament.c_str()));
                    labelPret->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
                    labelPret->setFont(QFont("Arial", 12, QFont::Bold)); // Setează fontul și dimensiunea textului pentru preț
                    horizontalLayout->addWidget(labelPret);


                    QPushButton* buttonINF = new QPushButton();
                    buttonINF->setText("Informatii");
                    buttonINF->setFixedSize(70, 20); // Setează dimensiunea butonului
                    // Conectați semnalul clicked al butonului "Informatii" la slot-ul ButtonInformatiiMedicament()
                    connect(buttonINF, &QPushButton::clicked, this, std::bind(&dashBoard::ButtonInformatiiMedicament, this, numeMedicament));

                    horizontalLayout->addWidget(buttonINF, 0, Qt::AlignBottom | Qt::AlignCenter); // Adaugă butonul în layout-ul orizontal



                    // Creează butonul în colțul din dreapta jos
                    QPushButton* button = new QPushButton();
                    button->setFixedSize(70, 50); // Setează dimensiunea butonului
                    QPixmap buttonIcon = QPixmap("C:/Users/alexm/Desktop/poo proiect/oop proiect clinica/poze/add-shop.png").scaled(button->size(), Qt::KeepAspectRatio);
                    button->setIcon(buttonIcon);
                    button->setIconSize(buttonIcon.size());

                    Medicament_shop* medicament_shop = findMedicamentByName(numeMedicament);
                    if (medicament_shop == nullptr)
                    {
                        medicament_shop = new Medicament_shop(numeMedicament,pretMedicament,pix);
                    }
                    connect(button, &QPushButton::clicked, this, std::bind(&dashBoard::ButtonAddCosMedicament, this, medicament_shop));


                    horizontalLayout->addWidget(button, 0, Qt::AlignBottom | Qt::AlignRight); // Adaugă butonul în layout-ul orizontal


                    // Adaugă layout-ul orizontal în layout-ul vertical
                    frameLayout->addLayout(horizontalLayout);

                    // Adaugă chenarul pentru medicament în layout-ul principal
                    mainLayout->addWidget(frame, row, col);

                    col++;
                    if (col == 3) {
                        col = 0;
                        row++;
                    }
                }
            } else {
                qDebug() << "Vectorul splitted_response nu are suficiente elemente.";
            }

            // Setează layout-ul pe widget-ul pageShopMedicamente
            ui->pageShopMedicamente->setLayout(mainLayout);

        } else {
            // Handle other types of messages from server
        }
    } else {
        // Handle receive error
    }
}


void dashBoard::on_btnShop_clicked()
{
    // Shop
    this->ui->StackedWidgetAplicatie->currentWidget()->close();
    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageShop);
    this->ui->StackedWidgetMedicamente->setCurrentWidget(ui->pageShopMedicamente);
    this->ui->pageShop->show();
    this->reset_layout_shop();
    this->pagina_shop = 0;
    this->Actualizare_shop();
}



void dashBoard::on_btnBack_clicked()
{
    //navigare la stanga in shop
    if(this->pagina_shop>0)
    {
        this->pagina_shop--;
    }
    this->reset_layout_shop();
    this->Actualizare_shop();
}




void dashBoard::on_pushButton_2_clicked()
{
    //navigare la dreapta in shop
    this->pagina_shop++;
    this->reset_layout_shop();
    this->Actualizare_shop();;
}




//--------------------------------------------------------------------------------------------------------
//ACCOUNT:






void dashBoard::on_btnAccountDateCont_clicked()
{
    this->ui->lblaccountCNP->setText(QString::fromStdString(this->client_pacient->getCNP()));
    this->ui->lblaccountEmail->setText(QString::fromStdString(this->client_pacient->getEmail()));
    this->ui->lblaccountNrTelefon->setText(QString::fromStdString(this->client_pacient->getPhonenumber()));
    this->ui->lblaccountNume->setText(QString::fromStdString(this->client_pacient->getNume()));
    this->ui->lblaccountPrenume->setText(QString::fromStdString(this->client_pacient->getPrenume()));
    this->ui->lblaccountUsername->setText(QString::fromStdString(this->client_pacient->getUsername()));
    this->ui->lblaccountParola->setText(QString::fromStdString(this->client_pacient->getParola()));

    this->ui->lblaccountspecializareDoctor->setText(QString::fromStdString(this->client_pacient->getSpecializare()));

    if(this->client_pacient == dynamic_cast<Pacient*>(client_pacient))
    {
        //este un pacient
        this->ui->lblaccountPacientdoctor->setText("Pacient");
        this->ui->lblaccountspecializareDoctor->hide();
    } else
    {
        this->ui->lblaccountPacientdoctor->setText("Doctor");
        //this->ui->lblaccountspecializareDoctor->setText(QString::fromStdString(this->client_pacient->getSpecializare()));
        this->ui->lblaccountspecializareDoctor->show();
    }

    this->ui->StackedWidgetAplicatie->currentWidget()->close();
    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageAccountDateCont);
    this->ui->pageAccountDateCont->show();

}


void dashBoard::on_btnBackToShopFromMedicament_2_clicked()
{
    //buton back din DateCont
    this->ui->StackedWidgetAplicatie->currentWidget()->close();
    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageAccount);
    this->ui->pageAccount->show();
}


void dashBoard::on_btnAccountSchimbaParola_clicked()
{
    this->ui->labelEroareSchimbareParola->hide();
    this->ui->lineEditParolaVeche->clear();
    this->ui->lineEditParolaNoua1->clear();
    this->ui->lineEditParolaNoua2->clear();
    this->ui->StackedWidgetAplicatie->currentWidget()->close();
    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageAccountSchimbaParola);
    this->ui->pageAccountSchimbaParola->show();
}


void dashBoard::on_btnBackToShopFromMedicament_3_clicked()
{
    //buton back din Schimba Parola
    this->ui->StackedWidgetAplicatie->currentWidget()->close();
    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageAccount);
    this->ui->pageAccount->show();
}





void dashBoard::on_btnVeziParolaVeche_clicked()
{
    if(this->ui->btnVeziParolaVeche->text() == "⚠︎︎")
    {
        ui->lineEditParolaVeche->setEchoMode(QLineEdit::Password);
        this->ui->btnVeziParolaVeche->setText("👁");
    } else if(this->ui->btnVeziParolaVeche->text() == "👁")
    {
        ui->lineEditParolaVeche->setEchoMode(QLineEdit::Normal);
        this->ui->btnVeziParolaVeche->setText("⚠︎︎");
    }
}


void dashBoard::on_btnVeziParolaNoua1_clicked()
{
    if(this->ui->btnVeziParolaNoua1->text() == "⚠︎︎")
    {
        ui->lineEditParolaNoua1->setEchoMode(QLineEdit::Password);
        this->ui->btnVeziParolaNoua1->setText("👁");
    } else if(this->ui->btnVeziParolaNoua1->text() == "👁")
    {
        ui->lineEditParolaNoua1->setEchoMode(QLineEdit::Normal);
        this->ui->btnVeziParolaNoua1->setText("⚠︎︎");
    }
}


void dashBoard::on_btnVeziParolaNoua2_clicked()
{
    if(this->ui->btnVeziParolaNoua2->text() == "⚠︎︎")
    {
        ui->lineEditParolaNoua2->setEchoMode(QLineEdit::Password);
        this->ui->btnVeziParolaNoua2->setText("👁");
    } else if(this->ui->btnVeziParolaNoua2->text() == "👁")
    {
        ui->lineEditParolaNoua2->setEchoMode(QLineEdit::Normal);
        this->ui->btnVeziParolaNoua2->setText("⚠︎︎");
    }
}

void dashBoard::myFunction_timer() {
    // Ascunde eticheta
    this->ui->labelEroareSchimbareParola->hide();
}


void dashBoard::on_pushButton_clicked(){

}


void dashBoard::on_btnAccountSchimbaParola_2_clicked()
{
    if(this->ui->lineEditParolaVeche->text() != QString::fromStdString(this->client_pacient->getParola()))
    {
        this->ui->labelEroareSchimbareParola->setText("Parola veche nu este corecta.");
        this->ui->labelEroareSchimbareParola->show();
    } else if(this->ui->lineEditParolaNoua1->text() != this->ui->lineEditParolaNoua2->text())
    {
        this->ui->labelEroareSchimbareParola->setText("Parolele noi nu coincid.");
        this->ui->labelEroareSchimbareParola->show();
    } else if(this->ui->lineEditParolaNoua1->text().isEmpty() || this->ui->lineEditParolaNoua2->text().isEmpty())
    {
        this->ui->labelEroareSchimbareParola->setText("Casetele pentru parolele noi sunt goale.");
        this->ui->labelEroareSchimbareParola->show();
    }
    else {
        QByteArray byteParolaNoua = this->ui->lineEditParolaNoua1->text().toUtf8();
        const char* dataParolaNoua = byteParolaNoua.constData();
        QByteArray byteUsername= (QString::fromStdString(this->client_pacient->getUsername())).toUtf8();
        const char* dataUsername = byteUsername.constData();


        char* buffer= (char*)malloc(5+sizeof(dataParolaNoua)+
                                       sizeof(dataUsername));
        if(this->client_pacient = dynamic_cast<Pacient*>(client_pacient))
        {
            //este un pacient
            strcpy(buffer,"9#");
        } else
        {
            //este un doctor
            strcpy(buffer,"13#");
        }
        strcat(buffer,dataUsername);
        strcat(buffer,"#");
        strcat(buffer,dataParolaNoua);

        if (ClientConnection::getInstance().sendData(buffer)) {
            // Message sent successfully
            qDebug() << "Message sent: " << buffer;
            // insertCreds()
        }


        char responseBuffer[1024];
        if(ClientConnection::getInstance().receiveData(responseBuffer, sizeof(responseBuffer)))
        {
            qDebug() << "Mesaj primit: " << responseBuffer;
            if (strcmp(responseBuffer, "OK") == 0) {
                // Handle successful response from server
                qDebug() << "ok\n";
                this->client_pacient->setParola(this->ui->lineEditParolaNoua1->text().toStdString());
            }
            else if (strcmp(responseBuffer, "NOK") == 0) {
                // Handle error response from server
                qDebug() << "NOK\n";
            }
        } else {
            // Handle receive error

        }
    }
}

void dashBoard::setBackWindow(MainWindow* window){
    this->mainWindow=window;
}

void dashBoard::on_btnAccountLogOut_clicked()
{
    delete client_pacient;
    delete timer;
    this->close();
    this->mainWindow->show();
}



//--------------------------------------------------------------------------------------------
//Vezi programari din Account


void dashBoard::ButtonBifeazaProgramareClicked(QString tableIDProgramare) {
    //qDebug() <<"s-a apasat butonul de: "<<this->client_pacient->getNume()<<"\n";
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        // Verifică dacă este un Doctor
        if (dynamic_cast<Doctor*>(client_pacient)) {
            button->setStyleSheet("background-color: green; color: white; border: none;");


            QByteArray byteIDProgramare = tableIDProgramare.toUtf8();
            const char* dataIDProgramare = byteIDProgramare.constData();

            char* buffer = (char*)malloc(sizeof(dataIDProgramare)+4);


            strcpy(buffer,"14#");
            strcat(buffer,dataIDProgramare);

            if (ClientConnection::getInstance().sendData(buffer)) {
                // Message sent successfully
                qDebug() << "Message sent: " << buffer;
                // insertCreds()
            }

            char responseBuffer[4096];
            if(ClientConnection::getInstance().receiveData(responseBuffer, sizeof(responseBuffer)))
            {
                qDebug() << "Mesaj primit: " << responseBuffer;
                if (strcmp(responseBuffer, "OK") == 0)
                {
                    qDebug() << "Am primit ok\n";
                }
                else{
                    // Handle error response from server
                    qDebug() << "NOK\n";
                }
            } else {
                // Handle receive error
                qDebug() <<" eroare la primire mesaj ButtonBifeazaProgramareClicked.";
            }
        }
    }
}

void dashBoard::setupTableColumnsWidth(){
    //QString imagePath = "C:/Users/alexm/Desktop/poo proiect/oop proiect clinica/poze/background.png";
    //QString styleSheet = QString("background-image: url(%1); background-repeat: no-repeat; background-position: center;").arg(imagePath);
    //ui->pageVeziProgramari->setStyleSheet(styleSheet);

    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,65);
    ui->tableWidget->setColumnWidth(2,65);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,220);
    ui->tableWidget->setColumnWidth(5,90);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
}


void dashBoard::on_btnAccountVeziProgramari_clicked()
{
    ui->tableWidget->clearContents(); // Elimină conținutul celulelor
    ui->tableWidget->setRowCount(0); // Elimină toate rândurile din tabel

    QByteArray byteUsername = (QString::fromStdString(this->client_pacient->getUsername())).toUtf8();
    const char* dataUsername = byteUsername.constData();

    char* buffer = (char*)malloc(sizeof(dataUsername)+3);

    if(this->client_pacient == dynamic_cast<Pacient*>(client_pacient))
    {
        //este un pacient
        strcpy(buffer,"10#");
    } else
    {
        strcpy(buffer,"11#");
    }

    strcat(buffer,dataUsername);

    if (ClientConnection::getInstance().sendData(buffer)) {
        // Message sent successfully
        qDebug() << "Message sent: " << buffer;
        // insertCreds()
    }


    char responseBuffer[4096];
    if(ClientConnection::getInstance().receiveData(responseBuffer, sizeof(responseBuffer)))
    {
        qDebug() << "Mesaj primit: " << responseBuffer;
        std::vector<std::string> splitted_response = CUtils::understandData(responseBuffer, '$');
        if (splitted_response[0]=="10" || splitted_response[0]=="11")
        {
            // Handle successful response from server
            if(splitted_response.size()>=2)
            {
                auto it = std::next(splitted_response.begin(), 1);

                // Parcurgem vectorul de la al doilea element
                for (; it != splitted_response.end(); ++it)
                {
                    const std::string& programare = *it;
                    std::vector<std::string> splitted_programare = CUtils::understandData(programare,'#');

                    int row_tabela = ui->tableWidget->rowCount();
                    ui->tableWidget->insertRow(row_tabela);

                    QString tableIDProgramare = QString::fromStdString(splitted_programare[0]);
                    QString tableNume = QString::fromStdString(splitted_programare[1]);
                    QString tableData = QString::fromStdString(splitted_programare[2]);
                    QString tableOra = QString::fromStdString(splitted_programare[3]);
                    QString tableMotiv = QString::fromStdString(splitted_programare[4]);

                    QPushButton* buttonFinalizat = new QPushButton();
                    buttonFinalizat->setFixedSize(90, 28); // Setează dimensiunea butonului
                    //QPixmap buttonIcon;
                    if(splitted_programare[5]=="nu")
                        buttonFinalizat->setStyleSheet("background-color: red; color: white; border: none;");
                    else
                        buttonFinalizat->setStyleSheet("background-color: green; color: white; border: none;");
                    // buttonFinalizat->setIcon(buttonIcon);
                    // buttonFinalizat->setIconSize(buttonIcon.size());
                    connect(buttonFinalizat, &QPushButton::clicked, this, std::bind(&dashBoard::ButtonBifeazaProgramareClicked,this,tableIDProgramare));


                    ui->tableWidget->setItem(row_tabela,0,new QTableWidgetItem(tableIDProgramare));
                    ui->tableWidget->setItem(row_tabela,1,new QTableWidgetItem(tableNume));
                    ui->tableWidget->setItem(row_tabela,2,new QTableWidgetItem(tableData));
                    ui->tableWidget->setItem(row_tabela,3,new QTableWidgetItem(tableOra));
                    ui->tableWidget->setItem(row_tabela,4,new QTableWidgetItem(tableMotiv));
                    ui->tableWidget->setCellWidget(row_tabela,5,buttonFinalizat);


                }
                setupTableColumnsWidth();
                ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
            }else {
                qDebug() << "Vectorul splitted_response nu are suficiente elemente.";
            }

        }
        else{
            // Handle error response from server
            qDebug() << "NOK\n";
        }
    } else {
        // Handle receive error

    }


    this->ui->StackedWidgetAplicatie->currentWidget()->close();
    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageVeziProgramari);
    this->ui->pageVeziProgramari->show();
}










//--------------------------------------------------------------------------------------------------
//afectiune

void dashBoard::reset_layout_afectiuni() {
    // Verifică dacă widget-ul pageProgramari are un layout setat
    QLayout *layout = ui->scrollAreaWidgetAfectiuni->layout();
    if (layout) {
        // Șterge toate widget-urile din layout-ul actual al pageProgramari
        QLayoutItem* child;
        while ((child = layout->takeAt(0)) != nullptr) {
            // Șterge widget-ul din layout
            delete child->widget();
            // Șterge item-ul din layout
            delete child;
        }
        // Eliberează memoria ocupată de layout
        delete layout;
        // Setează layout-ul pageProgramari la nullptr pentru a evita referințele nule
        ui->scrollAreaWidgetAfectiuni->setLayout(nullptr);
    }
}



void dashBoard::handleInfoButtonClicked()
{
    qDebug() << "Message sent: a mers \n";
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QVariant variant = button->property("AfectiuneData");

    if (variant.canConvert<Afectiune*>()) {
        Afectiune* afectiune = variant.value<Afectiune*>();
        this->ui->lblNumeAfectiune->setText(QString::fromStdString(afectiune->getNume()));
        this->ui->TextEditCEESTE->setText("Ce este "+QString::fromStdString(afectiune->getNume())+":");
        this->ui->lblCeEsteAfectiune->setText(QString::fromStdString(afectiune->getCeEste()));
        this->ui->lblCauzeAfectiune->setText(QString::fromStdString(afectiune->getCauze()));
        this->ui->lblSimptomeAfectiune->setText(QString::fromStdString(afectiune->getSimptome()));
        this->ui->btnMedicamentRecomandatAfectiune->setText(QString::fromStdString(afectiune->getMedicamente()));
    }
    this->ui->StackedWidgetAplicatie->currentWidget()->close();
    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageAfectiune);
    this->ui->pageAfectiune->show();
}




void dashBoard::on_btnSearchAfectiune_clicked()
{
    reset_layout_afectiuni();

    QByteArray byteAfectiune = this->ui->lineEditTextSearchAfectiune->text().toUtf8();
    const char* dataAfectiune = byteAfectiune.constData();

    char* buffer = (char*)malloc(sizeof(dataAfectiune)+3);

    strcpy(buffer,"12#");
    strcat(buffer,dataAfectiune);

    if (ClientConnection::getInstance().sendData(buffer)) {
        // Message sent successfully
        qDebug() << "Message sent: " << buffer;
        // insertCreds()
    }

    char responseBuffer[4096];
    if(ClientConnection::getInstance().receiveData(responseBuffer, sizeof(responseBuffer)))
    {
        qDebug() << "Mesaj primit: " << responseBuffer;
        std::vector<std::string> splitted_response = CUtils::understandData(responseBuffer, '$');
        if (splitted_response[0]=="12")
        {
            QGridLayout* mainLayout = new QGridLayout(ui->scrollAreaWidgetAfectiuni);
            mainLayout->setSpacing(5); // Setează spațiul între widget-uri în layout
            int row = 0;
            int col = 0;

            // Handle successful response from server
            if(splitted_response.size()>=2)
            {
                auto it = std::next(splitted_response.begin(), 1);

                // Parcurgem vectorul de la al doilea element
                for (; it != splitted_response.end(); ++it) {
                    const std::string& aff = *it;
                    std::vector<std::string> splitted_afectiune = CUtils::understandData(aff, '#');

                    Afectiune* afectiune = new Afectiune(splitted_afectiune[0], splitted_afectiune[1], splitted_afectiune[2], splitted_afectiune[3], splitted_afectiune[4]);

                    // Creează un chenar pentru fiecare afecțiune
                    QFrame* frame = new QFrame();
                    frame->setFixedSize(300, 220);
                    frame->setStyleSheet("background-color: #f0f0f0; color: black; border: 2px solid #ccc; border-radius: 5px;");

                    // Creează un layout pentru chenar
                    QVBoxLayout* frameLayout = new QVBoxLayout(frame);

                    // Adaugă numele afecțiunii în partea de sus a chenarului
                    QLabel* nameLabel = new QLabel(QString::fromStdString(afectiune->getNume()));
                    nameLabel->setAlignment(Qt::AlignCenter);
                    nameLabel->setFont(QFont("Arial", 14, QFont::Bold));
                    frameLayout->addWidget(nameLabel);

                    // Adaugă textul din membrul CeEste sub numele afecțiunii
                    QLabel* ceEsteLabel = new QLabel(QString::fromStdString(afectiune->getCeEste()));
                    ceEsteLabel->setWordWrap(true); // Setează împachetarea cuvintelor
                    ceEsteLabel->setAlignment(Qt::AlignCenter); // Aliniază textul la centru
                    ceEsteLabel->setFont(QFont("Arial", 12, QFont::Bold));
                    ceEsteLabel->setMaximumWidth(500); // Limitează lățimea maximă a textului
                    QFontMetrics metrics(ceEsteLabel->font());
                    QString elidedText = metrics.elidedText(QString::fromStdString(afectiune->getCeEste()), Qt::ElideRight, ceEsteLabel->maximumWidth());
                    ceEsteLabel->setText(elidedText); // Setează textul tăiat la dimensiunea potrivită
                    frameLayout->addWidget(ceEsteLabel);

                    // Adaugă un buton "Informații" în partea de jos a chenarului
                    QPushButton* infoButton = new QPushButton("Informații");
                    QVariant variant;
                    variant.setValue(afectiune);
                    infoButton->setProperty("AfectiuneData", variant);
                    infoButton->setFixedSize(260, 45);
                    infoButton->setStyleSheet("background-color: #4CAF50; color: white; border: none; border-radius: 5px;");
                    frameLayout->addWidget(infoButton, 0, Qt::AlignCenter);

                    // Conectează semnalul clicked al butonului la slotul tău
                    connect(infoButton, &QPushButton::clicked, this, &dashBoard::handleInfoButtonClicked);

                    // Adaugă chenarul în layout-ul principal al scroll area
                    mainLayout->addWidget(frame, row, col);

                    // Incrementarea coloanei și rândului pentru a trece la următorul loc de afișare
                    col++;
                    if (col == 3) {
                        col = 0;
                        row++;
                    }
                }
            }
            else
            {
                qDebug() << "Vectorul splitted_response nu are suficiente elemente.";
            }
            ui->scrollAreaWidgetAfectiuni->setLayout(mainLayout);
        }
        else{
            // Handle error response from server
            qDebug() << "NOK\n";
        }
    } else {
        // Handle receive error

    }
}


void dashBoard::on_btnBackFromAfectiune_clicked()
{
    this->ui->StackedWidgetAplicatie->currentWidget()->close();
    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageSearch);
    this->ui->pageSearch->show();
}



void dashBoard::on_btnMedicamentRecomandatAfectiune_clicked()
{
    QByteArray byteNumeMedicament = (this->ui->btnMedicamentRecomandatAfectiune->text()).toUtf8();
    const char* dataNumeMedicament = byteNumeMedicament.constData();

    char* buffer = (char*)malloc(sizeof(dataNumeMedicament)+2);
    strcpy(buffer,"8#");
    strcat(buffer,dataNumeMedicament);

    if (ClientConnection::getInstance().sendData(buffer)) {
        // Message sent successfully
        qDebug() << "Message sent: " << buffer;
    }

    char responseBuffer[1000];
    if (ClientConnection::getInstance().receiveData(responseBuffer, sizeof(responseBuffer)))
    {

        qDebug() << "Mesaj primit: " << responseBuffer;
        std::vector<std::string> splitted_response = CUtils::understandData(responseBuffer, '#');

        this->ui->lblNumeMedicament->setText(QString::fromStdString(splitted_response[1]));
        this->ui->lblProviderMedicament->setText(QString::fromStdString(splitted_response[2]));
        this->ui->lblInformatiiMedicament->setText(QString::fromStdString(splitted_response[3]));
        this->ui->lblPretMedicament->setText(QString::fromStdString(splitted_response[4]));
        this->ui->lblPrescriptie->setText(QString::fromStdString(splitted_response[5]));
        this->ui->lblStoc->setText(QString::fromStdString(splitted_response[6]));

        char* buffer_to_send = (char*)malloc(sizeof(dataNumeMedicament) + 3);
        strcpy(buffer_to_send, "7#");
        strcat(buffer_to_send, dataNumeMedicament);
        ClientConnection::getInstance().sendData(buffer_to_send);


        int NrOfBytes = 0;
        uint8_t* poza=primire_poza(NrOfBytes);


        QImage image;
        image.loadFromData(poza, NrOfBytes);
        QPixmap pix = QPixmap::fromImage(image);
        ui->pozaMedicament->setPixmap(pix.scaled(450,300,Qt::KeepAspectRatio));
    }


    this->ui->StackedWidgetAplicatie->currentWidget()->close();
    this->ui->btnBack->hide();
    this->ui->pushButton_2->hide();
    this->previous_page=23;
    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageShop);
    this->ui->StackedWidgetMedicamente->setCurrentWidget(ui->pageMedicament);
}



//-----------------------------------------------------------------------------------------
//COS CUMPARATURI


void dashBoard::reset_layout_vezi_cos_cumparaturi() {
    // Verifică dacă widget-ul pageProgramari are un layout setat
    QLayout *layout = ui->scrollAreaCosCumparaturi->layout();
    if (layout) {
        // Șterge toate widget-urile din layout-ul actual al pageProgramari
        QLayoutItem* child;
        while ((child = layout->takeAt(0)) != nullptr) {
            // Șterge widget-ul din layout
            delete child->widget();
            // Șterge item-ul din layout
            delete child;
        }
        // Eliberează memoria ocupată de layout
        delete layout;
        // Setează layout-ul pageProgramari la nullptr pentru a evita referințele nule
        ui->scrollAreaCosCumparaturi->setLayout(nullptr);
    }
}


void dashBoard::on_btnAccountCosCumparaturi_clicked()
{
    reset_layout_vezi_cos_cumparaturi();

    QGridLayout* mainLayout = new QGridLayout(ui->scrollAreaCosCumparaturi);
    mainLayout->setSpacing(5); // Setează spațiul între widget-uri în layout
    int row = 0;
    int col = 0;

    //parcurg tot cosul de cumparaturi
    for (const auto& pair : this->CosCumparaturi) {
        Medicament_shop* medicament = pair.first;
        int cantitate = pair.second;

        // Creează un chenar pentru fiecare medicament
        QFrame* frame = new QFrame();
        frame->setFixedSize(300, 300);
        frame->setStyleSheet("background-color: #f0f0f0; color: black; border: 2px solid #ccc; border-radius: 5px;");

        // Creează un layout pentru chenar
        QVBoxLayout* frameLayout = new QVBoxLayout(frame);

        // QLabel* labelPoza= medicament->returnPoza();
        // frameLayout->addWidget(labelPoza);
        QLabel* labelPoza = new QLabel();
        labelPoza->setPixmap(medicament->returnPoza());
        labelPoza->setPixmap(medicament->returnPoza().scaled(300,300));
        frameLayout->addWidget(labelPoza);

        // Adaugă numele medicamentului în partea de sus a chenarului
        QLabel* numeMedicament = new QLabel(QString::fromStdString(medicament->returnNume()));
        numeMedicament->setAlignment(Qt::AlignCenter);
        numeMedicament->setFont(QFont("Arial", 14, QFont::Bold));
        frameLayout->addWidget(numeMedicament);

        // Creează un layout orizontal pentru preț și cantitate
        QHBoxLayout* priceQuantityLayout = new QHBoxLayout();

        QLabel* pretMedicament = new QLabel(QString::fromStdString(medicament->getPret()));
        pretMedicament->setAlignment(Qt::AlignLeft);
        pretMedicament->setFont(QFont("Arial", 14, QFont::Bold));
        priceQuantityLayout->addWidget(pretMedicament);

        QLabel* cantitateMedicament = new QLabel(QString::number(cantitate));
        cantitateMedicament->setAlignment(Qt::AlignRight);
        cantitateMedicament->setFont(QFont("Arial", 14, QFont::Bold));
        priceQuantityLayout->addWidget(cantitateMedicament);

        frameLayout->addLayout(priceQuantityLayout);


        QHBoxLayout* total = new QHBoxLayout();

        float pret_total=0;
        float pret_bucata = std::stof(medicament->getPret());
        pret_total = pret_bucata * cantitate;
        QLabel* pret_medicamente = new QLabel(QString::number(pret_total));
        pret_medicamente->setAlignment(Qt::AlignCenter);
        pret_medicamente->setFont(QFont("Arial", 30, QFont::Bold));


        float pret_cos;
        if(this->ui->lblPretCos->text() == "")
        {
            pret_cos=0;
        } else
            pret_cos = (this->ui->lblPretCos->text()).toFloat();
        pret_cos += pret_total;
        this->ui->lblPretCos->setText(QString::number(pret_cos));

        total->addWidget(pret_medicamente);

        frameLayout->addLayout(total);

        // Adaugă chenarul în layout-ul principal
        mainLayout->addWidget(frame, row, col);

        col++;
        if (col == 3) {
            col = 0;
            row++;
        }
    }
    ui->scrollAreaCosCumparaturi->setLayout(mainLayout);


    this->ui->StackedWidgetAplicatie->currentWidget()->close();
    this->ui->StackedWidgetAplicatie->setCurrentWidget(ui->pageVeziCosCumparaturi);
    this->ui->pageVeziCosCumparaturi->show();
}




















