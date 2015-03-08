#ifndef USBHID_H
#define USBHID_H

#include <QObject>

class USBHID : public QObject
{
    Q_OBJECT
public:
    explicit USBHID(QObject *parent = 0);

signals:

public slots:

};

#endif // USBHID_H
