#include "gut_raster.h"
#include "gut_run.h"
#include "unit_hsuplfan.h"

namespace Gut{

UnitHSUplFan::UnitHSUplFan()
{
    // Set some constants
    m_sName = "Hillslope/Upland/Fan";
    m_sSafename = "HSUplFan";
    Setup();
    // We give the option in the child class in case we have to write our own for
    // a special case
    CreateEvidenceRaster();
}

void UnitHSUplFan::Setup()
{
    double dBankFullWidth = 1; // TODO: NEED TO GET THIS

    // Set up the Parameters for the linear threasholding commands
    // that RasterManager needs to run.
    QList<QString> qlParamsBFThresh = QList<QString>()
            << "0" << QString::number(EvidenceMinProb)
            << "0" << QString::number(EvidenceMaxProb);

    QList<QString> qlParamsMDThresh = QList<QString>()
            << "10" << QString::number(EvidenceMinProb)
            << "15" << QString::number(EvidenceMaxProb);

    QList<QString> qlParamsBFDThresh = QList<QString>()
            << QString::number(0.2 * dBankFullWidth) << QString::number(EvidenceMinProb)
            << QString::number(0.1 * dBankFullWidth) << QString::number(EvidenceMaxProb);

    QList<QString> qlParamsReliefThresh = QList<QString>()
            << "0.8"<< QString::number(EvidenceMinProb)
            << "1.0"<< QString::number(EvidenceMaxProb);

    // Now either retrieve or create the Rasters.
    GutRaster * grBFThresh     = GutRaster::GetOrCreateRaster(RASTER_INTERMEDIATE, RM_LINTHRESH,
                                                              GutRaster::GetOriginalRaster(RM_BANKFULL),
                                                              "BF_Threshold",
                                                              &qlParamsBFThresh);
    GutRaster * grMDThresh     = GutRaster::GetOrCreateRaster(RASTER_INTERMEDIATE, RM_LINTHRESH,
                                                              GutRaster::GetOriginalRaster(RM_BANKFULL),
                                                              "Mean_Detrended_Slope_Threshold",
                                                              &qlParamsMDThresh);
    GutRaster * grBFDThresh    = GutRaster::GetOrCreateRaster(RASTER_INTERMEDIATE, RM_LINTHRESH,
                                                              GutRaster::GetOriginalRaster(RM_BANKFULL),
                                                              "Relief_Threshold",
                                                              &qlParamsBFDThresh);
    GutRaster * grReliefThresh = GutRaster::GetOrCreateRaster(RASTER_INTERMEDIATE, RM_LINTHRESH,
                                                              GutRaster::GetOriginalRaster(RM_BANKFULL),
                                                              "Relief_Threshold",
                                                              &qlParamsReliefThresh);



}



}
