#ifndef GUT_INTERFACE_H
#define GUT_INTERFACE_H

#include "gut_global.h"
#include "gut_exception.h"

namespace Gut{

enum EvidenceRasters{
    ER_SlOPE
};

extern "C" DLL_API const char * GetLibVersion();
extern "C" DLL_API int GutRun(const char * psXMLFile);
extern "C" DLL_API int GutInit(const char * psXMLFile);
extern "C" DLL_API void GetReturnCodeAsString(unsigned int eErrorCode, char * sErr, unsigned int iBufferSize);

}

#endif // GUT_INTERFACE_H
