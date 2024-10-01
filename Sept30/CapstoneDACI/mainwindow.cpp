#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
using namespace std;
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

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

//declaring needed I/O variables
string txtFile = "";
ifstream inputFile(txtFile);
ofstream file;
namespace fs = std::filesystem;
string directoryPath = "DACILabFiles";
string picDirectory = "DACIImages";

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

    vector<QString> files;
    QStringList fileNames;

    if(fs::exists(directoryPath))
    {
        for(const auto & entry : fs::directory_iterator(directoryPath))
        {
            if(entry.is_regular_file())
            {
                // files.push_back(QString::fromStdString(entry.path().string()));
                fileNames.push_back(QString::fromStdString(entry.path().string()));
            }
        }

        ui->LabChoose->addItems(fileNames);
    }
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
    if(index == -1)
    {
        ui->label_13->clear();
        ui->LabName->setText("Please Choose Lab ->");
        ui->Task1->setText("Task1");
        ui->Task2->setText("Task2");
        ui->Task3->setText("Task3");
        ui->Task4->setText("Task4");
        ui->Task5->setText("Task5");
    }
    else
    {
        //int optNum = ui->LabChoose->count();
        labScreenSetUp(ui->LabChoose->currentText().toStdString());
        cout << "Current Text" << ui->LabChoose->currentText().toStdString() << endl;
    }
    // if (index == 0)
    // {
    //     QPixmap lab1("C:\\Users\\brook\\OneDrive\\Documents\\CapstoneDACI\\LabCircuit.png");
    //     txtFile = "lab1.txt";
    //     ui->label_13->setPixmap(lab1);
    //     ui->LabName->setText("Laboratory #1");
    //     ui->Task1->setText("Connect the voltage to V1 measurement");
    //     ui->Task2->setText("Connect the voltage across the resistor to the V2 measurement.");
    //     ui->Task3->setText("Connect the current through R2 to the I1 Measurement");
    //     ui->Task4->setText("Ensure the connections correspond to the picture");
    //     ui->Task5->setText("Turn on the power supply and record the measurements");
    // }
    // else if (index == 1)
    // {
    //     txtFile = "lab2.txt";
    //     ui->label_13->clear();
    //     ui->LabName->setText("Laboratory #2");
    //     ui->Task1->setText("Attach the V1 Lead accross R1");
    //     ui->Task2->setText("Break and Bridge the current measurement for the inductor");
    //     ui->Task3->setText("Connect the current through R2 to the I1 Measurement");
    //     ui->Task4->setText("Ensure the connections correspond to the picture");
    //     ui->Task5->setText("Turn on the power supply and record the measurements");
    // }
    // else
    // {
    //    txtFile = "";
    //    ui->label_13->clear();
    //    ui->LabName->setText("Please Choose Lab ->");
    //    ui->Task1->setText("Task1");
    //    ui->Task2->setText("Task2");
    //    ui->Task3->setText("Task3");
    //    ui->Task4->setText("Task4");
    //    ui->Task5->setText("Task5");
    // }
}

// string directoryPath = "DACILabFiles";
// string picDirectory = "DACIImages";

//Func to pull text file info once file is passed
void MainWindow::labScreenSetUp(string s)
{
    if(!fs::exists(directoryPath))
    {
        //create directory
        fs::create_directory(directoryPath);
    }
    //read info after directory is created/checked
  //  string filePath = directoryPath;
  //  filePath = filePath + "//" + s;
   // char read[30];
    inputFile.open(s);

    if(inputFile.fail())
    {
        ui->LabName->setText("Invalid File");
    }

    QString searchN = "Name: ";
    string n = searchFile(searchN.toStdString()).toStdString();
    ui->LabName->setText(QString::fromStdString(n));
    cout << "Name: " << n << endl;

    if(!fs::exists(picDirectory))
    {
        //create image directory
        fs::create_directory(picDirectory);
    }

    string searchI = "Image: ";
    string sImage = picDirectory + "\\" + searchFile(searchI).toStdString();
    QPixmap setImage(QString::fromStdString(sImage));
    ui->label_13->setPixmap(setImage);
    cout << sImage << endl;

    //Add code for the task steps
}

QString MainWindow::searchFile(string search)
{
 //   string searchN = "Name: ";
    bool isFound = 0;
    QString ret;
    while(!inputFile.eof())
    {
        string temp = "";
        getline(inputFile, temp);
        for(int i=0; i<search.length();i++)
        {
            if(temp[i] == search[i])
                isFound = 1;
            else
            {
                isFound = 0;
                break;
            }
        }
        if(isFound)
        {
            for(int i = search.length();i<temp.size();i++)
                ret = ret + temp[i];
            break;
        }
    }

    if(inputFile.eof()&&(!isFound))
        ret = ret + "Invalid File Format";

    inputFile.close();

    return ret;
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
    ui->eTaskNum->clear();

    // vector<QString> files;
    // QStringList fileNames;

    // if(fs::exists(directoryPath))
    // {
    //     for(const auto & entry : fs::directory_iterator(directoryPath))
    //     {
    //         if(entry.is_regular_file())
    //         {
    //            // files.push_back(QString::fromStdString(entry.path().string()));
    //             fileNames.push_back(QString::fromStdString(entry.path().string()));
    //         }
    //     }

    //     ui->LabChoose->addItems(fileNames);
    // }
 //   ui->LabChoose->addItem();
}


void MainWindow::on_SavedVals_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//Func to create new textfile once button is clicked
void MainWindow::createNewLab()
{
    string labName = ui->eName->text().toStdString();

    if(!fs::exists(directoryPath))
    {
        //create directory
        fs::create_directory(directoryPath);
    }
    //read info after directory is created/checked
    string filePath = directoryPath;
    filePath = filePath + "//" + labName;

    file.open(filePath);
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
    ui->eTaskNum->clear();
}

void MainWindow::on_CreateLab_clicked()
{
    createNewLab();
}
