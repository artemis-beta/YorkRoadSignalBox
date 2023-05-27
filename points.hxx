#ifndef POINTS_HXX
#define POINTS_HXX

#include "global_params.hxx"

#include <QObject>
#include <QDebug>
#include <QTimer>

namespace YRB
{
    class Points : public QObject
    {
        Q_OBJECT
        private:
            PointsState _current_state = YRB::PointsState::Normal;
            int _id = -1;
        public:
            Points() {}
            Points(const int& id) : _id(id) {}
            PointsState getState() const {return _current_state;}
            void setState(const YRB::PointsState state) {
                _current_state = state;
                QTimer::singleShot(1000, this, [this, state]{pointsStateChanged(state);});
            }
            int id() const {return _id;}
        signals:
            void pointsStateChanged(YRB::PointsState state);
    };
};
#endif // POINTS_HXX
