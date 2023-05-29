#ifndef YRMAINWINDOW_HXX
#define YRMAINWINDOW_HXX

#include <QMainWindow>
#include <QTimer>
#include "leverframe.hxx"
#include "interlocking.hxx"
#include "graphics.hxx"
#include "signal_34.hxx"
#include "signal_2.hxx"
#include "simulationpanel.hxx"

QT_BEGIN_NAMESPACE
namespace Ui { class YRMainWindow; }
QT_END_NAMESPACE

class YRMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    YRMainWindow(QWidget *parent = nullptr);
    YRB::LeverFrame* _lever_frame = new YRB::LeverFrame(this);
    YRB::InterLocking* _interlocking = new YRB::InterLocking(_lever_frame);
    YRB::Graphics* _graphics = new YRB::Graphics(this);
    QTimer* _sim_timer = new QTimer(this);
    Signal34* _signal_34 = new Signal34(this);
    Signal2* _signal_2 = new Signal2(this);
    SimulationPanel* _sim_panel = new SimulationPanel(this);
    QList<QThread*> _threads = {};
    ~YRMainWindow();

private:
    Ui::YRMainWindow *ui;
    char _service_position{'\0'};
    bool _simulation_running{false};
    void _lever_action(const int& i);
    QMap<int, QPushButton*> _lever_frame_buttons;
public slots:
    void move_service()
    {
       _interlocking->getBlockSection(_service_position)->setOccupied(true);

       // Check that the signal of the neighbouring block is clear
       if(_interlocking->getBlockSection(_service_position)->getNeighbour()->getBlockSignal()) {
            if(_interlocking->getBlockSection(_service_position)->getNeighbour()->getBlockSignal()->getState() == YRB::SignalState::On) return;
       }
       emit block_motion(_service_position, _interlocking->getBlockSection(_service_position)->getNeighbour()->id());
       _service_position = _interlocking->getBlockSection(_service_position)->getNeighbour()->id();
       qDebug() << _service_position;
    }
    void block_motion(char origin, char destination) {
        QTimer::singleShot(500, _graphics, [this, destination](){_graphics->updateBlockGraphic(destination, true);});
        QTimer::singleShot(1500, _graphics, [this, origin](){_graphics->updateBlockGraphic(origin, false);});
    }
    void run_service() {
        if(_simulation_running) {
            qDebug() << "Simulation already running";
            return;
        }
        _service_position = 'A';
        emit _graphics->updateBlockGraphic('A', true);
        _simulation_running = true;
        qDebug() << "Starting timer";
        _sim_timer->start();
    }

};
#endif // YRMAINWINDOW_HXX
