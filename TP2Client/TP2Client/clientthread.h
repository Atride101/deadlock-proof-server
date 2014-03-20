#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>

#define NUMBER_OF_RESOURCES 3

class ClientThread : public QThread
{
    Q_OBJECT
public:
    ClientThread(int id, QString serverIP, int serverPort, int m, QObject *parent);

    void run();

private:
    int         index;
    QString     serverAddress;
    int         serverPortNumber;
    int         M;
    int         allocated[NUMBER_OF_RESOURCES];
    int         maximum[NUMBER_OF_RESOURCES];
};

#endif // CLIENTTHREAD_H
