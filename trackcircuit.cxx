#include "trackcircuit.hxx"

QMap<QString, YRB::TrackCircuit*> YRB::TrackCircuits(QWidget* parent) {
    QMap<QString, YRB::TrackCircuit*> blocks_ = {};
    QList<QString> block_names_ = {
      "A",
      "B",
      "C",
      "D",
      "E",
      "F"
    };

    for(const QString& block : block_names_) {
        blocks_[block] = new YRB::TrackCircuit(block, parent, ":/svgs/svgs/Block_"+block+".svg");
    }

    return blocks_;
}
