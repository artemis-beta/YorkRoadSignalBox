#ifndef YRMAINWINDOW_HXX
#define YRMAINWINDOW_HXX

#include <QMainWindow>
#include "leverframe.hxx"
#include "interlocking.hxx"
#include "graphics.hxx"
#include "signal_34.hxx"

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
    Signal34* _signal_34 = new Signal34(this);
    QList<QThread*> _threads = {};
    ~YRMainWindow();

private:
    Ui::YRMainWindow *ui;
    char _service_position{'\0'};
    bool _simulation_running{false};
    void _lever_action(const int& i);
    void _run_service();
    QMap<int, QPushButton*> _lever_frame_buttons;
public slots:
    void _move_service()
    {
       _interlocking->getBlockSection(_service_position)->setOccupied(true);
       _service_position = _interlocking->getBlockSection(_service_position)->getNeighbour()->id();
    }
};
#endif // YRMAINWINDOW_HXX
