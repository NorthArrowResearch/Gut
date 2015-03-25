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
    CheckRasterManVersion();
    CheckGutVersion();
}

void GutEngine::CheckRasterManVersion(){

    QString sVersion = QString(EXEVERSION);
    QString sLibVersion = QString(Gut::GetLibVersion());

    if (sVersion.compare(sLibVersion, Qt::CaseInsensitive) != 0){
        QString sErr = QString("Rasterman is at: %1, and needs to be %2").arg(sVersion).arg(sLibVersion);
        throw Gut::GutException(RASTERMAN_VERSION, sErr);
    }
}

void GutEngine::CheckGutVersion(){

    QString sVersion = QString(EXEVERSION);
    QString sLibVersion = QString(RasterManager::GetLibVersion());

    if (sVersion.compare(sLibVersion, Qt::CaseInsensitive) != 0){
        QString sErr = QString("Gut Exe is at: %1, Library is at %2").arg(sVersion).arg(sLibVersion);
        throw RasterManager::RasterManagerException(RASTERMAN_VERSION, sErr);
    }
}

int GutEngine::Run(int argc, char *argv[])
{
    // Initialize GDAL drivers
    GDALAllRegister();

    int eResult = Gut::PROCESS_OK;
    if (argc == 5)
    {
        return Gut::RunGut(argv[1]);
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
