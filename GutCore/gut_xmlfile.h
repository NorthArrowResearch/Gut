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
    XMLFile(QString sXmlFile, bool bInput);
    ~XMLFile();
    void Load(QString &sFilePath);
    void CopyTmpToOutput();
    void Init(QString &sFilePath);
    void AddMeta(QString sTagName, QString sTagValue);
    QString GetTmpFileName(QString xmlOutputFile);
    void Log(QString sMsg, QString sException, int nSeverity, int indent);
    void QueueStatus(QString sID, StatusCode nCode, StatusType nType, int nTime);
    void AddStatus(QString sID, StatusCode nCode, StatusType nType, int nTime);
    void WriteDomToFile();


    void AddResult(QString sTagName, QString sTagValue);
private:

    QFile * m_xmlFile;

    QString m_sXMLFilePath;
    QString m_sTMPFilePath;

    QDomDocument * m_pDoc;

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
