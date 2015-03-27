#ifndef GUTRASTER_H
#define GUTRASTER_H
#include "raster.h"
#include "rastermanager_interface.h"
#include "gut_interface.h"

namespace Gut{


enum RasterManOperation{
  RM_SLOPE,
  RM_LINTHRESH,
  RM_INVERT,
  RM_MASKVAL
};

enum RasterType{
  RASTER_ORIGINAL,
  RASTER_TEMPORARY,
  RASTER_INTERMEDIATE,
  RASTER_FINAL
};

class GutRaster
{
public:

    /**
     * @brief GutRaster
     * @param eRasterType
     */
    GutRaster(EvidenceRaster eRasterType);

    /**
     * @brief GutRaster
     * @param eRasterType
     * @param sFilename
     */
    GutRaster(EvidenceRaster eRasterType, QString sFilename);

    ~GutRaster();

    void Init(EvidenceRaster eRasterType);

    /**
     * @brief GetType
     * @return
     */
    inline EvidenceRaster GetType(){ return m_RasterType; }

    /**
     * @brief IsInUse
     * @return
     */
    inline bool IsInUse(){ return m_bInUse; }

private:

    // Raster Type
    QString m_RasterPath;
    EvidenceRaster m_RasterType;

    bool m_bInUse;
    bool m_bKeep;

    RasterManager::Raster * m_BaseRaster;
    RasterManager::Raster * m_NormRaster;

    QList<QString *> m_TemporaryRasters;
    QList<QString *> m_CombinationMembership;

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
