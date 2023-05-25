#include "signal.hxx"

void YRB::Signal::tryClear(YRB::SignalState state)
{
    if(!protectedBlockOccupied())
    {
        _current_state = state;
    }
}
