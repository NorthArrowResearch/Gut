#define MY_DLL_EXPORT

#include "gut.h"
#include "gut_interface.h"
#include "gut_exception.h"
#include "gut_global.h"

namespace Gut{

DLL_API const char * GetLibVersion(){ return GUTLIBVERSION; }

DLL_API bool CheckRMVersion(){
    QString sReqdVersion = QString(MINRASTERMAN);
    QString sLibVersion = QString(RasterManager::GetLibVersion());
    return sReqdVersion.compare(sLibVersion, Qt::CaseInsensitive) == 0;
}

DLL_API const char * GetReqRMVersion(){
    QString version = QString(MINRASTERMAN);
    const QByteArray qbVersion = version.toLocal8Bit();
    return qbVersion.data();
}

DLL_API const char * GetReqGDALVersion(){
    QString version = QString("%1.%2").arg(GDALMAJ).arg(GDALMIN);
    const QByteArray qbVersion = version.toLocal8Bit();
    return qbVersion.data();
}

DLL_API bool CheckGDALVersion(){
    QString vMaj = QString(GDALMAJ);
    QString vMin = QString(GDALMIN);

    return GDALCheckVersion(vMaj.toInt(), vMin.toInt(), NULL);
}

extern "C" DLL_API int RunGut(const char * psXMLFile){
    int eResult = PROCESS_OK;
    try{        
        GutRun * theRun = GutRun::Instance();
        theRun->Init(psXMLFile);
        eResult = theRun->Run();
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
