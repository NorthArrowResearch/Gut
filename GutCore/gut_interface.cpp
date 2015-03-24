#define MY_DLL_EXPORT

#include "gut_interface.h"
#include "gut_exception.h"
#include "gut_global.h"
#include "gut_site.h"

namespace Gut{

DLL_API const char * GetLibVersion(){ return LIBVERSION; }

extern "C" DLL_API int GutInit(const char * psXMLFile, const char * psDEMFile){
    int eResult = PROCESS_OK;
    try{
        Site theSite(psXMLFile, psDEMFile, psDEMFile, psDEMFile);
        eResult = theSite.Init();
    }
    catch (GutException& e){
        const QByteArray qbErr = e.GetReturnMsgAsString().toLocal8Bit();
        const char * pHabErr = qbErr.data();
        strncpy(sErr, pHabErr, iBufferSize);
        sErr[ iBufferSize - 1 ] = 0;
        return e.GetErrorCode();
    }
    catch (std::exception& e){
        eResult = OTHER_ERROR;
    }

    return eResult;
}

extern "C" DLL_API int GutRun(const char * psXMLFile){
    int eResult = PROCESS_OK;
    try{
        Site theSite(psXMLFile, psXMLFile, psXMLFile, psXMLFile);
        eResult = theSite.Run();
    }
    catch (GutException& e){
        const QByteArray qbErr = e.GetReturnMsgAsString().toLocal8Bit();
        const char * pHabErr = qbErr.data();
        strncpy(sErr, pHabErr, iBufferSize);
        sErr[ iBufferSize - 1 ] = 0;
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
