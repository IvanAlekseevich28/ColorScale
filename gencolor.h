#pragma once

#include <QOpenGLWidget>
#include "colorengine.h"

class QGenColor : public QOpenGLWidget
{
    Q_OBJECT
public:
    QGenColor(QWidget* parent, Draw::ColorEngine& eng);

    unsigned oneClrPixLen() const;
    QString getModeName()const;

public slots:
    void scaleTypeSwithed();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    void drawOneLine(const QColor& clr, const unsigned index);
    void drawOneLineWithText(const std::pair<Draw::TIntNum, QColor> &parClr, const unsigned index);

private:
    Draw::ColorEngine& m_eng;
    Draw::ColorEngine::eScaleType m_eScaleType;
};
