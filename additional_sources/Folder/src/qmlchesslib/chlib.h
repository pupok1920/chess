#ifndef CHLIB_H
#define CHLIB_H

#include <QtGlobal>

#if defined QMLCHESSLIB
 #define QMLCHESSLIB_COMMON_DLLSPEC Q_DECL_EXPORT
#else
 #define QMLCHESSLIB_COMMON_DLLSPEC Q_DECL_IMPORT
#endif

#endif