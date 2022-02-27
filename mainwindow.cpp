#include "mainwindow.h"
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Draw::ClrEngParams par;
    m_clrEng.reset(new Draw::ColorEngine(0xFF, par));
    m_pGenClr = new QGenColor(this, *m_clrEng);
//    auto layout_screen = new QHBoxLayout(this);
//    layout_screen->addWidget(widgetScale);

    this->setFixedSize(m_pGenClr->size());
    this->layout()->addWidget(m_pGenClr);
//    this->centralWidget()->setLayout(layout_screen);
}

MainWindow::~MainWindow()
{
}

