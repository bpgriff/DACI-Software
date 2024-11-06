#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
using namespace std;
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <QCheckBox>
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    gBoxLayout(new QVBoxLayout()) //try


{
    ui->setupUi(this);

    //try
    {
        ui->scrollArea->widget()->setLayout(gBoxLayout);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete gBoxLayout;
}

//declaring needed I/O variables
string txtFile = "";
ifstream inputFile(txtFile);
ofstream file;
namespace fs = std::filesystem;
string directoryPath = "DACILabFiles";
string picDirectory = "DACIImages";
int counter= 0;

//saved data vectors
vector <double> voltageSave{0};
vector <double> currentSave{0};
vector <double> voltageRead{0};
vector <double> currentRead{0};
vector <time_t> timeStamp{0};


void MainWindow::on_CustomMeas_clicked()
{
    //random number generator
    srand(time(0));

    voltageRead = {0};
    currentRead = {0};

    voltageRead.pop_back();
    currentRead.pop_back();

    for(int i = 0;i<8;i++)
    {
        voltageRead.push_back(rand() % 50);
        currentRead.push_back(rand() % 50);
    }

    ui->stackedWidget->setCurrentIndex(1);

    //TEST CASE!!!
    ui->V1->display(voltageRead[0]);
    ui->V2->display(voltageRead[1]);
    ui->V3->display(voltageRead[2]);
    ui->V4->display(voltageRead[3]);
    ui->I1->display(currentRead[0]);
    ui->I2->display(currentRead[1]);
    ui->I3->display(currentRead[2]);
    ui->I4->display(currentRead[3]);

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

    if(counter != 0)
    {
        ui->LabChoose->clear();
    }

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
    }
    else
    {
        labScreenSetUp(ui->LabChoose->currentText().toStdString());
       // cout << "Current Text" << ui->LabChoose->currentText().toStdString() << endl;
    }

}

// string directoryPath = "DACILabFiles";
// string picDirectory = "DACIImages";

//Func to pull text file info once file is passed
void MainWindow::labScreenSetUp(string s)
{
    ui->LabName->clear();
    ui->label_13->clear();

    if(counter > 0)
    {
        QLayoutItem *tempW;
        while( (tempW = ui->scrollArea->widget()->layout()->takeAt(0)) != NULL)
        {
            delete tempW->widget();
            delete tempW;
        }
    }

    if(!fs::exists(directoryPath))
    {
        //create directory
        fs::create_directory(directoryPath);
    }
    //read info after directory is created/checked
    inputFile.open(s);

    if(inputFile.fail())
    {
        ui->LabName->setText("Invalid File");
        return;
    }

    QString searchN = "Name: ";
    string n = searchFile(searchN.toStdString()).toStdString();
    ui->LabName->setText(QString::fromStdString(n));
  //  cout << "Name: " << n << endl;

    if(!fs::exists(picDirectory))
    {
        //create image directory
        fs::create_directory(picDirectory);
    }

    string searchI = "Image: ";
    string sImage = picDirectory + "\\" + searchFile(searchI).toStdString();
    //string sImage = searchFile(searchI).toStdString();
    QPixmap setImage(QString::fromStdString(sImage));
    ui->label_13->setPixmap(setImage);
   // cout << "pic file name - " << sImage << endl;

    //Add code for the task steps
    string searchTN = "Task Numbers: ";
    int tNum = searchFile(searchTN).toInt();
   // cout << "line nums - " << tNum << endl;

    //code to add steps

    string temp;
    string searchTemp;
    for(int i = 1; i<=tNum; i++)
    {
        QCheckBox *tcb = new QCheckBox();
        searchTemp = to_string(i) + ". ";
        temp = searchTemp + searchFile(searchTemp).toStdString();
        tcb->setText(QString::fromStdString(temp));
        ui->scrollArea->widget()->layout()->addWidget(tcb);
      //  temp = temp + searchTemp + searchFile(searchTemp).toStdString() + "\n";
    }
  //  ui->taskText->append(QString::fromStdString(temp));

    counter++;
    inputFile.close();

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

    //inputFile.close();

    return ret;
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
    string taskNum = ui->eTaskNum->text().toStdString();
    string tasks = ui->eTasks->toPlainText().toStdString();
    file << "Name: " << labName << endl;
    file << "Image: " << picName << endl;
    file << "Task Numbers: " << taskNum << endl;
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

void MainWindow::on_dataSave1_clicked()
{
    voltageSave.pop_back();
    currentSave.pop_back();

    for(int i = 0; i<voltageRead.size();i++)
    {
        voltageSave.push_back(voltageRead[i]);
        timeStamp.push_back(time(nullptr));
    }

    for(int i = 0; i<currentRead.size(); i++)
    {
        currentSave.push_back(currentRead[i]);
    }

    saveData();
}

void MainWindow::saveData()
{
    if(!fs::exists("savedData"))
    {
        fs::create_directory("savedData");
    }

    file.open("savedData//recentData");

    for(int i = 0; i<timeStamp.size(); i++)
    {
        file << timeStamp[i] << ",";
    }

    file << "\n";

    for(int i = 0; i<voltageSave.size(); i++)
    {
        file << voltageSave[i] << ",";
    }

    file << "\n";

    for(int i = 0; i<currentSave.size(); i++)
    {
        file << currentSave[i] << ",";
    }
}


void MainWindow::on_RefreshTable_clicked()
{
  //  QTableWidgetItem tempTW = new QTableWidgetItem();
 //   ui->SavedTable->setItem(1,1,new QTableWidgetItem("Time"));
    for(int i = 0; i<timeStamp.size(); i++)
    {
      char* tm = ctime(&timeStamp[i]);
      ui->SavedTable->setItem(0,i,new QTableWidgetItem(QString::fromStdString(tm)));
      //ui->SavedTable->setItem(0,i,new QTableWidgetItem(QString::fromStdString(to_string(timeStamp[i]))));
    }

  //  ui->SavedTable->setItem(2,1,new QTableWidgetItem("Voltage"));
    for(int i = 0; i<voltageSave.size(); i++)
    {
        ui->SavedTable->setItem(1,i,new QTableWidgetItem(QString::fromStdString(to_string(voltageSave[i]))));
    }

 //   ui->SavedTable->setItem(3,1,new QTableWidgetItem("Current"));
    for(int i = 0; i<currentSave.size(); i++)
    {
        ui->SavedTable->setItem(2,i,new QTableWidgetItem(QString::fromStdString(to_string(currentSave[i]))));
    }
}

