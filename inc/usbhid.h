#ifndef USBHID_H
#define USBHID_H

#include <QDir>
#include <QLibrary>
#include <QObject>
#include <QTimer>
#include "hidapi.h"

#include <QObject>

typedef struct hid_device_info* (*HID_ENUMERATE)(unsigned short, unsigned short);
typedef void (*HID_FREE_ENUMARATION)(struct hid_device_info*);
typedef hid_device* (*HID_OPEN)(unsigned short, unsigned short, wchar_t*);
typedef void (*HID_CLOSE)(hid_device *);
typedef int (*HID_GET_MANUFACTURER_STRING)(hid_device *, wchar_t *, size_t);
typedef int (*HID_GET_PRODUCT_STRING)(hid_device*, wchar_t*, size_t);
typedef int (*HID_GET_SERIAL_NUMBER_STRING)(hid_device*, wchar_t*, size_t);
typedef int (*HID_SET_NONBLOCKING)(hid_device*, int);
typedef int (*HID_SEND_FEATURE_REPORT)(hid_device*, const unsigned char*, size_t);
typedef int (*HID_GET_FEATURE_REPORT)(hid_device*, unsigned char*, size_t);
typedef int (*HID_WRITE)(hid_device*, const unsigned char*, size_t);
typedef int (*HID_READ)(hid_device*, unsigned char*, size_t);
typedef int (*HID_READ_TIMEOUT)(hid_device*, unsigned char*, size_t, int);
typedef wchar_t (*HID_ERROR)(hid_device*);

enum WorkState{STANDALONE, PC_MONITORING, PC_CONTROLS};



class USBHID : public QObject
{
    Q_OBJECT
public:
    explicit USBHID(QObject *parent = 0, unsigned int *ptr = 0);
    ~USBHID();

    hid_device *handle;
    unsigned char buttons;
    bool isLibLoaded();
    int OpenDevice(unsigned short pid, unsigned short vid);


    void setWorkingMode(int);

    void SetTxToDevice(){
        TxToDevice = true;
    }

    void SetRxFromDevice(){
        TxToDevice = false;
    }

private:
    QDir* curDir;
    QLibrary* lib;

    QTimer timer;

    uint *pCube;

    HID_OPEN hid_open;
    HID_ENUMERATE hid_enumerate;
    HID_FREE_ENUMARATION hid_free_enumeration;
    HID_GET_MANUFACTURER_STRING hid_get_manufacturer_string;
    HID_GET_PRODUCT_STRING hid_get_product_string;
    HID_GET_SERIAL_NUMBER_STRING hid_get_serial_number_string;
    HID_SET_NONBLOCKING hid_set_nonblocking;
    HID_SEND_FEATURE_REPORT hid_send_feature_report;
    HID_GET_FEATURE_REPORT hid_get_feature_report;
    HID_READ_TIMEOUT hid_read_timeout;
    HID_READ hid_read;
    HID_WRITE hid_write;
    HID_ERROR hid_error;
    HID_CLOSE hid_close;

    bool TxToDevice;

signals:
    void HIDStateChanged(bool state);

public slots:
    void updateHID();

};

#endif // USBHID_H
