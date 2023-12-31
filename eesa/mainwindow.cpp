#include "mainwindow.h"
#include"FileOperations.h"
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
    NoteBook.loadAll();
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

    if(!isValidName(qFname.toStdString()))
    {
        QMessageBox::warning(this,"warning","wrong inputs. please enter a correct First Name !!!!");
    }
    else if(!isValidName(qLname.toStdString()))
    {
        QMessageBox::warning(this,"warning","wrong inputs. please enter a correct Last Name !!!!");
    }
    else if(!isValidEmail(qEmail.toStdString()))
    {
        QMessageBox::warning(this,"warning","wrong inputs. please enter a corect Email !!!!");
    }
    else if(qNumber=="" && Numbers.empty())
    {
      QMessageBox::warning(this,"warning","wrong inputs. Please enter a valid phone number!!!!");
    }
    else if(!isValidPhoneNumber(qNumber.toStdString()) && qNumber!="")
    {
        QMessageBox::warning(this,"warning","wrong inputs. Please enter a valid phone number!!!!");
    }
    else if (!IsThisNotRepetitiveNumber(NoteBook,qNumber.toStdString()))
    {
        QMessageBox::warning(this,"Warning","This number already exists !!! Please enter a unique number.");
    }
    else
    {
       auto ans = QMessageBox::question(this,"Question","Do you want to add another phone number?",QMessageBox::Yes | QMessageBox::No);
        if (ans==QMessageBox::Yes)
       {
           on_Add_Phone_Number_PB_clicked();
       }
        else if (ans==QMessageBox::No)
        {
        ChekPrint=false;
        on_Add_Phone_Number_PB_clicked();
        ChekPrint=true;
        user new_user;
        new_user.setUser(qFname.toStdString(),qLname.toStdString(),qEmail.toStdString());
        // new_user.addNumber(make_pair(qNumber.toStdString(),static_cast<PhoneType>(Phone_Type)));
        new_user.numbers= Numbers;
        NoteBook.addUser(new_user);
        QString nuser ="First Name: "+qFname+"\tLast Name :"+qLname+"\tEmail :"+qEmail;
        QMessageBox::information(this,"information","This user : " + nuser + "\n has been successfully added.");
        Numbers.clear();
        ui->Fname_lineEdit->clear();
        ui->Lname_lineEdit->clear();
        ui->Email_lineEdit->clear();
        ui->Phone_Number_lineEdit->clear();
        ui->textEdit_1->clear();
       }
    }

}

void MainWindow::on_Add_Phone_Number_PB_clicked()
{
    QString qNumber = ui->Phone_Number_lineEdit->text();
    QString qType = ui->Phone_Type_comboBox->currentText();
    int Phone_Type=stringToIntPhoneType(qType.toStdString());

    if(!isValidPhoneNumber(qNumber.toStdString()) && ChekPrint)
    {
        QMessageBox::warning(this,"warning","wrong inputs. Please enter a valid phone number!!!!");
    }
    else if (qNumber!="" && !(IsThisNotRepetitiveNumber(NoteBook,qNumber.toStdString())))
    {
        QMessageBox::warning(this,"Warning","This number already exists !!! Please enter a unique number.");
    }
    else if(qNumber!="")
    {
        Numbers.push_back(make_pair(qNumber.toStdString(),static_cast<PhoneType>(Phone_Type)));
        int index = Numbers.size();
        string number=to_string(index)+ " : "+qNumber.toStdString()+"  (Category:"+phoneTypeToString(static_cast<PhoneType>(Phone_Type))+")";
        ui->textEdit_1->append(QString::fromStdString(number));
        ui->Phone_Number_lineEdit->clear();
    }

}

void MainWindow::on_Sort_PB_clicked()
{
    NoteBook.sort();
    on_show_PB_clicked();
}

void MainWindow::on_Delete_All_PB_clicked()
{
    auto anser = QMessageBox::question(this,"Question","Are you sure you want to delete it all?",QMessageBox::Yes | QMessageBox::Cancel);
    if (anser==QMessageBox::Yes)
    {
        NoteBook.deleteAll();
        ui->Fname_lineEdit->clear();
        ui->Lname_lineEdit->clear();
        ui->Email_lineEdit->clear();
        ui->Phone_Number_lineEdit->clear();
        ui->textEdit_1->clear();
        QMessageBox::information(this,"Information","Data Deleted Successfully.");
    }
    else // if (QMessageBox::Cancel)
        QMessageBox::information(this,"Information","The information was not deleted.");
}


void MainWindow::on_Save_PB_clicked()
{
    if(NoteBook.saveAll())
        QMessageBox::information(this,"Informatiom","All users saved to db.txt");
    else
        QMessageBox::warning(this,"Warning","Error opening db.txt for writing.");

}


