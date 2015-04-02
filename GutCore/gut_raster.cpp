#include "gut_raster.h"
#include "gut_run.h"

namespace Gut{

GutRaster::GutRaster(QString sFilename, RasterManCMD rmCMD){
    m_RasterType = RASTER_ORIGINAL;
    m_RasterFilePath = XMLFile::GetTmpFileName(sFilename, 6, "tif");
    m_eOp = rmCMD;
    // Init() not necessary if we're just loading a file.
}

GutRaster::GutRaster(RasterType eRasterType, RasterManCMD sRMOp, GutRaster* InputFile, QString OutputFile, QList<QString> *params)
{
    QList<GutRaster *> inputs = QList<GutRaster *>() << InputFile;
    Init(eRasterType, sRMOp, &inputs, OutputFile, params);
}

GutRaster::GutRaster(RasterType eRasterType,  RasterManCMD sRMOp, QList<GutRaster*> *InputFiles, QString OutputFile, QList<QString> *params)
{
    Init(eRasterType, sRMOp, InputFiles, OutputFile, params);
}

void GutRaster::Init(RasterType eRasterType,  RasterManCMD sRMOp, QList<GutRaster*> *InputFiles, QString OutputFile, QList<QString> *params)
{
    for (int n = 0; n < InputFiles->size(); ++n){
        m_qlInputRasters.append(InputFiles->at(n));
    }

    m_RasterFilePath = OutputFile;

    for (int n = 0; n < params->size(); ++n){
        m_qlParams.append(params->at(n));
    }
    m_eOp = sRMOp;

    switch (eRasterType) {
    case RASTER_ORIGINAL: break;
    case RASTER_TEMPORARY: break;
    case RASTER_INTERMEDIATE: break;
    case RASTER_FINAL: break;
    default:
        throw GutException(RASTER_TYPE, QString("Could not understand Raster Type: %1").arg(eRasterType));
        break;
    }

    try{
        switch (m_eOp) {
        case RM_SLOPE: Slope(); break;
        case RM_INVERT: Invert(); break;
        case RM_MASKVAL: MaskVal(); break;
        case RM_NORMALIZE: Normalize(); break;
        case RM_EUCLIDDIST: EuclidDist(); break;
        case RM_FILTER: Filter(); break;
        case RM_LINTHRESH: LinThresh(); break;
        case RM_AREATHRESH: AreaThresh(); break;
        default:
            throw GutException(RASTER_OPERATION, QString("Operation: %1").arg(m_eOp) );
            break;
        }
    }
    catch (RasterManager::RasterManagerException & e)
    {
        throw GutException(RASTERMAN_ERROR, e.GetReturnMsgAsString() );
    }

}

GutRaster * GutRaster::GetOriginalRaster(RasterManCMD rmOperation)
{
    bool bFound = false;
    GutRaster * theRaster;
    QList<GutRaster *> * pRasterStore = GutRun::Instance().GetRasterStore();
    foreach(GutRaster * gRaster, *pRasterStore)
    {
        if (gRaster->GetType() == RASTER_ORIGINAL &&
                rmOperation == gRaster->GetCommand() ){
            theRaster = gRaster;
            bFound = true;
            break;
        }
    }

    if(bFound){
        return theRaster;
    }
    else{
        throw GutException(FILE_WRITE_ERROR, QString("Could not find original raster") );
    }
}

GutRaster * GutRaster::GetOrCreateRaster(RasterType eRasterType, RasterManCMD rmOperation,
                                         GutRaster * qlInput, QString sOutput, QList<QString> *qlParams)
{
    QList<GutRaster *> inputs = QList<GutRaster *>() << qlInput;
    return GetOrCreateRaster(eRasterType, rmOperation, &inputs, sOutput, qlParams);
}

GutRaster * GutRaster::GetOrCreateRaster(RasterType eRasterType, RasterManCMD rmOperation,
                                         QList<GutRaster *> * qlInputs, QString sOutput, QList<QString> *qlParams)
{
    bool bFound = false;
    GutRaster * theRaster;
    QList<GutRaster *> * pRasterStore = GutRun::Instance().GetRasterStore();
    foreach(GutRaster * gRaster, *pRasterStore)
    {
        if (eRasterType == gRaster->GetType() &&
                rmOperation == gRaster->GetCommand() &&
                GutRaster::ComparePtrLists(qlInputs, gRaster->GetInputs()) &&
                GutRaster::CompareStringLists(qlParams, gRaster->GetParams()) ){
            theRaster = gRaster;
            bFound = true;
            break;
        }
    }

    // If not found then we make it.
    if (!bFound && eRasterType){
        theRaster = new GutRaster(eRasterType, rmOperation, qlInputs, sOutput, qlParams);

        // The farther down the process we are the least general re-use there should be
        // so "push_back" is the right choice.
        GutRun::Instance().PushRasterStore(theRaster);
        return theRaster;
    }
    return theRaster;
}


GutRaster::~GutRaster(){ }

QString GutRaster::CreateOutputRasterPath(QString sPathPrefix, QString sSuffix, bool bTmpDir){
    QString sDir = "";
    QString sFilename = XMLFile::GetTmpFileName(sPathPrefix, 5, sSuffix);

    if (bTmpDir)
        sDir = GutRun::Instance().GetGutTempDir();
    else
        sDir = GutRun::Instance().GetOutputDir();

    return QDir(sDir).filePath(sFilename);
}


bool GutRaster::ComparePtrLists(QList<GutRaster*> * ql1, QList<GutRaster*> * ql2){
    for (int n = 0; n < ql1->size(); ++n){
        if (ql1->at(n) != ql2->at(n)){
            return false;
        }
    }
    return true;
}

bool GutRaster::CompareStringLists(QList<QString> * ql1, QList<QString> * ql2){
    for (int n = 0; n < ql1->size(); ++n){
        if (ql1->at(n).compare(ql2->at(n), Qt::CaseInsensitive) != 0){
            return false;
        }
    }
    return true;
}

void GutRaster::VerifyInputs(int n){
    if (m_qlInputRasters.length() < n){
        throw GutException(RASTERMAN_PARAMS, "Could not find the output Raster(s)." );
    }
}

void GutRaster::VerifyParamNum(int n){
    if (m_qlParams.length() != n){
        throw GutException(RASTERMAN_PARAMS, "Not enough parameters to complete command." );
    }
}


void GutRaster::AreaThresh(){
    VerifyInputs(1);
    VerifyParamNum(1);

    RasterManager::AreaThreshold(GetInput(),
                                 GetOutput(),
                                 GetParamDouble(0));
}

void GutRaster::LinThresh(){
    VerifyInputs(1);
    VerifyParamNum(4);

    RasterManager::LinearThreshold(GetInput(),
                                   GetOutput(),
                                   GetParamDouble(0),
                                   GetParamDouble(1),
                                   GetParamDouble(2),
                                   GetParamDouble(3));
}

void GutRaster::EuclidDist(){
    VerifyInputs(1);

    RasterManager::RasterEuclideanDistance(GetInput(),
                                           GetOutput());
}

void GutRaster::Filter(){
    VerifyInputs(1);
    VerifyParamNum(2);

    RasterManager::RasterFilter("mean",
                                GetInput(),
                                GetOutput(),
                                GetParamInt(0),
                                GetParamInt(0)  );
}

void GutRaster::MaskVal(){
    VerifyInputs(1);
    VerifyParamNum(1);

    RasterManager::MaskValue(
                GetInput(),
                GetOutput(),
                GetParamDouble(0) );
}

void GutRaster::Slope(){
    VerifyInputs(1);

    RasterManager::CreateSlope(GetInput(),
                               GetOutput(),
                               RasterManager::SLOPE_DEGREES );
}

void GutRaster::Normalize(){
    VerifyInputs(1);

    RasterManager::RasterNormalize(GetInput(),
                                   GetOutput() );
}

void GutRaster::Invert(){
    VerifyInputs(1);

    RasterManager::RasterInvert(GetInput(),
                                GetOutput(),
                                1 );
}


}
