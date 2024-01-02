#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "notebook.h"
#include "deleteform.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Show_All_Users();
    void Show_User(user nuser,int Iindex);
    bool ChekPrint=true;
    List getNoteBook()
    {
        return NoteBook;
    };

private slots:

    void on_Add_PB_clicked();

    void on_clear_PB_clicked();

    void on_Add_Phone_Number_PB_clicked();

    void on_Delete_All_PB_clicked();

    void on_Save_PB_clicked();

    void on_Search_PB_clicked();

    void on_delete_PB_clicked();

    void on_Sort_and_Show_PB_clicked();

    void on_cancel_number_PB_clicked();

    void on_Exit_PB_clicked();

    void on_OK_PB_clicked();

private:
    Ui::MainWindow *ui;

    deleteform *delform;

    List NoteBook;
    vector<pair<string, PhoneType>> Numbers;
};
#endif // MAINWINDOW_H
