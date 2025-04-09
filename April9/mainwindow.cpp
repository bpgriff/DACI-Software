#define WIN32_LEAN_AND_MEAN

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "checkboxwordwrap.h"
#include "clickablelabel.h"
#include <string>
using namespace std;
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <QCheckBox>
#include <cstdlib>
#include <ctime>
#include <ftd2xx.h>
#include <chrono>
#include <thread>
#include <bitset>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    gBoxLayout(new QVBoxLayout()) //try


{
    ui->setupUi(this);
 //   QMainWindow::showFullScreen();
    QMainWindow::showMaximized();

    //try
    {
        ui->scrollArea->widget()->setLayout(gBoxLayout);
        ui->tabWidget->setTabText(0,"Home");
        ui->tabWidget->setTabText(1,"Front Panel");
        ui->tabWidget->setTabText(2,"Lab View");
        ui->tabWidget->setTabText(3,"Add Lab");
        ui->tabWidget->setTabText(4,"Saved Data");
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
vector <double> speedRead{0};
vector <double> speedSave{0};
vector <time_t> timeStamp{0};

//FTD2xx variables
//FTDI ftdi = new FTDI();
//FT_STATUS ftStatus;
//UINT32 bytesWritten = 0;


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
        // voltageRead.push_back(rand() % 50);
        // currentRead.push_back(rand() % 50);
        speedRead.push_back(rand() % 50);
    }

    ui->stackedWidget->setCurrentIndex(1);

  //  voltageRead = readChipData({1.2,2.3,4.5,10.8,12.0,24.1,44.0,240.2});
  //  currentRead = readChipData({0.03,0.1,1.1,2.1,3,4,5,6});

    // for(int i = 0;i<8;i++)
    // {
    //     voltageRead[i] = byteData(i);
    // }

  //  voltageRead[0] = byteData(0);
  //  voltageRead[1] = byteData(1);
  //  voltageRead[2] = byteData(2);
  //  voltageRead[3] = byteData(3);

   // voltageSave = readChipData();

    //TEST CASE!!!
    ui->V1->display(voltageSave[0]);
    ui->V2->display(voltageSave[1]);
    ui->V3->display(voltageSave[2]);
    ui->V4->display(voltageSave[3]);
    ui->I1->display(voltageSave[4]);
    ui->I2->display(voltageSave[5]);
    ui->I3->display(voltageSave[6]);
    ui->I4->display(voltageSave[7]);

    ui->lcdnumber->display(speedRead[8]);

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

    ui->Graphs->setCurrentIndex(0);
    QVector <double> x = QVector<double>(currentSave.begin(), currentSave.end());
    QVector <double> y = QVector<double>(voltageSave.begin(), voltageSave.end());
    ui->GraphLV->addGraph();
    ui->GraphLV->graph(0)->setData(x, y);
    ui->GraphLV->xAxis->setLabel("Current");
    ui->GraphLV->yAxis->setLabel("Voltage");
    ui->GraphLV->xAxis->setRange(0,50);
    ui->GraphLV->yAxis->setRange(0,50);
    ui->GraphLV->replot();
}


void MainWindow::on_TableView_clicked()
{
    ui->LabMeasView->setCurrentIndex(3);

    for(int i = 0; i<timeStamp.size(); i++)
    {
        char* tm = ctime(&timeStamp[i]);
        ui->L_Table->setItem(0,i,new QTableWidgetItem(QString::fromStdString(tm)));
    }

    for(int i = 0; i<voltageSave.size(); i++)
    {
        ui->L_Table->setItem(1,i,new QTableWidgetItem(QString::fromStdString(to_string(voltageSave[i]))));
    }

    for(int i = 0; i<currentSave.size(); i++)
    {
        ui->L_Table->setItem(2,i,new QTableWidgetItem(QString::fromStdString(to_string(currentSave[i]))));
    }

    for(int i = 0; i<speedSave.size(); i++)
    {
        ui->L_Table->setItem(3,i,new QTableWidgetItem(QString::fromStdString(to_string(speedSave[i]))));
    }

    ui->L_Table->resizeColumnsToContents();
    ui->L_Table->resizeRowsToContents();
    ui->L_Table->adjustSize();
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
    }

}


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

    if(!fs::exists(picDirectory))
    {
        //create image directory
        fs::create_directory(picDirectory);
    }

    string searchI = "Image: ";
    string sImage = picDirectory + "\\" + searchFile(searchI).toStdString();
    QPixmap setImage(QString::fromStdString(sImage));
    ui->label_13->setPixmap(setImage);

    //Add code for the task steps
    string searchTN = "Task Numbers: ";
    int tNum = searchFile(searchTN).toInt();

    //code to add steps

    string temp;
    string searchTemp;
    for(int i = 1; i<=tNum; i++)
    {
        CheckBoxWordWrap *tempWW = new CheckBoxWordWrap();
        tempWW->setCheckable(true);
        QCheckBox *tcb = new QCheckBox();
        searchTemp = to_string(i) + ". ";
        temp = searchTemp + searchFile(searchTemp).toStdString();
        tcb->setText(QString::fromStdString(temp));
        tempWW->setText(QString::fromStdString(temp));
        ui->scrollArea->widget()->layout()->addWidget(tempWW);
    }

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
    //clear the current values
    voltageSave.pop_back();
    currentSave.pop_back();
    speedSave.pop_back();
    timeStamp.pop_back();

    //repopulate the table
    for(int i = 0; i<voltageRead.size();i++)
    {
        voltageSave.push_back(voltageRead[i]);
        timeStamp.push_back(time(nullptr));
    }

    for(int i = 0; i<currentRead.size(); i++)
    {
        currentSave.push_back(currentRead[i]);
    }

    for(int i = 0; i<speedRead.size(); i++)
    {
        speedSave.push_back(speedRead[i]);
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

    for(int i = 1; i<timeStamp.size(); i++)
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

    file << "\n";

    for(int i = 0; i<speedSave.size(); i++)
    {
        file << speedSave[i] << ",";
    }
}


