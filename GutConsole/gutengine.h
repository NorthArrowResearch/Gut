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
    bool CheckLibersion();

};

}

#endif // GUTENGINE_H
