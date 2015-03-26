#include "gutengine.h"
#include "gut_exception.h"
#include "gut_interface.h"
#include "rastermanager_exception.h"
#include "rastermanager_interface.h"
#include "gut.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <cstring>
#include <QDebug>
#include <QString>

namespace Gut {

GutEngine::GutEngine()
{
    // GDAL and RM versions are checked

    // The C# needs an integer return but on the console we want to throw
    // an error with a little more evidence.
    QString sErr;

    if (!Gut::CheckGDALVersion()){
        sErr = QString("GDAL is: %1, and needs to be: %2")
                .arg(GDALVersionInfo("RELEASE_NAME") ).arg(Gut::GetReqGDALVersion());
        throw GutException(GDALVERSION, sErr);
    }
//    else if (!Gut::CheckRMVersion()){
//        sErr = QString("Rasterman is: %1, and needs to be %2")
//                .arg(RasterManager::GetLibVersion()).arg(Gut::GetReqRMVersion());
//        throw GutException(RASTERMAN_VERSION, sErr);
//    }
//    else if (!CheckLibersion()){
//        sErr = QString("Exe is at: %1, Library is at %2")
//                .arg(EXEVERSION).arg(Gut::GetLibVersion());
//        throw GutException(LIB_VERSION, sErr);
//    }

}


bool GutEngine::CheckLibersion(){
    return QString(EXEVERSION).compare(Gut::GetLibVersion(), Qt::CaseInsensitive) == 0;
}

int GutEngine::Run(int argc, char *argv[])
{
    // Initialize GDAL drivers
    GDALAllRegister();

    int eResult = Gut::PROCESS_OK;
    if (argc == 2)
    {
        GutRun * theRun = GutRun::Instance();
        theRun->Init(argv[1]);
        return theRun->Run();
    }
    else{
        std::cout << "\n Geomorphic Utilization Tool v"<<EXEVERSION;
        std::cout << "\n    Usage: gut <xml_input_file_path>";
        std::cout << "\n ";
        std::cout << "\n         Arguments:";
        std::cout << "\n                xml_input_file_path: Absolute full path to existing xml gut file.";
        std::cout << "\n";
        return eResult;
    }

    // De-initialize all GDAL drivers.
    GDALDestroyDriverManager();

}




}
