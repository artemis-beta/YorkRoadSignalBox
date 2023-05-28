#include "blocksection.hxx"

YRB::TrackCircuitStatus YRB::BlockSection::getState() {
    TrackCircuitStatus occupied_ = TrackCircuitStatus::Clear;
    for(const auto& tc : track_circuits_) {
        if(tc->getState() == TrackCircuitStatus::Occupied) occupied_ = TrackCircuitStatus::Occupied;
    }
    return occupied_;
}
