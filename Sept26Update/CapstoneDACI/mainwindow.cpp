#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
using namespace std;
#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

string txtFile = "";
ifstream inputFile(txtFile);
ofstream file;

void MainWindow::on_CustomMeas_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_LabFiles_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->LabChoose->setCurrentIndex(-1);
}


void MainWindow::on_ReturnHome_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_CircuitView_clicked()
{
    ui->LabMeasView->setCurrentIndex(0);
}


void MainWindow::on_MeasListView_clicked()
{
    ui->LabMeasView->setCurrentIndex(1);
}


void MainWindow::on_GraphView_clicked()
{
    ui->LabMeasView->setCurrentIndex(2);
}


void MainWindow::on_TableView_clicked()
{
    ui->LabMeasView->setCurrentIndex(3);
}


void MainWindow::on_LabChoose_currentIndexChanged(int index)
{
    if (index == 0)
    {
        QPixmap lab1("C:\\Users\\brook\\OneDrive\\Documents\\CapstoneDACI\\LabCircuit.png");
        txtFile = "lab1.txt";
        ui->label_13->setPixmap(lab1);
        ui->LabName->setText("Laboratory #1");
        ui->Task1->setText("Connect the voltage to V1 measurement");
        ui->Task2->setText("Connect the voltage across the resistor to the V2 measurement.");
        ui->Task3->setText("Connect the current through R2 to the I1 Measurement");
        ui->Task4->setText("Ensure the connections correspond to the picture");
        ui->Task5->setText("Turn on the power supply and record the measurements");
    }
    else if (index == 1)
    {
        txtFile = "lab2.txt";
        ui->label_13->clear();
        ui->LabName->setText("Laboratory #2");
        ui->Task1->setText("Attach the V1 Lead accross R1");
        ui->Task2->setText("Break and Bridge the current measurement for the inductor");
        ui->Task3->setText("Connect the current through R2 to the I1 Measurement");
        ui->Task4->setText("Ensure the connections correspond to the picture");
        ui->Task5->setText("Turn on the power supply and record the measurements");
    }
    else
    {
       txtFile = "";
       ui->label_13->clear();
       ui->LabName->setText("Please Choose Lab ->");
       ui->Task1->setText("Task1");
       ui->Task2->setText("Task2");
       ui->Task3->setText("Task3");
       ui->Task4->setText("Task4");
       ui->Task5->setText("Task5");
    }
}

//Func to pull text file info once file is passed
void MainWindow::labScreenSetUp(string s)
{
    char read[30];
    inputFile.open(s);

    if(inputFile.fail())
    {
        ui->LabName->setText("Invalid File");
    }

    inputFile.getline(read,30,'/');
    ui->LabName->setText(read);
    cout << read;

    // if(inputFile.is_open())
    // {
    //     inputFile.getline(line,150);
    //     ui->LabName->setText(line);
    // }
    // else
    //     ui->LabName->setText("Invalid File");
}

void MainWindow::on_EnterButton_clicked()
{
    string input = ui->inputFile->text().toStdString();
    labScreenSetUp(input);
    ui->inputFile->clear();
}


void MainWindow::on_AddLabFile_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->eName->clear();
    ui->ePic->clear();
    ui->eTasks->clear();
}


void MainWindow::on_SavedVals_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//Func to create new textfile once button is clicked
void MainWindow::createNewLab()
{
    string labName = ui->eName->text().toStdString();
    file.open(labName);
    string picName = ui->ePic->text().toStdString();
    string tasks = ui->eTasks->toPlainText().toStdString();
    file << "Name: " << labName << endl;
    file << "Image: " << picName << endl;
    file << tasks << endl;

  //  cout << "Name: " << labName << endl;
  //  cout << "Image: " << picName << endl;
  //  cout << tasks << endl;

    file.close();
}

void MainWindow::on_ReturnH_LPg_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_ReturnH_SPg_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_ClearAll_clicked()
{
    ui->eName->clear();
    ui->ePic->clear();
    ui->eTasks->clear();
}

void MainWindow::on_CreateLab_clicked()
{
    createNewLab();
}
