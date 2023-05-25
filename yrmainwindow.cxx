#include "yrmainwindow.hxx"
#include "ui_yrmainwindow.h"

YRMainWindow::YRMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::YRMainWindow)
{
    ui->setupUi(this);
    const YRB::Scaler* scaler_ = new YRB::Scaler;
    this->setFixedSize(scaler_->screen_width(), scaler_->screen_height());
}

YRMainWindow::~YRMainWindow()
{
    delete ui;
}

