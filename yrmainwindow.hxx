#ifndef YRMAINWINDOW_HXX
#define YRMAINWINDOW_HXX

#include <QMainWindow>
#include "leverframe.hxx"

QT_BEGIN_NAMESPACE
namespace Ui { class YRMainWindow; }
QT_END_NAMESPACE

class YRMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    YRMainWindow(QWidget *parent = nullptr);
    YRB::LeverFrame* _lever_frame = new YRB::LeverFrame(this);
    ~YRMainWindow();

private:
    Ui::YRMainWindow *ui;
};
#endif // YRMAINWINDOW_HXX
