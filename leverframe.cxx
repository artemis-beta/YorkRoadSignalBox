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

//    connect(_levers[13], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd13(EWRB::LeverState)));
//    connect(_levers[14], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd14(EWRB::LeverState)));
//    connect(_levers[15], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd15(EWRB::LeverState)));
//    connect(_levers[17], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd17(EWRB::LeverState)));
//    connect(_levers[19], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd19(EWRB::LeverState)));
//    connect(_levers[20], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd20(EWRB::LeverState)));
//    connect(_levers[21], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd21(EWRB::LeverState)));
//    connect(_levers[22], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd22(EWRB::LeverState)));
//    connect(_levers[23], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd23(EWRB::LeverState)));
//    connect(_levers[26], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd26(EWRB::LeverState)));
//    connect(_levers[27], SIGNAL(sendCurrentLeverDestination(EWRB::LeverState)), this, SLOT(updatePointsInd27(EWRB::LeverState)));


}
