#include "savedata.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <ftd2xx.h>
#include <string>

SaveData::SaveData()
{
  //   // public static FTDI ftdi = new FTDI();
  //   // public static FT_STATUS ftStatus;
  //   // public static UINT32 bytesWritten = 0;

  //       ftdi.SetBaudRate(9600);

  //       FT_HANDLE ftHandle;
  //       DWORD EventDWord;
  //       DWORD TxBytes;
  //       DWORD RxBytes;
  //       DWORD BytesReceived; //number of bytes read

  //       //received data
  //       char RxBuffer[256];

  //       ftStatus = FT_Open(0, &ftHandle);
  //       if(ftStatus != FT_OK)
  //       {
  //           //open failed
  //           return;
  //       }

  //       FT_GetStatus(ftHandle, &RxBytes, &TxBytes, &EventDWord);
  //       if(RxBytes > 0)
  //       {
  //           ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
  //           if(ftStatus == FT_OK)
  //           {
  //               //read okay, RxBytes read
  //               //output?????
  //               if(static_cast<int>(RxBytes) == 8)
  //               {
  //                   std::string data(BytesReceived.begin(), BytesReceived.end());
  //                   int dataInt = stoi(data, 0, 2);
  //               }
  //           }
  //           else
  //           {
  //               //read failed.
  //               return;
  //           }
  //       }

  //       FT_Close(ftHandle);

  // //  ftdi.OpenByIndex(0);
  // //  ftdi.SetBaudRate(9600);
}


