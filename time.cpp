#include "time.h"

#define MIL_PER_SEC     1000
#define SEC_PER_MIN     60
#define MIN_PER_HOUR    60
#define HOUR_PER_DAY    24

Time::Time (int msec)
    : m_msec(msec)
{

}

Time::Time(int hour, int min, int sec, int msec)
{
    int x = 1;
    m_msec = 0;
    m_msec += x* msec;   x *= MIL_PER_SEC;
    m_msec += x* sec;    x *= SEC_PER_MIN;
    m_msec += x* min;    x *= MIN_PER_HOUR;
    m_msec += x* hour;   x *= HOUR_PER_DAY;
}

int Time::hour() const
{
    int x = MIL_PER_SEC * SEC_PER_MIN * MIN_PER_HOUR;
    return (m_msec/x);
}

int Time::min() const
{
    int x = MIL_PER_SEC * SEC_PER_MIN;
    int d = MIN_PER_HOUR;
    return (m_msec/x)%d;
}

int Time::sec() const
{
    int x = MIL_PER_SEC;
    int d = SEC_PER_MIN;
    return (m_msec/x)%d;
}

int Time::msec() const
{
    int d = MIL_PER_SEC;
    return m_msec%d;
}

int Time::msecTotal() const
{
    return m_msec;
}

bool Time::operator<=  (const Time &t) const
{
    return m_msec <=  t.m_msec;
}

bool Time::operator>=  (const Time &t) const
{
    return m_msec >=  t.m_msec;
}
