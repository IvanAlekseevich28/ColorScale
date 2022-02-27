#ifndef QSLIDERPARAM_H
#define QSLIDERPARAM_H

#include <QHBoxLayout>
#include <QObject>
#include <QLineEdit>
#include <QSlider>

struct MinMax
{
    int min;
    int max;
    MinMax(int max) : min(0), max(max) {}
    MinMax(int min, int max) : min(min), max(max) {}
};

class QSliderParam : public QHBoxLayout
{
    Q_OBJECT
public:
    QSliderParam(QWidget* parent, QString name, MinMax mm, int val);

signals:
    void newValue(int);

private slots:
    void valueChanged(int value);
    void valueChanged(QString strValue);

private:
    QSlider* m_pSlider;
    QLineEdit* m_pLineEdit;
};

#endif // QSLIDERPARAM_H
