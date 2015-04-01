#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include "gut_exception.h"
#include "gut_interface.h"
#include "gutengine.h"
#include "rastermanager_exception.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    try
    {
        Gut::GutEngine * rm = new Gut::GutEngine();
        int eResult = rm->Run(argc, argv);
        if (eResult <= 0) {
            std::cout << std::endl <<  Gut::GutException::GetReturnCodeOnlyAsString(eResult)<< std::endl;
        }
        else {
            std::cerr << std::endl << "Error: " <<  Gut::GutException::GetReturnCodeOnlyAsString(eResult)<< std::endl;
            exit (EXIT_FAILURE);
        }
        exit (EXIT_SUCCESS);
    }
    catch (Gut::GutException & e)
    {
        std::cerr << "Gut Error: " << e.GetReturnMsgAsString().toStdString() << std::endl;
        exit (EXIT_FAILURE);
    }
    catch (std::exception & e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        exit (EXIT_FAILURE);
    }
    //return a.exec();
    qApp->quit();


}
