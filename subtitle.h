#ifndef SUBTITLE_H
#define SUBTITLE_H

#include "time.h"

#include <QString>
#include <vector>

using namespace std;

class Subtitle
{

public:
    Subtitle(int _id, Time _t0, Time _t1, vector<QString> &_lines) :
        id(_id),
        t0(_t0),
        t1(_t1),
        lines(_lines)
    {

    }

    const Time &startTime() const { return t0;}

    const Time &endTime() const { return t1;}

    const vector<QString> &getLines() const { return lines; }

    int duration() const { return t1.msecTotal() - t0.msecTotal();}

private:
    int id;
    Time t0;
    Time t1;
    vector<QString> lines;
};

#endif // SUBTITLE_H
