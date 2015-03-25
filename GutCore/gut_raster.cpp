#include "gut_raster.h"

namespace Gut{

GutRaster::GutRaster(EvidenceRaster eRasterType, const char * sFilename){
    Init(eRasterType);
    m_RasterPath = QString(sFilename);
    m_BaseRaster = new RasterManager::Raster(sFilename);
}

GutRaster::GutRaster(EvidenceRaster eRasterType){
    Init(eRasterType);
}

void GutRaster::Init(EvidenceRaster eRasterType){
    m_RasterType = eRasterType;
    m_RasterParent = NULL;
    m_NormRaster = NULL;
    m_BaseRaster = NULL;
    m_bInUse = true;
}

GutRaster::~GutRaster()
{
    if (m_BaseRaster != NULL)
        delete m_BaseRaster;
    if (m_NormRaster != NULL)
        delete m_NormRaster;
}

QString GutRaster::GetOutputPath(QString sPathPrefix){
    return "";
}

int GutRaster::CreateChannelMask(){
    return PROCESS_OK;
}
int GutRaster::CreateSlope(){
    m_RasterPath = GetOutputPath("INT_Slope-");
    const QByteArray psFilename = m_RasterPath.toLocal8Bit();
    return RasterManager::CreateSlope(psFilename.data(), psFilename.data(), RasterManager::SLOPE_DEGREES);
}
int GutRaster::CreateMeanDetrendedSlope(){
    return PROCESS_OK;
}
int GutRaster::CreateRelief(){
    return PROCESS_OK;
}
int GutRaster::CreateBankfullDepth(){
    return PROCESS_OK;
}
int GutRaster::CreateBankFullDistance(){
    return PROCESS_OK;
}
int GutRaster::CreateBankFullHeightAbove(){
    return PROCESS_OK;
}
int GutRaster::CreateDetrendedStdDeviation(){
    return PROCESS_OK;
}
int GutRaster::CreateInverseFill(){
    return PROCESS_OK;
}
int GutRaster::CreateDistanceFromNonConcavities(){
    return PROCESS_OK;
}
int GutRaster::CreateConcavity(){
    return PROCESS_OK;
}
int GutRaster::CreateConvexity(){
    return PROCESS_OK;
}
int GutRaster::CreateActiveFloodPlain(){
    return PROCESS_OK;
}
int GutRaster::CreateTerrace(){
    return PROCESS_OK;
}
int GutRaster::CreatePlanarRapid(){
    return PROCESS_OK;
}
int GutRaster::CreatePlanarRunglide(){
    return PROCESS_OK;
}
int GutRaster::CreateHillSlope(){
    return PROCESS_OK;
}
int GutRaster::CreateCutBank(){
    return PROCESS_OK;
}
int GutRaster::CreateChannelMargin(){
    return PROCESS_OK;
}

}
