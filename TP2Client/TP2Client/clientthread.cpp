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

    QString maximumMsg = "max : " + QString::number(maximum[0]) + " " + QString::number(maximum[1]) + " " + QString::number(maximum[2]);
    qDebug() << maximumMsg;
}

void ClientThread::run()
{
    int request[3];
    bool wait = false;
    char responseMsg[20] = "";
    QString maximumMsg = QString::number(index)
            + " 3 " + QString::number(maximum[0])
            + " " + QString::number(maximum[1])
            + " " + QString::number(maximum[2])
            + "\n";

    // Loop over the M requests made by one process
    for (int i = 0; i < M; i++) {

        if (i < M - 1) {
            // Randomization of the request's resources
            // The values are randomized within a certain range (they are always valid)
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

        // Loop over the same request if the request is refused by the
        // server because the resources are unavailable at the time
        do {
            QTcpSocket socket;
            socket.connectToHost(serverAddress, serverPortNumber);

            if (!socket.waitForConnected())
                qDebug() << "Could not connect, error:\n" << socket.errorString();
            else
                qDebug() << "Connection established";

            // Sending maximum resource demands
            socket.write(maximumMsg.toStdString().c_str());
            socket.waitForBytesWritten();

            // Sending request
            QString requestMsg = QString::number(index)
                    + " 3 " + QString::number(request[0])
                    + " " + QString::number(request[1])
                    + " " + QString::number(request[2])
                    + "\n";
            socket.write(requestMsg.toStdString().c_str());
            socket.waitForBytesWritten();
            qDebug() << "request : " << requestMsg;

            // Reading response
            socket.waitForReadyRead();
            socket.readLine(responseMsg, 20);
            qDebug() << "response : " << QString(responseMsg);
            QStringList responseMsgList = QString(responseMsg).split(" ");
            int response = responseMsgList[0].toInt();

            // Processing response
            if (response == -1) {
                wait = false;
                break;
            }
            if (response > 0) {
                wait = true;
                sleep(response);
            }
            if (response == 0) {
                wait = false;
                allocated[0] -= request[0];
                allocated[1] -= request[1];
                allocated[2] -= request[2];
            }

            socket.close();

        } while (wait == true);

        sleep(1);
    }

    exit(0);
}