void MainWindow::on_RefreshTable_clicked()
{
    for(int i = 0; i<timeStamp.size(); i++)
    {
      char* tm = ctime(&timeStamp[i]);
      ui->SavedTable->setItem(0,i,new QTableWidgetItem(QString::fromStdString(tm)));
    }

    for(int i = 0; i<voltageSave.size(); i++)
    {
        ui->SavedTable->setItem(1,i,new QTableWidgetItem(QString::fromStdString(to_string(voltageSave[i]))));
    }

    for(int i = 0; i<currentSave.size(); i++)
    {
        ui->SavedTable->setItem(2,i,new QTableWidgetItem(QString::fromStdString(to_string(currentSave[i]))));
    }

    for(int i = 0; i<speedSave.size(); i++)
    {
        ui->SavedTable->setItem(3,i,new QTableWidgetItem(QString::fromStdString(to_string(speedSave[i]))));
    }

    ui->SavedTable->resizeColumnsToContents();
    ui->SavedTable->resizeRowsToContents();
    ui->SavedTable->adjustSize();
}


//func to populate table on Saved Value Page
void MainWindow::on_PopTable_clicked()
{
    ui->Graphs->setCurrentIndex(0);
    QVector <double> x = QVector<double>(currentSave.begin(), currentSave.end());
    QVector <double> y = QVector<double>(voltageSave.begin(), voltageSave.end());
    ui->GraphSV->addGraph();
    ui->GraphSV->graph(0)->setData(x, y);
    ui->GraphSV->xAxis->setLabel("Current");
    ui->GraphSV->yAxis->setLabel("Voltage");
    ui->GraphSV->xAxis->setRange(0,50);
    ui->GraphSV->yAxis->setRange(0,50);
    ui->GraphSV->replot();
}




void MainWindow::on_PopTable_VT_clicked()
{
    ui->Graphs->setCurrentIndex(1);

 //   QVector <double> x = QVector<double>(timeStamp.begin(), timeStamp.end());
    QVector <double> x = {1,2,3,4,5,6,7,8};
    QVector <double> y = QVector<double>(voltageSave.begin(), voltageSave.end());
    ui->GraphVoltTime->addGraph();
    ui->GraphVoltTime->graph(0)->setData(x, y);
    ui->GraphVoltTime->xAxis->setLabel("Time");
    ui->GraphVoltTime->yAxis->setLabel("Voltage");
  //  ui->GraphSV->xAxis->setRange(0,50);
    ui->GraphVoltTime->yAxis->setRange(0,50);
    ui->GraphVoltTime->replot();
}


void MainWindow::on_PopTable_CT_clicked()
{
    ui->Graphs->setCurrentIndex(2);

  //  QVector <double> x = QVector<double>(timeStamp.begin(), timeStamp.end());
    QVector <double> x = {1,2,3,4,5,6,7,8};
    QVector <double> y = QVector<double>(currentSave.begin(), currentSave.end());
    ui->GraphCurrTime->addGraph();
    ui->GraphCurrTime->graph(0)->setData(x, y);
    ui->GraphCurrTime->xAxis->setLabel("Time");
    ui->GraphCurrTime->yAxis->setLabel("Current");
    //  ui->GraphSV->xAxis->setRange(0,50);
    ui->GraphCurrTime->yAxis->setRange(0,50);
    ui->GraphCurrTime->replot();
}

