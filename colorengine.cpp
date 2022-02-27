#include "colorengine.h"
#include <cmath>
#include <sstream>


#define MIN_HSL_SL 0
#define MAX_HSL_SL 255

#define VAL_k 1000
#define VAL_M 1000000
#define VAL_G 1000000000
#define VAL_T 1000000000000
#define VAL_P 1000000000000000

namespace Draw
{

ColorEngine::ColorEngine(TRGB rgb, ClrEngParams params)
{
    setParams(params, true);
    setBaseColor(rgb);
}

QColor ColorEngine::getColorByValue(const TIntNum &value, const QColor& base) const
{
    if (value == 0)
        return base;
    if (value > m_logScale.rbegin()->first)
        return m_logScale.rbegin()->second;

    return m_logScale.lower_bound(value)->second;
}


void ColorEngine::setBaseColor(TRGB rgb)
{
    QColor clr = int2Clr(rgb);
    clr.getHsv(&m_baseH, &m_baseS, &m_baseV);
    recalcLogScale();
}

void ColorEngine::setBaseColor(QColor clr)
{
    clr.getHsv(&m_baseH, &m_baseS, &m_baseV);
    recalcLogScale();
}

QColor ColorEngine::getBaseColor() const
{
    QColor clr;
    clr.setHsv(m_baseH, m_baseS, m_baseV);
    return clr;
}

void ColorEngine::setSpecLen(const TIntNum &newSpecLen)
{
    m_params.specLen = newSpecLen;
    recalcLogScale();
}

void ColorEngine::setMaxValue(const TIntNum &newMaxValue)
{
    m_params.maxValue = newMaxValue;
    recalcLogScale();
}

void ColorEngine::recalcLogScale()
{
    m_logScale = genLogScale();
}

std::vector<QColor> ColorEngine::genSpec() const
{
    std::vector<QColor> spec;
    int S(m_params.S.min);
    int V(m_params.V.max);
    const unsigned stepV = (m_params.V.max - m_params.V.min) / m_params.specLen;
    const unsigned stepS = (m_params.S.max - m_params.S.min) / m_params.specLen;
    for (unsigned i = 0; i < m_params.specLen; i++)
    {
        QColor clr = QColor::fromHsv(m_baseH,S,V);
        spec.push_back(clr);
        S += stepS;
        V -= stepV;
    }

    return spec;
}

std::map<TIntNum, QColor> ColorEngine::genLogScale() const
{
    std::map<TIntNum, QColor> scale;

    const TFltNum power = std::log(m_params.maxValue) / std::log(m_params.specLen);
    auto spec = genSpec();
    for (unsigned x = 0; x < spec.size(); x++)
    {
        TIntNum limit = pow(x, power);
        scale.insert(std::make_pair(limit+1, spec[x]));
    }
    return scale;
}

QColor ColorEngine::int2Clr(TRGB rgb)
{
    QColor qclr;
    qclr.setRed((rgb & 0xff0000) >> 16);
    qclr.setGreen((rgb & 0x00ff00) >> 8);
    qclr.setBlue(rgb & 0x0000ff);
    return qclr;
}

int ColorEngine::correctSLvalues(int val)
{
    return (val > 0 ? val : -val) % (MAX_HSL_SL + 1);
}

std::string ColorEngine::int2Str(TIntNum num)
{
    std::stringstream sstr;
    if (num < 0) sstr << "-";
    num = num > 0 ? num : -num;

    if (num < VAL_k)
        sstr << num;
    else if (num < VAL_M)
        sstr << (num / VAL_k) << "k";
    else if (num < VAL_G)
        sstr << (num / VAL_M) << "M";
    else if ((long long)num < VAL_T)
        sstr << (num / VAL_G) << "B";
    else
        sstr << "none";

    return sstr.str();
}

const ClrEngParams &ColorEngine::params() const
{
    return m_params;
}

const std::map<TIntNum, QColor> &ColorEngine::logScale() const
{
    return m_logScale;
}

void ColorEngine::setParams(const ClrEngParams &newParams, bool noCalc)
{
    m_params = newParams;
    m_params.V.cut(MIN_HSL_SL, MAX_HSL_SL);
    m_params.S.cut(MIN_HSL_SL, MAX_HSL_SL);
    if (noCalc == false)
        recalcLogScale();
}

void ColorEngine::setS(MinMax newS)
{
    m_params.S = newS;
    m_params.S.cut(MIN_HSL_SL, MAX_HSL_SL);
}

void ColorEngine::setV(MinMax newV)
{
    m_params.V = newV;
    m_params.V.cut(MIN_HSL_SL, MAX_HSL_SL);
}

}
