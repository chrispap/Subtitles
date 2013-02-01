#ifndef TIME_H
#define TIME_H

#define MIL_PER_SEC     1000
#define SEC_PER_MIN     60
#define MIN_PER_HOUR    60
#define HOUR_PER_DAY    24

class Time
{
private:
    int totalMilliseconds;

public:
    Time (int _milliseconds):
        totalMilliseconds(_milliseconds)
    {
    }

    Time(int hour, int min, int sec, int msec=0)
    {
        int x = 1;
        totalMilliseconds = 0;
        totalMilliseconds += x* msec;   x *= MIL_PER_SEC;
        totalMilliseconds += x* sec;    x *= SEC_PER_MIN;
        totalMilliseconds += x* min;    x *= MIN_PER_HOUR;
        totalMilliseconds += x* hour;   x *= HOUR_PER_DAY;
    }

    bool operator<=  (const Time &t) { return totalMilliseconds <=  t.totalMilliseconds; }
    bool operator>=  (const Time &t) { return totalMilliseconds >=  t.totalMilliseconds; }

    int hour() const
    {
        int x = MIL_PER_SEC * SEC_PER_MIN * MIN_PER_HOUR;
        return (totalMilliseconds/x);
    }

    int min() const
    {
        int x = MIL_PER_SEC * SEC_PER_MIN;
        int d = MIN_PER_HOUR;
        return (totalMilliseconds/x)%d;
    }

    int sec() const
    {
        int x = MIL_PER_SEC;
        int d = SEC_PER_MIN;
        return (totalMilliseconds/x)%d;
    }

    int msec() const
    {
        int d = MIL_PER_SEC;
        return totalMilliseconds%d;
    }

    int msecTotal() const
    {
        return totalMilliseconds;
    }

};

#endif // TIME_H
