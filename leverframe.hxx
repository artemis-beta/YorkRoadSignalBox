#ifndef LEVERFRAME_HXX
#define LEVERFRAME_HXX

#include <stdlib.h>

#include <QMap>
#include <QSvgWidget>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QSoundEffect>
#include <QThread>

#include "scaling.hxx"
#include "framelever.hxx"
#include "trackcircuit.hxx"

namespace YRB
{
    class LeverFrame : public QObject
    {
        Q_OBJECT
        private:
            QSoundEffect* _lever_sound = new QSoundEffect;
            QSoundEffect* _lever_failed = new QSoundEffect;
            QSoundEffect* _panel_update = new QSoundEffect;
            QMap<int, FrameLever*> _levers;
            const Scaler* scaler_ = new Scaler;
            QMap<QString, TrackCircuit*> track_circuits_;
            QWidget* _parent = nullptr;
            void _play_failed() {_lever_failed->play();}
            void _play_lever_sound() {_lever_sound->play();}
        public:
            LeverFrame(QWidget* parent);
            FrameLever* operator[](const int& i)
            {
                return _levers[i];
            }
            QList<int> levers() const {return _levers.keys();}
            void update();
            void moveLever(const int& i, LeverState lever_state, bool points_move)
            {
                if(_levers[i]->getState() == LeverState::Mid) _play_failed();
                else if(lever_state != LeverState::Mid)_play_lever_sound();
                else _play_failed();
                _levers[i]->moveLever(lever_state, points_move);
            }
            QMap<QString, TrackCircuit*> getTrackCircuits() {
                return track_circuits_;
            }
        signals:
            void frameUpdate(int id, YRB::LeverState state);
        public slots:
            void frameLeverUpdate(int id, YRB::LeverState state) {
                emit frameUpdate(id, state);
            }
            void panelUpdate() {
                qDebug() << "PLAYING SOUND";
                _panel_update->play();
            }
    };
};
#endif // LEVERFRAME_HXX
