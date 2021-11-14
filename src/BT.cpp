#include "Globals.h"
#ifdef XBluetooth
    #if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
    #error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
    #endif
    BluetoothSerial SerialBT;
#endif