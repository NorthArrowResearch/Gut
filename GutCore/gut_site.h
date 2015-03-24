#ifndef SITE_H
#define SITE_H

#include <QHash>
#include <QDomElement>
#include <QDir>
#include <QFile>
#include <QTime>
#include "gut_raster.h"
#include <QString>

namespace Gut{

class Site
{
public:
    Site();
    Site(const char *argv1, const char *argv2, const char *argv3, const char *argv4);
    ~Site();

    /**
     * @brief Init writes the inputs.xml file Running it with no parameters generates an empty file
     * @return
     */
    int Init();

    /**
     * @brief Init
     * @param argv1
     * @param argv2
     * @param argv3
     * @param argv4
     * @return
     */
    int Init(const char *argv1, const char *argv2, const char *argv3, const char *argv4);

    /**
     * @brief Run gut on the XML file that has been passed in
     * @return
     */
    int Run();
    /**
     * @brief GetRaster
     * @param eRasterType
     * @return
     */\
    static GutRaster * GetRaster(EvidenceRaster eRasterType);

private:
    static QHash<int, GutRaster *> m_RasterStore;

    // 3 XML files used here:
    static QFile m_XML_Inputs;
    static QFile m_XML_Results;
    static QFile m_XML_Logs;

    // These global params get read from the XML input file
    static int param1;
    static QString param2;
};


}
#endif // SITE_H
