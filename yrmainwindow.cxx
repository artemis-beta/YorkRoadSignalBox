#include "yrmainwindow.hxx"
#include "ui_yrmainwindow.h"

YRMainWindow::YRMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::YRMainWindow)
{
    ui->setupUi(this);
    const YRB::Scaler* scaler_ = new YRB::Scaler;
    this->setFixedSize(scaler_->screen_width(), scaler_->screen_height());

    _add_indicators();

    for(int i{1}; i < 12; ++i)
    {
        _lever_frame_buttons[i] = new QPushButton(this);
        connect(_lever_frame_buttons[i], &QPushButton::clicked, [this, i](){_lever_action(i);});
        _lever_frame_buttons[i]->move(scaler_->scale_width(32+(i-1)*45), 0.72*scaler_->screen_height());
        _lever_frame_buttons[i]->setFixedSize(scaler_->scale_width(20), scaler_->scale_height(80));
        _lever_frame_buttons[i]->setStyleSheet("QPushButton { background-color: transparent; border: 0px }");
    }

    _lever_frame->update();
    connect(_lever_frame, &YRB::LeverFrame::frameUpdate, graphics_, &YRB::Graphics::updateLeverGraphic);
    connect(_interlocking, &YRB::InterLocking::broadcastSignal, graphics_, &YRB::Graphics::updateSignalGraphic);
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

void YRMainWindow::_add_indicators()
{
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection('C'));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection('E'));
    _lever_frame->addSignalMapIndicator(_interlocking->getBlockSection('F'));
}
