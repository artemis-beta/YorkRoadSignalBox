#include "leverframe.hxx"

YRB::LeverFrame::LeverFrame(QWidget* parent)
{
    _parent = parent;
    _frame_svg = new QSvgWidget(QString(":/svgs/media/YRFrame.svg"), _parent);
    const Scaler* scaler_ = new Scaler;
    _frame_svg->setFixedSize(scaler_->screen_width(), scaler_->screen_height());

    for(int i{1}; i < 12; ++i)
    {
        if(QVector<int>({1, 5, 8, 9, 10, 11}).contains(i)) {
            _levers[i] = new YRB::SpareLever(i, _parent);
        }
        else if(QVector<int>({2, 3, 4}).contains(i)) {
            _levers[i] = new YRB::HomeLever(i, _parent);
        }
        else if(i == 7) {
            _levers[i] = new YRB::FacingPointLockLever(i, _parent);
        }
        else {
            _levers[i] = new YRB::PointsLever(i, _parent);
        }
        _levers[i]->PlaceAt(scaler_->scale_width(32+(i-1)*45), 0.72*scaler_->screen_height());
        _levers[i]->showSVG();
    }

    _lever_failed->setSource(QUrl::fromLocalFile(":/audio/audio/lever_fail.wav"));
    _lever_sound->setSource(QUrl::fromLocalFile(":/audio/audio/lever_move_1.wav"));

}

void YRB::LeverFrame::update(const int& i)
{
    qDebug() << "Running Frame Update...";

    if(i == -1)
    {

        for(auto si : _sig_indicators)
        {
            si->update();
        }
    }

    else
    {
        if(_sig_indicators.contains(i))_sig_indicators[i]->update();
    }

    for(const auto& tc : track_circuits_) {
        tc->update();
    }

}

void YRB::LeverFrame::placeSigIndicators()
{
    _sig_indicators[2]->PlaceAt(scaler_->scale_width(155), scaler_->scale_height(136.5));
    _sig_indicators[3]->PlaceAt(scaler_->scale_width(336), scaler_->scale_height(124));
    _sig_indicators[4]->PlaceAt(scaler_->scale_width(336), scaler_->scale_height(166));
}
