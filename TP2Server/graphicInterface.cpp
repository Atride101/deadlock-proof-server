///
/// This class manage the graphical interface
///
/// You really wont need to change
/// this class, but if you do
/// state it in your report
///

#include <QtNetwork>
#include "graphicInterface.h"
#include "ui_graphicInterface.h"

GraphicInterface::GraphicInterface(int numRAM, int numHD, int numPRI, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GraphicInterface)
{
    ui->setupUi(this);

    //Look for available IP's to connect
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // add to the IP combo box all IPv4 address, including localhost(127.0.0.1)
    for (int i = 0; i < ipAddressesList.size(); i++) {
        if (ipAddressesList.at(i).toIPv4Address())
        {
            ui->ipCombo->addItem(ipAddressesList.at(i).toString());
            ipv4AddressesList.push_back(ipAddressesList.at(i));
        }
    }

    // Set Different Resources names and values
    QString resourcesNames[]      = {"RAM Memory: ","Hard Drive:     ", "Printers:          "};
    int numInstancesOfResource[]  = {numRAM,numHD,numPRI};
    numberOfResources = 3;

    //Create server
    server = new Server(numInstancesOfResource,this);
    connect(server,SIGNAL(sendMessageToLog(QString)),ui->logTextBox,SLOT(appendPlainText(QString)));
    connect(server,SIGNAL(updateAddResourceInGUI(int,int)),this,SLOT(addInstanceOfResource(int,int)));

    QVBoxLayout *resourcesLayout = new QVBoxLayout;
    for (int i = 0 ; i < numberOfResources ; i++)
    {
        resourcesMeters[i] = new ResourceMeter(resourcesNames[i],0,numInstancesOfResource[i],numInstancesOfResource[i]);
        resourcesLayout->addWidget(resourcesMeters[i]);
    }
    ui->resourcesFrame->setLayout(resourcesLayout);
}

GraphicInterface::~GraphicInterface()
{
    server->stopServer();
    delete ui;
}

void GraphicInterface::addInstanceOfResource(int resourceIndex, int numberOfInstances)
{//Update resource bar/meter
    resourcesMeters[resourceIndex]->addResources(numberOfInstances);
}

void GraphicInterface::on_startButton_clicked()
{
    if (!server->isRunning())
    {
        if ( server->startServer(ui->ipCombo->currentText(),ui->portLineEdit->text().toInt()))
        {
            ui->statusLabel->setText("Server is running on:");
            ui->startButton->setText("Stop server");
            ui->ipCombo->setEnabled(false);
            ui->portLineEdit->setText(QString::number(server->getPort()));
            ui->portLineEdit->setEnabled(false);
        }
    }
    else
    {
        server->stopServer();
        ui->statusLabel->setText("Server is not running");
        ui->startButton->setText("Start server");
        ui->ipCombo->setEnabled(true);
        ui->portLineEdit->setEnabled(true);
    }
}

void GraphicInterface::on_quitButton_clicked()
{
    this->close();
}
