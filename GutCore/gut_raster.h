#ifndef GUTRASTER_H
#define GUTRASTER_H
#include "gut_interface.h"
#include "rmoperation.h"

namespace Gut{

enum RasterType{
  RASTER_ORIGINAL,
  RASTER_TEMPORARY,
  RASTER_INTERMEDIATE,
  RASTER_FINAL
};

class GutRaster
{
public:

    // Constructor for simply loading an existing raster
    GutRaster(QString sRasterPath);
    // Constructor for creating one from a rasterman Operation
    GutRaster(RasterType eRasterType, RMOperation stRMOp);
    ~GutRaster();

    inline RMOperation * GetRMOperation(){ return m_RMOperation; }

    inline QString GetPath(){ return m_RasterFilePath; }

    /**
     * @brief GetType
     * @return
     */
    inline RasterType GetType(){ return m_RasterType; }

private:

    // Raster Type
    QString m_RasterFilePath;
    RasterType m_RasterType;
    RMOperation * m_RMOperation;
    bool m_bKeep;

    /**
     * @brief Create
     * @param eRasterType
     * @param eOp
     * @param qlParams
     */
    void Create(RasterType eRasterType, RasterManCMD eOp, QList<QString *> qlParams);

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
