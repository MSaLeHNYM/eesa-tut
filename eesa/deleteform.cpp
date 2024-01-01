#include "deleteform.h"
#include "notebook.h"
#include "ui_deleteform.h"
#include <QMessageBox>

deleteform::deleteform(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::deleteform)
{
    ui->setupUi(this);

    QStringList headers{"First Name","Last Name","Email","Numbers"};

    ui->delete_tableWidget->setColumnCount(4);
    ui->delete_tableWidget->setShowGrid(true);
    ui->delete_tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->delete_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->delete_tableWidget->setHorizontalHeaderLabels(headers);
    ui->delete_tableWidget->horizontalHeader()->setStretchLastSection(true);
    // connect(ui->delete_tableWidget-> horizontalHeader(),SIGNAL(sectionResized(int, int, int)),this,SLOT(resizeRowsToContents()));
}

deleteform::~deleteform()
{
    delete ui;
}



void deleteform::FillTable(List res)
{
    for(const auto &_user : res.getnotebook())
    {
        int row = ui->delete_tableWidget->rowCount();
        ui->delete_tableWidget->insertRow(row);
        QTableWidgetItem *FNameItem=new QTableWidgetItem(QString::fromStdString(_user.getFirstName()));
        QTableWidgetItem *LNameItem=new QTableWidgetItem(QString::fromStdString(_user.getLastName()));
        QTableWidgetItem *EmailItem=new QTableWidgetItem(QString::fromStdString(_user.getEmail()));
        string numberitem="";
        int i=1;
        for(const auto &number : _user.getNumbers())
        {
            numberitem+=to_string(i)+")"+number.first+"(Category:"+phoneTypeToString(number.second)+")"+"\n";
            i++;
        }
        QTableWidgetItem *NumbersItem=new QTableWidgetItem(QString::fromStdString(numberitem));

        ui->delete_tableWidget->setItem(row,0,FNameItem);
        ui->delete_tableWidget->setItem(row,1,LNameItem);
        ui->delete_tableWidget->setItem(row,2,EmailItem);
        ui->delete_tableWidget->setItem(row,3,NumbersItem);
    }
}
void deleteform::on_OK_PB_clicked()
{
    QItemSelectionModel *select = ui->delete_tableWidget->selectionModel();
    auto Indexs = select->selectedRows();
    if(Indexs.empty())
    {
        QMessageBox::warning(this,"Warning","NO users selected for Delete!!!.");
        return;
    }
    for(auto index : Indexs)
    {
        selectedIndex.push_back(index.row());
    }
    ui->delete_tableWidget->clear();
    this->close();

}

