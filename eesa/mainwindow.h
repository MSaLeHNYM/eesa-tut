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


    bool ChekPrint=true;
    List getNoteBook()
    {
        return NoteBook;
    };

private slots:
    void on_showAddUserMenu_PB_clicked();

    void on_show_PB_clicked();

    void on_clear_PB_clicked();

    void on_Add_PB_clicked();

    void on_Add_Phone_Number_PB_clicked();

    void on_Sort_PB_clicked();

    void on_Delete_All_PB_clicked();

    void on_Save_PB_clicked();

    void on_Search_PB_clicked();

    void on_delete_PB_clicked();

private:
    Ui::MainWindow *ui;
    // MainWindow *mainform;
    deleteform *delform;

    List NoteBook;
    vector<pair<string, PhoneType>> Numbers;
};
#endif // MAINWINDOW_H
