/****************************************************************************
** Meta object code from reading C++ file 'inputmanager.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Render/inputmanager.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inputmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSInputManagerENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSInputManagerENDCLASS = QtMocHelpers::stringData(
    "InputManager",
    "deployAffix_signal",
    "",
    "showTowerStatus",
    "std::shared_ptr<Tower>",
    "tower",
    "trigerMenu",
    "QAction*",
    "act",
    "mousePressEvent",
    "QMouseEvent*",
    "event",
    "arrangeMTtower",
    "pos",
    "RTButtonClicked",
    "MTButtonClicked",
    "GigglesChoosed",
    "FlippyChoosed",
    "SplendidChoosed",
    "save",
    "saveMap"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSInputManagerENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x06,    1 /* Public */,
       3,    1,   87,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    1,   90,    2, 0x0a,    4 /* Public */,
       9,    1,   93,    2, 0x0a,    6 /* Public */,
      12,    1,   96,    2, 0x0a,    8 /* Public */,
      14,    0,   99,    2, 0x08,   10 /* Private */,
      15,    0,  100,    2, 0x08,   11 /* Private */,
      16,    0,  101,    2, 0x08,   12 /* Private */,
      17,    0,  102,    2, 0x08,   13 /* Private */,
      18,    0,  103,    2, 0x08,   14 /* Private */,
      19,    0,  104,    2, 0x08,   15 /* Private */,
      20,    0,  105,    2, 0x08,   16 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, QMetaType::QPoint,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject InputManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSInputManagerENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSInputManagerENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSInputManagerENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<InputManager, std::true_type>,
        // method 'deployAffix_signal'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showTowerStatus'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<std::shared_ptr<Tower>, std::false_type>,
        // method 'trigerMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAction *, std::false_type>,
        // method 'mousePressEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QMouseEvent *, std::false_type>,
        // method 'arrangeMTtower'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'RTButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'MTButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'GigglesChoosed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'FlippyChoosed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'SplendidChoosed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'save'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'saveMap'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void InputManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InputManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->deployAffix_signal(); break;
        case 1: _t->showTowerStatus((*reinterpret_cast< std::add_pointer_t<std::shared_ptr<Tower>>>(_a[1]))); break;
        case 2: _t->trigerMenu((*reinterpret_cast< std::add_pointer_t<QAction*>>(_a[1]))); break;
        case 3: _t->mousePressEvent((*reinterpret_cast< std::add_pointer_t<QMouseEvent*>>(_a[1]))); break;
        case 4: _t->arrangeMTtower((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 5: _t->RTButtonClicked(); break;
        case 6: _t->MTButtonClicked(); break;
        case 7: _t->GigglesChoosed(); break;
        case 8: _t->FlippyChoosed(); break;
        case 9: _t->SplendidChoosed(); break;
        case 10: _t->save(); break;
        case 11: _t->saveMap(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (InputManager::*)();
            if (_t _q_method = &InputManager::deployAffix_signal; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (InputManager::*)(std::shared_ptr<Tower> );
            if (_t _q_method = &InputManager::showTowerStatus; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *InputManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InputManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSInputManagerENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int InputManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void InputManager::deployAffix_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void InputManager::showTowerStatus(std::shared_ptr<Tower> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
