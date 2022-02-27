#include "mainwindow.h"
#include <QLayout>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Draw::ClrEngParams par;
    m_clrEng.reset(new Draw::ColorEngine(0xFF, par));
    m_pGenClr = new QGenColor(this, *m_clrEng);

    auto pLayoutMain = new QVBoxLayout(this);
    auto pLayoutParams = new QHBoxLayout(this);
    pLayoutMain->addWidget(m_pGenClr);

    auto pSlider_red    = new QSliderParam(this, "   Red:", MinMax(255), 0);
    auto pSlider_green  = new QSliderParam(this, " Green:", MinMax(255), 34);
    auto pSlider_blue   = new QSliderParam(this, "  Blue:", MinMax(255), 255);

    connect(pSlider_red, SIGNAL(newValue(int)), this, SLOT(sliderChanged_red(int)));
    connect(pSlider_green, SIGNAL(newValue(int)), this, SLOT(sliderChanged_green(int)));
    connect(pSlider_blue, SIGNAL(newValue(int)), this, SLOT(sliderChanged_blue(int)));

    pLayoutParams->addLayout(pSlider_red);
    pLayoutParams->addLayout(pSlider_green);
    pLayoutParams->addLayout(pSlider_blue);

    pLayoutMain->addLayout(pLayoutParams);

    QWidget *pWindow = new QWidget(this);
    pWindow->setLayout(pLayoutMain);

    this->setCentralWidget(pWindow);
}

MainWindow::~MainWindow()
{
}

void MainWindow::sliderChanged_red(int red)
{
    auto clr = m_clrEng->getBaseColor();
    clr.setRed(red % 256);
    m_clrEng->setBaseColor(clr);
    m_pGenClr->update();
}

void MainWindow::sliderChanged_green(int green)
{
    auto clr = m_clrEng->getBaseColor();
    clr.setGreen(green % 256);
    m_clrEng->setBaseColor(clr);
    m_pGenClr->update();
}

void MainWindow::sliderChanged_blue(int blue)
{
    auto clr = m_clrEng->getBaseColor();
    clr.setBlue(blue % 256);
    m_clrEng->setBaseColor(clr);
    m_pGenClr->update();
}

