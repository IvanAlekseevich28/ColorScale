#pragma once

struct MinMax
{
    int min;
    int max;
    MinMax(int max) : min(0), max(max) {}
    MinMax(int min, int max) : min(min), max(max){}
    bool isCorrect(int limitMin, int limitMax)const;
    void cut(int limitMin, int limitMax);
    void cut(MinMax limit);
};

inline bool MinMax::isCorrect(int limitMin, int limitMax) const
{
    if (min > max)
        return false;
    if (min < limitMin || max > limitMax)
        return false;

    return true;
}

inline void MinMax::cut(int limitMin, int limitMax)
{
    if (min < limitMin) min = limitMin;
    if (max > limitMax) max = limitMax;
    if (min > max) min = max;
}

inline void MinMax::cut(MinMax limit)
{
    cut(limit.min, limit.max);
}
