#include "clientthread.h"
#include <QtNetwork>
#include <time.h>

ClientThread::ClientThread(int id, QString serverIP, int serverPort, int m, QObject *parent)
    : QThread(parent), index(id), serverAddress(serverIP), serverPortNumber(serverPort), M(m)
{
    // Initialization of data structures
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
        allocated[i] = 0;

    int totalResources[NUMBER_OF_RESOURCES] = {20, 100, 5};

    // Randomization of the maximum requested resources
    // The values cannot be bigger than the total resources of each type
    // These totals are fixed at 20, 100, 5
    srand (time(NULL)); // randomized seed
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
        maximum[i] = rand() % (totalResources[i] + 1);
}

void ClientThread::run()
{
    int sleepTime = 0;
    bool wait = false;

    //********************************************
    // Sending maximum resource needs to the server
    //********************************************
    QTcpSocket socket;
    socket.connectToHost(serverAddress, serverPortNumber);

    if (!socket.waitForConnected())
        qDebug() << "Could not connect, error:\n" << socket.errorString();
    else
        qDebug() << "Connection established";

    QString maximumMsg = QString::number(index) + " " + QString::number(NUMBER_OF_RESOURCES);
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
        maximumMsg += " " + QString::number(maximum[i]);
    qDebug() << "    Sending maximum: " << maximumMsg;

    // Writing maximum to socket
    socket.write(maximumMsg.toStdString().c_str());
    socket.waitForBytesWritten();

    socket.disconnectFromHost();
    // Artificial waiting time added to make the server alternate between the processes
    sleep(1);

    //********************************************
    // Sending requests to the server
    //********************************************
    // Loop over the M requests made by one process
    for (int i = 0; i < M; i++) {
        int request[NUMBER_OF_RESOURCES];

        if (i < M - 1) {
            // Randomization of the request's resources
            // The values are randomized within a certain range (they are always valid)
            while (true) {
                for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
                    request[i] = rand() % (maximum[i] + 1) - maximum[i] + allocated[i];

                // Checks if the resource requests are either all positive or all negative
                bool allPositive = true;
                for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
                    if (request[i] < 0)
                        allPositive = false;
                }

                bool allNegative = true;
                for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
                    if (request[i] > 0)
                        allNegative = false;
                }

                if (allPositive || allNegative)
                    break;
            }
        }
        // Frees all allocated resources with the final request
        else {
            for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
                request[i] = allocated[i];
        }

        // Try the same request again after a certain time if the request is
        // refused by the server because the resources are unavailable at the time
        do {
            QTcpSocket socket;
            socket.connectToHost(serverAddress, serverPortNumber);

            if (!socket.waitForConnected())
                qDebug() << "Could not connect, error:\n" << socket.errorString();
            else
                qDebug() << "Connection established";

            QString requestMsg = QString::number(index) + " " + QString::number(NUMBER_OF_RESOURCES);
            for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
                requestMsg += " " + QString::number(request[i]);
            qDebug() << "    Request: " << requestMsg;

            // Writing request to socket
            socket.write(requestMsg.toStdString().c_str());
            socket.waitForBytesWritten();

            // Reading response
            socket.waitForReadyRead();
            char responseMsg[20] = "";
            socket.read(responseMsg, 20);
            qDebug() << "    Response: " << QString(responseMsg);

            //Parsing response
            QStringList responseMsgList = QString(responseMsg).split(" ");
            int response = responseMsgList[0].toInt();

            // Processing response
            if (response == -1) {
                wait = false;
                sleepTime = 0;
            }
            if (response > 0) {
                wait = true;
                sleepTime = response;
            }
            if (response == 0) {
                wait = false;
                sleepTime = 0;
                for (int i = 0; i < NUMBER_OF_RESOURCES; i++)
                    allocated[i] -= request[i];
            }

            socket.disconnectFromHost();
            // Artificial waiting time added to make the server alternate between the processes
            sleep(1);

        } while (wait == true);

        // The amount of time to wait before sending the same request again
        sleep(sleepTime);
    }

    exit(0);
}
