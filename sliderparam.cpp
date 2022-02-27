#include "sliderparam.h"
#include <QLabel>
#include <QIntValidator>

QSliderParam::QSliderParam(QWidget* parent, QString name, MinMax mm, int val)
{
    auto pLabel = new QLabel(name, parent);
    m_pSlider = new QSlider(parent);
    m_pLineEdit = new QLineEdit(QString::number(val), parent);

    m_pSlider->setMinimum(mm.min);
    m_pSlider->setMaximum(mm.max);
    m_pSlider->setValue(val);
    m_pSlider->setOrientation(Qt::Horizontal);

    auto pValidator = new QIntValidator(mm.min, mm.max, parent);
    m_pLineEdit->setValidator(pValidator);

    connect(m_pSlider, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
    connect(m_pLineEdit, SIGNAL(textChanged(QString)), this, SLOT(valueChanged(QString)));

    addWidget(pLabel);
    addWidget(m_pSlider);
    addWidget(m_pLineEdit);
}

void QSliderParam::valueChanged(int value)
{
    emit newValue(value);
    m_pLineEdit->setText(QString::number(value));
    m_pSlider->setValue(value);
}

void QSliderParam::valueChanged(QString strValue)
{
    valueChanged(strValue.toInt());
}
