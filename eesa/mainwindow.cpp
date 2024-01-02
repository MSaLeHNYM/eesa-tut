#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include<qdir.h>
#include"fileop.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    NoteBook=loadAll();
    delform = new deleteform();
}

MainWindow::~MainWindow()
{
    delete delform;
    delete ui;
}

//Functions for MainWindow

void MainWindow::Show_User(user nuser , int Iindex=1)
{
    string name =to_string(Iindex)+" )\n"+"First Name : "+nuser.getFirstName()+"\t \\ Last Name : "+nuser.getLastName()+"\nEmail : "+nuser.getEmail();
    ui->main_textEdit->append(QString::fromStdString(name));
    ui->main_textEdit->append("Numbers:");
    int Jindex=1;
    for(const auto &entry :nuser.getNumbers())
    {
        string number=to_string(Jindex)+" )"+entry.first+"  (Category:"+phoneTypeToString(entry.second)+")";
        ui->main_textEdit->append(QString::fromStdString(number));
        Jindex++;
    }
    ui->main_textEdit->append("__________________________________________");


}
void MainWindow::Show_All_Users()
{

    int Iindex=1;
    for(const user &nuser : NoteBook.getnotebook())
    {
        Show_User(nuser,Iindex);
        Iindex++;
    }
}





//Functions for MainWindow Slots

void MainWindow::on_Add_PB_clicked()
{
    QString qFname = ui->Fname_lineEdit->text();
    QString qLname = ui->Lname_lineEdit->text();
    QString qEmail = ui->Email_lineEdit->text();
    QString qNumber = ui->Phone_Number_lineEdit->text();

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
    else if (!IsThisNotRepetitiveEmail(NoteBook,qEmail.toStdString()))
    {
        QMessageBox::warning(this,"Warning","This Email already exists !!! Please enter a unique Email.");
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
            new_user.numbers= Numbers;
            NoteBook.addUser(new_user);
            QString nuser ="First Name: "+qFname+"\tLast Name :"+qLname+"\tEmail :"+qEmail;
            QMessageBox::information(this,"information","This user : " + nuser + "\n has been successfully added.");
            Numbers.clear();
            ui->Fname_lineEdit->clear();
            ui->Lname_lineEdit->clear();
            ui->Email_lineEdit->clear();
            ui->Phone_Number_lineEdit->clear();
            ui->Phone_textEdit->clear();
        }
    }

}

void MainWindow::on_Sort_and_Show_PB_clicked()
{
    ui->main_textEdit->setText("All users :");
    ui->main_textEdit->append("==========================================");
    NoteBook.sort();
    Show_All_Users();
}

void MainWindow::on_clear_PB_clicked()
{
    ui->main_textEdit->setText("Choose what you want :");
    ui->main_lineEdit->clear();
    ui->Fname_lineEdit->clear();
    ui->Lname_lineEdit->clear();
    ui->Email_lineEdit->clear();
    ui->Phone_Number_lineEdit->clear();
    ui->Phone_textEdit->clear();
    Numbers.clear();
}

void MainWindow::on_Search_PB_clicked()
{
    QString qentry = ui->main_lineEdit->text();
    if (qentry=="")
    {
        QMessageBox::warning(this,"Warning","please enter something to search for.");
        return;
    }
    List res ;
    if (qentry=="*")
    {
        res=NoteBook;
    }
    else
    {
        res = NoteBook.search(qentry.toStdString());
    }
    ui->main_textEdit->clear();
    ui->Phone_textEdit->clear();
    if (res.getnotebook().empty())
    {
        QMessageBox::information(this,"Information","No users were found for your search!!.");
    }
    else
    {
        ui->main_textEdit->append("These users were found for your search :");
        ui->main_textEdit->append("==========================================");
        int Iindex=1;
        for(const user &nuser :res.getnotebook())
        {
            Show_User(nuser,Iindex);
            Iindex++;
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
        ui->Phone_textEdit->append(QString::fromStdString(number));
        ui->Phone_Number_lineEdit->clear();
    }

}

void MainWindow::on_cancel_number_PB_clicked()
{
    ui->Phone_textEdit->clear();
    Numbers.clear();
}




void MainWindow::on_delete_PB_clicked()
{

    QString qentry = ui->main_lineEdit->text();
    if (qentry=="")
    {
        QMessageBox::warning(this,"Warning","please enter something to Delete for.");
        return;
    }
    List res;
    if (qentry=="*")
    {
        res=NoteBook;
    }
    else
    {
        res = NoteBook.search(qentry.toStdString());
    }


    if(res.getnotebook().empty())
    {
        QMessageBox::information(this,"Information","No users were found for your Delete!!.");
        return;
    }
    delform->FillTable(res);
    delform->exec();
    if(delform->Yes_Or_NO)
    {
        for(auto index :delform->getselectedIndex())
        {
            user user_d=res.getnotebook()[index];
            NoteBook.deleteuser(user_d);
        }
        delform->getselectedIndex().clear();
        QMessageBox::information(this,"Information","Your selected users have been successfully deleted.");
        on_Sort_and_Show_PB_clicked();
    }



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
        ui->Phone_textEdit->clear();
        QMessageBox::information(this,"Information","Data Deleted Successfully.");
    }
    else // if (QMessageBox::Cancel)
        QMessageBox::information(this,"Information","The information was not deleted.");
}

void MainWindow::on_Save_PB_clicked()
{

    if(saveAll(NoteBook))
        QMessageBox::information(this,"Informatiom","All users saved to db.txt");
    else
        QMessageBox::warning(this,"Warning","Error opening db.txt for writing.");

}

void MainWindow::on_Exit_PB_clicked()
{
    on_Save_PB_clicked();
}


void MainWindow::on_OK_PB_clicked()
{
    QString qentry = ui->main_lineEdit->text();
    if (qentry=="")
    {
        QMessageBox::warning(this,"Warning","please enter something to Do.");
        return;
    }
    if (qentry=="*")
    {
       on_Sort_and_Show_PB_clicked();
    }

}

