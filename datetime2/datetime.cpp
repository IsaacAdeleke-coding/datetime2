//
//  datetime.cpp
//  datetime2
//
//  Created by Isaac Adeleke on 12/12/24.
//

#include "datetime.hpp"
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <cmath>
using namespace std;

// Time Implementation
Time::Time(int hour, int minute, int second) : hour(hour), minute(minute), second(second) {}

void Time::addSeconds(int seconds) {
    second += seconds;
    minute += second / 60;
    second %= 60;
    if (second < 0) {
        second += 60;
        minute--;
    }

    hour += minute / 60;
    minute %= 60;
    if (minute < 0) {
        minute += 60;
        hour--;
    }

    hour %= 24;
    if (hour < 0) hour += 24;
}

void Time::addMinutes(int minutes) { addSeconds(minutes * 60); }
void Time::addHours(int hours) { addSeconds(hours * 3600); }

std::string Time::toString() const {
    ostringstream oss;
    oss << setw(2) << setfill('0') << hour << ":"
        << setw(2) << setfill('0') << minute << ":"
        << setw(2) << setfill('0') << second;
    return oss.str();
}

// Date Implementation
Date::Date(int year, int month, int day) : year(year), month(month), day(day) {}

bool Date::isLeapYear(int year) const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int Date::daysInMonth(int year, int month) const {
    if (month == 2) return isLeapYear(year) ? 29 : 28;
    if (month == 4 || 6 || 9 || 11) return 30;
    return 31;
}

void Date::addDays(int days) {
    day += days;
    while (day > daysInMonth(year, month)) {
        day -= daysInMonth(year, month);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }
    while (day <= 0) {
        month--;
        if (month <= 0) {
            month = 12;
            year--;
        }
        day += daysInMonth(year, month);
    }
}

void Date::addMonths(int months) {
    month += months;
    while (month > 12) {
        month -= 12;
        year++;
    }
    while (month <= 0) {
        month += 12;
        year--;
    }
    day = min(day, daysInMonth(year, month));
}

void Date::addYears(int years) { year += years; }

std::string Date::toString() const {
    ostringstream oss;
    oss << setw(4) << setfill('0') << year << "-"
        << setw(2) << setfill('0') << month << "-"
        << setw(2) << setfill('0') << day;
    return oss.str();
}

std::string Date::dayOfWeek() const {
    int q = day;
    int m = (month < 3) ? month + 12 : month;
    int Y = (month < 3) ? year - 1 : year;

    int K = Y % 100;
    int J = Y / 100;

    int h = (q + (13 * (m + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

    switch (h) {
        case 0: return "Saturday";
        case 1: return "Sunday";
        case 2: return "Monday";
        case 3: return "Tuesday";
        case 4: return "Wednesday";
        case 5: return "Thursday";
        case 6: return "Friday";
        default: return "Invalid";
    }
}

// DateTime Implementation
DateTime::DateTime(int year, int month, int day, int hour, int minute, int second, int timeZoneOffset)
    : date(year, month, day), time(hour, minute, second), timeZoneOffset(timeZoneOffset) {}

void DateTime::adjustToTimeZone(int newTimeZoneOffset) {
    int offsetDifference = newTimeZoneOffset - timeZoneOffset;
    time.addSeconds(offsetDifference * 60);
    timeZoneOffset = newTimeZoneOffset;
}

int DateTime::differenceInSeconds(const DateTime& dt1, const DateTime& dt2) {
    int totalDays1 = dt1.date.year * 365 + dt1.date.day;
    for (int i = 0; i < dt1.date.month - 1; ++i) {
        totalDays1 += dt1.date.daysInMonth(dt1.date.year, i + 1);
    }

    int totalDays2 = dt2.date.year * 365 + dt2.date.day;
    for (int i = 0; i < dt2.date.month - 1; ++i) {
        totalDays2 += dt2.date.daysInMonth(dt2.date.year, i + 1);
    }

    int dayDifference = totalDays1 - totalDays2;
    int secondDifference = (dt1.time.hour * 3600 + dt1.time.minute * 60 + dt1.time.second) -
                           (dt2.time.hour * 3600 + dt2.time.minute * 60 + dt2.time.second);

    return dayDifference * 86400 + secondDifference;
}

std::string DateTime::serialize() const {
    ostringstream oss;
    oss << date.year << "-" << setw(2) << setfill('0') << date.month << "-"
        << setw(2) << setfill('0') << date.day << "T" << setw(2) << setfill('0') << time.hour << ":"
        << setw(2) << setfill('0') << time.minute << ":" << setw(2) << setfill('0') << time.second
        << "Z" << timeZoneOffset;
    return oss.str();
}

DateTime DateTime::deserialize(const std::string& serialized) {
    int year, month, day, hour, minute, second, offset;
    char dash1, dash2, T, colon1, colon2, Z;

    istringstream iss(serialized);
    iss >> year >> dash1 >> month >> dash2 >> day >> T >> hour >> colon1 >> minute >> colon2 >> second >> Z >> offset;

    if (dash1 != '-' || dash2 != '-' || T != 'T' || colon1 != ':' || colon2 != ':' || Z != 'Z') {
        throw invalid_argument("Invalid serialized format");
    }

    return DateTime(year, month, day, hour, minute, second, offset);
}

std::string DateTime::format(const std::string& formatString) const {
    string result;
    for (size_t i = 0; i < formatString.size(); ++i) {
        if (formatString.substr(i, 4) == "YYYY") {
            result += to_string(date.year);
            i += 3;
        } else if (formatString.substr(i, 2) == "MM") {
            result += (date.month < 10 ? "0" : "") + to_string(date.month);
            i += 1;
        } else if (formatString.substr(i, 2) == "DD") {
            result += (date.day < 10 ? "0" : "") + to_string(date.day);
            i += 1;
        } else if (formatString.substr(i, 2) == "HH") {
            result += (time.hour < 10 ? "0" : "") + to_string(time.hour);
            i += 1;
        } else if (formatString.substr(i, 2) == "MM") {
            result += (time.minute < 10 ? "0" : "") + to_string(time.minute);
            i += 1;
        } else if (formatString.substr(i, 2) == "SS") {
            result += (time.second < 10 ? "0" : "") + to_string(time.second);
            i += 1;
        } else {
            result += formatString[i];
        }
    }
    return result;
}
