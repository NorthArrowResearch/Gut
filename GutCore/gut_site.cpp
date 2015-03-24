#include "gut_site.h"

namespace Gut{

/* --------------------------------------------------------------- */
/* -- Static Variables need to be instantiated in CPP
      Check .h file for definition.                                */
QHash<int, HMVariable *> Project::m_hmvariable_store;

/* --------------------------------------------------------------- */

Site::Site(const char * argv1, const char * argv2, const char * argv3, const char * argv4)
{
}

GutRaster *Site::GetRaster(EvidenceRaster eRasterType)
{

}

int Site::Init()
{

}


Site::~Site()
{
    // Empty the raster store
    QHashIterator<int, GutRaster *> i(m_RasterStore);
    while (i.hasNext()) {
        i.next();
        delete i.value();
    }
    m_RasterStore.clear();

    // Empty the paramter store
    QHashIterator<int, GutParam *> i(m_ParamStore);
    while (i.hasNext()) {
        i.next();
        delete i.value();
    }
    m_ParamStore.clear();
}



}
