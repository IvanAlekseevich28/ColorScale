#include "range.h"
#include <QLabel>
#include <QIntValidator>
#include <QString>

QRange::QRange(QWidget *parent, QString name, MinMax curMM, MinMax limitMM) : m_limitMM(limitMM)
{
    curMM.cut(limitMM);
    m_pLineEditMin = new QLineEdit(QString::number(curMM.min), parent);
    m_pLineEditMax = new QLineEdit(QString::number(curMM.max), parent);

    auto pLabelName = new QLabel(name, parent);
    auto pLabelSpace = new QLabel(" - ", parent);

    addWidget(pLabelName);
    addWidget(m_pLineEditMin);
    addWidget(pLabelSpace);
    addWidget(m_pLineEditMax);
}

void QRange::changeDiff(int newDiff)
{

}

void QRange::changedMin(int newMin)
{

}

void QRange::changedMax(int newMax)
{

}
