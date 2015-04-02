#ifndef GUTRASTER_H
#define GUTRASTER_H
#include "gut_interface.h"
#include <QList>
#include "rastermanager_interface.h"
#include "rastermanager_exception.h"

namespace Gut{

const double EvidenceMinProb = 0.01;
const double EvidenceMaxProb = 0.99;

enum RasterType{
  RASTER_ORIGINAL,      // We do not creat these. We simply load them
  RASTER_TEMPORARY,     // Not actually part of the workflow. Just a throw-away raster between steps.
  RASTER_INTERMEDIATE,  // Part of the workflow. This raster represents a mark on the path to evidence rasters.
  RASTER_FINAL          // Actual evidence raster
};

enum RasterManCMD{
    RM_SLOPE,
    RM_INVERT,
    RM_MASKVAL,
    RM_NORMALIZE,
    RM_EUCLIDDIST,
    RM_FILTER,
    RM_LINTHRESH,
    RM_AREATHRESH,

    // Some rasters are just passed in and are not the results
    // Of rasterman operations. We need a way to find these.
    // So we treat them as a kind of operation
    RM_DEM,
    RM_WATEREXTENT,
    RM_DETRENDED,
    RM_BANKFULL
};

class GutRaster
{
public:

    // Constructor for simply loading an existing raster
    GutRaster(QString sRasterPath, RasterManCMD rmCMD);

    // Constructor for making the raster and rasterman op in one go
    GutRaster(RasterType eRasterType, RasterManCMD sRMOp, GutRaster *InputFiles, QString OutputFile, QList<QString> *params);
    GutRaster(RasterType eRasterType, RasterManCMD sRMOp, QList<GutRaster *> *InputFiles, QString OutputFile, QList<QString> *params);

    ~GutRaster();

    inline RasterManCMD GetCommand(){ return m_eOp; }

    inline QString GetRasterPath(){ return m_RasterFilePath; }

    inline QList<GutRaster *> * GetInputs(){ return &m_qlInputRasters; }
    inline QList<QString> * GetParams(){ return &m_qlParams; }

    inline const char * GetInput(){
        return GetInput(0);
    }
    inline const char * GetInput(int n){
        return m_qlInputRasters.at(n)->GetOutput();
    }
    inline const char * GetOutput(){
        const QByteArray qbFileName = m_RasterFilePath.toLocal8Bit();
        return qbFileName.data();
    }

    // It's convenient when there's only one file to return A nice QList.
    static inline QList<QString> GetSingleInput(QString filename){
        return QList<QString>() << filename;
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

    /**
     * @brief GetType
     * @return
     */
    inline RasterType GetType(){ return m_RasterType; }

    /**
     * @brief GetOrCreateRaster
     * @param eRasterType
     * @param rmOperation
     * @param qlInputs
     * @param sOutput
     * @param qlParams
     * @return
     */
    static GutRaster *GetOrCreateRaster(RasterType eRasterType, RasterManCMD rmOperation, GutRaster * qlInput, QString sOutput, QList<QString> *qlParams);
    static GutRaster *GetOrCreateRaster(RasterType eRasterType, RasterManCMD rmOperation, QList<GutRaster *> *qlInputs, QString sOutput, QList<QString> *qlParams);
    static GutRaster *GetOriginalRaster(RasterManCMD rmOperation);

private:

    // Raster Type
    RasterManCMD m_eOp;
    QList<GutRaster *> m_qlInputRasters;  // One or more inputs.
    QList<QString> m_qlParams;

    static bool CompareStringLists(QList<QString> *ql1, QList<QString> *ql2);
    static bool ComparePtrLists(QList<GutRaster *> *ql1, QList<GutRaster *> *ql2);

    // There can be only one output. Makeconcurrent is the one exception
    // that will need to be handled different.
    QString m_RasterFilePath;
    RasterType m_RasterType;

    void Init(RasterType eRasterType, RasterManCMD sRMOp, QList<GutRaster *> *InputFiles, QString OutputFile, QList<QString> *params);

    // Check we've got valid inputs.
    void VerifyInputs(int n);
    void VerifyParamNum(int n);

    inline const char * QlistToConstChar(QList<QString> ql, int n){
        const QByteArray qbFieldName = ql.at(n).toLocal8Bit();
        return qbFieldName.data();
    }

    // Functions to call specific RM Interface commands
    void Normalize();
    void Slope();
    void MaskVal();
    void Filter();
    void EuclidDist();
    void LinThresh();
    void Invert();
    void AreaThresh();

    /**
     * @brief CreateOutputRasterPath
     * @param sPathPrefix
     * @param sSuffix
     * @param bTmpDir
     * @return
     */
    QString CreateOutputRasterPath(QString sPathPrefix, QString sSuffix, bool bTmpDir);
};

}
#endif // GUTRASTER_H
