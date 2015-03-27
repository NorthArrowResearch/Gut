#ifndef UNIT_H
#define UNIT_H



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

private:

    void CreateEvidenceRaster();
    virtual void Setup()=0;
};

}

#endif // UNIT_H
