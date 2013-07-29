#ifndef SUBTITLE_H
#define SUBTITLE_H

#include "time.h"

#include <stdio.h>
#include <vector>
#include <QString>

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

    const int getId() const {return id;}

    const Time &startTime() const { return t0;}

    const Time &endTime() const { return t1;}

    const vector<QString> &getLines() const { return lines; }

    int duration() const { return t1.msecTotal() - t0.msecTotal();}

    void print() const
    {
        printf("id:%-4d - %2d:%2d:%2d:%3d - ", getId(), startTime().hour(), startTime().min(), startTime().sec(), startTime().msec());
        printf("%2d:%2d:%2d:%3d ", endTime().hour(), endTime().min(), endTime().sec(), endTime().msec());
        printf("[");
        for (int i=0; i<lines.size(); i++) printf("%s", lines.at(i).toAscii().constData());
        printf("]\n");

    }

private:
    int id;
    Time t0;
    Time t1;
    vector<QString> lines;
};

#endif // SUBTITLE_H
