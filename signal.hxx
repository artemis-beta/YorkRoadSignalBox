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
            const int _id = -1;
            bool protected_block_occupied = false;
            SignalState _previous_state = SignalState::On;
            SignalState _current_state = SignalState::On;
        public:
            Signal() {}
            Signal(const int& id) : _id(id) {};
            SignalState getState() const {return _current_state;};
            int id() const {return _id;}
            void tryClear(SignalState state = SignalState::Off) {
                if(!protected_block_occupied)
                {
                    _current_state = state;
                    _previous_state = state;
                    QTimer::singleShot(1000, this, [this]{signalAspectChanged(_id, _current_state);});
                }
            }
            void setOn(bool set_on)
            {
                if(!set_on) return;
                _current_state = SignalState::On;
                _previous_state = SignalState::On;
                QTimer::singleShot(1000, this, [this]{signalAspectChanged(_id, _current_state);});
            }
        signals:
            void signalAspectChanged(int id, YRB::SignalState state);
        public slots:
            void signalUpdateFromBlock(bool is_occupied)
            {
                protected_block_occupied = is_occupied;
                if(is_occupied) _current_state = SignalState::On;
                _current_state = _previous_state;
            }
    };

    class ShuntSignal : public Signal
    {
        public:
            ShuntSignal(const int& id) : Signal(id) {}
    };
};

#endif // SIGNAL_HXX
