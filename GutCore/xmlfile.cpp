#include "xmlfile.h"
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>
#include <QDomElement>
#include <QXmlStreamWriter>

#include "gut_exception.h"

namespace Gut{

XMLFile::XMLFile(QString sXmlFile, XMLFileType bInput)
{
    // No matter what type of file it is the path gets set here.
    m_sXMLFilePath = sXmlFile;
    m_sTMPFilePath = "";
    m_XMLType = bInput;
    switch (bInput) {
    case INPUT_FILE:
        Load(sXmlFile);
        break;
    case RESULTS_FILE:
        InitResults(sXmlFile);
        break;
    case LOG_FILE:
        InitLog(sXmlFile);
        break;
    default: break;
    }

}

void XMLFile::EnsureFilePath( QString &sFilePath, bool bHasTmp ){

    QFileInfo sNewFileInfo(sFilePath);
    QDir sNewDir = QDir(sNewFileInfo.absolutePath());
    QString sTmpPrefix = "_GUT_TMP_" + sNewFileInfo.baseName();

    // Delete a file if it already exists.
    if (sNewFileInfo.exists())
        QFile::remove(sNewFileInfo.absoluteFilePath());

    // Make a path if we don't have one already.
    if (!sNewDir.exists()){
      sNewDir.mkpath(".");
    }

    if (bHasTmp){
        // On the log we write to a temporary file to get around collisions
        m_sTMPFilePath = QDir(sNewDir).filePath( GetTmpFileName(sTmpPrefix, 8, "xml"));
        m_xmlFile = new QFile(m_sTMPFilePath);

        // Clean up all older TMP files
        QStringList slTmpFiles;
        QString fileName = sTmpPrefix + "*.xml";
        slTmpFiles = sNewDir.entryList(QStringList(fileName),
                                     QDir::Files | QDir::NoSymLinks);

        foreach(QString sTmpFile, slTmpFiles){
            // If the file was already there remove it
            QString sTmpFilePath = QDir(sNewDir).filePath( sTmpFile );
            if (QFile::exists(sTmpFilePath))
                QFile::remove(sTmpFilePath);
        }

    }
    else{
        m_xmlFile = new QFile(sFilePath);
    }
}

void XMLFile::InitResults( QString &sFilePath ){

    EnsureFilePath( sFilePath, false );

    m_pDoc = new QDomDocument;

    // Clean up the status items
    QDomElement documentElement = m_pDoc->documentElement();

    /* open a file */
    if (!m_xmlFile->open(QIODevice::WriteOnly))
        throw GutException(FILE_READ_ONLY, m_xmlFile->fileName());
    else
    {

        QDomElement results = m_pDoc->createElement("results");
        QDomElement meta = m_pDoc->createElement("meta_data");

        results.appendChild(meta);

        QDomNode xmlNode = m_pDoc->createProcessingInstruction("xml",
                                     "version=\"1.0\" encoding=\"ISO-8859-1\"");

        m_pDoc->appendChild(xmlNode);
        m_pDoc->appendChild(results);

    }
    m_xmlFile->close();
    WriteDomToFile();

}

// Create the file with the base skeleton we need. Then close it.
void XMLFile::InitLog( QString &sFilePath ){

    // Make sure we have the paths necessary
    EnsureFilePath( sFilePath, true );

    m_pDoc = new QDomDocument;

    // Clean up the status items
    QDomElement documentElement = m_pDoc->documentElement();

    /*open a file */
    if (!m_xmlFile->open(QIODevice::WriteOnly))
        throw GutException(FILE_READ_ONLY, m_xmlFile->fileName());
    else
    {

        QDomElement log = m_pDoc->createElement("log");
        QDomElement status = m_pDoc->createElement("status");
        QDomElement results = m_pDoc->createElement("results");
        QDomElement meta = m_pDoc->createElement("meta_data");
        QDomElement messages = m_pDoc->createElement("messages");

        log.appendChild(results);
        log.appendChild(meta);
        log.appendChild(messages);
        log.appendChild(status);

        QDomNode xmlNode = m_pDoc->createProcessingInstruction("xml",
                                     "version=\"1.0\" encoding=\"ISO-8859-1\"");

        m_pDoc->appendChild(xmlNode);
        m_pDoc->appendChild(log);

    }
    m_xmlFile->close();
    WriteDomToFile();
}

void XMLFile::Load(QString &sFilePath)
{
    if (sFilePath.isEmpty() || sFilePath.isNull())
        throw GutException(FILE_NOT_FOUND, "Filepath was empty");
    else
        if (!QFile::exists(sFilePath))
            throw GutException(FILE_NOT_FOUND, sFilePath);

    m_pDoc = new QDomDocument;
    m_xmlFile = new QFile(sFilePath);
    if (!m_xmlFile->open(QIODevice::ReadOnly))
        throw GutException(FILE_READ_ONLY, sFilePath);

    if (!m_pDoc->setContent(m_xmlFile->readAll())) {
        m_xmlFile->close();
        throw GutException(DOM_LOAD_ERROR, sFilePath);
    }
}

void XMLFile::CopyTmpToOutput(){
    try{
        if (QFile::exists(m_sXMLFilePath))
        {
            QFile::remove(m_sXMLFilePath);
        }

        QFile::copy(m_sTMPFilePath, m_sXMLFilePath);
    }catch(std::exception e)
    {
         //Do nothing. We don't care that it can't write.
    }
}

void XMLFile::AddMeta(QString sTagName, QString sTagValue){
    QDomElement meta_data, meta_data_tag;
    QDomElement documentElement = m_pDoc->documentElement();
    QDomNodeList elements = documentElement.elementsByTagName( "meta_data" );
    QDomText sMsgTxt = m_pDoc->createTextNode(sTagValue.toHtmlEscaped());

    if( elements.size() == 0 )
    {
      meta_data = m_pDoc->createElement( "meta_data" );
      documentElement.insertBefore( meta_data, documentElement );
    }
    else if( elements.size() == 1 )
    {
      meta_data = elements.at(0).toElement();
    }

    // Create the message itself
    meta_data_tag = m_pDoc->createElement( sTagName );
    meta_data_tag.appendChild(sMsgTxt);
    meta_data.appendChild( meta_data_tag );

    WriteDomToFile();
}

void XMLFile::AddResult(QString sTagName, QString sTagValue){
//    QDomElement report_data, sim_data, tagresult, report_data_tag;
//    QDomElement documentElement = m_pDoc->documentElement();

//    int nSimID = logSim->GetID();
//    QString simName = logSim->GetName();

//    // First search for (create if necessary) a results.
//    QDomNodeList reportEl = documentElement.elementsByTagName( "results" );

//    if( reportEl.size() == 0 )
//    {
//      report_data = m_pDoc->createElement( "results" );
//      documentElement.insertBefore( report_data, documentElement );
//    }
//    else if( reportEl.size() == 1 )
//    {
//      report_data = reportEl.at(0).toElement();
//    }

//    // Create the simulation node if it doesn't already exist
//    QDomNodeList simEl = report_data.childNodes();
//    QDomText sMsgTxt = m_pDoc->createTextNode(sTagValue.toHtmlEscaped());

//    bool bFound = false;
//    for(int n= 0; n < simEl.length(); n++){
//        QDomElement elSimulation = simEl.at(n).toElement();

//        QString sSimID = QString::number(nSimID);
//        QString simAttrID = elSimulation.attribute("id");

//        if (elSimulation.hasAttribute("id") && simAttrID.compare(sSimID, Qt::CaseInsensitive) == 0){
//            sim_data = elSimulation;
//            bFound = true;
//        }
//    }

//    if( !bFound )
//    {
//      sim_data = m_pDoc->createElement( "simulation" );
//      sim_data.setAttribute("id", QString::number(nSimID));
//      sim_data.setAttribute("name", simName);
//      report_data.appendChild(sim_data);
//    }

//    // Create the message itself
//    tagresult = m_pDoc->createElement( sTagName );
//    tagresult.appendChild(sMsgTxt);
//    tagresult.appendChild( report_data_tag );
//    sim_data.appendChild(tagresult);

    WriteDomToFile();

}

QString XMLFile::GetTmpFileName(QString sFileName, int randomStringLength, QString sSuffix)
{    
   QString tmpName =  QString("%1_%2.%3").arg(sFileName).arg(RandomString(randomStringLength)).arg(sSuffix);
   return tmpName;
}

QString XMLFile::GetTmpFolderName(QString sFolderName, int randomStringLength)
{
   return sFolderName + QString("_") + RandomString(randomStringLength);
}

QString XMLFile::RandomString(int length){
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");

    QString randomString;

    for(int i=0; i < length; ++i)
    {
        int index = qrand() % possibleCharacters.length();
        QChar nextChar = possibleCharacters.at(index);
        randomString.append(nextChar);
    }
    return randomString;
}

void XMLFile::Log(QString sMsg, QString sException, int nSeverity, int indent)
{
    QDomElement messages, message, exception, description;
    QDomElement documentElement = m_pDoc->documentElement();
    QDomNodeList elements = documentElement.elementsByTagName( "messages" );

    QDomText sMsgTxt = m_pDoc->createTextNode(sMsg.toHtmlEscaped());
    QDomText sExceptionTxt = m_pDoc->createTextNode(sException.toHtmlEscaped());

    if( elements.size() == 0 )
    {
      messages = m_pDoc->createElement( "messages" );
      documentElement.insertBefore( messages, documentElement );
    }
    else if( elements.size() == 1 )
    {
      messages = elements.at(0).toElement();
    }

    // Create the message itself
    message = m_pDoc->createElement( "message" );
    message.setAttribute( "severity", nSeverity );
    message.setAttribute( "indent", indent );

    // Timestamps are useful
    QDateTime local(QDateTime::currentDateTime());
    message.setAttribute("timestamp", local.toString(Qt::ISODate));

    // Now create the description of the message
    description = m_pDoc->createElement( "description" );
    description.appendChild(sMsgTxt);
    message.appendChild( description );

    // Only create an exception if we need to.
    if (nSeverity != 0 && sException.compare("") != 0){
        exception = m_pDoc->createElement( "exception" );
        exception.appendChild(sExceptionTxt);
        message.appendChild( exception );
    }
    messages.appendChild( message );

    WriteDomToFile();
}


void XMLFile::QueueStatus(QString sID, StatusCode nCode, StatusType nType, int nTime)
{
    QDomElement statusEl, statusNode;
    QDomElement documentElement = m_pDoc->documentElement();
    QDomNodeList statusNL = documentElement.elementsByTagName( "status" );

    if( statusNL.size() == 0 )
    {
      statusEl = m_pDoc->createElement( "status" );
      documentElement.insertBefore( statusEl, documentElement );
    }
    else if( statusNL.size() == 1 )
    {
      statusEl = statusNL.at(0).toElement();
    }

    // Create the message itself
    statusNode = m_pDoc->createElement( enumToString( nType ) );
    statusNode.setAttribute( "value", enumToString( nCode ) );
    statusNode.setAttribute( "time", QString::number( nTime ) );
    statusNode.setAttribute( "id", sID );

    // Timestamps are useful
    QDateTime local(QDateTime::currentDateTime());
    statusNode.setAttribute("timestamp", local.toString(Qt::ISODate));

    statusEl.appendChild( statusNode );

    WriteDomToFile();
}

void XMLFile::AddStatus(QString sID, StatusCode nCode, StatusType nType, int nTime){
    QueueStatus(sID, nCode, nType, nTime);
    WriteDomToFile();
}

void XMLFile::WriteDomToFile(){

    // Great. Now Write the domelement to the file.
    // We're competing with the Desktop app for this file so we will try
    // a bunch of times to open it.
    int n = 0;
    while ( !m_xmlFile->open( QIODevice::WriteOnly | QIODevice::Text ) ){
        n++;
        if (n >= 100)
            throw GutException(FILE_WRITE_ERROR,  m_xmlFile->fileName());
        mySleep(50);
    }

    const int Indent = 4;

    QTextStream out(m_xmlFile);
    m_pDoc->save(out, Indent);
    m_xmlFile->close();

    if (m_sTMPFilePath.length() > 0)
        CopyTmpToOutput();

}


XMLFile::~XMLFile(){

    if (!m_xmlFile == NULL)
    {
        if (m_xmlFile->isOpen())
            m_xmlFile->close();

        delete m_xmlFile;
    }
    // Now clean up the temparary file.
    if (QFile::exists(m_sTMPFilePath))
    {
        QFile::remove(m_sTMPFilePath);
    }

    // Delete the TMP file
    delete m_pDoc;
}


}
