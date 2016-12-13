#ifndef __MY_TIME_FUNC_H
#define __MY_TIME_FUNC_H

#include <string>

struct MyDay {
    int year;
    int month;
    int date;
    int week;
};

class MyDate {
public:
    MyDate();
    MyDate(std::string dt);
    MyDate(int year, int month, int date = 0, int week = 0);
    ~MyDate();
    bool isLeapYear();
    bool isLeapYear(int y);
    int sub(const MyDay);
    int getWeek();
    void calendar();
    inline MyDay getDay() { return thisDay;}
private:
    MyDay thisDay;
    static const MyDay mBaseDay;
    static const char mStrSplit = '/';
    static const int mCommonYear = 0;
    static const int mLeapYear   = 1;
    static const int mMonthDay[2][12];
    void _initFunc(int year, int month, int day);
    const MyDay* maxDay(const MyDay*, const MyDay*);
};

#endif
