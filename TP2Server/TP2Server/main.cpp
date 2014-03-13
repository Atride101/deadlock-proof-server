/*!
 * TP2 - IFT2245
 * Server application to simulate un system that
 * allocates resources to clients. (to be run alonside
 * the client application using the same IP address and port)
 *
 * @author David Quiroz Marin
 * @param A     Initial number of instances of Memory
 * @param B     Initial number of instances of Hard Drive
 * @param C     Initial number of instances of Printers
 */

#include <QApplication>
#include <QtCore>

#include "graphicInterface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int initResources[] = {20,100,5};
    //If the initial number of instances are passed as parameters replace the default values
    if (argc > 1)
    {
        if (argc != 4)
        {
            qDebug() << "Need to specify 3 initial values";
            return 0;
        }
        for (int i = 0 ; i < 3 ; i++)
            initResources[i] = atoi(argv[i+1]);
    }

    GraphicInterface w(initResources[0],initResources[1],initResources[2]);
    w.show();

    return a.exec();
}
