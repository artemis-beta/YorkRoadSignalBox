#ifndef SERVICE_HXX
#define SERVICE_HXX

#include <QObject>

class Service : public QObject
{
private:
    QWidget* parent = nullptr;
public:
    Q_OBJECT;
    Service();
};

#endif // SERVICE_HXX
