#ifndef SIGNAL_HXX
#define SIGNAL_HXX

#include <QObject>
#include <QTimer>
#include "global_params.hxx"

namespace YRB
{

    class Signal : public QObject
    {
        Q_OBJECT
        private:
            bool _block_occupied = false;
            const int _id = -1;
            SignalState _current_state = SignalState::On;
        public:
            Signal() {}
            Signal(const int& id) : _id(id) {};
            SignalState getState() const {return _current_state;};
            int id() const {return _id;}
            void tryClear(SignalState state = SignalState::Off) {
                if(!protectedBlockOccupied())
                {
                    _current_state = state;
                    QTimer::singleShot(1000, this, [this]{signalAspectChanged(_id, _current_state);});
                }
            }
            void setBlockOccupied(bool is_occupied) {_block_occupied = is_occupied;}
            bool protectedBlockOccupied() const {return _block_occupied;}
            void setOn(bool set_on)
            {
                if(!set_on) return;
                _current_state = SignalState::On;
                QTimer::singleShot(1000, this, [this]{signalAspectChanged(_id, _current_state);});
            }
        signals:
            void signalAspectChanged(int id, YRB::SignalState state);
    };

    class ShuntSignal : public Signal
    {
        public:
            ShuntSignal(const int& id) : Signal(id) {}
    };
};

#endif // SIGNAL_HXX
