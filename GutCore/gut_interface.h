#ifndef GUT_INTERFACE_H
#define GUT_INTERFACE_H

#include "gut_global.h"
#include "gut_exception.h"

namespace Gut{

// Here is a list of evidence rasters we will use.
enum EvidenceRaster{

    // The four original rasters (OR_)
    OR_DEM,
    OR_WATER_EXTENT,
    OR_BANKFULL,
    OR_DETRENDED,

    // These are some intermediate evidence rasters (ER_)
    ER_CHANNEL_MASK,
    ER_SlOPE,
    ER_MEAN_DETRENDED_SLOPE,
    ER_RELIEF,
    ER_BANKFUL_DEPTH,
    ER_BANKFULL_DISTANCE,
    ER_BANKFUL_HEIGHT_ABOVE,
    ER_DETRENDED_STD_DEVIATION,
    ER_INVERSE_FILL,
    ER_DISTANCE_FROM_NON_QUALIFYING_CONCAVITIES,

    // Final Member Rasters (MR_)
    MR_CONCAVITY,
    MR_CONVEXITY,
    MR_ACTIVE_FLOODPLAIN,
    MR_TERRACE,
    MR_PLANAR_RAPID,
    MR_PLANAR_RUNGLIDE,
    MR_HILLSLOPE,
    MR_CUTBANK,
    MR_CHANNEL_MARGIN

};

extern "C" DLL_API const char * GetLibVersion();
extern "C" DLL_API int GutRun(const char * psXMLFile);
extern "C" DLL_API int GutInit(const char * psXMLFile);
extern "C" DLL_API void GetReturnCodeAsString(unsigned int eErrorCode, char * sErr, unsigned int iBufferSize);

}

#endif // GUT_INTERFACE_H
