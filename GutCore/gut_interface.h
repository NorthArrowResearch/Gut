#ifndef GUT_INTERFACE_H
#define GUT_INTERFACE_H

#include "gut_global.h"
#include "gut_exception.h"

namespace Gut{

extern "C" DLL_API const char * GetLibVersion();
extern "C" DLL_API const char * GetReqRMVersion();
extern "C" DLL_API bool CheckRMVersion();

extern "C" DLL_API const char * GetReqGDALVersion();
extern "C" DLL_API bool CheckGDALVersion();

extern "C" DLL_API int RunGut(const char * psXMLFile);
extern "C" DLL_API void GetReturnCodeAsString(unsigned int eErrorCode, char * sErr, unsigned int iBufferSize);

}

#endif // GUT_INTERFACE_H
