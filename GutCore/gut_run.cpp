#define MY_DLL_EXPORT
#include "gut_run.h"
#include <QDebug>

namespace Gut{

/* --------------------------------------------------------------- */
/* -- Static Variables need to be instantiated in CPP
      Check .h file for definition.                                */
//GutRun * GutRun::m_pInstance = NULL;
/* --------------------------------------------------------------- */

void GutRun::Init(const char * psXMLInput)
{
    m_XML_Inputs = new XMLFile(psXMLInput, INPUT_FILE);
    m_elConf = m_XML_Inputs->Document();

    // First thing first: we need to get the log file location and the
    // Output dir.
    QString sDir = GetInputParamText("outputs", "dir");
    QString sTempDir = GetInputParamText("outputs", "tempdir");
    QString sLog = GetInputParamText("outputs", "log");
    QString sResults = GetInputParamText("outputs", "results");

    // Set the output path first
    qdOutputDir = QDir(sDir);
    qdTempDir = QDir(sTempDir);

    m_XML_Results = new XMLFile(qdOutputDir.filePath(sResults), RESULTS_FILE);
    m_XML_Logs = new XMLFile(qdOutputDir.filePath(sLog), LOG_FILE);

    // By default we clean up our temporary files but we can choose to retain them.
    bCleanTMP = true;
    QString sKeepTmp = GetInputParamText("visit", "clean");
    if (sKeepTmp.compare("false",Qt::CaseInsensitive) == 0)
        bCleanTMP = false;

    // Now set up a temporary Folder inside 'qdTempDir' for storing Rasters
    qdGutRunTempDir = QDir(qdTempDir.absoluteFilePath( XMLFile::GetTmpFolderName("_GUT_RUN", 8) ) );

    // Make a path if we don't have one already.
    if (!qdGutRunTempDir.exists()){
      qdGutRunTempDir.mkpath(".");
    }
    else{
        throw GutException(PATH_ERROR, QString("Temp folder collision: %1").arg(qdGutRunTempDir.absolutePath()) );
    }
}

void GutRun::InitCheck(){
    if (m_XML_Inputs == NULL)
        throw GutException(INIT_ERROR);
}

GutRun::GutRun()
{
    m_XML_Results = NULL;
    m_XML_Logs = NULL;
    m_XML_Inputs = NULL;
}

void GutRun::Run(const char * psXMLInput)
{
    Init(psXMLInput);
    InitCheck(); // Make sure this singleton class has been initialized properly.
    LoadSourceRasters();
    CreateUnits();
    CombineUnits();
    ClassifyUnits();
}

void GutRun::CreateUnits(){
    m_UnitStore.append(new UnitHSUplFan());
}

void GutRun::CombineUnits(){
    // TODO: EVerything
}

void GutRun::ClassifyUnits(){
    // TODO: EVerything
}

void GutRun::LoadSourceRasters(){

    // Kick-Start the process with the original 4 Rasters we can't derive.
    m_RasterStore.push_back(new GutRaster(GetSourceRasterPath("dem") ) );
    m_RasterStore.push_back(new GutRaster(GetSourceRasterPath("waterextent") ) );
    m_RasterStore.push_back(new GutRaster(GetSourceRasterPath("bankfull") ) );
    m_RasterStore.push_back(new GutRaster(GetSourceRasterPath("detrended") ) );

}


QString GutRun::GetInputParamText(QString containerName, QString tagName){

    QDomNodeList elOutputContainer = m_elConf->elementsByTagName(containerName);
    QString msg;

    if (elOutputContainer.length() == 0){
        msg = QString("Could not find <%1> container within input xml file")
                .arg(containerName);
        throw GutException(INPUT_FILE_ERROR, msg);
    }
    QDomNodeList elOutputs = elOutputContainer.at(0).childNodes();

    for(int n= 0; n < elOutputs.length(); n++){
        QDomElement elOutput = elOutputs.at(n).toElement();
        if (elOutput.tagName().compare(tagName, Qt::CaseInsensitive) == 0){
            if (elOutput.text().length() == 0){
                msg = QString("<%1> inside <%2> was blank")
                        .arg(tagName).arg(containerName);
                throw GutException(INPUT_FILE_ERROR, msg);
            }
            else{
                return elOutput.text();
            }
        }
    }

    msg = QString("Could not find <%1> inside <%2> tag within input xml file")
            .arg(tagName).arg(containerName);
    throw GutException(INPUT_FILE_ERROR, msg);

}


QString GutRun::GetSourceRasterPath(QString sType){

    QDomNodeList elOutputContainer = m_elConf->elementsByTagName("inputs");
    QString msg;

    if (elOutputContainer.length() == 0){
        msg = QString("Could not find <inputs> container within input xml file");
        throw GutException(INPUT_FILE_ERROR, msg);
    }
    QDomNodeList elRasters = elOutputContainer.at(0).childNodes();

    for(int n= 0; n < elRasters.length(); n++){
        QDomElement elRaster = elRasters.at(n).toElement();

        if (elRaster.tagName().compare("raster", Qt::CaseInsensitive) == 0){
            QDomNodeList dlType = elRaster.elementsByTagName("type");
            if (dlType.length() != 0){
                QDomElement elType = dlType.at(0).toElement();
                if (elType.text().compare(sType, Qt::CaseInsensitive) == 0){
                    QDomNodeList dlPath = elRaster.elementsByTagName("path");
                    if (dlPath.length() != 0){
                        QDomElement elPath = dlPath.at(0).toElement();
                        if (elPath.text().compare("", Qt::CaseInsensitive) == 0 || !QFileInfo(elPath.text()).exists()){
                            msg = QString("raster: %1 does not exist at path: %2" )
                                    .arg(sType).arg(elPath.text());
                            throw GutException(INPUT_FILE_ERROR, msg);
                        }
                        return elPath.text();

                    }
                    else{
                        msg = QString("<path> tage missing for raster: %1")
                                .arg(sType);
                        throw GutException(INPUT_FILE_ERROR, msg);
                    }
                }
            }
        }
    }

    msg = QString("Could not find path to raster: %1 input xml file")
            .arg(sType);
    throw GutException(INPUT_FILE_ERROR, msg);

}

QString GutRun::BaseFileNameAppend(QString sFullFilePath, QString sAppendStr){

    QFileInfo sNewFileInfo(sFullFilePath);
    QString sFilePath = sNewFileInfo.absolutePath();
    QString sBaseName = sNewFileInfo.baseName();
    QString sSuffix = sNewFileInfo.completeSuffix();

    QString newPath = QDir(sFilePath).absoluteFilePath( sBaseName + sAppendStr + QString(".") + sSuffix);

    return newPath;
}

GutRaster * GutRun::GetCreateRaster(RasterType eRasterType, RMOperation rmOperation)
{
    bool bFound = false;
    GutRaster * theRaster;
    foreach(GutRaster * gRaster, m_RasterStore)
    {
        if (gRaster->GetType() == eRasterType &&
                *gRaster->GetRMOperation() == rmOperation){
            theRaster = gRaster;
            bFound = true;
            break;
        }
    }

    // If not found then we make it.
    if (!bFound){
        theRaster = new GutRaster(eRasterType, rmOperation);

        // The farther down the process we are the least general re-use there should be
        // so "push_back" is the right choice.
        m_RasterStore.push_back(theRaster);
    }

    return theRaster;
}

GutRun::~GutRun()
{
    qDebug()<< "DESTRUCTOR";

    // Clean up the TMP folder if it is needed
    // We're deletign a folder here so we need some sanity checks so there's
    // No chance of deleting someone's root folder.
    if (qdGutRunTempDir.exists() && qdGutRunTempDir.absolutePath().length() > 10){
        if (!qdGutRunTempDir.removeRecursively()){
            throw GutException(PATH_ERROR, QString("Error removing path: %1").arg(qdGutRunTempDir.absolutePath()) );
        }
    }

    qDeleteAll(m_RasterStore);

    if (m_XML_Inputs != NULL)
        delete m_XML_Inputs;
    if (m_XML_Logs != NULL)
        delete m_XML_Logs;
    if (m_XML_Results != NULL)
        delete m_XML_Results;
}

}
