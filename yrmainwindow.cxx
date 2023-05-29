#include "yrmainwindow.hxx"
#include "ui_yrmainwindow.h"

YRMainWindow::YRMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::YRMainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("York Road Signal Frame");
    const YRB::Scaler* scaler_ = new YRB::Scaler;
    this->setFixedSize(scaler_->screen_width(), scaler_->screen_height());
    _signal_34->show();

    for(int i{1}; i < 12; ++i)
    {
        _lever_frame_buttons[i] = new QPushButton(this);
        connect(_lever_frame_buttons[i], &QPushButton::clicked, [this, i](){_lever_action(i);});
        _lever_frame_buttons[i]->move(scaler_->scale_width(32+(i-1)*45), 0.72*scaler_->screen_height());
        _lever_frame_buttons[i]->setFixedSize(scaler_->scale_width(20), scaler_->scale_height(80));
        _lever_frame_buttons[i]->setStyleSheet("QPushButton { background-color: transparent; border: 0px }");
    }

    _lever_frame->update();
    connect(_lever_frame, &YRB::LeverFrame::frameUpdate, _graphics, &YRB::Graphics::updateLeverGraphic);
    connect(_interlocking, &YRB::InterLocking::broadcastSignal, _graphics, &YRB::Graphics::updateSignalGraphic);
    connect(_interlocking, &YRB::InterLocking::broadcastSignal, _signal_34, &Signal34::setSignal);
    connect(_interlocking, &YRB::InterLocking::broadcastPoints, _graphics, &YRB::Graphics::updatePointsGraphic);
    connect(_interlocking, &YRB::InterLocking::broadcastPoints, _signal_34, &Signal34::setFeatherIndicator);
    connect(_interlocking, &YRB::InterLocking::broadcastSignal, _lever_frame, &YRB::LeverFrame::panelUpdate);
    connect(_interlocking, &YRB::InterLocking::broadcastPoints, _lever_frame, &YRB::LeverFrame::panelUpdate);
}

void YRMainWindow::_run_service() {

    if(_simulation_running) {
        qDebug() << "Simulation already running";
        return;
    }
    _service_position = 'A';
    _simulation_running = true;

    while(_service_position != 'G' && _service_position != 'F')
    {
        QTimer::singleShot(5000, this, &YRMainWindow::_move_service);
    }
    _service_position = '\0';
}

YRMainWindow::~YRMainWindow()
{
    delete ui;
}

void YRMainWindow::_lever_action(const int &i)
{

    if(!_interlocking->Query(i))
    {
        qDebug() << "Invalid Move";
        return;
    }
    _lever_frame->update();
}
