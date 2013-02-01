#ifndef TIME_H
#define TIME_H

#define MIL_PER_SEC     1000
#define SEC_PER_MIN     60
#define MIN_PER_HOUR    60
#define HOUR_PER_DAY    24

typedef unsigned long int ulong;

class Time
{
private:
    ulong totalMilliseconds;

public:
    Time(int hour=0, int min=0, int sec=0, int msec=0)
    {
        ulong x = 1;
        totalMilliseconds = 0;
        totalMilliseconds += x* msec;   x *= MIL_PER_SEC;
        totalMilliseconds += x* sec;    x *= SEC_PER_MIN;
        totalMilliseconds += x* min;    x *= MIN_PER_HOUR;
        totalMilliseconds += x* hour;   x *= HOUR_PER_DAY;
    }

    int hour() const
    {
        ulong x = MIL_PER_SEC * SEC_PER_MIN * MIN_PER_HOUR;
        ulong d = HOUR_PER_DAY;
        return (totalMilliseconds/x);
    }

    int min() const
    {
        ulong x = MIL_PER_SEC * SEC_PER_MIN;
        ulong d = MIN_PER_HOUR;
        return (totalMilliseconds/x)%d;
    }

    int sec() const
    {
        ulong x = MIL_PER_SEC;
        ulong d = SEC_PER_MIN;
        return (totalMilliseconds/x)%d;
    }

    int msec() const
    {
        ulong d = MIL_PER_SEC;
        return totalMilliseconds%d;
    }

    int msecTotal() const
    {
        return totalMilliseconds;
    }

};

#endif // TIME_H
