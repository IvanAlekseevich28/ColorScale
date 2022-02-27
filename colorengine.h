#pragma once

#include <vector>
#include <map>
#include <QColor>
#include <string>
#include "minmax.h"

namespace Draw
{
typedef unsigned TRGB;
typedef unsigned TIntNum;
typedef double TFltNum;

struct ClrEngParams
{
    MinMax S = MinMax(30,255,0);
    MinMax V = MinMax(30,255,0);
    TIntNum specLen = 16;
    TIntNum maxValue = 0x8FFFFFFF;
};

class ColorEngine
{
public:
    ColorEngine(TRGB rgb, ClrEngParams params = ClrEngParams());

    inline QColor getColorByValue(const TIntNum &value)const
        {return m_logScale.lower_bound(value)->second;}
    std::vector<QColor> genSpec()const;

    void setBaseColor(TRGB rgb);
    void setBaseColor(QColor clr);

    QColor getBaseColor()const;

    void setSpecLen(const TIntNum &newSpecLen);

    void setMaxValue(const TIntNum &newMaxValue);

    void setS(MinMax newS);

    void setV(MinMax newV);

    void setParams(const ClrEngParams &newParams, bool noCalc = false);

    const std::map<TIntNum, QColor> &logScale() const;

    const ClrEngParams &params() const;

    static std::string int2Str(TIntNum num);

private:
    void recalcLogScale();
    std::map<TIntNum, QColor> genLogScale()const;
    static QColor int2Clr(TRGB rgb);
    static int correctSLvalues(int val);

private:
    int m_baseH;
    int m_baseS;
    int m_baseV;

    ClrEngParams m_params;

    std::map<TIntNum, QColor> m_logScale;
};
}
