#ifndef SignalIndicator_HXX
#define SignalIndicator_HXX

#include "signal.hxx"
#include "blocksection.hxx"

#include <QMap>
#include <QThread>
#include <QDebug>
#include <QGuiApplication>
#include <QScreen>

namespace YRB
{
    class SignalIndicator
    {
        private:
            int _position[2] = {0, 0};
            QMap<SignalState, BlockSection*> _entry_blocks;
            QWidget* _parent = nullptr;
        public:
            SignalIndicator(QWidget* parent, BlockSection* valid_block) :
                _parent(parent)
            {
                _entry_blocks[SignalState::Off] = valid_block;
            }
            void PlaceAt(const int& x, const int& y);
            void addValidBlocks(SignalState state, BlockSection* block)
            {
                _entry_blocks[state] = block;
            }
            void setState(SignalState state, int delay_ms=0) {
                QThread::msleep(delay_ms);

            }
            Signal* getMirroredSignal() const {return _entry_blocks[SignalState::Off]->getBlockSignal();}
        signals:
            void signalChange(int id, YRB::SignalState state);
    };

};

#endif // SignalIndicator_HXX
