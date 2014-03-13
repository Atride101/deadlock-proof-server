#include <QtNetwork>

#include <stdlib.h>
#include <iostream>
#include <stdio.h>

#include "server.h"

Server::Server(int numResources[], QWidget *parent)
:   parentWidget(parent)
{
    tcpServer = new QTcpServer(parentWidget);
    // For this QTcpServer whenever a new conection is detected
    // we call the function proccesRequest()
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(processRequest()));
    logStream.setString(&logString);

    //Initialization of data structures
    for (int i = 0 ; i < NUMBER_OF_RESOURCES ; i++)
        available[i] = numResources[i];
}

/// This function is called whenever the system
/// receives a connection. The function "nextPendingConnection()"
/// takes one request from a internal list of pending connections
/// and returns it as a object QTcpSoket, to read, or write on it
void Server::processRequest()
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    logStream << "-Processing request from ip: " << clientConnection->peerAddress().toString();
    printStreamToLog();

    // Reading the maximum requested resources
    clientConnection->waitForReadyRead();
    char max[20] = "empty";
    qDebug() << clientConnection->read(max, 20);
    QStringList maxList = QString(max).split(" ");
    int user = maxList[0].toInt();
    int r1Max = maxList[2].toInt();
    int r2Max = maxList[3].toInt();
    int r3Max = maxList[4].toInt();

    // Writing maximum requested resources in database
    maximum[user][0] = r1Max;
    maximum[user][1] = r2Max;
    maximum[user][2] = r3Max;

    // Reading the request
    clientConnection->waitForReadyRead();
    char request[20] = "empty";
    qDebug() << clientConnection->read(request, 20);
    logStream << QString(request);
    printStreamToLog();
    QStringList requestList = QString(request).split(" ");
    //int user = requestList[0].toInt();
    int r1 = requestList[2].toInt();
    int r2 = requestList[3].toInt();
    int r3 = requestList[4].toInt();

    // Processing the request
    int modifiedResources [] = {r1, r2, r3};
    addInstancesOfResources(modifiedResources);

    // Writing response
    QString response = QString::number(user) + " " + QString::number(r1) + " " + QString::number(r2) + " " + QString::number(r3);
    clientConnection->write(response.toStdString().c_str());
    clientConnection->waitForBytesWritten();

    //Close conection and free the memory once the connection is lost
    connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));
    clientConnection->disconnectFromHost();
}

/// This funtion should update the values of the
/// data structures when a request is granted
void Server::addInstancesOfResources(int numberOfInstances[NUMBER_OF_RESOURCES])
{
    /// This is to update the values of the resource meters
    /// in the GUI, (positive values add to the respective
    /// meter bar and negative values reduce it)
    for (int i = 0 ; i < NUMBER_OF_RESOURCES ; i++)
        emit updateAddResourceInGUI(i, numberOfInstances[i]);
}



/// This is a convinient function to easily print to the log window in the GUI
/// Call it after adding some output to "logStream"
void Server::printStreamToLog(){
    emit sendMessageToLog(logString);
    logStream.flush();
    logString.clear();
}

/// This function makes the server to listen to the
/// address and port specified by the GUI and prints a message to the GUI log
bool Server::startServer(const QString & address, quint16 port)
{
    if (tcpServer->listen(QHostAddress(address),port))
    {
        logStream << tr("The server started on\n\nIP: %1\nport: %2\n\n").arg(address).arg(tcpServer->serverPort());
        logStream << "with " << NUMBER_OF_RESOURCES << " types of resources:\n";
        for (int i = 0 ; i < NUMBER_OF_RESOURCES ; i++)
            logStream << available[i] << " ";
        logStream << "\n-Start the client application now.";
        printStreamToLog();
        return true;
    }

    logStream << tr("-Unable to start the server: %1.").arg(tcpServer->errorString());
    printStreamToLog();
    return false;
}

/// This function stops the server and prints a message to the GUI log
void Server::stopServer()
{
    tcpServer->close();
    logStream << "-Server has stopped\n";
    logStream << "-----------------------";
    printStreamToLog();
}

/// This funtion returns true if server is running, false otherwise
bool Server::isRunning(){
    return tcpServer->isListening();
}

/// This funtion returns the port number
int Server::getPort(){
    return tcpServer->serverPort();
}
