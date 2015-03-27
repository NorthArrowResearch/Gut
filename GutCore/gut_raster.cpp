#include "gut_raster.h"
#include "gut_run.h"

namespace Gut{

GutRaster::GutRaster(EvidenceRaster eRasterType, QString sFilename){
    Init(eRasterType);
    m_RasterPath = sFilename;
    const QByteArray qbFileName = sFilename.toLocal8Bit();
    m_BaseRaster = new RasterManager::Raster(qbFileName.data());
}

GutRaster::GutRaster(EvidenceRaster eRasterType){
    Init(eRasterType);
}

void GutRaster::Init(EvidenceRaster eRasterType){
    m_RasterType = eRasterType;
    m_NormRaster = NULL;
    m_BaseRaster = NULL;
    m_bInUse = true;
}


GutRaster::~GutRaster(){
    if (m_BaseRaster != NULL)
        delete m_BaseRaster;
    if (m_NormRaster != NULL)
        delete m_NormRaster;
}

QString GutRaster::CreateOutputRasterPath(QString sPathPrefix, QString sSuffix, bool bTmpDir){
    QString sDir = "";
    if (bTmpDir)
        sDir = GutRun::Instance()->GetTempDir();
    else
        sDir = GutRun::Instance()->GetOutputDir();

    return QDir(sDir).filePath(sPathPrefix + QString(".") + sSuffix );
}





}
