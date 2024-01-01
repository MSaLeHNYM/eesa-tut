#ifndef DELETEFORM_H
#define DELETEFORM_H

#include "notebook.h"
#include <QDialog>

namespace Ui {
class deleteform;
}

class deleteform : public QDialog
{
    Q_OBJECT

public:
    explicit deleteform(QWidget *parent = nullptr);
    ~deleteform();

    void FillTable(List res);

    vector<int> getselectedIndex()
    {
        return selectedIndex;
    }

private slots:


    void on_OK_PB_clicked();

private:
    Ui::deleteform *ui;
    vector<int> selectedIndex;
};

#endif // DELETEFORM_H
