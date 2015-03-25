#ifndef GUTEXCEPTION_H
#define GUTEXCEPTION_H

#include <QString>

namespace Gut{

enum GutOutputCodes {
    PROCESS_OK
    , INPUT_FILE_ERROR
    , INPUT_FILE_TRANSFORM_ERROR
    , INPUT_FILE_NOT_VALID
    , INPUT_FILE_CANNOT_BE_MADE
    , FILE_NOT_FOUND
    , FILE_PRESENT
    , PATH_ERROR
    , FILE_WRITE_ERROR

    , OUTPUT_FILE_MISSING
    , OUTPUT_FILE_ERROR
    , OUTPUT_NO_DATA_ERROR
    , OUTPUT_FILE_EXT_ERROR
    , OUTPUT_UNHANDLED_DRIVER

    , DOM_LOAD_ERROR
    , FILE_READ_ONLY

    , GDALVERSION
    , RASTERMAN_VERSION
    , LIB_VERSION

    , OTHER_ERROR = 999
};


class GutException :public std::exception
{
public:
    inline GutException(int nErrorCode){ Init(nErrorCode, "");}
    inline GutException(int nErrorCode, QString sMsg){ Init(nErrorCode, sMsg); }

    inline ~GutException() throw() {}
    /**
     * @brief init
     */
    inline void Init(int nErrorCode, QString sMsg){
        m_nErrorCode = nErrorCode;
        m_sEvidence = sMsg;
    }
    /**
     * @brief GetErrorCode
     * @return
     */
    inline int GetErrorCode(){ return m_nErrorCode; }

    // Define the error messages
    inline static const char * GetReturnCodeOnlyAsString(int eErrorCode){
        switch (eErrorCode)
        {
        case PROCESS_OK:
            return "process completed successfully";
            break;

        case INPUT_FILE_ERROR:
            return "input file error";
            break;

        case INPUT_FILE_TRANSFORM_ERROR:
            return "input raster map projection error";
            break;

        case OUTPUT_FILE_MISSING:
            return "input raster file is missing or cannot be found";
            break;

        case  OUTPUT_FILE_ERROR:
            return "output file error";
            break;

        case  OUTPUT_NO_DATA_ERROR:
            return "NoData error on output raster";
            break;

        case  OUTPUT_FILE_EXT_ERROR:
            return "Output raster file extension error";
            break;

        case OUTPUT_UNHANDLED_DRIVER:
            return "Unhandled output raster type";
            break;

        case OTHER_ERROR:
            return "Unspecified error";
            break;

        case INPUT_FILE_NOT_VALID:
            return "Input Exists but is Invalid";
            break;

        case RASTERMAN_VERSION:
            return "Rasterman is the wrong version";
            break;

        case LIB_VERSION:
            return "Gut Library version is different from executable";

        case PATH_ERROR:
            return "File Path Error";
            break;

        case FILE_NOT_FOUND:
            return "Could not locate file";

        case FILE_PRESENT:
            return "File was present and should not have been";

        case INPUT_FILE_CANNOT_BE_MADE:
            return "File cannot be derived. It must be passed in as an input.";

        case GDALVERSION:
            return "Insufficient GDAL version detected.";
            break;

        default:
            return "Unhandled Raster Manager Error.";
            break;
        }
    };

    /**
     * @brief GetReturnMsgAsString: This function returns more information than GetReturnCodeOnlyAsString
     * @return
     */
    inline QString GetReturnMsgAsString(){
        QString sOutput = "";
        QString sErrMsg = GetReturnCodeOnlyAsString(m_nErrorCode);
        if (m_sEvidence.length() > 0){
            sOutput = sErrMsg + ": " + m_sEvidence;
        }
        return sOutput;
    }

private:
    int m_nErrorCode;
    QString m_sEvidence;
};

}



#endif // GUTEXCEPTION_H
