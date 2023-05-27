#ifndef GRAPHICS_HXX
#define GRAPHICS_HXX

#include <QSvgWidget>
#include <QMap>
#include "global_params.hxx"
#include "scaling.hxx"

namespace YRB {
    class Graphics : public QObject
    {
    QWidget* _parent = nullptr;
    QSvgWidget* _frame_svg = nullptr;
    QMap<int, QMap<SignalState, QSvgWidget*>> _map_indicator_svgs;
    QMap<int, QMap<LeverState, QSvgWidget*>> _lever_svgs;
    Scaler* _scaler = new Scaler;
    void _place_signal_at(const int id, const int x, const int y);
    void _place_lever_at(const int id, const int x, const int y);
    void _set_lever_size_at(const int id, const int x, const int y);
    void _set_signal_size_at(const int id, const int x, const int y);
    public:
        Graphics(QWidget* parent);
    public slots:
        void updateSignalGraphic(int id, YRB::SignalState state) {
            _map_indicator_svgs[id][YRB::SignalState::Off]->hide();
            _map_indicator_svgs[id][YRB::SignalState::On]->hide();
            _map_indicator_svgs[id][state]->show();
        }
        void updateLeverGraphic(int id, YRB::LeverState state) {
            _lever_svgs[id][YRB::LeverState::On]->hide();
            _lever_svgs[id][YRB::LeverState::Mid]->hide();
            _lever_svgs[id][YRB::LeverState::Off]->hide();
            _lever_svgs[id][state]->show();
        }
    };
};
#endif // GRAPHICS_HXX
