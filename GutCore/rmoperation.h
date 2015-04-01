#ifndef RMOPERATION_H
#define RMOPERATION_H
#include "raster.h"
#include "rastermanager_interface.h"
#include "rastermanager_exception.h"
#include <QList>

namespace Gut{

enum RasterManCMD{
  RM_SLOPE,
  RM_LINTHRESH,
  RM_INVERT,
  RM_MASKVAL,
  RM_NORMALIZE,
  RM_EUCLIDDIST,
  RM_FILTER,



  RM_NONE
};


class RMOperation
{
public:
    RMOperation();
    void Run();

    bool operator ==(RMOperation &other);
    bool operator !=(RMOperation &other);

    inline RasterManCMD GetCommand(){ return m_eOp; }

    inline QList<QString> * GetInputs(){return &m_qlInputFiles; }
    inline QList<QString> * GetOutputs(){return &m_qlInputFiles; }
    inline QList<QString> * GetParams(){return &m_qlInputFiles; }

    inline const char * GetInputPath(){
        return GetInputPath(0);
    }
    inline const char * GetInputPath(int n){
        return QlistToConstChar(m_qlInputFiles, n);
    }
    inline const char * GetOutputPath(){
        return GetOutputPath(0);
    }
    inline const char * GetOutputPath(int n){
        return QlistToConstChar(m_qlOutputFiles, n);
    }
    inline const char * GetParamString(int n){
        return QlistToConstChar(m_qlParams, n);
    }
    inline double GetParamDouble(int n){
        return m_qlParams.at(n).toDouble();
    }
    inline int GetParamInt(int n){
        return m_qlParams.at(n).toInt();
    }

private:
    // A rasterman operation is the same variables over and over.
    RasterManCMD m_eOp;
    QList<QString> m_qlInputFiles;
    QList<QString> m_qlOutputFiles;
    QList<QString> m_qlParams;

    void VerifyInputs(int n);
    void VerifyOutputs(int n);
    void VerifyParamNum(int n);

    void Normalize();
    void Slope();
    void MaskVal();
    void Filter();
    void EuclidDist();
    void LinThresh();
    void Invert();
    void AreaThresh();

    inline const char * QlistToConstChar(QList<QString> ql, int n){
        const QByteArray qbFieldName = ql.at(n).toLocal8Bit();
        return qbFieldName.data();
    }

    bool CompareLists(QList<QString> *ql1, QList<QString> *ql2);
};

}
#endif // RMOPERATION_H
