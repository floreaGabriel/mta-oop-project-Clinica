#include "register.h"
#include "ui_register.h"
#include "clientconnection.h"
#include <QDebug>
#include <QTimer>
#include <QRegularExpressionValidator>


Register::Register(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Register)
{

    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(myFunction_timer()));

    connectInputTextChangedSignals();



    hideErrorMessages();

    ui->radPacient->pressed();
    ui->radPacient->setChecked(1);

    this->add_specializari_combo();


    ui->cstPassword1->setEchoMode(QLineEdit::Password);
    ui->cstPassword2->setEchoMode(QLineEdit::Password);


    setFixedSize(size());
}

Register::~Register()
{
    delete ui;
}



void Register::add_specializari_combo(){

    ui->comboSpecializare->addItem("Oftalmolog");
    ui->comboSpecializare->addItem("Dentist");
    ui->comboSpecializare->addItem("Cardiolog");
    ui->comboSpecializare->addItem("Hematolog");
    ui->comboSpecializare->addItem("Pediatru");
    ui->comboSpecializare->addItem("Psihiatru");
    ui->comboSpecializare->addItem("Ginecolog");
}



void Register::connectInputTextChangedSignals(){
    connect(ui->cstUsername, &QLineEdit::textChanged, this, &Register::onUsernameTextChanged);
    connect(ui->cstFirstName, &QLineEdit::textChanged, this, &Register::onFirstNameTextChanged);
    connect(ui->cstLastName, &QLineEdit::textChanged, this, &Register::onLastNameTextChanged);
    connect(ui->cstPhoneNumber, &QLineEdit::textChanged, this, &Register::onPhoneNumberTextChanged);
    connect(ui->cstEmail, &QLineEdit::textChanged, this, &Register::onEmailTextChanged);
    connect(ui->cstCNP, &QLineEdit::textChanged, this, &Register::onCNPTextChanged);
}



void Register::onUsernameTextChanged(const QString &text)
{
    // Verifică lungimea textului și caracterele valide și actualizează stilul în consecință
    QString styleSheet;
    QRegularExpression regex("^[a-zA-Z0-9_]{0,15}$"); // Permite litere mari și mici, cifre și caracterul underscore (_)
    if (!regex.match(text).hasMatch()) {
        // Dacă textul conține caractere invalide, setează culoarea conturului pe roșu
        styleSheet = "QLineEdit:focus { border: 2px solid black; }"
                     "QLineEdit:!focus { border: 2px solid red; }";
    } else {
        // Altfel, setează culoarea conturului pe negru
        styleSheet = "QLineEdit:focus { border: 2px solid black; }"
                     "QLineEdit:!focus { border: 2px solid black; }";
    }

    // Aplică stilul actualizat
    ui->cstUsername->setStyleSheet(styleSheet);
}



void Register::onFirstNameTextChanged(const QString &text)
{
    // Verificați lungimea textului și caracterele valide și actualizați stilul în consecință
    QString styleSheet;
    QRegularExpression regex("^[a-zA-Z]{0,15}$");
    if (text.length() > 15 || !regex.match(text).hasMatch()) {
        // Dacă textul are mai mult de 15 caractere sau nu conține doar litere, setați culoarea conturului pe roșu
        styleSheet = "QLineEdit:focus { border: 2px solid black; }"
                     "QLineEdit:!focus { border: 2px solid red; }";
    } else {
        // Altfel, setați culoarea conturului pe negru
        styleSheet = "QLineEdit:focus { border: 2px solid black; }"
                     "QLineEdit:!focus { border: 2px solid black; }";
    }

    // Aplicați stilul actualizat
    ui->cstFirstName->setStyleSheet(styleSheet);
}



