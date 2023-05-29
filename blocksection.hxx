#ifndef BLOCKSECTION_HXX
#define BLOCKSECTION_HXX

#include "global_params.hxx"
#include "signal.hxx"
#include "points.hxx"
#include "trackcircuit.hxx"

namespace YRB
{
    class BlockSection : public QObject
    {
        Q_OBJECT
        private:
            const char _id = '\0';
            Signal* _block_signal = nullptr;
            QList<TrackCircuit*> track_circuits_ = {};
            Points* _points = nullptr;
            SignalState _required_state = SignalState::Off;
            bool _occupied = false;
            QList<PointsState> _required_points_state = {};
            BlockSection* _next = nullptr;
            BlockSection* _prev = nullptr;
            const QList<Signal*> _counter_signals = {}; // Signals in opposing direction
        public:
            BlockSection(){}
            BlockSection(const char id) : _id(id) {}
            void addTrackCircuits(const QList<TrackCircuit*>& circuits) {
                track_circuits_.append(circuits);
            }
            void setRequiredState(SignalState state) {_required_state = state;}
            void setRequiredPointsState(PointsState state) {_required_points_state = {state};}
            void setRequiredPointsState(QList<PointsState> states) {_required_points_state = states;}
            void setBlockSignal(Signal* signal) {
                _block_signal = signal;
            }
            void setBlockPoints(Points* points) {_points = points;}
            void setOccupied(bool is_occupied)
            {
                _occupied = is_occupied;
                if(_prev) {
                    _prev->setOccupied(false);
                    return;
                }
                emit blockStatusChanged(is_occupied);
            };
            TrackCircuitStatus getState();
            BlockSection* getNeighbour() {return _next;}
            SignalState getRequiredState() const {return _required_state;}
            Signal* getBlockSignal() const {return _block_signal;}
            Points* getPoints() const {return _points;}
            int id() const {return _id;}
            void setNeighbour(BlockSection* other){
                _next = other;
                _next->setPrevious(this);
            }
            void setPrevious(BlockSection* other){
                _prev = other;
            }
       signals:
            void blockStatusChanged(bool is_occupied);

    };
};

#endif // BLOCKSECTION_HXX
