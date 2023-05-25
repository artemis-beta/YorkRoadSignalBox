#ifndef FRAMELEVER_HXX
#define FRAMELEVER_HXX

#include <QMainWindow>
#include <QSvgWidget>
#include <QMap>
#include <QObject>
#include <QDebug>
#include <QPushButton>
#include <QScreen>
#include <QGuiApplication>
#include <QSoundEffect>
#include <QTimer>

#include "global_params.hxx"
#include "scaling.hxx"

namespace YRB
{
    class FrameLever;

    class PointsChange : public QObject
    {
        Q_OBJECT
        private:
            FrameLever* _parent;
            QTimer* _timer = new QTimer();
            bool _point_finished = false;
        public:
            PointsChange(FrameLever* _parent);
            bool getState();
            void run()
            {
                _point_finished = false;
                _timer->start(10);
                _point_finished = true;
            }
        public slots:
            void timerEnded()
            {
                if(_point_finished)
                {
                    emit pointFinished();
                }
                _point_finished = false;
            }

        signals:
            void pointFinished();
    };

    class FrameLever : public QObject
    {
        Q_OBJECT
        private:
            QWidget* _parent = nullptr;
            QMap<LeverState, QSvgWidget*> _svgs = {{}};
            PointsChange* _points_change = new PointsChange(this);
            LeverType _type;
            int _coords[2] = {0,0};
            const int _id = -1;
            bool _locked = false;
            LeverState _current_state = LeverState::Off, _prev_state= LeverState::Off;
        public:
            FrameLever(){}
            FrameLever(const int& id, const QString& lever_name, QWidget* parent, LeverType type) :
                _id(id), _parent(parent), _type(type)
            {
                const Scaler* scaler_ = new Scaler;
                connect(_points_change, SIGNAL(pointFinished()), this, SLOT(pointsChangedFinished()));
                _svgs[LeverState::Off] = new QSvgWidget(QString(":/svgs/media/")+lever_name+QString("_LeverBack.svg"), _parent);
                _svgs[LeverState::Off]->setFixedSize(scaler_->scale_width(25), scaler_->scale_height(100));
                _svgs[LeverState::Off]->hide();
                _svgs[LeverState::Mid] = new QSvgWidget(QString(":/svgs/media/")+lever_name+QString("_LeverMid.svg"), _parent);
                _svgs[LeverState::Mid]->setFixedSize(scaler_->scale_width(25), scaler_->scale_height(100));
                _svgs[LeverState::Mid]->hide();
                _svgs[LeverState::On] = new QSvgWidget(QString(":/svgs/media/")+lever_name+QString("_LeverForward.svg"), _parent);
                _svgs[LeverState::On]->setFixedSize(scaler_->scale_width(25), scaler_->scale_height(100));
                _svgs[LeverState::On]->hide();
            }
            LeverState reverse(LeverState state) const
            {
                return (state == LeverState::On) ? LeverState::Off : LeverState::On;
            }
            QSvgWidget* getWidget() const {return _svgs[_current_state];}
            void PlaceAt(const int& x, const int& y);
            void hideSVG();
            void showSVG();
            void moveLever(LeverState state = LeverState::Off, bool points_delay=false);
            void Lock(bool lock_lever) {_locked = lock_lever;}
            bool isLocked() const {return _locked;}
            LeverType getType() const {return _type;}
            LeverState getState() const {return _current_state;}
            int id() const {return _id;}
        signals:
            void sendCurrentLeverDestination(LeverState state);
        public slots:
            void pointsChangedFinished();
    };

    class HomeLever : public FrameLever
    {
        public:
            HomeLever(const int& id, QWidget* parent) : FrameLever(id, QString("Red"), parent, LeverType::Signal) {}
    };

    class PointsLever : public FrameLever
    {
        public:
            PointsLever(const int& id, QWidget* parent) : FrameLever(id, QString("Black"), parent, LeverType::Points){}
    };

    class FacingPointLockLever : public FrameLever
    {
        public:
            FacingPointLockLever(const int& id, QWidget* parent) : FrameLever(id, QString("Blue"), parent, LeverType::Points){}
    };

    class SpareLever : public FrameLever
    {
        public:
            SpareLever(const int& id, QWidget* parent) : FrameLever(id, QString("White"), parent, LeverType::Points){}
    };
};



#endif // FRAMELEVER_HXX