void Register::onLastNameTextChanged(const QString &text)
{
    // Verifică lungimea textului și caracterele valide și actualizează stilul în consecință
    QString styleSheet;
    QRegularExpression regex("^[a-zA-Z]+(?:[- ]?[a-zA-Z]+){0,14}$");
    if (text.length() > 30 || !regex.match(text).hasMatch()) {
        // Dacă textul are mai mult de 15 caractere sau nu respectă formatul permis, setează culoarea conturului pe roșu
        styleSheet = "QLineEdit:focus { border: 2px solid black; }"
                     "QLineEdit:!focus { border: 2px solid red; }";
    } else {
        // Altfel, setează culoarea conturului pe negru
        styleSheet = "QLineEdit:focus { border: 2px solid black; }"
                     "QLineEdit:!focus { border: 2px solid black; }";
    }

    // Aplică stilul actualizat
    ui->cstLastName->setStyleSheet(styleSheet);
}



void Register::onPhoneNumberTextChanged(const QString &text)
{
    // Verifică lungimea textului și caracterele valide și actualizează stilul în consecință
    QString styleSheet;
    if (text.length() != 10 || !text.contains(QRegularExpression("^[0-9]{10}$"))) {
        // Dacă textul nu are exact 10 caractere sau nu conține doar cifre, setează culoarea conturului pe roșu
        styleSheet = "QLineEdit:focus { border: 2px solid black; }"
                     "QLineEdit:!focus { border: 2px solid red; }";
    } else {
        // Altfel, setează culoarea conturului pe negru
        styleSheet = "QLineEdit:focus { border: 2px solid black; }"
                     "QLineEdit:!focus { border: 2px solid black; }";
    }

    // Aplică stilul actualizat
    ui->cstPhoneNumber->setStyleSheet(styleSheet);
}



void Register::onEmailTextChanged(const QString &text)
{
    // Verifică dacă textul este un email valid și actualizează stilul în consecință
    QString styleSheet;
    QRegularExpression regex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (!regex.match(text).hasMatch()) {
        // Dacă textul nu corespunde unui format de email valid, setează culoarea conturului pe roșu
        styleSheet = "QLineEdit:focus { border: 2px solid black; }"
                     "QLineEdit:!focus { border: 2px solid red; }";
    } else {
        // Altfel, setează culoarea conturului pe negru
        styleSheet = "QLineEdit:focus { border: 2px solid black; }"
                     "QLineEdit:!focus { border: 2px solid black; }";
    }

    // Aplică stilul actualizat
    ui->cstEmail->setStyleSheet(styleSheet);
}



void Register::onCNPTextChanged(const QString &text)
{
    // Verifică lungimea textului și dacă conține doar cifre și actualizează stilul în consecință
    QString styleSheet;
    if (text.length() != 13 || !text.contains(QRegularExpression("^[0-9]{13}$"))) {
        // Dacă textul nu are exact 13 cifre, setează culoarea conturului pe roșu
        styleSheet = "QLineEdit:focus { border: 2px solid black; }"
                     "QLineEdit:!focus { border: 2px solid red; }";
    } else {
        // Altfel, setează culoarea conturului pe negru
        styleSheet = "QLineEdit:focus { border: 2px solid black; }"
                     "QLineEdit:!focus { border: 2px solid black; }";
    }

    // Aplică stilul actualizat
    ui->cstCNP->setStyleSheet(styleSheet);
}






void Register::setBackWindow(MainWindow* window)
{
    this->mainWindow=window;
}



void Register::on_pushButton_clicked()
{
    //butonul de back

    this->close();
    this->mainWindow->show();
}


void Register::myFunction_timer() {
    // Ascunde eticheta
    this->ui->testflorica->hide();
}



