#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QThread>
#include <QTcpSocket>

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
    int         allocated[3];
    int         max[3];
};

#endif // CLIENTTHREAD_H
