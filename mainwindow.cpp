#include "mainwindow.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Color scale");

    Draw::ClrEngParams par;
    m_clrEng.reset(new Draw::ColorEngine(0xFF, par));
    m_pGenClr = new QGenColor(this, *m_clrEng);

    auto pLayoutMain = new QVBoxLayout(this);
    pLayoutMain->addWidget(m_pGenClr);

    auto pLayoutRGB = new QHBoxLayout(this);
    auto pSlider_red    = new QSliderParam(this, "   Red:", MinMax(255), 0);
    auto pSlider_green  = new QSliderParam(this, " Green:", MinMax(255), 0);
    auto pSlider_blue   = new QSliderParam(this, "  Blue:", MinMax(255), 255);

    connect(pSlider_red, SIGNAL(newValue(int)), this, SLOT(sliderChanged_red(int)));
    connect(pSlider_green, SIGNAL(newValue(int)), this, SLOT(sliderChanged_green(int)));
    connect(pSlider_blue, SIGNAL(newValue(int)), this, SLOT(sliderChanged_blue(int)));

    pLayoutRGB->addLayout(pSlider_red);
    pLayoutRGB->addLayout(pSlider_green);
    pLayoutRGB->addLayout(pSlider_blue);


    auto pLayoutCount = new QHBoxLayout(this);
    auto pSlider_pow  = new QSliderParam(this, " Max 2 Power:", MinMax(8, 31), 31);
    auto pSlider_len  = new QSliderParam(this, " Spectrum lenght:", MinMax(2, 32), 16);
    m_PBScaleMode = new QPushButton("Scale mode", this);
    setButtonScaleModName();

    connect(pSlider_pow, SIGNAL(newValue(int)), this, SLOT(sliderChanged_power2(int)));
    connect(pSlider_len, SIGNAL(newValue(int)), this, SLOT(sliderChanged_specLen(int)));
    connect(m_PBScaleMode, SIGNAL(released()), this, SLOT(buttonRelease_ScaleMod()));

    pLayoutCount->addLayout(pSlider_pow);
    pLayoutCount->addLayout(pSlider_len);
    pLayoutCount->addWidget(m_PBScaleMode);


    auto pLayoutSV = new QHBoxLayout(this);
    auto pSlider_hsv_V_min = new QSliderParam(this, " HSV Value (min):", MinMax(64, 255), 255);
    auto pSlider_hsv_S_max = new QSliderParam(this, " HSV Saturation (max):", MinMax(16, 255), 255);

    connect(pSlider_hsv_V_min, SIGNAL(newValue(int)), this, SLOT(sliderChanged_HSV_V_min(int)));
    connect(pSlider_hsv_S_max, SIGNAL(newValue(int)), this, SLOT(sliderChanged_HSV_S_max(int)));

    pLayoutSV->addLayout(pSlider_hsv_S_max);
    pLayoutSV->addLayout(pSlider_hsv_V_min);

    pLayoutMain->addLayout(pLayoutRGB);
    pLayoutMain->addLayout(pLayoutSV);
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

void MainWindow::sliderChanged_HSV_S_max(int maxS)
{
    auto params = m_clrEng->params();
    params.S.max = maxS;
    m_clrEng->setParams(params);
    m_pGenClr->update();
}

void MainWindow::sliderChanged_HSV_V_min(int minV)
{
    auto params = m_clrEng->params();
    params.V.min = minV;
    m_clrEng->setParams(params);
    m_pGenClr->update();
}

void MainWindow::buttonRelease_ScaleMod()
{
    m_pGenClr->scaleTypeSwithed();
    setButtonScaleModName();
}

void MainWindow::setButtonScaleModName()
{
    QString name = "Scale mod: " + m_pGenClr->getModeName();
    m_PBScaleMode->setText(name);
}

