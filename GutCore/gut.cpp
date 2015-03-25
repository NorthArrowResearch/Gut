#define MY_DLL_EXPORT
#include "gut.h"

namespace Gut{

/* --------------------------------------------------------------- */
/* -- Static Variables need to be instantiated in CPP
      Check .h file for definition.                                */
QHash<EvidenceRaster, GutRaster *> GutRun::m_RasterStore;

/* --------------------------------------------------------------- */

GutRun::GutRun(const char * psXMLInput)
{

}

GutRaster *GutRun::GetRaster(EvidenceRaster eRasterType)
{
    // Go into the raster store and get the raster we want
    return m_RasterStore.find(eRasterType).value();
}

int GutRun::Run()
{
    return PROCESS_OK;
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

}



}
