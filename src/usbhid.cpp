#include "inc/usbhid.h"
#include <QDebug>

#define DEVICE_PID 0x0483
#define DEVICE_VID 0x5711

USBHID::USBHID(QObject *parent, unsigned int *ptr) :
    QObject(parent)
{
    buttons = 0;
    handle = 0;
    pCube = ptr;

    curDir = new QDir();
    lib = new QLibrary(curDir->absolutePath() + "/hidapi");
    lib->load();

    hid_open = (HID_OPEN)lib->resolve("hid_open");
    hid_close = (HID_CLOSE)lib->resolve("hid_close");
    hid_set_nonblocking = (HID_SET_NONBLOCKING)lib->resolve("hid_set_nonblocking");
    hid_send_feature_report = (HID_SEND_FEATURE_REPORT)lib->resolve("hid_send_feature_report");
    hid_get_feature_report = (HID_GET_FEATURE_REPORT)lib->resolve("hid_get_feature_report");
    hid_enumerate = (HID_ENUMERATE)lib->resolve("hid_enumerate");
    hid_free_enumeration = (HID_FREE_ENUMARATION)lib->resolve("hid_free_enumeration");
    hid_get_manufacturer_string = (HID_GET_MANUFACTURER_STRING)lib->resolve("hid_get_manufacturer_string");
    hid_get_product_string = (HID_GET_PRODUCT_STRING)lib->resolve("hid_get_product_string");
    hid_get_serial_number_string = (HID_GET_SERIAL_NUMBER_STRING)lib->resolve("hid_get_serial_number_string");
    hid_read = (HID_READ)lib->resolve("hid_read");
    hid_read_timeout = (HID_READ_TIMEOUT)lib->resolve("hid_read_timeout");
    hid_write = (HID_WRITE)lib->resolve("hid_write");
    hid_error = (HID_ERROR)lib->resolve("hid_error");

    if(!lib->isLoaded())
        qDebug() << "HIDAPI.dll failed to load";

    timer.setInterval(20);
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateHID()));
    timer.start();
}


USBHID::~USBHID()
{

}


bool USBHID::isLibLoaded()
{
    if(!lib->isLoaded()) return false;
    return true;
}



void USBHID::updateHID()
{
    //hid_close(handle);

    if(!handle)
    {
        OpenDevice(DEVICE_PID, DEVICE_VID);
        emit HIDStateChanged(false);
        return;
    }
    else
    {
        emit HIDStateChanged(true);
    }

    //Receive from device
    if(handle && TxToDevice==false)
    {
        char Rx[65];
        int size;

        size = hid_read(handle, (unsigned char*)&Rx, 65);     // Read requested state

        switch(*Rx)
        {
        case 0:
            break;

        case 1:
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            for(int i = 0; i<32; i++) *(pCube+i) = *(Rx+i+1);
            break;

        case 5:
            for(int i = 0; i<32; i++) *(pCube+i+32) = *(Rx+i+1);
            break;

        case 6:
            buttons = *(Rx+1);
            break;

        default:
            break;
        }
    }

    //Transmit to device
    if(handle && TxToDevice==true)
    {
        static int report = 0;
        unsigned char Rx[35];
        const unsigned char reportSize[] = {33,33};

        switch(report)
        {
        case 0:
            Rx[0] = 1;
            for(int i=1; i<33; i++) Rx[i] = *(pCube+i-1);

            //hid_write(handle, Rx, 30);
            hid_send_feature_report(handle, Rx, reportSize[report]);

            report = 1;
            break;

        case 1:
            Rx[0] = 2;
            for(int i=1; i<33; i++) Rx[i] = *(pCube+i+31);

            //hid_write(handle, Rx, 30);
            hid_send_feature_report(handle, Rx, reportSize[report]);

            report = 0;
            break;
        }
    }
}


void USBHID::setWorkingMode(int mode)
{
    if(handle)
    {
        unsigned char Rx[4];
        Rx[0] = 3;
        Rx[1] = mode;
        Rx[2] = Rx[3] = 0;
        hid_send_feature_report(handle, Rx, 4);
        qDebug() << " Sended Feature report!";
    }
}


int USBHID::OpenDevice(unsigned short pid, unsigned short vid)
{
    if(!isLibLoaded()) return 1;

    handle = hid_open(pid, vid, NULL);

    if (handle){
        qDebug() << "Device Loaded!!!";
        hid_set_nonblocking(handle, 0);
        return 0;
    }
    else{
        //qDebug() << ".....Device Load Fails.....";
        return 1;
    }
}
