#ifndef XMLFILE_H
#define XMLFILE_H

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
    void AddResult(Simulation *logSim, QString sTagName, QString sTagValue);
    QString GetTmpFileName(QString xmlOutputFile);
    void Log(QString sMsg, QString sException, int nSeverity, int indent);
    void QueueStatus(QString sID, StatusCode nCode, StatusType nType, int nTime);
    void AddStatus(QString sID, StatusCode nCode, StatusType nType, int nTime);
    void WriteDomToFile();
};

#endif // XMLFILE_H
