#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notebook.h"
#include "fileoperations.h"
#include <QMessageBox>
#include <vector>
#include <QCoreApplication>
#include <qdir.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    //load Everything
    NoteBook = loadAll();



    ui->setupUi(this);
    // Display the welcome banner on the screen
    const char* welcomeBanner = R"(
██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗    ████████╗ ██████╗
██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝    ╚══██╔══╝██╔═══██╗
██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗         ██║   ██║   ██║
██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝         ██║   ██║   ██║
╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗       ██║   ╚██████╔╝
 ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝       ╚═╝    ╚═════╝

███╗   ██╗ ██████╗ ████████╗███████╗██████╗  ██████╗  ██████╗ ██╗  ██╗     █████╗ ██████╗ ██████╗
████╗  ██║██╔═══██╗╚══██╔══╝██╔════╝██╔══██╗██╔═══██╗██╔═══██╗██║ ██╔╝    ██╔══██╗██╔══██╗██╔══██╗
██╔██╗ ██║██║   ██║   ██║   █████╗  ██████╔╝██║   ██║██║   ██║█████╔╝     ███████║██████╔╝██████╔╝
██║╚██╗██║██║   ██║   ██║   ██╔══╝  ██╔══██╗██║   ██║██║   ██║██╔═██╗     ██╔══██║██╔═══╝ ██╔═══╝
██║ ╚████║╚██████╔╝   ██║   ███████╗██████╔╝╚██████╔╝╚██████╔╝██║  ██╗    ██║  ██║██║     ██║
╚═╝  ╚═══╝ ╚═════╝    ╚═╝   ╚══════╝╚═════╝  ╚═════╝  ╚═════╝ ╚═╝  ╚═╝    ╚═╝  ╚═╝╚═╝     ╚═╝
    )";

    // Set a fixed-width font for the QLabel
    QFont fixedWidthFont("Courier New", 11);
    ui->Screen->setFont(fixedWidthFont);

    // Print the welcome banner to the screen
    ui->Screen->setText(QString(welcomeBanner));

    // ui->Screen->setText(QDir::currentPath());

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
    IsInSearch = false;
}



void MainWindow::UpdateTextShower(){
    QString text;
    for(auto &entry : ui_numbers){
        QString element = QString::fromStdString(entry.first) + "  (" + QString::number(static_cast<int>(entry.second)) + ")\n";
        text.append(element);
    }
    ui->Screen->setText(text);
    IsInSearch = false;
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
    IsInSearch = false;
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
    IsInSearch = false;
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
        SearchRes = NoteBook.search(entry.toStdString());
        int count = 0;
        for(auto &uu : SearchRes.$getNoteBook()){
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
    IsInSearch = true;
    ui->Screen->setText(text);
}





void MainWindow::on_SaveAll_PB_2_clicked()
{
    saveAll(NoteBook);
}


void MainWindow::on_SaveAll_PB_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete All", "Are you sure you want to delete all users?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // User clicked Yes, delete all users
        NoteBook.deleteAll();// Assuming you have a clear() function in your List class
        UpdateTextShower();
        QMessageBox::information(this, "Success", "All users deleted successfully", QMessageBox::Ok);
    } else {
        // User clicked No or canceled, do nothing
    }
}


void MainWindow::on_Exit_PB_clicked()
{
    saveAll(NoteBook);
    QCoreApplication::quit();
}


void MainWindow::on_DeleteUser_PB_clicked()
{
    // if (IsInSearch)
    // {
    //     int inputIndex = ui->IndexToDelete_PB->text().toInt();

    //     // Check if inputIndex is in the valid range (1 - SearchRes.size())
    //     if (inputIndex >= 1 && inputIndex <= SearchRes.size())
    //     {
    //         // Display a confirmation message to the user
    //         QMessageBox::StandardButton reply;
    //         reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete this user?",
    //                                       QMessageBox::Yes | QMessageBox::No);

    //         if (reply == QMessageBox::Yes)
    //         {
    //             // Delete the user at the specified index
    //             NoteBook.deleteUser(SearchRes[inputIndex - 1]);

    //             // Reset search state and clear search results
    //             IsInSearch = false;
    //             SearchRes.clear();

    //             // Update the UI or display a message indicating successful deletion
    //             UpdateTextShower();
    //             QMessageBox::information(this, "Success", "User deleted successfully", QMessageBox::Ok);
    //         }
    //         // If the user clicks "No," do nothing (cancel deletion)
    //     }
    //     else
    //     {
    //         // Display an error message if the inputIndex is out of range
    //         QMessageBox::critical(this, "Error", "Invalid index. Please enter a valid index.", QMessageBox::Ok);
    //     }
    // }
    // else
    // {
    //     QMessageBox::critical(this, "Error", "First search for the user you want to delete, then input the index!", QMessageBox::Ok);
    // }
}

