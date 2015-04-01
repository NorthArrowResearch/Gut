#ifndef UNIT_H
#define UNIT_H
#include <QString>

namespace Gut{

enum GeoUnit{
  TIER2_CUTBANK,
  TIER2_HILLSLOPE_UPLAND_FAN,
  TIER2_FLOODPLAIN,
  TIER2_CHANNEL_MARGIN,

  TIER2_CONVEXITY,
  TIER2_CONCAVITY,
  TIER2_PLANAR,
};

class Unit
{
public:
    Unit();

protected:
    QString m_sName;
    QString m_sSafename;

    // This is the generic way we combine intermediate rasters
    // to get a combined membership raster.
    // (See process 2: Combined membership.
    void CreateEvidenceRaster();

private:
    virtual void Setup()=0;

};

}

#endif // UNIT_H
