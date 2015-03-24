#ifndef GUTRASTER_H
#define GUTRASTER_H
#include "raster.h"
#include "gut_interface.h"

namespace Gut{

class GutRaster
{
public:
    GutRaster();
    ~GutRaster();

    void CreateNormalizedRaster();

    inline EvidenceRaster GetType(){ return m_RasterType; }
    inline RasterManager::Raster * GetBaseRaster(){
            return m_BaseRaster;
    }
    inline RasterManager::Raster * GetNormalizedRaster(){
        if (m_BaseRaster == NULL)
            CreateNormalizedRaster();
        return m_NormRaster;
    }
    inline bool IsInUse(){ return m_bInUse; }

private:
    // Raster Type
    EvidenceRaster m_RasterType;

    bool m_bInUse;

    // Is there a parent?
    GutRaster * m_RasterParent;
    RasterManager::Raster * m_BaseRaster;
    RasterManager::Raster * m_NormRaster;
};

}
#endif // GUTRASTER_H
