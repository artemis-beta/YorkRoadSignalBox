#include "blocksection.hxx"

YRB::TrackCircuitStatus YRB::BlockSection::getState() {
    TrackCircuitStatus occupied_ = TrackCircuitStatus::Clear;
    for(const auto& tc : track_circuits_) {
        if(tc->getState() == TrackCircuitStatus::Occupied) occupied_ = TrackCircuitStatus::Occupied;
    }
    return occupied_;
}

void YRB::BlockSection::update()
{
    bool is_occupied_ = getState() == TrackCircuitStatus::Occupied;
    _block_signal->setBlockOccupied(is_occupied_);
    _block_signal->setOn(is_occupied_);
}
