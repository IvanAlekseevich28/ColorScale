#include "colorengine.h"
#include <cmath>
#include <sstream>


#define MAX_HSL_SL 100
#define VAL_k 1000
#define VAL_M 1000000
#define VAL_G 1000000000
#define VAL_T 1000000000000
#define VAL_P 1000000000000000

namespace Draw
{

ColorEngine::ColorEngine(TRGB rgb, ClrEngParams params)
{
    setParams(params);
    setBaseColor(rgb);
}


void ColorEngine::setBaseColor(TRGB rgb)
{
    QColor clr = int2Clr(rgb);
    clr.getHsl(&m_baseH, &m_baseS, &m_baseL);
    recalcLogScale();
}

void ColorEngine::setSpecLen(const TIntNum &newSpecLen)
{
    m_params.specLen = newSpecLen;
}

void ColorEngine::setMaxValue(const TIntNum &newMaxValue)
{
    m_params.maxValue = newMaxValue;
}

void ColorEngine::recalcLogScale()
{
    m_logScale = genLogScale();
}

std::vector<QColor> ColorEngine::genSpec() const
{
    std::vector<QColor> spec;
    int S(m_params.minL);
    int L(MAX_HSL_SL);
    const unsigned stepL = (MAX_HSL_SL - m_params.minL) / m_params.specLen;
    const unsigned stepS = (MAX_HSL_SL - m_params.minS) / m_params.specLen;
    for (unsigned i = 0; i < m_params.specLen; i++)
    {
        QColor clr = QColor::fromHsl(m_baseH,S,L);
        spec.push_back(clr);
        S += stepS; L -= stepL;
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

void ColorEngine::setParams(const ClrEngParams &newParams)
{
    m_params = newParams;
    m_params.minL = correctSLvalues(newParams.minL);
    m_params.minS = correctSLvalues(newParams.minS);
}

void ColorEngine::setMinL(int newMinL)
{
    m_params.minL = correctSLvalues(newMinL);
}

void ColorEngine::setMinS(int newMinS)
{
    m_params.minS = correctSLvalues(newMinS);
}

}
