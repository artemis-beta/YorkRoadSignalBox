#ifndef SIGNAL_HXX
#define SIGNAL_HXX

#include "global_params.hxx"

namespace YRB
{

    class Signal
    {
        private:
            bool _block_occupied = false;
            const int _id = -1;
            SignalState _current_state = SignalState::On;
        public:
            Signal() {}
            Signal(const int& id) : _id(id) {};
            SignalState getState() const {return _current_state;};
            int id() const {return _id;}
            void tryClear(SignalState state = SignalState::Off);
            void setBlockOccupied(bool is_occupied) {_block_occupied = is_occupied;}
            bool protectedBlockOccupied() const {return _block_occupied;}
            void setOn(bool set_on)
            {
                if(set_on) _current_state = SignalState::On;
            }
    };

    class ShuntSignal : public Signal
    {
        public:
            ShuntSignal(const int& id) : Signal(id) {}
    };
};

#endif // SIGNAL_HXX
