#ifndef SITE_H
#define SITE_H

#include <QHash>
#include <QDomElement>
#include <QDir>
#include <QFile>
#include <QTime>
#include "gut_raster.h"
#include <QString>
#include "xmlfile.h"

namespace Gut{


class DLL_API GutRun{
public:
   static GutRun * Instance();
   void Init(const char *psXMLInput);
   /**
    * @brief Run gut on the XML file that has been passed in
    * @return
    */
   void Run();


   /**
    * @brief GetRaster
    * @param eRasterType
    * @return
    */
   GutRaster * GetCreateRaster(RasterManOperation eRasterType);

   inline QString GetOutputDir(){ return qdOutputDir.absolutePath(); }
   inline QString GetTempDir(){ return qdTempDir.absolutePath(); }

   static QString BaseFileNameAppend(QString sFullFilePath, QString sAppendStr);


private:
   GutRun();  // Private so that it can  not be called
   GutRun(GutRun const&){}            // copy constructor is private
   ~GutRun();

   void CombineRasters();

   GutRun& operator=(GutRun const&){}  // assignment operator is private
   static GutRun* m_pInstance;

   /**
    * @brief EnsureFile deletes a file if it already exists and recursively creates folders
    * @param sFilePath
    */
   void EnsureFile(QString sFilePath);
   /**
    * @brief GetInputParamText
    * @param containerName
    * @param tagName
    * @return
    */
   QString GetInputParamText(QString containerName, QString tagName);

   QDir qdOutputDir;
   QDir qdTempDir;

   QHash<EvidenceRaster, GutRaster *> m_RasterStore;

   // 3 XML files used here:
   XMLFile * m_XML_Inputs;
   QDomDocument * m_elConf;
   XMLFile * m_XML_Results;
   XMLFile * m_XML_Logs;

   // These global params get read from the XML input file
   int param1;
   QString param2;
   void MakeEvidenceRasters();
   void LoadSourceRasters();
   QString GetSourceRasterPath(QString sType);

   void InitCheck();
};

}
#endif // SITE_H
