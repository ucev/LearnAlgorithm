#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "time_func.h"

using namespace std;

MyDate::MyDate() {
}

MyDate::MyDate(string dt) {
    int arr[3] = {0, 0, 0};
    int startpos = 0;
    int endpos;
    for (int i = 0; i < 3; i++) {
        endpos = dt.find(mStrSplit, startpos);
	if (endpos != string::npos) {
	    arr[i] = atoi(dt.substr(startpos, endpos - startpos).c_str());
	    startpos = endpos + 1;
	} else {
	    arr[i] = atoi(dt.substr(startpos).c_str());
	    break;
	}
    }
    for (int i = 0; i < 3; ++i) {
        cout << arr[i] << "   ";
    }
    cout << endl;
    _initFunc(arr[0], arr[1], arr[2]);
}

MyDate::MyDate(int year, int month, int date, int week) {
    _initFunc(year, month, date);
    if (week > 0) {
        week = week;
    }
}

MyDate::~MyDate() {
}

bool MyDate::isLeapYear() {
    return isLeapYear(thisDay.year);
}

bool MyDate::isLeapYear(int y) {
    return !(y % 4 != 0 || (y % 100 == 0 && y % 400 != 0));
}

int MyDate::sub(const MyDay dt) {
    if (thisDay.date <=0 || dt.date <=0) {
        return 0;
    }
    int dayCount = 0;
    const MyDay* max = maxDay(&thisDay, &dt);
    const MyDay* min = &thisDay == max ? &dt : &thisDay;
    for (int y = min->year; y <= max->year; y++) {
        int arrPos = isLeapYear(y) ? mLeapYear : mCommonYear;
	int monMin = 0;
	int monMax = 12;
	if (y == min->year) {
	    monMin = min->month - 1;
	    dayCount -= min->date;
	} else if (y == max->year) {
	    monMax = max->month - 1;
	    dayCount += max->date;
	}
	for (int i = monMin; i < monMax; i++) {
	    dayCount += mMonthDay[arrPos][i];
	}
    }
    return min == &thisDay ? -dayCount : dayCount;
}

int MyDate::getWeek() {
    int daySub = sub(mBaseDay);
    int s = daySub % 7;
    int w =  (mBaseDay.week + s) % 7;
    return w == 0 ? 7 : w;
}

void MyDate::calendar() {
    for (int i = 0; i < 12; ++i) {
        cout << mMonthDay[1][i] << "  ";
    }
    cout << endl;
    bool leapYear = isLeapYear();
    int arrPos = leapYear ? mLeapYear : mCommonYear;
    MyDate dt(thisDay.year, thisDay.month, 1);
    const int dayCount = mMonthDay[arrPos][thisDay.month - 1];
    int w = thisDay.week == 7 ? 0 : dt.getWeek();
    int outCount = 0;
    for (int i = 0; i < w; i++, outCount++) {
	cout << setw(2) << ' ' << setw(3) << ' ';
    }
    for (int i = 1; i <= dayCount; i++) {
	cout << setw(2) << i << setw(3) << ' ';
	outCount++;
	if (outCount % 7 == 0) {
	    outCount = 0;
	    cout << endl;
	}
    }
    cout << endl;
}

void MyDate::_initFunc(int y, int m, int d) {
    thisDay.year = y;
    thisDay.month = m;
    thisDay.date = d;
    if (y != mBaseDay.year && m != mBaseDay.month && d != mBaseDay.date) {
        thisDay.week = getWeek();
    }
}

const MyDay* MyDate::maxDay(const MyDay* a, const MyDay* b) {
    if (a->year > b->year) {
        return a;
    } else if (a->year < b->year) {
        return b;
    } else {
        if (a->month > b->month) {
	    return a;
	} else if (a->month < b->month) {
	    return b;
	} else {
	    if (a->date > b->date) {
	        return a;
	    } else {
	        return b;
	    }
	}
    }
}

const MyDay MyDate::mBaseDay = {2000, 1, 1, 6};
const int MyDate::mMonthDay[2][12] = {
        {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
        {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
    };
