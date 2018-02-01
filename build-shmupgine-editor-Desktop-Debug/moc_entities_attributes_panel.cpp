/****************************************************************************
** Meta object code from reading C++ file 'entities_attributes_panel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../shmupgine-editor/entities_attributes_panel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'entities_attributes_panel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_entities_attributes_panel_t {
    QByteArrayData data[13];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_entities_attributes_panel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_entities_attributes_panel_t qt_meta_stringdata_entities_attributes_panel = {
    {
QT_MOC_LITERAL(0, 0, 25), // "entities_attributes_panel"
QT_MOC_LITERAL(1, 26, 8), // "showMenu"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 14), // "handle_actions"
QT_MOC_LITERAL(4, 51, 8), // "QAction*"
QT_MOC_LITERAL(5, 60, 16), // "remove_attribute"
QT_MOC_LITERAL(6, 77, 10), // "attribute*"
QT_MOC_LITERAL(7, 88, 4), // "attr"
QT_MOC_LITERAL(8, 93, 20), // "update_current_index"
QT_MOC_LITERAL(9, 114, 5), // "index"
QT_MOC_LITERAL(10, 120, 13), // "remove_entity"
QT_MOC_LITERAL(11, 134, 10), // "new_entity"
QT_MOC_LITERAL(12, 145, 22) // "update_what_is_visible"

    },
    "entities_attributes_panel\0showMenu\0\0"
    "handle_actions\0QAction*\0remove_attribute\0"
    "attribute*\0attr\0update_current_index\0"
    "index\0remove_entity\0new_entity\0"
    "update_what_is_visible"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_entities_attributes_panel[] = {

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
       1,    0,   49,    2, 0x0a /* Public */,
       3,    1,   50,    2, 0x0a /* Public */,
       5,    1,   53,    2, 0x0a /* Public */,
       8,    1,   56,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x0a /* Public */,
      11,    0,   60,    2, 0x0a /* Public */,
      12,    0,   61,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QModelIndex,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void entities_attributes_panel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        entities_attributes_panel *_t = static_cast<entities_attributes_panel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showMenu(); break;
        case 1: _t->handle_actions((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->remove_attribute((*reinterpret_cast< attribute*(*)>(_a[1]))); break;
        case 3: _t->update_current_index((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 4: _t->remove_entity(); break;
        case 5: _t->new_entity(); break;
        case 6: _t->update_what_is_visible(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        }
    }
}

const QMetaObject entities_attributes_panel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_entities_attributes_panel.data,
      qt_meta_data_entities_attributes_panel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *entities_attributes_panel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *entities_attributes_panel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_entities_attributes_panel.stringdata0))
        return static_cast<void*>(const_cast< entities_attributes_panel*>(this));
    return QWidget::qt_metacast(_clname);
}

int entities_attributes_panel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
