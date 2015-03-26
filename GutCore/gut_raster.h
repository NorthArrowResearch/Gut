#ifndef GUTRASTER_H
#define GUTRASTER_H
#include "raster.h"
#include "rastermanager_interface.h"
#include "gut_interface.h"

namespace Gut{

class GutRaster
{
public:

    GutRaster(EvidenceRaster eRasterType);

    GutRaster(EvidenceRaster eRasterType, QString sFilename);

    ~GutRaster();

    void Init(EvidenceRaster eRasterType);

    /**
     * @brief CreateNormalizedRaster
     * @return
     */
    int CreateNormalizedRaster(){
        return PROCESS_OK;
    }

    /**
     * @brief GetType
     * @return
     */
    inline EvidenceRaster GetType(){ return m_RasterType; }

    /**
     * @brief GetBaseRaster
     * @return
     */
    RasterManager::Raster * GetBaseRaster();

    /**
     * @brief GetNormalizedRaster
     * @return
     */
    RasterManager::Raster * GetNormalizedRaster();

    /**
     * @brief IsInUse
     * @return
     */
    inline bool IsInUse(){ return m_bInUse; }

    /**
     * @brief CreateBaseRaster just choosing which create function to run
     * @return
     */
    inline int CreateBaseRaster()
    {
        // First disallow anything that cannot be derived.
        switch (m_RasterType) {
        case OR_DEM: return INPUT_FILE_CANNOT_BE_MADE; break;
        case OR_WATER_EXTENT: return INPUT_FILE_CANNOT_BE_MADE; break;
        case OR_BANKFULL: return INPUT_FILE_CANNOT_BE_MADE; break;
        case OR_DETRENDED: return INPUT_FILE_CANNOT_BE_MADE; break;
            // Also what happens if the type hasn't been set.
        case ER_NONE: return INPUT_FILE_NOT_VALID; break;
        default: break;
        }

        switch (m_RasterType) {
        case ER_CHANNEL_MASK:
            return CreateChannelMask();
            break;
        case ER_SlOPE:
            return CreateSlope();
            break;
        case ER_MEAN_DETRENDED_SLOPE:
            return CreateMeanDetrendedSlope();
            break;
        case ER_RELIEF:
            return CreateRelief();
            break;
        case ER_BANKFUL_DEPTH:
            return CreateBankfullDepth();
            break;
        case ER_BANKFULL_DISTANCE:
            return CreateBankFullDistance();
            break;
        case ER_BANKFUL_HEIGHT_ABOVE:
            return CreateBankFullHeightAbove();
            break;
        case ER_DETRENDED_STD_DEVIATION:
            return CreateDetrendedStdDeviation();
            break;
        case ER_INVERSE_FILL:
            return CreateInverseFill();
            break;
        case ER_DISTANCE_FROM_NON_QUALIFYING_CONCAVITIES:
            return CreateDistanceFromNonConcavities();
            break;
        case MR_CONCAVITY:
            return CreateConcavity();
            break;
        case MR_CONVEXITY:
            return CreateConvexity();
            break;
        case MR_ACTIVE_FLOODPLAIN:
            return CreateActiveFloodPlain();
            break;
        case MR_TERRACE:
            return CreateTerrace();
            break;
        case MR_PLANAR_RAPID:
            return CreatePlanarRapid();
            break;
        case MR_PLANAR_RUNGLIDE:
            return CreatePlanarRunglide();
            break;
        case MR_HILLSLOPE:
            return CreateHillSlope();
            break;
        case MR_CUTBANK:
            return CreateCutBank();
            break;
        case MR_CHANNEL_MARGIN:
            return CreateChannelMargin();
            break;
        default:
            break;
        }
        return PROCESS_OK;
    }


private:
    // Each function runs the Rasterman Tasks Necessary to create a raster
    int CreateChannelMask();
    int CreateSlope();
    int CreateMeanDetrendedSlope();
    int CreateRelief();
    int CreateBankfullDepth();
    int CreateBankFullDistance();
    int CreateBankFullHeightAbove();
    int CreateDetrendedStdDeviation();
    int CreateInverseFill();
    int CreateDistanceFromNonConcavities();
    int CreateConcavity();
    int CreateConvexity();
    int CreateActiveFloodPlain();
    int CreateTerrace();
    int CreatePlanarRapid();
    int CreatePlanarRunglide();
    int CreateHillSlope();
    int CreateCutBank();
    int CreateChannelMargin();

    // Raster Type
    QString m_RasterPath;
    EvidenceRaster m_RasterType;
    bool m_bInUse;

    // Is there a parent?
    GutRaster * m_RasterParent;
    RasterManager::Raster * m_BaseRaster;
    RasterManager::Raster * m_NormRaster;

    /**
     * @brief CreateOutputRasterPath
     * @param sPathPrefix
     * @param sSuffix
     * @param bTmpDir
     * @return
     */
    QString CreateOutputRasterPath(QString sPathPrefix, QString sSuffix, bool bTmpDir);
};

}
#endif // GUTRASTER_H
