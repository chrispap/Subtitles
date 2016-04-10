#ifndef TIME_H
#define TIME_H

class Time
{
public:
    Time (int _milliseconds);

    Time(int hour, int min, int sec, int msec=0);

    int hour() const;

    int min() const;

    int sec() const;

    int msec() const;

    int msecTotal() const;

    bool operator<= (const Time &t) const;

    bool operator>= (const Time &t) const;

private:
    int m_msec;
};

#endif
