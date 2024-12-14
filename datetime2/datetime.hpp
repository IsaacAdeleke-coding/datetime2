#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <string>

// Base Class: TimeBase
class TimeBase {
public:
    virtual std::string toString() const = 0;
    virtual ~TimeBase() = default;
};

// Derived Class: Time
class Time : public TimeBase {
private:
    int hour, minute, second;
public:
    Time(int hour, int minute, int second);
    void addSeconds(int seconds);
    void addMinutes(int minutes);
    void addHours(int hours);
    std::string toString() const override;
};

// Base Class: DateBase
class DateBase {
public:
    virtual std::string toString() const = 0;
    virtual std::string dayOfWeek() const = 0;
    virtual ~DateBase() = default;
};

// Derived Class: Date
class Date : public DateBase {
private:
    int year, month, day;
    bool isLeapYear(int year) const;
    int daysInMonth(int year, int month) const;
public:
    Date(int year, int month, int day);
    void addDays(int days);
    void addMonths(int months);
    void addYears(int years);
    std::string toString() const override;
    std::string dayOfWeek() const override;
};

// Derived Class: DateTime
class DateTime : public Date, public Time {
private:
    int timeZoneOffset;
public:
    DateTime(int year, int month, int day, int hour, int minute, int second, int timeZoneOffset);
    void adjustToTimeZone(int newTimeZoneOffset);
    static int differenceInSeconds(const DateTime& dt1, const DateTime& dt2);
    std::string serialize() const;
    static DateTime deserialize(const std::string& serialized);
    std::string format(const std::string& formatString) const;
};

#endif // DATETIME_HPP
