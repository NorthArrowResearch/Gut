#define MY_DLL_EXPORT
#include "gut.h"
#include <QDebug>

namespace Gut{

/* --------------------------------------------------------------- */
/* -- Static Variables need to be instantiated in CPP
      Check .h file for definition.                                */
GutRun * GutRun::m_pInstance = NULL;
/* --------------------------------------------------------------- */

GutRun * GutRun::Instance(const char * psXMLInput)
{
   if (!m_pInstance)   // Only allow one instance of class to be generated.
      m_pInstance = new GutRun(psXMLInput);

   return m_pInstance;
}

GutRun::GutRun(const char * psXMLInput)
{
    m_XML_Results = NULL;
    m_XML_Logs = NULL;
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


QString GutRun::BaseFileNameAppend(QString sFullFilePath, QString sAppendStr){

    QFileInfo sNewFileInfo(sFullFilePath);
    QString sFilePath = sNewFileInfo.absolutePath();
    QString sBaseName = sNewFileInfo.baseName();
    QString sSuffix = sNewFileInfo.completeSuffix();

    QString newPath = QDir(sFilePath).absoluteFilePath( sBaseName + sAppendStr + QString(".") + sSuffix);

    return newPath;
}

GutRaster * GutRun::GetRaster(EvidenceRaster eRasterType)
{
    // Go into the raster store and get the raster we want
    return m_RasterStore.find(eRasterType).value();
}

int GutRun::Run()
{

    qDebug() << "asdfasDFASDFASDFASDFASDFASDFSA";
    return PROCESS_OK;
}

GutRun::~GutRun()
{
    // Empty the raster store
    QHashIterator<EvidenceRaster, GutRaster *> i(m_RasterStore);
    while (i.hasNext()) {
        i.next();
        delete i.value();
    }
    m_RasterStore.clear();

    if (m_XML_Inputs != NULL)
        delete m_XML_Inputs;
    if (m_XML_Logs != NULL)
        delete m_XML_Logs;
    if (m_XML_Results != NULL)
        delete m_XML_Results;

}



}
