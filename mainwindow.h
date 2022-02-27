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

private:
    std::shared_ptr<Draw::ColorEngine> m_clrEng;
    QGenColor* m_pGenClr;
};
#endif // MAINWINDOW_H
