#include "deleteform.h"
#include "ui_deleteform.h"

deleteform::deleteform(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::deleteform)
{
    ui->setupUi(this);
}

deleteform::~deleteform()
{
    delete ui;
}
