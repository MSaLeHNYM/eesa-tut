#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "notebook.h"

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


private slots:
    void on_showAddUserMenu_PB_clicked();
    void on_Add_this_Number_PB_clicked();
    void on_Add_This_User_PB_clicked();
    void on_ShowAllUser_PB_clicked();
    void on_pushButton_clicked();
    void on_SaveAll_PB_2_clicked();

    void on_SaveAll_PB_clicked();

    void on_Exit_PB_clicked();

    void on_DeleteUser_PB_clicked();

private:
    void UpdateTextShower();

    Ui::MainWindow *ui;

    List NoteBook;
    vector<pair<string, PhoneType>> ui_numbers;
    List SearchRes;
    bool IsInSearch =false ;

};
#endif // MAINWINDOW_H
