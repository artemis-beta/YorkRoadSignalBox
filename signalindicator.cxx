#include "signalindicator.hxx"

void YRB::SignalIndicator::PlaceAt(const int &x, const int &y)
{
    _position[0] = x;
    _position[1] = y;

    for(auto svg : _svgs)
    {
        svg->move(x, y);
    }
}

void YRB::SignalIndicator::update()
{
    for(auto svg : _svgs)
    {
        svg->hide();
    }

    // State is not important here we just use it to retrieve the signal
    _svgs[_entry_blocks[YRB::SignalState::Off]->getBlockSignal()->getState()]->show();
}
