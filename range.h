#ifndef QRANGE_H
#define QRANGE_H

#include <QHBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include "minmax.h"

class QRange : public QHBoxLayout
{
    Q_OBJECT
public:
    QRange(QWidget* parent, QString name, MinMax curMM, MinMax limitMM);

signals:
    void newData(MinMax);

public slots:
    void changeDiff(int newDiff);

private slots:
    void changedMin(int newMin);
    void changedMax(int newMax);

private:
    QLineEdit* m_pLineEditMin;
    QLineEdit* m_pLineEditMax;
    MinMax m_limitMM;
};

#endif // QRANGE_H
