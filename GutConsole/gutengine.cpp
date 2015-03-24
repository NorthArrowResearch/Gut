#include "gutengine.h"
#include "gut_exception.h"
#include "rastermanager_exception.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <cstring>
#include <QDebug>

namespace Gut {

GutEngine::GutEngine()
{
    CheckRasterManVersion();
    CheckGutVersion();
}

void GutEngine::CheckRasterManVersion(){

    QString sVersion = QString(EXEVERSION);
    QString sLibVersion = QString(Gut::GetLibVersion());
    Gut::
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

    int eResult = HabitatModel::PROCESS_OK;
    if (argc == 2)
    {
        eResult = GutRun(argc, argv);
        return eResult;
    }
    if (argc == 5)
    {
        eResult = GutInit(argc, argv);
        return eResult;
    }
    else{
        std::cout << "\n Geomorphic Utilization Tool v"<<VERSION;
        std::cout << "\n    Initializing: gut <root_project_path> <xml_input_def_file_path> <xml_input_conf_file_path> <xml_output_file_path>";
        std::cout << "\n ";
        std::cout << "\n        Arguments:";
        std::cout << "\n                  root_project_path: Absolute full path to existing project folder.";
        std::cout << "\n            xml_input_def_file_path: Absolute full path to existing xml definitions file.";
        std::cout << "\n           xml_input_conf_file_path: Absolute full path to existing xml configuration file.";
        std::cout << "\n               xml_output_file_path: Absolute full path to desired xml output file.";
        std::cout << "\n ";
        std::cout << "\n    Running: gut <xml_input_file_path>";
        std::cout << "\n ";
        std::cout << "\n         Arguments:";
        std::cout << "\n                xml_input_file_path: Absolute full path to existing xml gut file.";
        std::cout << "\n";
        return eResult;
    }
}

int GutEngine::GutInit(int argc, char *argv[])
{
    int eResult = HabitatModel::PROCESS_OK;

    // Initialize GDAL drivers
    GDALAllRegister();

    HabitatModel::Project theProject(argv[1], argv[2], argv[3], argv[4]);
    eResult = theProject.Run();

    // De-initialize all GDAL drivers.
    GDALDestroyDriverManager();

    return eResult;
}


int GutEngine::GutRun(int argc, char *argv[])
{
    int eResult = HabitatModel::PROCESS_OK;

    // Initialize GDAL drivers
    GDALAllRegister();

    Gut::Project theProject(argv[1], argv[2], argv[3], argv[4]);
    eResult = theProject.Run();

    // De-initialize all GDAL drivers.
    GDALDestroyDriverManager();

    return eResult;
}



}
