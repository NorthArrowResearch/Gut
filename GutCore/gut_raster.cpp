#include "gut_raster.h"
#include "gut.h"

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
    m_RasterParent = NULL;
    m_NormRaster = NULL;
    m_BaseRaster = NULL;
    m_bInUse = true;
}

RasterManager::Raster * GutRaster::GetBaseRaster()
{
    if (m_BaseRaster == NULL)
        CreateBaseRaster();
    return m_BaseRaster;
}

RasterManager::Raster *GutRaster::GetNormalizedRaster()
{
    if (m_BaseRaster == NULL)
        CreateNormalizedRaster();
    return m_NormRaster;
}

GutRaster::~GutRaster()
{
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

// -------------------------------------------------------------------------------------------
//  Everything below here is simply stringing together RasterManagerCommands to get an evidence Raster
// -------------------------------------------------------------------------------------------

int GutRaster::CreateChannelMask(){
    return PROCESS_OK;
}
int GutRaster::CreateSlope(){
    m_RasterPath = CreateOutputRasterPath("INT_Slope-", "tif", true);
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
    RasterManager::Raster * rDetrended = GutRun::Instance()->GetRaster(OR_DEM)->GetBaseRaster();
    m_RasterPath = CreateOutputRasterPath("ER-ActiveFloodPlain", "tif", false);
    const QByteArray psFilename = m_RasterPath.toLocal8Bit();
    int eResult = RasterManager::CreateSlope(rDetrended->FilePath(),
                                      psFilename.data(),
                                      RasterManager::SLOPE_DEGREES);

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
