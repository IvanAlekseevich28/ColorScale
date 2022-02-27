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
    pLayoutMain->addWidget(m_pGenClr);

    auto pLayoutRGB = new QHBoxLayout(this);
    auto pSlider_red    = new QSliderParam(this, "   Red:", MinMax(255), 0);
    auto pSlider_green  = new QSliderParam(this, " Green:", MinMax(255), 34);
    auto pSlider_blue   = new QSliderParam(this, "  Blue:", MinMax(255), 255);

    connect(pSlider_red, SIGNAL(newValue(int)), this, SLOT(sliderChanged_red(int)));
    connect(pSlider_green, SIGNAL(newValue(int)), this, SLOT(sliderChanged_green(int)));
    connect(pSlider_blue, SIGNAL(newValue(int)), this, SLOT(sliderChanged_blue(int)));

    pLayoutRGB->addLayout(pSlider_red);
    pLayoutRGB->addLayout(pSlider_green);
    pLayoutRGB->addLayout(pSlider_blue);


    auto pLayoutCount = new QHBoxLayout(this);
    auto pSlider_pow    = new QSliderParam(this, "     Max 2 Power:", MinMax(8, 31), 31);
    auto pSlider_len  = new QSliderParam(this, " Spectrum lenght:", MinMax(2, 32), 16);

    connect(pSlider_pow, SIGNAL(newValue(int)), this, SLOT(sliderChanged_power2(int)));
    connect(pSlider_len, SIGNAL(newValue(int)), this, SLOT(sliderChanged_specLen(int)));

    pLayoutCount->addLayout(pSlider_pow);
    pLayoutCount->addLayout(pSlider_len);

    pLayoutMain->addLayout(pLayoutRGB);
    pLayoutMain->addLayout(pLayoutCount);

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

void MainWindow::sliderChanged_power2(int pow2)
{
    int maxValue = 1 << pow2;
    m_clrEng->setMaxValue(maxValue);
    m_pGenClr->update();
}

void MainWindow::sliderChanged_specLen(int len)
{
    m_clrEng->setSpecLen(len);
    m_pGenClr->update();
}

