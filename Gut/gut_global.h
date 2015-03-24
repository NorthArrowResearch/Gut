#ifndef GUT_GLOBAL_H
#define GUT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(_WIN32) || defined(_WIN64)
#   ifdef MY_DLL_EXPORT
#       define DLL_API __declspec(dllexport)
#   else
#       define DLL_API __declspec(dllimport)
#   endif
#else
#   define DLL_API
#endif

#endif // GUT_GLOBAL_H






