#include "interlocking.hxx"

YRB::InterLocking::InterLocking(YRB::LeverFrame* lever_frame)
{
    _lever_frame = lever_frame;

    // Qt is not happy without having at least one template entry

    _signal_lever_connections = {{1,{new FrameLever, {new Signal, YRB::SignalState::Off}}}};
    _point_lever_connections = {{6, {new FrameLever, new Points}}};

    _setup_block_sections();
    _add_points();
    _add_signals();
    _connect_levers();
    _create_logic_table();

}

void YRB::InterLocking::_create_logic_table()
{
    _logic[1] = {};                            // Lever 1 requires no conditions

    _logic[2] = {};

    _logic[4] = {{YRB::LeverState::On,
                    {{6, YRB::LeverState::Off}}},
                 {YRB::LeverState::Off, {}}
                };
    _logic[3] = {{YRB::LeverState::On,
                    {{6, YRB::LeverState::On}}},
                 {YRB::LeverState::Off, {}}
                };
    _logic[6] = {{YRB::LeverState::On,
                  {{4, YRB::LeverState::Off}, {3, YRB::LeverState::Off}}},
                 {YRB::LeverState::Off,
                  {{4, YRB::LeverState::Off}, {3, YRB::LeverState::Off}}},
                };
}

void YRB::InterLocking::update(const int& i)
{
    if(!_logic.keys().contains(i)) return;    // Safety for dev purposes in case all levers not set up yet

    lever_logic _temp = _logic[i];

    interlock_coordinate _coords = _temp[reverse(_lever_frame->operator[](i)->getState())];

    for(auto lever : _coords.keys())
    {
        bool toLock = _lever_frame->operator[](lever)->getState() != _coords[lever] && _lever_frame->operator[](lever)->getState() != YRB::LeverState::Mid;

        if(toLock) qDebug() << "Lever "<< i << " Locked by Lever " << lever << " !";
        _lever_frame->operator[](i)->Lock(toLock);
        if(toLock) return;
    }

    qDebug() << "Interlocking for Lever " << i;

    // As lever move successful, lock all levers which have this lever as a requirement and the state is not met

    for(auto lever : _coords.keys())
    {
        lever_logic _lever_log = _logic[lever];
        if(_lever_log[reverse(_lever_frame->operator[](lever)->getState())].contains(i))
        {
            // Checks that not only the lever is present in other lever lock definition, but attempted move is not a valid
            if(_lever_log[reverse(_lever_frame->operator[](lever)->getState())][i] != reverse(_lever_frame->operator[](i)->getState()))
            {
                qDebug() << "Locking Lever " << lever;
                _lever_frame->operator[](lever)->Lock(true);
            }
            else
            {
                qDebug() << "Releasing Lever " << lever;
                _lever_frame->operator[](lever)->Lock(false);
            }
        }
    }

}

void YRB::InterLocking::_perform_action(const int& i)
{
     qDebug() << "Lever state: " << ((_lever_frame->operator[](i)->getState() == YRB::LeverState::Off) ? "Off" : "On");
    if(_signal_lever_connections.contains(i))
    {
        lever_active_signal_state state = _signal_lever_connections[i].second;

        // If attempting lever on and the block is occupied then do not release signal
        if(reverse(_lever_frame->operator[](i)->getState()) != YRB::LeverState::Off && state.first->protectedBlockOccupied())
        {
            qDebug() << "Could not release signal " << state.first->id() << ", Block Occupied";
            return;
        }
        else if(reverse(_lever_frame->operator[](i)->getState()) == YRB::LeverState::On)
        {
            qDebug() << "Setting Signal " << state.first->id() << " to On";
            state.first->setOn(true);
        }
        else
        {
            qDebug() << "Clearing Signal " << state.first->id() << " to Off: Aspect " << int(state.first->getState());
            state.first->tryClear(state.second);
        }
    }
    else if(_point_lever_connections.contains(i))
    {
        if(_lever_frame->operator[](i)->getState() == YRB::LeverState::On)
        {
            qDebug() << "Setting Points to Reverse";
            _point_lever_connections[i].second->setState(YRB::PointsState::Reverse);
        }
        else {
            qDebug() << "Setting Points to Normal";
            _point_lever_connections[i].second->setState(YRB::PointsState::Normal);
        }
    }
}

bool YRB::InterLocking::Query(const int& id)
{
    update(id);

    qDebug() << "Moving Lever " << id;

    if(_lever_frame->operator[](id)->isLocked())
    {
        _lever_frame->moveLever(id, YRB::LeverState::Mid, id == _points->id());
        return false;
    }
    else
    {
        _lever_frame->moveLever(id, YRB::LeverState::Off, id == _points->id());
    }

    _perform_action(id);

    return true;
}

void YRB::InterLocking::_connect(const int& id, YRB::HomeLever* lever, YRB::Signal* signal, YRB::SignalState aspect)
{
    _signal_lever_connections[id] = {};
    _signal_lever_connections[id] = {lever, {signal, aspect}};
    connect(signal, &YRB::Signal::signalAspectChanged, this, &YRB::InterLocking::signalAspectUpdate);
}

void YRB::InterLocking::_connect(const int& id, YRB::PointsLever* lever, YRB::Points* points)
{
    _point_lever_connections[id] = {lever, points};
    connect(points, &YRB::Points::pointsStateChanged, this, &YRB::InterLocking::pointsUpdate);
}

void YRB::InterLocking::_setup_block_sections()
{
    QMap<QString, TrackCircuit*> _lf_tc = _lever_frame->getTrackCircuits();

    for(const char& alpha : QList<char>({'A', 'B', 'C', 'D', 'E', 'F', 'G'})) {
        _block_sections[alpha] = new YRB::BlockSection(alpha);
    }
    _block_sections['C']->setBlockSignal(_signals[2]);
    _block_sections['F']->setBlockSignal(_signals[3]);
    _block_sections['E']->setBlockSignal(_signals[4]);

}

void YRB::InterLocking::_add_points()
{
    _points = new YRB::Points(6);

    _block_sections['E']->setBlockPoints(_points);
    _block_sections['E']->setRequiredPointsState(PointsState::Normal);
    _block_sections['F']->setBlockPoints(_points);
    _block_sections['F']->setRequiredPointsState(PointsState::Reverse);
}

void YRB::InterLocking::_add_signals()
{
    _signals[2] = new YRB::Signal(2);
    _signals[3] = new YRB::Signal(3);
    _signals[4] = new YRB::Signal(4);

    _block_sections['C']->setBlockSignal(_signals[2]);
    _block_sections['C']->setRequiredState(YRB::SignalState::Off);

    _block_sections['E']->setBlockSignal(_signals[4]);
    _block_sections['E']->setRequiredState(YRB::SignalState::Off);

    _block_sections['F']->setBlockSignal(_signals[3]);
    _block_sections['F']->setRequiredState(YRB::SignalState::Off);
}

void YRB::InterLocking::_connect_levers()
{
    for(const int& sig_id : QList<int>({2, 3, 4})) {
        _connect(sig_id, (HomeLever*)_lever_frame->operator[](sig_id), _signals[sig_id], YRB::SignalState::Off);
    }

    _connect(6, (PointsLever*)_lever_frame->operator[](6), _points);

}

