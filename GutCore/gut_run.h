#ifndef SITE_H
#define SITE_H

#include <QHash>
#include <QDomElement>
#include <QDir>
#include <QFile>
#include <QTime>
#include <QString>
#include "gut_raster.h"
#include "xmlfile.h"
#include "unit.h"
#include "unit_hsuplfan.h"

namespace Gut{

class DLL_API GutRun{
public:
    // This is an implementation of the meyers singleton pattern.
    inline static GutRun& Instance()
    {
        static GutRun instance;
        return instance;
    }

   /**
    * @brief Run gut on the XML file that has been passed in
    * @return
    */
   void Run(const char *psXMLInput);

   inline QList<GutRaster *> * GetRasterStore(){ return &m_RasterStore; }
   inline void PushRasterStore(GutRaster * theRaster){ m_RasterStore.push_back(theRaster); }

   // Some getters and setters
   /**
    * @brief GetOutputDir
    * @return
    */
   inline QString GetOutputDir(){ return qdOutputDir.absolutePath(); }
   /**
    * @brief GetTempDir
    * @return
    */
   inline QString GetGutTempDir(){ return qdGutRunTempDir.absolutePath(); }
   /**
    * @brief CreateRasterName
    * @return
    */
   QString CreateRasterName();
   /**
    * @brief BaseFileNameAppend
    * @param sFullFilePath
    * @param sAppendStr
    * @return
    */
   static QString BaseFileNameAppend(QString sFullFilePath, QString sAppendStr);


private:
   GutRun();               // Private so that it can  not be called
   GutRun(GutRun const&){} // copy constructor is private
   ~GutRun();

   GutRun& operator=(GutRun const&){} // assignment operator is private
   static GutRun* m_pInstance;        // Holds the pointer to itself as a singleton

   void InitCheck();

   // Workflow methods
   void Init(const char *psXMLInput);
   void LoadSourceRasters();
   void CreateUnits();
   void CombineUnits();
   void ClassifyUnits();   

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

   //   TEMP Folders:
   QDir qdTempDir;       // This is the root TMP dir specified by the XML file.
   QDir qdGutRunTempDir; // This is the Specific TMP dir inside which we find our TMP rasters.
   bool bCleanTMP;       // Clean up the tmp files we create.

   QList<GutRaster *> m_RasterStore;
   QList<Unit *> m_UnitStore;

   // 3 XML files used here:
   XMLFile * m_XML_Inputs;
   QDomDocument * m_elConf;
   XMLFile * m_XML_Results;
   XMLFile * m_XML_Logs;

   // These global params get read from the XML input file
   int param1;
   QString param2;
   QString GetSourceRasterPath(QString sType);


};

}
#endif // SITE_H
