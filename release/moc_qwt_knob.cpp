/****************************************************************************
** Meta object code from reading C++ file 'qwt_knob.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "C:/Qt/QWT/qwt_knob.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qwt_knob.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QwtKnob_t {
    QByteArrayData data[17];
    char stringdata[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QwtKnob_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QwtKnob_t qt_meta_stringdata_QwtKnob = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 9),
QT_MOC_LITERAL(2, 18, 9),
QT_MOC_LITERAL(3, 28, 11),
QT_MOC_LITERAL(4, 40, 11),
QT_MOC_LITERAL(5, 52, 9),
QT_MOC_LITERAL(6, 62, 11),
QT_MOC_LITERAL(7, 74, 10),
QT_MOC_LITERAL(8, 85, 10),
QT_MOC_LITERAL(9, 96, 7),
QT_MOC_LITERAL(10, 104, 6),
QT_MOC_LITERAL(11, 111, 6),
QT_MOC_LITERAL(12, 118, 8),
QT_MOC_LITERAL(13, 127, 4),
QT_MOC_LITERAL(14, 132, 3),
QT_MOC_LITERAL(15, 136, 3),
QT_MOC_LITERAL(16, 140, 5)
    },
    "QwtKnob\0knobStyle\0KnobStyle\0markerStyle\0"
    "MarkerStyle\0knobWidth\0borderWidth\0"
    "totalAngle\0markerSize\0NoStyle\0Raised\0"
    "Sunken\0NoMarker\0Tick\0Dot\0Nub\0Notch"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QwtKnob[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       7,   14, // properties
       2,   35, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, 0x80000000 | 2, 0x0009510b,
       3, 0x80000000 | 4, 0x0009510b,
       5, QMetaType::Int, 0x00095103,
       6, QMetaType::Int, 0x00095103,
       7, QMetaType::Double, 0x00095103,
       8, QMetaType::Int, 0x00095103,
       6, QMetaType::Int, 0x00095103,

 // enums: name, flags, count, data
       2, 0x0,    3,   43,
       4, 0x0,    5,   49,

 // enum data: key, value
       9, uint(QwtKnob::NoStyle),
      10, uint(QwtKnob::Raised),
      11, uint(QwtKnob::Sunken),
      12, uint(QwtKnob::NoMarker),
      13, uint(QwtKnob::Tick),
      14, uint(QwtKnob::Dot),
      15, uint(QwtKnob::Nub),
      16, uint(QwtKnob::Notch),

       0        // eod
};

void QwtKnob::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject QwtKnob::staticMetaObject = {
    { &QwtAbstractSlider::staticMetaObject, qt_meta_stringdata_QwtKnob.data,
      qt_meta_data_QwtKnob,  qt_static_metacall, 0, 0}
};


const QMetaObject *QwtKnob::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QwtKnob::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QwtKnob.stringdata))
        return static_cast<void*>(const_cast< QwtKnob*>(this));
    if (!strcmp(_clname, "QwtAbstractScale"))
        return static_cast< QwtAbstractScale*>(const_cast< QwtKnob*>(this));
    return QwtAbstractSlider::qt_metacast(_clname);
}

int QwtKnob::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtAbstractSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
     if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< KnobStyle*>(_v) = knobStyle(); break;
        case 1: *reinterpret_cast< MarkerStyle*>(_v) = markerStyle(); break;
        case 2: *reinterpret_cast< int*>(_v) = knobWidth(); break;
        case 3: *reinterpret_cast< int*>(_v) = borderWidth(); break;
        case 4: *reinterpret_cast< double*>(_v) = totalAngle(); break;
        case 5: *reinterpret_cast< int*>(_v) = markerSize(); break;
        case 6: *reinterpret_cast< int*>(_v) = borderWidth(); break;
        default: break;
        }
        _id -= 7;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setKnobStyle(*reinterpret_cast< KnobStyle*>(_v)); break;
        case 1: setMarkerStyle(*reinterpret_cast< MarkerStyle*>(_v)); break;
        case 2: setKnobWidth(*reinterpret_cast< int*>(_v)); break;
        case 3: setBorderWidth(*reinterpret_cast< int*>(_v)); break;
        case 4: setTotalAngle(*reinterpret_cast< double*>(_v)); break;
        case 5: setMarkerSize(*reinterpret_cast< int*>(_v)); break;
        case 6: setBorderWidth(*reinterpret_cast< int*>(_v)); break;
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
