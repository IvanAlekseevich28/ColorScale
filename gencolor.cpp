#include "gencolor.h"
#include <cmath>

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QPainter>

#define MAX_HSL_SL 100
#define MIN_HSL_SL 36
#define SCALE_HEIGHT 200
#define SCALE_WIDTH 1024

QGenColor::QGenColor(QWidget *parent, Draw::ColorEngine &eng) :
    QOpenGLWidget(parent), m_eng(eng), m_eScaleType(Draw::ColorEngine::ST_log)
{
    QOpenGLWidget::setFixedSize(SCALE_WIDTH, SCALE_HEIGHT);
    update();
}

void QGenColor::initializeGL()
{
    QOpenGLFunctions* pFunc = QOpenGLContext::currentContext()->functions();
    pFunc->glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void QGenColor::resizeGL(int nWidth, int nHeight)
{
    glViewport(0, 0, nWidth, nHeight);
}

void QGenColor::paintGL()
{
    unsigned i = 0;
    for (const auto& pairClr : m_eng.scale(m_eScaleType))
        drawOneLineWithText(pairClr, i++);
}

void QGenColor::drawOneLine(const QColor &clr, const unsigned index)
{
    QPainter p(this);
    p.setPen(clr);
    p.setBrush(QBrush(clr));
//    p.drawText()
    p.drawRect(index*oneClrPixLen(), 0, oneClrPixLen(), SCALE_HEIGHT);
}

void QGenColor::drawOneLineWithText(const std::pair<Draw::TIntNum, QColor> &parClr, const unsigned index)
{
    QPainter p(this);
    p.setPen(parClr.second);
    p.setBrush(QBrush(parClr.second));
    const int w = oneClrPixLen();
    const int x = index*w;
    const int numsH = 25;
    const int scaleH = SCALE_HEIGHT - numsH;

    p.drawRect(x, 0, w, scaleH);
    std::string strNum(Draw::ColorEngine::int2Str(parClr.first));

    p.setPen(Qt::white);
    p.drawText(x, SCALE_HEIGHT-8, QString::fromStdString(strNum));
}

unsigned QGenColor::oneClrPixLen() const
{
    auto specLen = m_eng.params().specLen;
    return SCALE_WIDTH / specLen;
}

QString QGenColor::getModeName() const
{
    switch (m_eScaleType)
    {
    case Draw::ColorEngine::ST_log:
        return "log";
    case Draw::ColorEngine::ST_pow2:
        return "pow2";
    default:
        return "unknown";
    }
}

void QGenColor::scaleTypeSwithed()
{
    switch (m_eScaleType)
    {
    case Draw::ColorEngine::ST_log:
        m_eScaleType = Draw::ColorEngine::ST_pow2;
        break;
    case Draw::ColorEngine::ST_pow2:
        m_eScaleType = Draw::ColorEngine::ST_log;
        break;
    default:
        m_eScaleType = Draw::ColorEngine::ST_log;
    }
    update();
}
