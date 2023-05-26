#ifndef SignalIndicator_HXX
#define SignalIndicator_HXX

#include "signal.hxx"
#include "blocksection.hxx"
#include "scaling.hxx"

#include <QMap>
#include <QSvgWidget>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

namespace YRB
{
    class SignalIndicator
    {
        private:
            QMap<SignalState, QSvgWidget*> _svgs;
            int _position[2] = {0, 0};
            QMap<SignalState, BlockSection*> _entry_blocks;
            QWidget* _parent = nullptr;
        public:
            SignalIndicator(QWidget* parent, BlockSection* valid_block) :
                _parent(parent)
            {
                const Scaler* scaler_ = new Scaler;
                _entry_blocks[SignalState::Off] = valid_block;
                _svgs[SignalState::Off] = new QSvgWidget(":/svgs/media/Sig_Off.svg", _parent);
                _svgs[SignalState::Off]->setFixedSize(scaler_->scale_width(13), scaler_->scale_height(13));
                _svgs[SignalState::Off]->hide();
                _svgs[SignalState::On] = new QSvgWidget(":/svgs/media/Sig_On.svg", _parent);
                _svgs[SignalState::On]->setFixedSize(scaler_->scale_width(13), scaler_->scale_height(13));
            }
            void PlaceAt(const int& x, const int& y);
            void addValidBlocks(SignalState state, BlockSection* block)
            {
                _entry_blocks[state] = block;
            }
            void update();
            Signal* getMirroredSignal() const {return _entry_blocks[SignalState::Off]->getBlockSignal();}
    };

};

#endif // SignalIndicator_HXX
