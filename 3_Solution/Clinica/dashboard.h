#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>

#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <map>
#include <QTimer>
#include <QRegularExpressionValidator>

#include "mainwindow.h"
#include"disponibilitate_programari.h"
#include"pacient.h"
#include"doctor.h"
#include"cutils.h"
#include"exception.h"
#include"afectiune.h"


namespace Ui {
class dashBoard;
}

class dashBoard : public QDialog
{
    Q_OBJECT

public:
    explicit dashBoard(QWidget *parent = nullptr,IUser* usser=nullptr);
    ~dashBoard();

    void setBackWindow(MainWindow* window);
    void creaza_vector_disp_prog(char* tot_stringul);
    void print_widget_programari();

    uint8_t* primire_poza(int& NrOfBytes);

    void Actualizare_shop();
    void setupTableColumnsWidth();

private slots:
    void myFunction_timer();

    void handleInfoButtonClicked();

    void ButtonBifeazaProgramareClicked();

    void on_btnHome_clicked();

    void on_btnSchedule_clicked();

    void on_btnShop_clicked();

    void on_btnShop_2_clicked();

    void on_btnAcoount_clicked();

    void on_btnSearchDoctori_clicked();

    void reset_layout_programari();

    void reset_layout_shop();

    void reset_layout_afectiuni();

    void ButtonOraProgramareClicked();

    void ButtonInformatiiMedicament(const std::string& numeMedicament);

    void ButtonAddCosMedicament(const std::string& numeMedicament);

    void on_btnBack_clicked();

    void on_pushButton_2_clicked();

    void on_btnBackToShopFromMedicament_clicked();

    void on_btnAccountDateCont_clicked();

    void on_btnBackToShopFromMedicament_2_clicked();

    void on_btnAccountSchimbaParola_clicked();

    void on_btnBackToShopFromMedicament_3_clicked();

    void on_pushButton_clicked();

    void on_btnVeziParolaVeche_clicked();

    void on_btnVeziParolaNoua1_clicked();

    void on_btnVeziParolaNoua2_clicked();

    void on_btnAccountSchimbaParola_2_clicked();

    void on_btnAccountVeziProgramari_clicked();

    void on_btnSearchAfectiune_clicked();

    void on_btnBackFromAfectiune_clicked();

    void on_btnMedicamentRecomandatAfectiune_clicked();

    void on_btnAccountLogOut_clicked();

private:
    Ui::dashBoard *ui;
    MainWindow* mainWindow = nullptr;

    IUser* client_pacient;
    std::map<std::string,int> CosCumparaturi;
    std::vector<Disponibilitate_Programari*> disp_prog_vect;
    int previous_page;

    QTimer *timer;

    bool exista_doctor_in_vector(std::string nume,std::string prenume,std::string CNP);
    void modify_hour_doctor(std::string nume,std::string prenume,std::string CNP,std::string hour);

    int pagina_shop;



};

#endif // DASHBOARD_H
