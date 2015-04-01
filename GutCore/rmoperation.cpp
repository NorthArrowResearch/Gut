#include "rmoperation.h"
#include "gut_exception.h"

namespace Gut{

RMOperation::RMOperation()
{
}

void RMOperation::Run()
{

    try{
        switch (m_eOp) {
        case RM_LINTHRESH: LinThresh(); break;
        case RM_INVERT: Invert(); break;
        case RM_MASKVAL: MaskVal(); break;
        case RM_NONE: break;
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

bool RMOperation::operator==(RMOperation &other) {
    // NB: This list is sorted quickest to longest so that it won't
    // Cost that much if things aren't equal.

    // Compare the name of the operation
    if (GetCommand() != other.GetCommand())
        return false;

    // Compare element counts
    if (GetParams()->size() != other.GetParams()->size() ||
            GetInputs()->size() != other.GetInputs()->size() ||
            GetOutputs()->size() != other.GetOutputs()->size())
        return false;

    // Now compare elements one at a time
    if (!CompareLists(GetInputs(), other.GetInputs()) ||
            !CompareLists(GetOutputs(), other.GetOutputs()) ||
            !CompareLists(GetParams(), other.GetParams()))
        return false;


    return true;

}
bool RMOperation::operator!=(RMOperation &other) {
    return !(*this == other);
}

bool RMOperation::CompareLists(QList<QString> * ql1, QList<QString> * ql2){
    for (int n = 0; n < ql1->size(); ++n){
        if (ql1->at(n).compare(ql2->at(n), Qt::CaseInsensitive) != 0){
            return false;
        }
    }
    return true;
}


void RMOperation::VerifyInputs(int n){
    if (m_qlOutputFiles.length() < n){
        throw GutException(RASTERMAN_PARAMS, "Could not find the output file(s)." );
    }
}

void RMOperation::VerifyOutputs(int n){
    if (m_qlInputFiles.length() < n){
        throw GutException(RASTERMAN_PARAMS, "Could not find the input file(s)." );
    }
}

void RMOperation::VerifyParamNum(int n){
    if (m_qlParams.length() != n){
        throw GutException(RASTERMAN_PARAMS, "Not enough parameters to complete command." );
    }
}


void RMOperation::AreaThresh(){
    VerifyInputs(1);
    VerifyOutputs(1);
    VerifyParamNum(1);

    RasterManager::AreaThreshold(GetInputPath(),
                                   GetOutputPath(),
                                   GetParamDouble(0));
}

void RMOperation::LinThresh(){
    VerifyInputs(1);
    VerifyOutputs(1);
    VerifyParamNum(4);

    RasterManager::LinearThreshold(GetInputPath(),
                                   GetOutputPath(),
                                   GetParamDouble(0),
                                   GetParamDouble(1),
                                   GetParamDouble(2),
                                   GetParamDouble(3));
}

void RMOperation::EuclidDist(){
    VerifyInputs(1);
    VerifyOutputs(1);

    RasterManager::RasterEuclideanDistance(GetInputPath(),
                                           GetOutputPath());
}

void RMOperation::Filter(){
    VerifyInputs(1);
    VerifyOutputs(1);
    VerifyParamNum(2);

    RasterManager::RasterFilter("mean",
                                GetInputPath(),
                                GetOutputPath(),
                                GetParamInt(0),
                                GetParamInt(0)  );
}

void RMOperation::MaskVal(){
    VerifyInputs(1);
    VerifyOutputs(1);
    VerifyParamNum(1);

    RasterManager::MaskValue(
                GetInputPath(),
                GetOutputPath(),
                GetParamDouble(0) );
}

void RMOperation::Slope(){
    VerifyInputs(1);
    VerifyOutputs(1);

    RasterManager::CreateSlope(GetInputPath(),
                               GetOutputPath(),
                               RasterManager::SLOPE_DEGREES);
}

void RMOperation::Normalize(){
    VerifyInputs(1);
    VerifyOutputs(1);

    RasterManager::RasterNormalize(GetInputPath(),
                                   GetOutputPath() );
}

void RMOperation::Invert(){
    VerifyInputs(1);
    VerifyOutputs(1);

    RasterManager::RasterInvert(GetInputPath(),
                                GetOutputPath(),
                                1 );
}



}