void Register::on_pushButton_2_clicked()
{
    //butonul de register
    hideErrorMessages();


    if (anyFieldHasRedBorder())
    {
        QString message = "<html><center>";
        message += "Una sau mai multe casete<br>";
        message += "sunt completate incorect!";
        message += "</center></html>";
        ui->testflorica->setText(message);
        ui->testflorica->show();
    }
    else if (anyFieldIsEmpty())
    {
        // Afișează un mesaj că unele câmpuri sunt goale
        QString message = "<html><center>";
        message += "Una sau mai multe casete<br>";
        message += "sunt goale!";
        message += "</center></html>";
        ui->testflorica->setText(message);
        ui->testflorica->show();
    }
    else if(passwordsDoNotMatch())
    {
        ui->testflorica->setText("Parolele nu coincid.");
        ui->testflorica->show();
    }
    else if(doctorCodeIsIncorrect())
    {
        ui->CODGresit->setText("COD GRESIT!");
        ui->CODGresit->show();
    }
    else
    {
        IRequest* req = new RequestRegister(ui->cstUsername->text(),ui->cstPassword1->text(),ui->cstPassword2->text(),ui->cstFirstName->text(),ui->cstLastName->text(),
                                            ui->cstPhoneNumber->text(),ui->cstEmail->text(),ui->cstCNP->text(),this->ui->radDoctor->isChecked(),ui->comboSpecializare->currentText());
        req->requestSEND();
        delete req;


        char responseBuffer[1024];
        if(ClientConnection::getInstance().receiveData(responseBuffer, sizeof(responseBuffer)))
        {
            qDebug() << "Mesaj primit: " << responseBuffer;
            if (strcmp(responseBuffer, "OK") == 0) {
                // Handle successful response from server
                qDebug() << "USERUL A FOST ADAUGAT IN BAZA DE DATE\n";

                this->close();
                this->mainWindow->show();

            }

            else if (strcmp(responseBuffer, "ALREADY EXISTS") == 0) {
                qDebug() << "USERUL EXISTA DEJA IN BAZA DE DATE\n";
                ui->testflorica->setText("USERUL EXISTA DEJA.");
                ui->testflorica->show();

                timer->start(5000);

            }
            else {
                // Handle error response from server
                qDebug() << "USERUL NU A FOST ADAUGAT CU SUCCES\n";
            }
        } else {
            // Handle receive error
        }
    }
}


void Register::hideErrorMessages() {
    ui->testflorica->hide();
    ui->CODGresit->hide();
}


bool Register::doctorCodeIsIncorrect(){
    return this->ui->radDoctor->isChecked() && this->ui->cstCodDoctor->text()!="2303";
}


bool Register::passwordsDoNotMatch(){
    return ui->cstPassword1->text() != ui->cstPassword2->text();
}


bool Register::anyFieldHasRedBorder(){
    return ui->cstUsername->styleSheet().contains("border: 2px solid red;") ||
           ui->cstPassword1->styleSheet().contains("border: 2px solid red;") ||
           ui->cstPassword2->styleSheet().contains("border: 2px solid red;") ||
           ui->cstFirstName->styleSheet().contains("border: 2px solid red;") ||
           ui->cstLastName->styleSheet().contains("border: 2px solid red;") ||
           ui->cstPhoneNumber->styleSheet().contains("border: 2px solid red;") ||
           ui->cstEmail->styleSheet().contains("border: 2px solid red;") ||
           ui->cstCNP->styleSheet().contains("border: 2px solid red;");
}


bool Register::anyFieldIsEmpty()
{
    return ui->cstUsername->text().isEmpty() || ui->cstPassword1->text().isEmpty() || ui->cstPassword2->text().isEmpty()
        || ui->cstFirstName->text().isEmpty() || ui->cstLastName->text().isEmpty() || ui->cstPhoneNumber->text().isEmpty()
           || ui->cstEmail->text().isEmpty() || ui->cstCNP->text().isEmpty() ;
}



void Register::on_radPacient_pressed()
{
    this->ui->codDoctor->hide();
    this->ui->cstCodDoctor->hide();
    this->ui->comboSpecializare->hide();
    this->ui->labelSpecializare->hide();

    this->ui->cstCodDoctor->clear();
}


void Register::on_radDoctor_pressed()
{
    this->ui->codDoctor->show();
    this->ui->cstCodDoctor->show();
    this->ui->comboSpecializare->show();
    this->ui->labelSpecializare->show();
}

