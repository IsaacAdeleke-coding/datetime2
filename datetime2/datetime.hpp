#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <string>

// Base Class: DateTimeBase
class DateTimeBase {
public:
    virtual std::string toString() const = 0;
    virtual ~DateTimeBase() = default;
};

// Derived Class: Time
class Time : public DateTimeBase {
public:
    int hour, minute, second;

    Time(int hour = 0, int minute = 0, int second = 0);
    void addSeconds(int seconds);
    void addMinutes(int minutes);
    void addHours(int hours);
    std::string toString() const override;
};

// Derived Class: Date
class Date : public DateTimeBase {
public:
    int year, month, day;

    Date(int year = 1970, int month = 1, int day = 1);
    bool isLeapYear(int year) const;
    int daysInMonth(int year, int month) const;
    void addDays(int days);
    void addMonths(int months);
    void addYears(int years);
    std::string toString() const override;
    std::string dayOfWeek() const; // Returns the day of the week
};

// Derived Class: DateTime
class DateTime : public Date, public Time {
public:
    int timeZoneOffset; // Time zone offset in minutes (e.g., -300 for EST)

    DateTime(int year, int month, int day, int hour, int minute, int second, int timeZoneOffset = 0);

    void adjustToTimeZone(int newTimeZoneOffset);
    void applyDaylightSavingTime(int dstStartMonth, int dstStartDay, int dstEndMonth, int dstEndDay);

    static int differenceInSeconds(const DateTime& dt1, const DateTime& dt2);

    std::string serialize() const;
    static DateTime deserialize(const std::string& serialized);

    std::string format(const std::string& formatString) const;
};

#endif // DATETIME_HPP
