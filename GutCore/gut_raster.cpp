#include "gut_raster.h"
#include "gut_run.h"

namespace Gut{

GutRaster::GutRaster(QString sFilename){
    m_RasterType = RASTER_ORIGINAL;

    m_RasterPath = sFilename;
    m_RMOperation = NULL;
}

GutRaster::GutRaster(RasterType eRasterType, RMOperation stRMOp){

}

void GutRaster::Create(RasterType eRasterType, RasterManCMD eOp, QList<QString *> qlParams)
{
    switch (eRasterType) {
    case RASTER_ORIGINAL: break;
    case RASTER_TEMPORARY: break;
    case RASTER_INTERMEDIATE: break;
    case RASTER_FINAL: break;
    default:
        throw GutException(RASTER_TYPE, QString("Could not understand Raster Type: %1").arg(eRasterType));
        break;
    }
}


GutRaster::~GutRaster(){

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
