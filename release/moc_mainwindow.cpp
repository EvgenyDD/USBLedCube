/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata[259];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 25),
QT_MOC_LITERAL(2, 37, 0),
QT_MOC_LITERAL(3, 38, 11),
QT_MOC_LITERAL(4, 50, 12),
QT_MOC_LITERAL(5, 63, 16),
QT_MOC_LITERAL(6, 80, 13),
QT_MOC_LITERAL(7, 94, 3),
QT_MOC_LITERAL(8, 98, 11),
QT_MOC_LITERAL(9, 110, 18),
QT_MOC_LITERAL(10, 129, 5),
QT_MOC_LITERAL(11, 135, 11),
QT_MOC_LITERAL(12, 147, 18),
QT_MOC_LITERAL(13, 166, 15),
QT_MOC_LITERAL(14, 182, 15),
QT_MOC_LITERAL(15, 198, 18),
QT_MOC_LITERAL(16, 217, 21),
QT_MOC_LITERAL(17, 239, 3),
QT_MOC_LITERAL(18, 243, 15)
    },
    "MainWindow\0onSoundcardSettingsAction\0"
    "\0onRunButton\0onStopButton\0onFrameProcessed\0"
    "fftProcessor*\0fft\0cubeRePaint\0"
    "onVisualizeClicked\0state\0onHIDUpdate\0"
    "onRadio_Visualizer\0onRadio_Effects\0"
    "onRadio_Monitor\0soundSettDlgAccptd\0"
    "onDeviceChooseChanged\0num\0onEffectChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    1,   82,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    1,   86,    2, 0x08 /* Private */,
      11,    1,   89,    2, 0x08 /* Private */,
      12,    0,   92,    2, 0x08 /* Private */,
      13,    0,   93,    2, 0x08 /* Private */,
      14,    0,   94,    2, 0x08 /* Private */,
      15,    0,   95,    2, 0x08 /* Private */,
      16,    1,   96,    2, 0x08 /* Private */,
      18,    1,   99,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   17,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->onSoundcardSettingsAction(); break;
        case 1: _t->onRunButton(); break;
        case 2: _t->onStopButton(); break;
        case 3: _t->onFrameProcessed((*reinterpret_cast< fftProcessor*(*)>(_a[1]))); break;
        case 4: _t->cubeRePaint(); break;
        case 5: _t->onVisualizeClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->onHIDUpdate((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->onRadio_Visualizer(); break;
        case 8: _t->onRadio_Effects(); break;
        case 9: _t->onRadio_Monitor(); break;
        case 10: _t->soundSettDlgAccptd(); break;
        case 11: _t->onDeviceChooseChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->onEffectChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
