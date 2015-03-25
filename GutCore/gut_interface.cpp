#define MY_DLL_EXPORT

#include "gut.h"
#include "gut_interface.h"
#include "gut_exception.h"
#include "gut_global.h"

namespace Gut{

DLL_API const char * GetLibVersion(){ return LIBVERSION; }

extern "C" DLL_API int RunGut(const char * psXMLFile){
    int eResult = PROCESS_OK;
    try{
        GutRun theGutRun(psXMLFile);
        eResult = theGutRun.Run();
    }
    catch (GutException& e){
        // At this point there's no XML file loaded so we need to just
        // return an error code
        return e.GetErrorCode();
    }
    catch (std::exception& e){
        eResult = OTHER_ERROR;
    }

    return eResult;
}



extern "C" DLL_API void GetReturnCodeAsString(unsigned int eErrorCode, char * sErr, unsigned int iBufferSize)
{
    const char * pHabErr = GutException::GetReturnCodeOnlyAsString(eErrorCode);
    strncpy(sErr, pHabErr, iBufferSize);
    sErr[ iBufferSize - 1 ] = 0;
}



}
