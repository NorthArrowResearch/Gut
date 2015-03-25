#ifndef SITE_H
#define SITE_H

#include <QHash>
#include <QDomElement>
#include <QDir>
#include <QFile>
#include <QTime>
#include "gut_raster.h"
#include <QString>
#include "gut_xmlfile.h"

namespace Gut{

class DLL_API GutRun
{
public:

    GutRun(const char *psXMLInput);
    ~GutRun();

    /**
     * @brief Run gut on the XML file that has been passed in
     * @return
     */
    int Run();

    /**
     * @brief GetRaster
     * @param eRasterType
     * @return
     */
    GutRaster * GetRaster(EvidenceRaster eRasterType);

private:
    static QHash<EvidenceRaster, GutRaster *> m_RasterStore;

    // 3 XML files used here:
    static XMLFile m_XML_Inputs;
    static XMLFile m_XML_Results;
    static XMLFile m_XML_Logs;

    // These global params get read from the XML input file
    static int param1;
    static QString param2;
};


}
#endif // SITE_H
