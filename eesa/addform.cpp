#include "addform.h"
#include "ui_addform.h"

AddForm::AddForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddForm)
{
    ui->setupUi(this);
}

AddForm::~AddForm()
{
    delete ui;
}
