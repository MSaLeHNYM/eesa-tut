#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notebook.h"
#include "fileoperations.h"
#include <QMessageBox>
#include <vector>
#include <qdir.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //load Everything
    NoteBook = loadAll();



    ui->setupUi(this);
    ui->Screen->setText(QDir::currentPath());

    // add items to combo box
    ui->comboBox->addItem("Main");
    ui->comboBox->addItem("Home");
    ui->comboBox->addItem("Work");
    ui->comboBox->addItem("Office");
    ui->comboBox->addItem("Fax");
}



MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_showAddUserMenu_PB_clicked()
{

}

void MainWindow::on_Add_this_Number_PB_clicked()
{
    QString num = ui->numberInput->text();
    int typeIndex = (ui->comboBox->currentIndex()) + 1;
    bool isUniq = true;

    // Check in ui_numbers
    for (auto &entry : ui_numbers)
    {
        if (entry.first == num.toStdString())
        {
            isUniq = false;
            break;
        }
    }

    // Check in NoteBook
    if (isUniq)
    {
        for (const auto &userEntry : NoteBook.$getNoteBook())
        {
            for (const auto &uu : userEntry.getNumbers())
            {
                if (uu.first == num.toStdString())
                {
                    isUniq = false;
                    break;
                }
            }
            if (!isUniq)
            {
                break; // Break outer loop if not unique
            }
        }
    }

    if (isUniq)
    {
        if (isValidPhoneNumber(num.toStdString()))
        {
            ui_numbers.push_back(make_pair(num.toStdString(), static_cast<PhoneType>(typeIndex)));
            UpdateTextShower();
        }
        else
        {
            QMessageBox::critical(this, "Error", "Number Is Not Valid", QMessageBox::Ok);
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "This Number Already Exists", QMessageBox::Ok);
    }
}



void MainWindow::UpdateTextShower(){
    QString text;
    for(auto &entry : ui_numbers){
        QString element = QString::fromStdString(entry.first) + "  (" + QString::number(static_cast<int>(entry.second)) + ")\n";
        text.append(element);
    }
    ui->Screen->setText(text);
}









void MainWindow::on_Add_This_User_PB_clicked()
{
    if(ui_numbers.size() >= 1){
        QString ui_fname = ui->FnameInput->text();
        QString ui_lname = ui->LnameInput->text();
        QString ui_email = ui->EmailInput->text();
        if((!(ui_fname.isEmpty())) || (!(ui_lname.isEmpty())) || (!(ui_email.isEmpty()))){
            if(isValidEmail(ui_email.toStdString())){
                user uu;
                uu.setUser(ui_fname.toStdString(),ui_lname.toStdString(),ui_email.toStdString());
                uu.addNumber(ui_numbers);
                NoteBook.addUser(uu);
                ui_numbers.clear();
                ui->FnameInput->clear();
                ui->LnameInput->clear();
                ui->EmailInput->clear();
                ui->numberInput->clear();
                ui->comboBox->setCurrentIndex(0);
                UpdateTextShower();
                QMessageBox::information(this, "Success", "User added successfully", QMessageBox::Ok);
            }else{
                QMessageBox::critical(this, "Error", "Email Is Not Valid", QMessageBox::Ok);

            }

        }else{
            QMessageBox::critical(this, "Error", "All Field Should Be complete", QMessageBox::Ok);
        }
    }else{
        QMessageBox::critical(this, "Error", "You Should Add At least one Number", QMessageBox::Ok);
        UpdateTextShower();
    }
}



void MainWindow::on_ShowAllUser_PB_clicked()
{
    ui_numbers.clear();
    QString text;
    if(NoteBook.$getNoteBook().size() == 0){
        ui->Screen->setText("There Is No User!!");
        return;
    }else{
        for(auto &uu : NoteBook.$getNoteBook()){
            text.append("First Name: " + QString::fromStdString(uu.getFirstName()) + "\n");
            text.append("Last Name: " + QString::fromStdString(uu.getLastName()) + "\n");
            text.append("Email: " + QString::fromStdString(uu.getEmail()) + "\n");
            text.append(QString::fromStdString(uu.getFirstName()) + "'s Numbers:\n");
            vector<pair<string, PhoneType>> nums = uu.getNumbers();
            if(nums.size() == 0){
                text.append("There Is No Num...\n");
            }else{
                for(auto &nn : nums){
                    text.append(QString::fromStdString(nn.first) + "  (" + QString::number(static_cast<int>(nn.second)) + ")\n");
                }
            }
            text.append("_________________\n");
        }
    }
    ui->Screen->setText(text);
}















void MainWindow::on_pushButton_clicked()
{
    QString entry;
    entry = ui->SearchInput->text();
    QString text;

    if(entry.size() == 0){
        QMessageBox::critical(this, "Error", "Fill Search Input First", QMessageBox::Ok);
        return;
    }else{
        List res = NoteBook.search(entry.toStdString());
        int count = 0;
        for(auto &uu : res.$getNoteBook()){
            count++;
            text.append(QString::number(count) + ":\n");
            text.append("   First Name: " + QString::fromStdString(uu.getFirstName()) + "\n");
            text.append("   Last Name: " + QString::fromStdString(uu.getLastName()) + "\n");
            text.append("   Email: " + QString::fromStdString(uu.getEmail()) + "\n");
            text.append("   " + QString::fromStdString(uu.getFirstName()) + "'s Numbers:\n\n");
            vector<pair<string, PhoneType>> nums = uu.getNumbers();
            if(nums.size() == 0){
                text.append("   There Is No Num...\n");
            }else{
                for(auto &nn : nums){
                    text.append("   " + QString::fromStdString(nn.first) + "  (" + QString::number(static_cast<int>(nn.second)) + ")\n");
                }
            }
            text.append("_________________\n");
        }

    }
    ui->Screen->setText(text);
}





void MainWindow::on_SaveAll_PB_2_clicked()
{
    saveAll(NoteBook);
}

