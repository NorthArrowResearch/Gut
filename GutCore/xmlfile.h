#ifndef XMLFILE_H
#define XMLFILE_H

#include <QString>
#include <QFile>
#include <QDomElement>

namespace Gut{

enum XML_LOG_SEVERITY {
    SEVERITY_SUCCESS = 0,
    SEVERITY_WARNING = 1,
    SEVERITY_ERROR = 2,
    SEVERITY_VERBOSE = 3,
};

enum XMLFileType{
    INPUT_FILE,
    RESULTS_FILE,
    LOG_FILE
};

enum StatusCode {
    STATUS_INITIALIZED
    , STATUES_LOADED
    , STATUS_PREPARED
    , STATUS_COMPLETE
};

enum StatusType {
    STATUSTYPE_PROJECT
    , STATUSTYPE_SIMULATION
};

inline QString enumToString(StatusCode eCode){
    switch (eCode){
    case STATUS_INITIALIZED: return "Initialized";
    case STATUES_LOADED: return "Loaded";
    case STATUS_PREPARED: return "Prepared Inputs";
    case STATUS_COMPLETE: return "Complete";
    default: return "Unknown Status Code";
    }
}

inline QString enumToString(StatusType eCode){
    switch (eCode){
    case STATUSTYPE_PROJECT: return "Project";
    case STATUSTYPE_SIMULATION: return "Simulation";
    default: return "unknown";
    }
}


class XMLFile
{
public:

    XMLFile();
    XMLFile(QString sXmlFile, XMLFileType bInput);
    ~XMLFile();
    void Load(QString &sFilePath);
    void CopyTmpToOutput();

    /**
     * @brief AddMeta
     * @param sTagName
     * @param sTagValue
     */
    void AddMeta(QString sTagName, QString sTagValue);


    void Log(QString sMsg, QString sException, int nSeverity, int indent);
    void QueueStatus(QString sID, StatusCode nCode, StatusType nType, int nTime);
    void AddStatus(QString sID, StatusCode nCode, StatusType nType, int nTime);
    void WriteDomToFile();

    /**
     * @brief Document
     * @return
     */
    inline QDomDocument * Document(){ return m_pDoc; }

    // inline void Log(QString sMsg){ Log(sMsg, "", SEVERITY_SUCCESS, 0); }
//        inline void LogDebug(QString sMsg, int indent){ Log(sMsg, "", SEVERITY_VERBOSE, indent); }
    void AddResult(QString sTagName, QString sTagValue);

    /**
     * @brief GetTmpFileName
     * @param xmlOutputFile
     * @param length
     * @param sSuffix
     * @return
     */
    static QString GetTmpFileName(QString sFileName, int length, QString sSuffix);
    /**
     * @brief GetTmpFolderName
     * @param sFolderName
     * @param randomStringLength
     * @return
     */
    static QString GetTmpFolderName(QString sFolderName, int randomStringLength);
    /**
     * @brief RandomString
     * @param length
     * @return
     */
    static QString RandomString(int length);
private:

    QFile * m_xmlFile;

    QString m_sXMLFilePath;
    QString m_sTMPFilePath;

    QDomDocument * m_pDoc;

    XMLFileType m_XMLType;

    void InitResults(QString &sFilePath);
    void InitLog(QString &sFilePath);

    void EnsureFilePath(QString &sFilePath, bool bHasTmp);

    inline void mySleep(int sleepMs)
    {
    #ifdef LINUX
        usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
    #endif
    #ifdef WINDOWS
        Sleep(sleepMs);
    #endif
    }



};

}
#endif // XMLFILE_H
