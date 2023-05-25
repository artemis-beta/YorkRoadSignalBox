#ifndef LEVERFRAME_HXX
#define LEVERFRAME_HXX

#include <stdlib.h>

#include <QMap>
#include <QSvgWidget>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>
#include <QSoundEffect>

#include "scaling.hxx"
#include "framelever.hxx"

namespace YRB
{
    class LeverFrame : public QObject
    {
        Q_OBJECT
        private:
            QSoundEffect* _lever_sound = new QSoundEffect;
            QSoundEffect* _lever_failed = new QSoundEffect;
            QMap<int, FrameLever*> _levers;
            const Scaler* scaler_ = new Scaler;
            QWidget* _parent = nullptr;
            QSvgWidget* _frame_svg = nullptr;
            void _play_failed() {_lever_failed->play();}
            void _play_lever_sound() {_lever_sound->play();}
        public:
            LeverFrame(QWidget* parent);
            FrameLever* operator[](const int& i)
            {
                return _levers[i];
            }
            QList<int> levers() const {return _levers.keys();}
            void update(const int& i=-1);
            void moveLever(const int& i, LeverState lever_state, bool points_move)
            {
                if(_levers[i]->getState() == LeverState::Mid) _play_failed();
                else if(lever_state != LeverState::Mid)_play_lever_sound();
                else _play_failed();
                _levers[i]->moveLever(lever_state, points_move);
            }
    };
};
#endif // LEVERFRAME_HXX
