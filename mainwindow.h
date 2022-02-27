#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gencolor.h"
#include "sliderparam.h"
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sliderChanged_red(int red);
    void sliderChanged_green(int green);
    void sliderChanged_blue(int blue);

    void sliderChanged_power2(int pow2);
    void sliderChanged_specLen(int len);

    void sliderChanged_HSV_S_max(int maxS);
    void sliderChanged_HSV_V_min(int minV);

private:
    std::shared_ptr<Draw::ColorEngine> m_clrEng;
    QGenColor* m_pGenClr;
};
#endif // MAINWINDOW_H
