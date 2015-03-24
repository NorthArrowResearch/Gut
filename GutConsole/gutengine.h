#ifndef GUTENGINE_H
#define GUTENGINE_H

#include <QString>

namespace Gut {

class GutEngine
{
public:
    GutEngine();
    int Run(int argc, char *argv[]);
private:

    void CheckRasterManVersion();
    void CheckGutVersion();

    int GutInit(int argc, char *argv[]);
    int GutRun(int argc, char *argv[]);

};

}

#endif // GUTENGINE_H
