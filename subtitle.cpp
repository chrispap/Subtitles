#include "subtitle.h"

using namespace std;

Subtitle::Subtitle(int _id, Time _t0, Time _t1, vector<QString> &_lines)
    : id(_id)
    , t0(_t0)
    , t1(_t1)
    , lines(_lines)
{

}

const int Subtitle::getId() const
{
    return id;
}

const Time& Subtitle::startTime() const
{
    return t0;
}

const Time& Subtitle::endTime() const
{
    return t1;
}

const vector<QString>& Subtitle::getLines() const
{
    return lines;
}

int Subtitle::duration() const
{
    return t1.msecTotal() - t0.msecTotal();
}

void Subtitle::print() const
{
    printf("id:%-4d - %2d:%2d:%2d:%3d - ", getId(), startTime().hour(), startTime().min(), startTime().sec(), startTime().msec());
    printf("%2d:%2d:%2d:%3d ", endTime().hour(), endTime().min(), endTime().sec(), endTime().msec());
    printf("[");
    for (unsigned i=0; i!=lines.size(); i++) {
        std::cout << lines.at(i).toStdString();
    }
    printf("]\n");
}
