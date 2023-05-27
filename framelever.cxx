#include "framelever.hxx"

void YRB::FrameLever::moveLever(YRB::LeverState state, bool points_delay)
{
    if(state == YRB::LeverState::Mid && _current_state != state)
    {
        _prev_state = _current_state;
        _current_state = state;
        return;
    }

    if(_current_state == LeverState::Off)
    {
        _prev_state = _current_state;
        _current_state = LeverState::On;
    }
    else if(_current_state == LeverState::Mid)
    {
        _current_state = (_locked) ? _prev_state : reverse(_prev_state);

    }
    else
    {
        _prev_state = _current_state;
        _current_state = LeverState::Off;
    }

    emit leverUpdate(this->id(), _current_state);
}

void YRB::FrameLever::pointsChangedFinished()
{
    _current_state = reverse(_prev_state);
}
