#ifndef SIMULATIONPANEL_HXX
#define SIMULATIONPANEL_HXX

#include <QMainWindow>
#include <QObject>
#include <QPushButton>

#include "scaling.hxx"

class SimulationPanel : public QMainWindow
{
    Q_OBJECT
public:
    explicit SimulationPanel(QWidget *parent = nullptr);
    QPushButton* runButton(){return run_button_;}
private:
    QPushButton* run_button_ = new QPushButton(this);
};

#endif // SIMULATIONPANEL_HXX
