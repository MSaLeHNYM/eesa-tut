#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_showAddUserMenu_PB_clicked()
{

}


void MainWindow::on_show_PB_clicked()
{
    ui->main_textEdit->clear();
    ui->main_textEdit->append("All users:");
    for(user nuser : NoteBook.getnotebook())
    {
        string name ="First Name: "+nuser.getFirstName()+"\tLast Name :"+nuser.getLastName()+"\tEmail :"+nuser.getEmail();
        ui->main_textEdit->append(QString::fromStdString(name));
        ui->main_textEdit->append("Numbers:");
        for(auto entry :nuser.getNumbers())
        {
            string number=entry.first+"  (Category:"+phoneTypeToString(entry.second);
            ui->main_textEdit->append(QString::fromStdString(number));
        }
        ui->main_textEdit->append("____________________________");
    }
}

void MainWindow::on_clear_PB_clicked()
{
    // ui->main_textEdit->clear();
    ui->main_textEdit->setText("Choose what you want :");
}


void MainWindow::on_Add_PB_clicked()
{
    QString qFname = ui->Fname_lineEdit->text();
    QString qLname = ui->Lname_lineEdit->text();
    QString qEmail = ui->Email_lineEdit->text();
    QString qNumber = ui->Phone_Number_lineEdit->text();
    QString qType = ui->Phone_Type_comboBox->currentText();
    int Phone_Type=stringToIntPhoneType(qType.toStdString());


    if(!isValidPhoneNumber(qNumber.toStdString()) || !isValidEmail(qEmail.toStdString()) || qFname==""||qLname=="")
    {
        QMessageBox::warning(this,"warning","wrong inputs. please check them!!!!");
    }
    else
    {
        user new_user;
        new_user.setUser(qFname.toStdString(),qLname.toStdString(),qEmail.toStdString());
        new_user.addNumber(make_pair(qNumber.toStdString(),static_cast<PhoneType>(Phone_Type)));
        NoteBook.addUser(new_user);
        QMessageBox::information(this,"information","This user has been successfully added");

        ui->Fname_lineEdit->clear();
        ui->Lname_lineEdit->clear();
        ui->Email_lineEdit->clear();
        ui->Phone_Number_lineEdit->clear();
        ui->Phone_Type_lineEdit->clear();
    }

}

