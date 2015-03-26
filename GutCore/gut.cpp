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

GutRaster * GutRun::GetRaster(EvidenceRaster eRasterType)
{
    // Go into the raster store and get the raster we want
    return m_RasterStore.find(eRasterType).value();
}

int GutRun::Run()
{
    LoadSourceRasters();
    MakeEvidenceRasters();
    return PROCESS_OK;
}

void GutRun::LoadSourceRasters(){

    // Start with the original 4 Rasters.
    m_RasterStore.insert(OR_DEM, new GutRaster(OR_DEM,  GetSourceRasterPath("dem") ) );
    m_RasterStore.insert(OR_WATER_EXTENT, new GutRaster(OR_WATER_EXTENT, GetSourceRasterPath("waterextent") ) );
    m_RasterStore.insert(OR_BANKFULL, new GutRaster(OR_BANKFULL, GetSourceRasterPath("bankfull") ) );
    m_RasterStore.insert(OR_DETRENDED, new GutRaster(OR_DETRENDED, GetSourceRasterPath("detrended") ) );
}

void GutRun::MakeEvidenceRasters(){

    // The middle rasters are created automatically.

    // Generate the evidence Rasters one-by-one
//    m_RasterStore.insert(MR_CONCAVITY, new GutRaster(MR_CONCAVITY));
//    m_RasterStore.insert(MR_CONVEXITY, new GutRaster(MR_CONVEXITY));
    m_RasterStore.insert(MR_ACTIVE_FLOODPLAIN, new GutRaster(MR_ACTIVE_FLOODPLAIN));
//    m_RasterStore.insert(MR_TERRACE, new GutRaster(MR_TERRACE));
//    m_RasterStore.insert(MR_PLANAR_RAPID, new GutRaster(MR_PLANAR_RAPID));
//    m_RasterStore.insert(MR_PLANAR_RUNGLIDE, new GutRaster(MR_PLANAR_RUNGLIDE));
//    m_RasterStore.insert(MR_HILLSLOPE, new GutRaster(MR_HILLSLOPE));
//    m_RasterStore.insert(MR_CUTBANK, new GutRaster(MR_CUTBANK));
//    m_RasterStore.insert(MR_CHANNEL_MARGIN, new GutRaster(MR_CHANNEL_MARGIN));

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
