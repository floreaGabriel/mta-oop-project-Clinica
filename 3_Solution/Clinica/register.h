#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
#include "mainwindow.h"
#include"requestregister.h"

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
    void setBackWindow(MainWindow* window);


private slots:
    void myFunction_timer();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_radPacient_pressed();

    void on_radDoctor_pressed();


    void onUsernameTextChanged(const QString &text);
    void onFirstNameTextChanged(const QString &text);
    void onLastNameTextChanged(const QString &text);
    void onPhoneNumberTextChanged(const QString &text);
    void onEmailTextChanged(const QString &text);
    void onCNPTextChanged(const QString &text);

private:
    Ui::Register *ui;
    MainWindow* mainWindow = nullptr;
    //Home* meniuPrincipalInstance = nullptr;
    QTimer *timer;
    void add_specializari_combo();


    void connectInputTextChangedSignals();
    void hideErrorMessages();
    bool anyFieldHasRedBorder();
    bool anyFieldIsEmpty();
    bool passwordsDoNotMatch();
    bool doctorCodeIsIncorrect();
};

#endif // REGISTER_H
