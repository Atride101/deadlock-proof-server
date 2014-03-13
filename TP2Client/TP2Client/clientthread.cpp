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
    int r1Max = rand() % 21;
    int r2Max = rand() % 101;
    int r3Max = rand() % 6;

    max[0] = r1Max;
    max[1] = r2Max;
    max[2] = r3Max;

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
        QString maximum = QString::number(index) + " 3 " + QString::number(max[0]) + " " + QString::number(max[1]) + " " + QString::number(max[2]);
        socket.write(maximum.toStdString().c_str());
        socket.waitForBytesWritten();

        int r1, r2, r3;
        if (i < M - 1) {
            // Randomization of the request's resources
            // The values are limited to the number of total resources of each type
            // These totals are fixed at 20, 100, 5
            bool valid = 0;
            while (!valid) {
                r1 = rand() % (max[0] + 1) - max[0] + allocated[0];
                r2 = rand() % (max[1] + 1) - max[1] + allocated[1];
                r3 = rand() % (max[2] + 1) - max[2] + allocated[2];

                // Checks if the resource requests are either all postive or all negative
                if ((r1 >= 0 && r2 >= 0 && r3 >= 0) || (r1 <= 0 && r2 <= 0 && r3 <= 0))
                    valid = 1;
            }
        }
        // Frees all allocated resources with the final request
        else {
            r1 = allocated[0];
            r2 = allocated[1];
            r3 = allocated[2];
        }

        allocated[0] -= r1;
        allocated[1] -= r2;
        allocated[2] -= r3;

        // Sending request
        QString request = QString::number(index) + " 3 " + QString::number(r1) + " " + QString::number(r2) + " " + QString::number(r3);
//        qDebug() << QString(request);
        socket.write(request.toStdString().c_str());
        socket.waitForBytesWritten();

        // Reading response
        socket.waitForReadyRead();
        char message[20] = "vide";
        socket.read(message, 20);
        qDebug() << QString(message);

        // Processing response

        //Use the function sleep(s) to put the thread
        //to sleep during s seconds
        sleep(2);
    }

    exit(0);
}
