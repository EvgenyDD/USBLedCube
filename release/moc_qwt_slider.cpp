/****************************************************************************
** Meta object code from reading C++ file 'qwt_slider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "C:/Qt/QWT/qwt_slider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwt_slider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QwtSlider_t {
    QByteArrayData data[16];
    char stringdata[177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QwtSlider_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QwtSlider_t qt_meta_stringdata_QwtSlider = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 13),
QT_MOC_LITERAL(2, 24, 8),
QT_MOC_LITERAL(3, 33, 15),
QT_MOC_LITERAL(4, 49, 16),
QT_MOC_LITERAL(5, 66, 10),
QT_MOC_LITERAL(6, 77, 11),
QT_MOC_LITERAL(7, 89, 7),
QT_MOC_LITERAL(8, 97, 7),
QT_MOC_LITERAL(9, 105, 9),
QT_MOC_LITERAL(10, 115, 10),
QT_MOC_LITERAL(11, 126, 8),
QT_MOC_LITERAL(12, 135, 11),
QT_MOC_LITERAL(13, 147, 15),
QT_MOC_LITERAL(14, 163, 6),
QT_MOC_LITERAL(15, 170, 6)
    },
    "QwtSlider\0scalePosition\0ScalePos\0"
    "backgroundStyle\0BackgroundStyles\0"
    "handleSize\0borderWidth\0spacing\0NoScale\0"
    "LeftScale\0RightScale\0TopScale\0BottomScale\0"
    "BackgroundStyle\0Trough\0Groove"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QwtSlider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       5,   14, // properties
       2,   29, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x0009510b,
       3, 0x80000000 | 4, 0x0009510b,
       5, QMetaType::QSize, 0x00095103,
       6, QMetaType::Int, 0x00095103,
       7, QMetaType::Int, 0x00095103,

 // enums: name, flags, count, data
       2, 0x0,    5,   37,
      13, 0x0,    2,   47,

 // enum data: key, value
       8, uint(QwtSlider::NoScale),
       9, uint(QwtSlider::LeftScale),
      10, uint(QwtSlider::RightScale),
      11, uint(QwtSlider::TopScale),
      12, uint(QwtSlider::BottomScale),
      14, uint(QwtSlider::Trough),
      15, uint(QwtSlider::Groove),

       0        // eod
};

void QwtSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject QwtSlider::staticMetaObject = {
    { &QwtAbstractSlider::staticMetaObject, qt_meta_stringdata_QwtSlider.data,
      qt_meta_data_QwtSlider,  qt_static_metacall, 0, 0}
};


const QMetaObject *QwtSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QwtSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QwtSlider.stringdata))
        return static_cast<void*>(const_cast< QwtSlider*>(this));
    if (!strcmp(_clname, "QwtAbstractScale"))
        return static_cast< QwtAbstractScale*>(const_cast< QwtSlider*>(this));
    return QwtAbstractSlider::qt_metacast(_clname);
}

int QwtSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtAbstractSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< ScalePos*>(_v) = scalePosition(); break;
        case 1: *reinterpret_cast< BackgroundStyles*>(_v) = backgroundStyle(); break;
        case 2: *reinterpret_cast< QSize*>(_v) = handleSize(); break;
        case 3: *reinterpret_cast< int*>(_v) = borderWidth(); break;
        case 4: *reinterpret_cast< int*>(_v) = spacing(); break;
        default: break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setScalePosition(*reinterpret_cast< ScalePos*>(_v)); break;
        case 1: setBackgroundStyle(*reinterpret_cast< BackgroundStyles*>(_v)); break;
        case 2: setHandleSize(*reinterpret_cast< QSize*>(_v)); break;
        case 3: setBorderWidth(*reinterpret_cast< int*>(_v)); break;
        case 4: setSpacing(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE
