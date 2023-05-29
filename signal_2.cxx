#include "signal_2.hxx"

Signal2::Signal2(QWidget *parent)
    : QMainWindow{parent}
{
    const YRB::Scaler* scaler_ = new YRB::Scaler;
    this->setGeometry(1.02*scaler_->screen_width(), 0.4*scaler_->screen_height(), 0.2*scaler_->screen_width(), 0.3*scaler_->screen_height());
    this->setWindowTitle("YR.2");
    signal_2_svg_->setGeometry(0, 0, this->width(), this->height());
    signal_2_svg_->show();
    stop_svgs_[YRB::SignalState::Off] = new QSvgWidget(":/svgs/media/Sig34_Off.svg", this);
    stop_svgs_[YRB::SignalState::Caution] = new QSvgWidget(":/svgs/media/Sig34_Off.svg", this);
    stop_svgs_[YRB::SignalState::On] = new QSvgWidget(":/svgs/media/Sig34_RedOn.svg", this);
    clear_svgs_[YRB::SignalState::On] = new QSvgWidget(":/svgs/media/Sig34_Off.svg", this);
    clear_svgs_[YRB::SignalState::Caution] = new QSvgWidget(":/svgs/media/Sig34_Off.svg", this);
    clear_svgs_[YRB::SignalState::Off] = new QSvgWidget(":/svgs/media/Sig34_GreenOn.svg", this);
    amber_svgs_[YRB::SignalState::Off] = new QSvgWidget(":/svgs/media/Sig34_Off.svg", this);
    amber_svgs_[YRB::SignalState::On] = new QSvgWidget(":/svgs/media/Sig34_Off.svg", this);
    amber_svgs_[YRB::SignalState::Caution] = new QSvgWidget(":/svgs/media/Sig34_AmberOn.svg", this);

    subsid_stop_svgs_[YRB::SignalState::Off] = new QSvgWidget(":/svgs/media/Sig34Subsid_Off.svg", this);
    subsid_stop_svgs_[YRB::SignalState::Caution] = new QSvgWidget(":/svgs/media/Sig34Subsid_Off.svg", this);
    subsid_stop_svgs_[YRB::SignalState::On] = new QSvgWidget(":/svgs/media/Sig34Subsid_RedOn.svg", this);
    subsid_clear_svgs_[YRB::SignalState::On] = new QSvgWidget(":/svgs/media/Sig34Subsid_Off.svg", this);
    subsid_clear_svgs_[YRB::SignalState::Caution] = new QSvgWidget(":/svgs/media/Sig34Subsid_Off.svg", this);
    subsid_clear_svgs_[YRB::SignalState::Off] = new QSvgWidget(":/svgs/media/Sig34Subsid_GreenOn.svg", this);
    subsid_amber_svgs_[YRB::SignalState::Off] = new QSvgWidget(":/svgs/media/Sig34Subsid_Off.svg", this);
    subsid_amber_svgs_[YRB::SignalState::On] = new QSvgWidget(":/svgs/media/Sig34Subsid_Off.svg", this);
    subsid_amber_svgs_[YRB::SignalState::Caution] = new QSvgWidget(":/svgs/media/Sig34Subsid_AmberOn.svg", this);

    set_stop_sig_size_(0.052*scaler_->screen_width(), 0.052*scaler_->screen_width());
    set_stop_sig_position_(0.076*scaler_->screen_width(), 0.1672*scaler_->screen_height());

    set_clear_sig_size_(0.051*scaler_->screen_width(), 0.051*scaler_->screen_width());
    set_clear_sig_position_(0.0761*scaler_->screen_width(), 0.045*scaler_->screen_height());

    set_caution_sig_size_(0.051*scaler_->screen_width(), 0.051*scaler_->screen_width());
    set_caution_sig_position_(0.0761*scaler_->screen_width(), 0.106*scaler_->screen_height());

    set_clear_subsid_position_(0.123*scaler_->screen_width(), 0.08*scaler_->screen_width());
    set_clear_subsid_size_(0.022*scaler_->screen_width(), 0.022*scaler_->screen_height());

    set_stop_subsid_position_(0.123*scaler_->screen_width(), 0.194*scaler_->screen_width());
    set_stop_subsid_size_(0.022*scaler_->screen_width(), 0.022*scaler_->screen_height());

    set_caution_subsid_position_(0.123*scaler_->screen_width(), 0.136*scaler_->screen_width());
    set_caution_subsid_size_(0.022*scaler_->screen_width(), 0.022*scaler_->screen_height());
    setAspect(YRB::SignalState::On);
}

void Signal2::set_clear_sig_position_(const int x, const int y)
{
    for(QSvgWidget* sig_aspect : clear_svgs_) {
        sig_aspect->move(x, y);
    }
}

void Signal2::set_clear_sig_size_(const int x, const int y)
{
    for(QSvgWidget* sig_aspect : clear_svgs_) {
        sig_aspect->setFixedSize(x, y);
    }
}

void Signal2::set_caution_sig_position_(const int x, const int y)
{
    for(QSvgWidget* sig_aspect : amber_svgs_) {
        sig_aspect->move(x, y);
    }
}

void Signal2::set_caution_sig_size_(const int x, const int y)
{
    for(QSvgWidget* sig_aspect : amber_svgs_) {
        sig_aspect->setFixedSize(x, y);
    }
}

void Signal2::set_stop_sig_position_(const int x, const int y)
{
    for(QSvgWidget* sig_aspect : stop_svgs_) {
        sig_aspect->move(x, y);
    }
}

void Signal2::set_stop_sig_size_(const int x, const int y)
{
    for(QSvgWidget* sig_aspect : stop_svgs_) {
        sig_aspect->setFixedSize(x, y);
    }
}

void Signal2::set_clear_subsid_position_(const int x, const int y)
{
    for(QSvgWidget* sig_aspect : subsid_clear_svgs_) {
        sig_aspect->move(x, y);
    }
}

void Signal2::set_clear_subsid_size_(const int x, const int y)
{
    for(QSvgWidget* sig_aspect : subsid_clear_svgs_) {
        sig_aspect->setFixedSize(x, y);
    }
}

void Signal2::set_caution_subsid_position_(const int x, const int y)
{
    for(QSvgWidget* sig_aspect : subsid_amber_svgs_) {
        sig_aspect->move(x, y);
    }
}

void Signal2::set_caution_subsid_size_(const int x, const int y)
{
    for(QSvgWidget* sig_aspect : subsid_amber_svgs_) {
        sig_aspect->setFixedSize(x, y);
    }
}

void Signal2::set_stop_subsid_position_(const int x, const int y)
{
    for(QSvgWidget* sig_aspect : subsid_stop_svgs_) {
        sig_aspect->move(x, y);
    }
}

void Signal2::set_stop_subsid_size_(const int x, const int y)
{
    for(QSvgWidget* sig_aspect : subsid_stop_svgs_) {
        sig_aspect->setFixedSize(x, y);
    }
}
