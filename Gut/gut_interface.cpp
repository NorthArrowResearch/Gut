#include "gut_interface.h"
#include "gut_exception.h"
#include "gut_global.h"

namespace Gut{

DLL_API const char * GetLibVersion(){ return LIBVERSION; }

extern "C" DLL_API int GutRun(const char * psXMLFile){
    int eResult = PROCESS_OK;
    try{
        HabitatModel::Project theProject(psProjectRoot, psXMLInputDef, psXMLInputConf, psXMLOutput);
        eResult = theProject.Run();
    }
    catch (HabitatException& e){
        const QByteArray qbErr = e.GetReturnMsgAsString().toLocal8Bit();
        const char * pHabErr = qbErr.data();
        strncpy(sErr, pHabErr, iBufferSize);
        sErr[ iBufferSize - 1 ] = 0;
        return e.GetErrorCode();
    }
    catch (std::exception& e){
        eResult = UNDEFINED_ERROR;
    }

    return eResult;
}

extern "C" DLL_API int GutInit(const char * psXMLFile){
    int eResult = PROCESS_OK;
    try{
        HabitatModel::Project theProject(psProjectRoot, psXMLInputDef, psXMLInputConf, psXMLOutput);
        eResult = theProject.Run();
    }
    catch (HabitatException& e){
        const QByteArray qbErr = e.GetReturnMsgAsString().toLocal8Bit();
        const char * pHabErr = qbErr.data();
        strncpy(sErr, pHabErr, iBufferSize);
        sErr[ iBufferSize - 1 ] = 0;
        return e.GetErrorCode();
    }
    catch (std::exception& e){
        eResult = UNDEFINED_ERROR;
    }

    return eResult;
}

extern "C" DLL_API void GetReturnCodeAsString(unsigned int eErrorCode, char * sErr, unsigned int iBufferSize)
{
    const char * pHabErr = Gut::GetReturnCodeOnlyAsString(eErrorCode);
    strncpy(sErr, pHabErr, iBufferSize);
    sErr[ iBufferSize - 1 ] = 0;
}



}
