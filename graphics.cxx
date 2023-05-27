#include "graphics.hxx"

YRB::Graphics::Graphics(QWidget* parent)
{
    _parent = parent;
    _frame_svg = new QSvgWidget(QString(":/svgs/media/YRFrame.svg"), _parent);
    _frame_svg->setFixedSize(_scaler->screen_width(), _scaler->screen_height());

    _point_ind_svgs = {
        {YRB::PointsState::Normal, {
                 {YRB::SignalState::On, new QSvgWidget(":/svgs/media/PointsIndicatorOn.svg", _parent)},
                 {YRB::SignalState::Off, new QSvgWidget(":/svgs/media/PointsIndicatorOff.svg", _parent)}
            }
        },
        {YRB::PointsState::Reverse, {
             {YRB::SignalState::On, new QSvgWidget(":/svgs/media/PointsIndicatorOn.svg", _parent)},
             {YRB::SignalState::Off, new QSvgWidget(":/svgs/media/PointsIndicatorOff.svg", _parent)}
            }
        }
    };

    _set_point_indicator_position(YRB::PointsState::Normal, _scaler->scale_width(156.5), _scaler->scale_height(212));
    _set_point_indicator_size(YRB::PointsState::Normal, _scaler->scale_width(20), _scaler->scale_height(20));
    _set_point_indicator_position(YRB::PointsState::Reverse, _scaler->scale_width(156.5), _scaler->scale_height(249.25));
    _set_point_indicator_size(YRB::PointsState::Reverse, _scaler->scale_width(20), _scaler->scale_height(20));


    for(const int& sig_id : signal_ids)
    {
        _map_indicator_svgs[sig_id] = {
            {SignalState::Off, new QSvgWidget(":/svgs/media/Sig_Off.svg", _parent)},
            {SignalState::On, new QSvgWidget(":/svgs/media/Sig_On.svg", _parent)},
        };
        _set_signal_size_at(sig_id, _scaler->scale_width(13), _scaler->scale_height(13));
    }

    _place_signal_at(2, _scaler->scale_width(155), _scaler->scale_height(136));
    _place_signal_at(3, _scaler->scale_width(336), _scaler->scale_height(124));
    _place_signal_at(4, _scaler->scale_width(336), _scaler->scale_height(166));

    for(const auto& [id, type] : levers.toStdMap()) {
        QString _lever_colour;
        switch(type) {
            case LeverType::Signal:
                _lever_colour = "Red";
                break;
            case LeverType::Points:
                _lever_colour = "Black";
                break;
            case LeverType::PointLock:
                _lever_colour = "Blue";
                break;
            default:
                _lever_colour = "White";
                break;
        }

        _lever_svgs[id] = {
            {LeverState::Off, new QSvgWidget(QString(":/svgs/media/")+_lever_colour+QString("_LeverBack.svg"), _parent)},
            {LeverState::Mid, new QSvgWidget(QString(":/svgs/media/")+_lever_colour+QString("_LeverMid.svg"), _parent)},
            {LeverState::On, new QSvgWidget(QString(":/svgs/media/")+_lever_colour+QString("_LeverForward.svg"), _parent)}
        };
        _place_lever_at(id, _scaler->scale_width(32+(id-1)*45), 0.72*_scaler->screen_height());
        _set_lever_size_at(id, _scaler->scale_width(25), _scaler->scale_height(100));
        _lever_svgs[id][LeverState::On]->hide();
        _lever_svgs[id][LeverState::Mid]->hide();
        _point_ind_svgs[YRB::PointsState::Normal][YRB::SignalState::On]->show();
        _point_ind_svgs[YRB::PointsState::Normal][YRB::SignalState::Off]->hide();
        _point_ind_svgs[YRB::PointsState::Reverse][YRB::SignalState::On]->hide();
        _point_ind_svgs[YRB::PointsState::Reverse][YRB::SignalState::Off]->show();
    }
}

void YRB::Graphics::_set_point_indicator_position(const YRB::PointsState state, const int x, const int y) {
    for(QSvgWidget* graphic : _point_ind_svgs[state]) {
        graphic->move(x, y);
    }
}

void YRB::Graphics::_set_point_indicator_size(const YRB::PointsState state, const int x, const int y) {
    for(QSvgWidget* graphic : _point_ind_svgs[state]) {
        graphic->setFixedSize(x, y);
    }
}

void YRB::Graphics::_place_signal_at(const int id, const int x, const int y) {
    for(QSvgWidget* graphic : _map_indicator_svgs[id]) {
        graphic->move(x, y);
    }
}

void YRB::Graphics::_set_signal_size_at(const int id, const int x, const int y) {
    for(QSvgWidget* graphic : _map_indicator_svgs[id]) {
        graphic->setFixedSize(x, y);
    }
}

void YRB::Graphics::_place_lever_at(const int id, const int x, const int y) {
    for(QSvgWidget* graphic : _lever_svgs[id]) {
        graphic->move(x, y);
    }
}

void YRB::Graphics::_set_lever_size_at(const int id, const int x, const int y) {
    for(QSvgWidget* graphic : _lever_svgs[id]) {
        graphic->setFixedSize(x, y);
    }
}
