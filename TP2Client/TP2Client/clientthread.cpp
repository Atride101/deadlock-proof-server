#include "clientthread.h"
#include <QtNetwork>
#include <time.h>

ClientThread::ClientThread(int id, QString serverIP, int serverPort, int m, QObject *parent)
    : QThread(parent), index(id), serverAddress(serverIP), serverPortNumber(serverPort), M(m)
{
    allocated[0] = 0;
    allocated[1] = 0;
    allocated[2] = 0;

    // Randomization of the maximum requested resources
    // The values cannot be bigger than the total resources of each type
    // These totals are fixed at 20, 100, 5
    srand (time(NULL)); // randomized seed
    maximum[0] = rand() % 21;
    maximum[1] = rand() % 101;
    maximum[2] = rand() % 6;

    //    QString request = "max : " + QString::number(r1Max) + " " + QString::number(r2Max) + " " + QString::number(r3Max);
    //    qDebug() << request;
}

void ClientThread::run()
{
    for (int i = 0; i < M; i++) {

        QTcpSocket socket;
        socket.connectToHost(serverAddress, serverPortNumber);

        if (!socket.waitForConnected())
            qDebug() << "Could not connect, error:\n" << socket.errorString();
        else
            qDebug() << "Connection established";

        // Sending maximum demands
        QString maximumMsg = QString::number(index)
                + " 3 " + QString::number(maximum[0])
                + " " + QString::number(maximum[1])
                + " " + QString::number(maximum[2]);
        socket.write(maximumMsg.toStdString().c_str());
        socket.waitForBytesWritten();

        int request[3];
        if (i < M - 1) {
            // Randomization of the request's resources
            // The values are randomized within a certain range so they are always valid
            while (true) {
                request[0] = rand() % (maximum[0] + 1) - maximum[0] + allocated[0];
                request[1] = rand() % (maximum[1] + 1) - maximum[1] + allocated[1];
                request[2] = rand() % (maximum[2] + 1) - maximum[2] + allocated[2];

                // Checks if the resource requests are either all postive or all negative
                if ((request[0] >= 0 && request[1] >= 0 && request[2] >= 0)
                        || (request[0] <= 0 && request[1]<= 0 && request[2] <= 0))
                    break;
            }
        }
        // Frees all allocated resources with the final request
        else {
            request[0] = allocated[0];
            request[1] = allocated[1];
            request[2] = allocated[2];
        }

        // Sending request
        QString requestMsg = QString::number(index)
                + " 3 " + QString::number(request[0])
                + " " + QString::number(request[1])
                + " " + QString::number(request[2]);
        socket.write(requestMsg.toStdString().c_str());
        socket.waitForBytesWritten();

        // Reading response
        socket.waitForReadyRead();
        char responseMsg[20] = "";
        socket.read(responseMsg, 20);
        qDebug() << QString(responseMsg);
        QStringList responseMsgList = QString(responseMsg).split(" ");
        int response = responseMsgList[0].toInt();

        // Processing response
        if (response == -1)
            break;
        if (response == 1)
            break;
        if (response == 0) {
            allocated[0] -= request[0];
            allocated[1] -= request[1];
            allocated[2] -= request[2];
        }

        //Use the function sleep(s) to put the thread
        //to sleep during s seconds
        sleep(2);
    }

    exit(0);
}
