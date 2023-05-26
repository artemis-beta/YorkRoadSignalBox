#ifndef YRMAINWINDOW_HXX
#define YRMAINWINDOW_HXX

#include <QMainWindow>
#include "leverframe.hxx"
#include "interlocking.hxx"

QT_BEGIN_NAMESPACE
namespace Ui { class YRMainWindow; }
QT_END_NAMESPACE

class YRMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    YRMainWindow(QWidget *parent = nullptr);
    YRB::LeverFrame* _lever_frame = new YRB::LeverFrame(this);
    YRB::InterLocking* _interlocking = new YRB::InterLocking(_lever_frame);
    ~YRMainWindow();

private:
    Ui::YRMainWindow *ui;
    void _lever_action(const int& i);
    void _add_indicators();
    QMap<int, QPushButton*> _lever_frame_buttons;
};
#endif // YRMAINWINDOW_HXX
