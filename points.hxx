#ifndef POINTS_HXX
#define POINTS_HXX

#include "global_params.hxx"

namespace YRB
{
    class Points
    {
        private:
            PointsState _current_state;
            int _id = -1;
        public:
            Points() {}
            Points(const int& id) : _id(id) {}
            PointsState getState() const {return _current_state;}
            int id() const {return _id;}
    };
};
#endif // POINTS_HXX
