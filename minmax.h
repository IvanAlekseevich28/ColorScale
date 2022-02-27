#pragma once

struct MinMax
{
    int min;
    int max;
    int diff;
    MinMax(int max, int diff=0) : min(0), max(max), diff(diff) {}
    MinMax(int min, int max, int diff=0) : min(min), max(max), diff(diff) {}
    bool isCorrect(int limitMin, int limitMax)const;
    void cut(int limitMin, int limitMax);
    void cut(MinMax limit);
};

inline bool MinMax::isCorrect(int limitMin, int limitMax) const
{
    if (min + diff > max)
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

inline void MinMax::cut(MinMax limit)
{
    cut(limit.min, limit.max);
}
