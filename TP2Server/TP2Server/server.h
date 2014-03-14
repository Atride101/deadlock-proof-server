#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>

#define NUMBER_OF_RESOURCES 3
#define NUMBER_OF_CUSTOMERS 5

class Server : public QObject
{
    Q_OBJECT
public:
    Server(int numResources[], QWidget *parent = 0);
    bool isRunning();
    int getPort();
    void addInstancesOfResources(int numberOfInstances[NUMBER_OF_RESOURCES]);

signals:
    void sendMessageToLog(QString message);
    void updateAddResourceInGUI(int resourceIndex, int numberOfInstances);

public slots:
    bool startServer(const QString &address, quint16 port = 0);
    void stopServer();
    void processRequest();

private:
    void printStreamToLog();
    int validateRequest(int user, int request[3]);
    bool safeState();

    QWidget *parentWidget;
    QTcpServer *tcpServer;
    QTextStream logStream;
    QString logString;

    //Data structures needed to implement bankers algorithm
    int available   [NUMBER_OF_RESOURCES];
    int maximum     [NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int allocation  [NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
    int need        [NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
};

#endif
