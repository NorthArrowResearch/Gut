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



    // Set up the commands that RasterManager needs to run.
    QList<QString> BankFulThresh = QList<QString>() << QString("")
                                                    << QString("")
                                                    << QString("")
                                                    << QString("");

    QList<QString> MeanDetrendedThresh = QList<QString>() << QString("")
                                                          << QString("")
                                                          << QString("")
                                                          << QString("");

    QList<QString> BankFullDistanceThresh = QList<QString>() << QString("")
                                                             << QString("")
                                                             << QString("")
                                                             << QString("");

    QList<QString> ReliefThresh = QList<QString>() << QString("")
                                                   << QString("")
                                                   << QString("")
                                                   << QString("");



}



}
