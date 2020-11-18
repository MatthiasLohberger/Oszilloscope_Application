#include "oscilloscope.h"

Oscilloscope::Oscilloscope(QObject *parent) : QObject(parent)
{
    connect(&OsziMainWindow, SIGNAL(BtSettingsButtonPressed),
            &BluetoothWindow, SLOT(showBluetoothWindow));
    // Zurückwechseln mit hide im BTWin direkt

    connect(&OsziConfigData, SIGNAL(newConfigData),
            &BluetoothWindow, SLOT(newDataForPlainTextWidget(&OsziConfigData)));



}



void Oscilloscope::showOscilloscopeMainWindow(){
    OsziMainWindow.show();
}










