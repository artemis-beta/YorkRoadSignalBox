#include "simulationpanel.hxx"

SimulationPanel::SimulationPanel(QWidget *parent)
    : QMainWindow{parent}
{
    const YRB::Scaler* scaler_ = new YRB::Scaler;
    this->setGeometry(1.02*scaler_->screen_width(), 0.82*scaler_->screen_height(), 0.2*scaler_->screen_width(), 0.1*scaler_->screen_height());
    this->setWindowTitle("Simulations");
    run_button_->move(0.3*this->width(), 0.1*this->height());
    run_button_->setText("Run");
    run_button_->show();
}
