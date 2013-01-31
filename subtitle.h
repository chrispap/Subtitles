#ifndef SUBTITLE_H
#define SUBTITLE_H

#include "time.h"

#include <string>

using namespace std;

class Subtitle
{

public:
    Subtitle(int _id, Time _t0, Time _t1, string _txt) :
        id(_id), t0(_t0), t1(_t1), txt(_txt) { }

    Time startTime() { return t0;}
    Time endTime() { return t1;}
    ulong duration() { return t1.msecTotal() - t0.msecTotal();}
    string getText() { return txt; }

private:
    int id;
    Time t0;
    Time t1;
    string txt;
};

#endif // SUBTITLE_H
