#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>

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
    void on_CustomMeas_clicked();

    void on_pushButton_2_clicked();

    void on_LabFiles_clicked();

    void on_ReturnHome_clicked();

    void on_CircuitView_clicked();

    void on_MeasListView_clicked();

    void on_GraphView_clicked();

    void on_TableView_clicked();

   // void on_comboBox_activated(int index);

   // void on_LabChoose_activated(int index);

    void on_LabChoose_currentIndexChanged(int index);

    //Func to pull all text file info once file is passed
    void labScreenSetUp(std::string s);

    void on_EnterButton_clicked();

    void on_AddLabFile_clicked();

    void on_SavedVals_clicked();

    void on_ReturnH_LPg_clicked();

    void on_ReturnH_SPg_clicked();

    void on_ClearAll_clicked();

    //func to create new text file once button is pushed
    void createNewLab();

    void on_CreateLab_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
