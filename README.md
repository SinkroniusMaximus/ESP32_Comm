# ESP32 Communications sketch
*ESP32 Communication example using Arduino framework. You can easily upload it to your esp32 dev board or alike. It contains seven communication options*

- Connect via the standard Serial port, this will be available from pin 1 and 3 on the esp32 dev board or via usb and using a serial monitor
- Connect via hardware Serial, this will be available from pin 16 and 17 on the esp32 dev board
- Connect to a nextion display to either hardware serial or the standard serial port, the protocol varies slightly, however don't worry it is supported
- Connect via bluetooth Serial, the bluetooth device acts as a serial port, the windows 10 drivers sucks but on Android using Serial Bluetooth Terminal works for example
- Connect via WIFIAP, this creates an access point, connect to the device using wifi and connect using a wifi client
- Connect via Husarnet, this connects the ESP32 to the cloud environment of husarnet and allows data transfer as well as a remote webserver

## Default hardware configuration:

- The sketch now contains the esp32 universal controller configuration, see /Images for the details
- Make your own cofiguration by modifying the IO definition in setup, pin definition in globals and the IO refresh method used in main.

## How does it communicate
Instead of creating variables of type int, bool or string, create Xint, Xbool or XString.
These variable types can be used for exchange. For example:
```cpp
Xbool Relay1;
```

At setup define the communication address using the following method:
```cpp
Relay1.Xinit("O1");
```

In this example sketch the variables are defined in a DB class, which also initializes the variables using: 
```cpp
DB.Xinit();
```
You can change this DB class to your likings.

Variables can now be addressed in the user program as:
```cpp 
DB.Relay1.x = true; 
DB.AnalogOutput1.val = 100;
DB.Message.txt = "some text";
```
As the communications class is defined as HMI_Comm, the communication is refreshed by placing the following in the loop:
```cpp 
HMI_Comm.CommXchange(terminator);
```
The class communicates with the following syntax "Address=Value*" in which * is used as the terminator.
For nextion devices the protocol adjusts to Address.val=Value, followed by '0xFF 0xFF 0xFF' as a terminator
For Husarnet http request is used, which is basically the webadress like /var/Address/Value or in this sketch example /var/data

In other words when you test the protocol using the serial monitor type: O1=1* and the value DB.Relay1.x will be updated and the output turns on.

## How to select a protocol
Open up the Globals.h and enable the different protocols by uncommenting the #define statements:
```cpp 
// #define XSerial
// #define XBluetooth
// #define XWifiAP
// #define XHWSerial
// #define XSerial_Nextion
// #define XHWSerial_Nextion
#define XHusarnet
```
logically XSerial and XSerial_Nextion cannot be enabled simultaneously, since that means it would use two protocol instructions on the same port.
The same goes for XHWSerial and XHWSerial_Nextion.
Having the serial monitor on the usb port using XSerial and the nextion HMI device on the hardware serial port using XHWSerial_Nextion, makes much more sense.
Having WifiAP and Husarnet on simultaneously is bound to result in conflict since that would mean they both use wifi, however this isn't tested.

## Creating a network
Variables can be shared among the different devices for example 
- the computer running a Processing sketch with sliders and buttons, the protocol is serial via usb or as a wifi client of the wifiap option
- the first esp32 has either wifiap or serial(or both) activated to connect to the computer, this chip also has the hw serial enabled
- the second esp32 connects to the first chip also using the hwserial port and connects to the cloud using husarnet
- the third esp32 connects to the second chip using husarnet, this chip also has the hw serial enabled and also it could be used on a remote location
- a tablet connects to the webserver of the second or third esp32 and can modify the variables using buttons on the webpage
- the fourth esp32 connects to the third chip using hw serial and to a nextion device using the standard serial port and also connects to a serial monitor or app using bluetooth
- and etc.
When a variable changes in one place the data is communicated throughout. 
The succession rate is not always 100%, for some protocols like Bluetooth, Husarnet and WifiAP it might work out of the box and otherwise you need to program some sort of confirmation or retry mechanism.

## Running a project

1. Clone this repo

2. Open the repo folder using VSC with installed Platformio extension

3. Select the communication options in Globals.h

4.1 in case you use husarnet this platformio.ini file works immediately, but when you don't you can comment out the unused depencencies.

also Provide your Wi-Fi networks credentials, rename the credentials-template.h to credentials.h and fill in the details.

```cpp
// WiFi credentials
const char *ssid = "FreeWifi";
const char *password = "hardtoguess";
```

4.2 Get your Husarnet VPN Join Code (allowing you to connect devices to the same VPN network)

> You will find your Join Code at **https://app.husarnet.com  
> -> Click on the desired network  
> -> `Add element` button  
> -> `Join Code` tab** 

4.3 Place your Husarnet Join Code here:

```cpp
const char *husarnetJoinCode = "fc94:b01d:1803:8dd8:b293:5c7d:7639:932a/xhfqwPxxxetyCExsSPRPn9"; // find at app.husarnet.com
```

4.4 Use a unique controller name for each controller, like "ESP32_HMI" or "ESP32_UC":
```cpp
const char *hostName = "my-esp32";
```

5. modify the variables to adapt to the program that you are making in DB.cpp and DB.h 

> Note when using husarnet the link to the webpage is found on app.husarnet.com, click on the button Web UI, however it might lead to LinkFromHusarnet/index.html, which doesn't exist in this example, therefor use LinkFromHusarnet/

> Note that there are processing and nextion example sketches included, the processing sketch requires you to get the controlP5 library

> Apparently the husarnet code involves a means of Over The Air (OTA) transfer, get informed if you need it!

> Video example: https://www.youtube.com/watch?v=lab9KZdaQsw

> I added a Serial.java in the Processing_HMI folder to override the usual serial port handling. It disables the RTS line so that the ESP32 doesn't restart on connecting. You can either delete it if you don't desire it, or you can generate a jar and replace the original class files or just leave it as it is. The last option is easiest, however it disables the intellisense feature.