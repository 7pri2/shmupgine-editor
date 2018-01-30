/****************************************************************************
** Meta object code from reading C++ file 'w_graphics_manager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../shmupgine-editor/w_graphics_manager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'w_graphics_manager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_w_graphics_manager_t {
    QByteArrayData data[13];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_w_graphics_manager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_w_graphics_manager_t qt_meta_stringdata_w_graphics_manager = {
    {
QT_MOC_LITERAL(0, 0, 18), // "w_graphics_manager"
QT_MOC_LITERAL(1, 19, 11), // "add_picture"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 10), // "fill_infos"
QT_MOC_LITERAL(4, 43, 5), // "index"
QT_MOC_LITERAL(5, 49, 12), // "update_infos"
QT_MOC_LITERAL(6, 62, 14), // "QStandardItem*"
QT_MOC_LITERAL(7, 77, 4), // "item"
QT_MOC_LITERAL(8, 82, 12), // "update_model"
QT_MOC_LITERAL(9, 95, 14), // "delete_picture"
QT_MOC_LITERAL(10, 110, 21), // "dis_or_enable_details"
QT_MOC_LITERAL(11, 132, 14), // "append_picture"
QT_MOC_LITERAL(12, 147, 8) // "filename"

    },
    "w_graphics_manager\0add_picture\0\0"
    "fill_infos\0index\0update_infos\0"
    "QStandardItem*\0item\0update_model\0"
    "delete_picture\0dis_or_enable_details\0"
    "append_picture\0filename"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_w_graphics_manager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    1,   50,    2, 0x08 /* Private */,
       5,    1,   53,    2, 0x08 /* Private */,
       8,    0,   56,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,
      10,    0,   58,    2, 0x08 /* Private */,
      11,    1,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void w_graphics_manager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        w_graphics_manager *_t = static_cast<w_graphics_manager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->add_picture(); break;
        case 1: _t->fill_infos((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->update_infos((*reinterpret_cast< QStandardItem*(*)>(_a[1]))); break;
        case 3: _t->update_model(); break;
        case 4: _t->delete_picture(); break;
        case 5: _t->dis_or_enable_details(); break;
        case 6: _t->append_picture((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject w_graphics_manager::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_w_graphics_manager.data,
      qt_meta_data_w_graphics_manager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *w_graphics_manager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *w_graphics_manager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_w_graphics_manager.stringdata0))
        return static_cast<void*>(const_cast< w_graphics_manager*>(this));
    if (!strcmp(_clname, "Singleton<w_graphics_manager>"))
        return static_cast< Singleton<w_graphics_manager>*>(const_cast< w_graphics_manager*>(this));
    return QWidget::qt_metacast(_clname);
}

int w_graphics_manager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
