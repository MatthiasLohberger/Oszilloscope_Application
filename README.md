# Oszilloscope_Application

This is the corresponding GitHub page to my bachelor’s thesis “Entwicklung einer Android Applikation mit dem Framework Qt in C++ für die Bluetooth-Kommunikation mit einem Oszilloskop” at the HAW Landshut. The EAS Board, the hardware which communicates with the Application via Bluetooth, has been designed by Prof. Dr. paed. Ivanov for the module EAS for the Master Electrical Engineering at the HAW Landshut. 
The application consists of two windows:

The MainWindow holds the central widget, which displays the sampled values of the EAS-Board. On the right side, there are widgets for setting the capture time, the trigger voltage und the entrance voltage:
![MainWindow](https://github.com/MatthiasLohberger/Oszilloscope_Application/tree/Qt/pictures/Main_Window.jpg)
!(https://github.com/MatthiasLohberger/Oszilloscope_Application/tree/Qt/pictures/Main_Window.jpg)
https://github.com/MatthiasLohberger/Oszilloscope_Application/tree/Qt/pictures/Main_Window.jpg

The second window is the BluetoothWindow with settings for the Bluetooth Connection, the Oszilloscope status as well as some additional settings for the Oscilloscope:
![BluetoothWindow](https://github.com/MatthiasLohberger/Oszilloscope_Application/tree/Qt/pictures/Settings_Window.jpg)

In order to use the Oscilloscope Application, execute the following steps at the beginning:
1.	Start the EAS-Board 
2.	Activate the location settings on your smartphone 
3.	Start the Oscilloscope Application 
4.	Confirm the appearing message to activate the Bluetooth settings of the application
5.	Search the EAS-Board in the settings by clicking on the “Search”-Button 
6.	Choose a device and click “Connect”

The latest release of the application can be downloaded under “releases” at the right side of the GitHub page.