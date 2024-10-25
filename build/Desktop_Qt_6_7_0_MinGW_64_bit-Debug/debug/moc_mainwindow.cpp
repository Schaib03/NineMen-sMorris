/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSMainWindowENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSMainWindowENDCLASS = QtMocHelpers::stringData(
    "MainWindow",
    "restartConfirmed",
    "",
    "quitConfirmed",
    "goToPlayMenu",
    "startGame",
    "GameMode",
    "pauseGame",
    "quitGamePrompt",
    "goToHistory",
    "goToSettings",
    "backToMainMenu",
    "restartGamePrompt",
    "restartGame",
    "resumeGame",
    "loadGame",
    "saveGame"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSMainWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x06,    1 /* Public */,
       3,    0,   99,    2, 0x06,    2 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,  100,    2, 0x0a,    3 /* Public */,
       5,    3,  101,    2, 0x0a,    4 /* Public */,
       7,    0,  108,    2, 0x0a,    8 /* Public */,
       8,    0,  109,    2, 0x0a,    9 /* Public */,
       9,    0,  110,    2, 0x0a,   10 /* Public */,
      10,    0,  111,    2, 0x0a,   11 /* Public */,
      11,    0,  112,    2, 0x0a,   12 /* Public */,
      12,    0,  113,    2, 0x0a,   13 /* Public */,
      13,    0,  114,    2, 0x0a,   14 /* Public */,
      14,    0,  115,    2, 0x0a,   15 /* Public */,
      15,    1,  116,    2, 0x0a,   16 /* Public */,
      16,    0,  119,    2, 0x0a,   18 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_CLASSMainWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSMainWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSMainWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>,
        // method 'restartConfirmed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quitConfirmed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goToPlayMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'startGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<GameMode, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'pauseGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'quitGamePrompt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goToHistory'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'goToSettings'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'backToMainMenu'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'restartGamePrompt'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'restartGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resumeGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'saveGame'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->restartConfirmed(); break;
        case 1: _t->quitConfirmed(); break;
        case 2: _t->goToPlayMenu(); break;
        case 3: _t->startGame((*reinterpret_cast< std::add_pointer_t<GameMode>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3]))); break;
        case 4: _t->pauseGame(); break;
        case 5: _t->quitGamePrompt(); break;
        case 6: _t->goToHistory(); break;
        case 7: _t->goToSettings(); break;
        case 8: _t->backToMainMenu(); break;
        case 9: _t->restartGamePrompt(); break;
        case 10: _t->restartGame(); break;
        case 11: _t->resumeGame(); break;
        case 12: _t->loadGame((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 13: _t->saveGame(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::restartConfirmed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (_t _q_method = &MainWindow::quitConfirmed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSMainWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::restartConfirmed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::quitConfirmed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
