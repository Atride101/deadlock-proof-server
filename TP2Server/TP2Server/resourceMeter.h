#ifndef RESOURCEMETER_H
#define RESOURCEMETER_H

///
/// This class implements just
/// a graphical meter to show
/// the currently available resources
///
/// You really wont need to change
/// this class, but if you do
/// state it in your report
///

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QTcpServer>

class ResourceMeter : public QWidget
{
    Q_OBJECT
public:
    explicit ResourceMeter(QString name, int min, int max, int current = -1, QWidget *parent = 0);

signals:

public slots:
    //To substract from just send a negative number
    void addResources(int n = 1);

private:
    QLabel *nameLabel;
    QProgressBar *bar;
};

#endif // RESOURCEMETER_H
