/****************************************************************************
** Meta object code from reading C++ file 'qwt_wheel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "C:/Qt/QWT/qwt_wheel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwt_wheel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QwtWheel_t {
    QByteArrayData data[11];
    char stringdata[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QwtWheel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QwtWheel_t qt_meta_stringdata_QwtWheel = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 13),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 12),
QT_MOC_LITERAL(4, 37, 10),
QT_MOC_LITERAL(5, 48, 9),
QT_MOC_LITERAL(6, 58, 7),
QT_MOC_LITERAL(7, 66, 10),
QT_MOC_LITERAL(8, 77, 11),
QT_MOC_LITERAL(9, 89, 16),
QT_MOC_LITERAL(10, 106, 4)
    },
    "QwtWheel\0setTotalAngle\0\0setViewAngle\0"
    "totalAngle\0viewAngle\0tickCnt\0wheelWidth\0"
    "borderWidth\0wheelBorderWidth\0mass"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QwtWheel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       7,   30, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x0a /* Public */,
       3,    1,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,

 // properties: name, type, flags
       4, QMetaType::Double, 0x00095103,
       5, QMetaType::Double, 0x00095103,
       6, QMetaType::Int, 0x00095103,
       7, QMetaType::Int, 0x00095103,
       8, QMetaType::Int, 0x00095103,
       9, QMetaType::Int, 0x00095103,
      10, QMetaType::Double, 0x00095103,

       0        // eod
};

void QwtWheel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QwtWheel *_t = static_cast<QwtWheel *>(_o);
        switch (_id) {
        case 0: _t->setTotalAngle((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->setViewAngle((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QwtWheel::staticMetaObject = {
    { &QwtAbstractSlider::staticMetaObject, qt_meta_stringdata_QwtWheel.data,
      qt_meta_data_QwtWheel,  qt_static_metacall, 0, 0}
};


const QMetaObject *QwtWheel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QwtWheel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QwtWheel.stringdata))
        return static_cast<void*>(const_cast< QwtWheel*>(this));
    return QwtAbstractSlider::qt_metacast(_clname);
}

int QwtWheel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtAbstractSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< double*>(_v) = totalAngle(); break;
        case 1: *reinterpret_cast< double*>(_v) = viewAngle(); break;
        case 2: *reinterpret_cast< int*>(_v) = tickCnt(); break;
        case 3: *reinterpret_cast< int*>(_v) = wheelWidth(); break;
        case 4: *reinterpret_cast< int*>(_v) = borderWidth(); break;
        case 5: *reinterpret_cast< int*>(_v) = wheelBorderWidth(); break;
        case 6: *reinterpret_cast< double*>(_v) = mass(); break;
        default: break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setTotalAngle(*reinterpret_cast< double*>(_v)); break;
        case 1: setViewAngle(*reinterpret_cast< double*>(_v)); break;
        case 2: setTickCnt(*reinterpret_cast< int*>(_v)); break;
        case 3: setWheelWidth(*reinterpret_cast< int*>(_v)); break;
        case 4: setBorderWidth(*reinterpret_cast< int*>(_v)); break;
        case 5: setWheelBorderWidth(*reinterpret_cast< int*>(_v)); break;
        case 6: setMass(*reinterpret_cast< double*>(_v)); break;
        default: break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
