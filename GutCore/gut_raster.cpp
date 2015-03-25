#include "gut_raster.h"

namespace Gut{

GutRaster::GutRaster(EvidenceRaster eRasterType, QString sFilename){

}

GutRaster::~GutRaster()
{

}

GutRaster::GutRaster(EvidenceRaster eRasterType)
{
    m_RasterParent = NULL;
    m_NormRaster = NULL;
    m_BaseRaster = NULL;
    m_bInUse = true;
    m_RasterType = eRasterType;
}

int GutRaster::CreateChannelMask(){
    return PROCESS_OK;
}
int GutRaster::CreateSlope(){
    return PROCESS_OK;
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
