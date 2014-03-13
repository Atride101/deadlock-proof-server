/*!
 * TP2 - IFT2245
 * Client application to emulate N clients making
 * M random requests. (to be run alonside the server
 * application using the same IP address and port)
 *
 * @author David Quiroz Marin
 * @param IP address
 * @param Conextion Port
 * @param N     The number of clients
 * @param M     The number of random requests
 */

#include <QCoreApplication>
#include "clientthread.h"

#define MAX_NUM_CLIENTS 10000

ClientThread *client[MAX_NUM_CLIENTS];

int main(int argc, char *argv[])
{
    QCoreApplication app(argc,argv);
    if (argc == 1 || argc != 5)
    {
        qDebug() << "Need to specify the following parameters:\n"
                    "server_ip_address server_port num_clients num_request";
        return 0;
    }
    int N = atoi(argv[3]);
    for (int i = 0 ; i <  N ; i++)
    {
        client[i] = new ClientThread(i, argv[1], atoi(argv[2]),atoi(argv[4]),&app);
        client[i]->start();
        sleep(1);
    }


    //We wait for all threads to finish before
    //closing the application and deleting the threads
    for (int i = 0 ; i < N ; i++)
        client[i]->wait(); //Similar pthread_join() function

    return 0;
}
