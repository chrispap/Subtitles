#ifndef SUBTITLE_H
#define SUBTITLE_H

#include "time.h"
#include <QString>
#include <iostream>
#include <vector>

class Subtitle
{

public:
    Subtitle(int _id, Time _t0, Time _t1, std::vector<QString> &_lines);

    const int getId() const;

    const Time &startTime() const;

    const Time &endTime() const;

    const std::vector<QString> &getLines() const;

    int duration() const;

    void print() const;

private:
    int id;
    Time t0;
    Time t1;
    std::vector<QString> lines;
};

#endif