//func for tab functionality
void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index ==-1)
        ui->stackedWidget->setCurrentIndex(0);
    else if(index == 0)
        ui->stackedWidget->setCurrentIndex(0);
    else if(index == 1)
        ui->stackedWidget->setCurrentIndex(1);
    else if(index == 2)
        ui->stackedWidget->setCurrentIndex(4);
    else if(index == 3)
        ui->stackedWidget->setCurrentIndex(3);
    else if(index == 4)
        ui->stackedWidget->setCurrentIndex(2);
}


//func for FT device
int MainWindow::byteData(int n)
{
    //FTDI variables
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesReceived; //number of bytes read

    //received data
    unsigned char RxBuffer[16] = {0};
   // char TxBuffer[256];

    //return value
    int dataInt = 0;

    DWORD numDevs = 0;
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if(ftStatus != FT_OK)
    {
        cout << "No device found" << "\n";
        return -1;
    }
    cout << "device found" << "\n";

    ftStatus = FT_Open(0, &ftHandle);
    if(ftStatus != FT_OK)
    {
        cout << "open failed" << "\n";
        //open failed
        return -1;
    }
    cout << "device opened" << "\n";
    cout << "Rx b4 write: " << RxBytes << "\n";

    FT_SetBaudRate(ftHandle,9600);
  //  ftStatus = FT_SetTimeouts(ftHandle, 1000, 1000);

    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_2, FT_PARITY_NONE);

    ftStatus = FT_SetDtr(ftHandle);
    if(ftStatus != FT_OK)
    {
        cout << "set terminal ready failed" << "\n";
        return -1;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));


    FT_GetQueueStatus(ftHandle, &RxBytes);
    cout << "status received" << "\n";
    cout << "RxBytes: " << RxBytes << "\n";

  //  std::this_thread::sleep_for(std::chrono::milliseconds(100));


      if(RxBytes > 0)
      {
        ftStatus = FT_Read(ftHandle, RxBuffer, 1, &BytesReceived);
        cout << "Bytes after read" << RxBytes << "\n";

        if(ftStatus == FT_OK)
        {
            //read okay, RxBytes read
            //int recNum = static_cast<int>(BytesReceived);

            if(ftStatus == FT_OK && static_cast<int>(BytesReceived) >= 1)
            {
                int asciiValue = static_cast<unsigned int>(RxBuffer[0]);
                cout << RxBuffer[0] << "\n";
                cout << asciiValue << "\n";
            }
        }
        else
        {
            //read failed.
            cout << "read failed" << "\n";
            return -1;
        }
    }

    FT_ClrDtr(ftHandle);

    ftStatus = FT_Close(ftHandle);

    return (int)RxBuffer[n];
}

vector<double> MainWindow::readChipData()
{
    vector<double> ret = {0};
    ret.pop_back();

    //FTDI variables
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    DWORD EventDWord;
    DWORD TxBytes;
    DWORD RxBytes;
    DWORD BytesWritten;
    DWORD BytesReceived; //number of bytes read

    char RxBuffer[2] = {0};

    //trasmit the passed buff (and convert to binary)
    // for(int i = 0; i<txBuff.size(); i++)
    // {
    //     memcpy(&TxBuffer[i*sizeof(double)], &txBuff[i], sizeof(double));
    // }

    DWORD numDevs = 0;
    ftStatus = FT_CreateDeviceInfoList(&numDevs);
    if(ftStatus != FT_OK)
    {
        cout << "No device found" << "\n";
        return {0};
    }

    ftStatus = FT_Open(0, &ftHandle);
    if(ftStatus != FT_OK)
    {
        //open failed
        return {0};
    }

    FT_SetBaudRate(ftHandle,9600);
    ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_2, FT_PARITY_NONE);


    for(int i = 0; i<9; i++)
    {
        ftStatus = FT_SetDtr(ftHandle);
        if(ftStatus != FT_OK)
            return {0};
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        FT_GetQueueStatus(ftHandle, &RxBytes);

        if(RxBytes > 0)
        {
            FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
            ret.push_back(static_cast<unsigned int>(RxBuffer[0]));
        }

        FT_ClrDtr(ftHandle);
    }

    // ftStatus = FT_SetDtr(ftHandle);
    // if(ftStatus != FT_OK)
    // {
    //     return {0};
    // }

    // FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);

    // if(RxBytes > 0)
    // {
    //     ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
    //     if(ftStatus != FT_OK)
    //     {
    //         //read okay, RxBytes read
    //         return {0};
    //     }
    // }

    FT_Close(ftHandle);

    return ret;
}

//test display for chip
void MainWindow::on_pushButton_clicked()
{
    int dataRx = byteData(0);
    ui->lcdNumber_10->display(dataRx);
}
