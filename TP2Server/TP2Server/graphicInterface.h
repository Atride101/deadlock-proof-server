#ifndef GRAPHICINTERFACE_H
#define GRAPHICINTERFACE_H

///
/// This class manage the graphical interface
///
/// You really wont need to change
/// this class, but if you do
/// state it in your report
///

#include <QDialog>
#include "resourceMeter.h"
#include "server.h"

#define NUM_MAX_RESOURCES 20

namespace Ui {
class GraphicInterface;
}

class GraphicInterface : public QDialog
{
    Q_OBJECT

public:
    explicit GraphicInterface(int numRAM, int numHD, int numPRI, QWidget *parent = 0);
    ~GraphicInterface();

private slots:
    void on_startButton_clicked();
    void on_quitButton_clicked();
    void addInstanceOfResource(int resourceIndex, int numberOfInstances = 1);

private:
    Ui::GraphicInterface *ui;
    int numberOfResources;
    ResourceMeter* resourcesMeters[NUM_MAX_RESOURCES];
    Server * server;
    QList<QHostAddress> ipv4AddressesList;
};

#endif // GRAPHICINTERFACE_H
