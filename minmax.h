#pragma once

struct MinMax
{
    int min;
    int max;
    MinMax(int max) : min(0), max(max) {}
    MinMax(int min, int max) : min(min), max(max) {}
    bool isCorrect(int limitMin, int limitMax, int limitDiff=0)const;
    void cut(int limitMin, int limitMax);
};

inline bool MinMax::isCorrect(int limitMin, int limitMax, int limitDiff) const
{
    if (min + limitDiff > max)
        return false;
    if (min < limitMin || max > limitMax)
        return false;

    return true;
}

inline void MinMax::cut(int limitMin, int limitMax)
{
    if (min < limitMin) min = limitMin;
    if (max > limitMax) max = limitMax;
}
