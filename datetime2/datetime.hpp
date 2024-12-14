//
//  datetime.hpp
//  datetime2
//
//  Created by Isaac Adeleke on 12/12/24.
//

#ifndef DATETIME_HPP
#define DATETIME_HPP

#include <string>

// Base class for Date and Time
class DateTimeBase {
public:
    virtual std::string toString() const = 0; // Pure virtual method
    virtual ~DateTimeBase() = default;       // Virtual destructor for polymorphism
};

// Time Class inheriting DateTimeBase
class Time : public DateTimeBase {
public:
    int hour, minute, second;

    Time(int hour = 0, int minute = 0, int second = 0);
    void addSeconds(int seconds);
    void addMinutes(int minutes);
    void addHours(int hours);
    std::string toString() const override;
};

// Date Class inheriting DateTimeBase
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

    // Calendar Operations
    std::string dayOfWeek() const; // Returns the day of the week
};

// DateTime Class inheriting DateTimeBase
class DateTime : public DateTimeBase {
public:
    Date date;
    Time time;
    int timeZoneOffset; // Time zone offset in minutes (e.g., -300 for EST)

    DateTime(int year, int month, int day, int hour, int minute, int second, int timeZoneOffset = 0);

    // Time Zone Conversion
    void adjustToTimeZone(int newTimeZoneOffset);

    // Difference
    static int differenceInSeconds(const DateTime& dt1, const DateTime& dt2);

    // Serialization and Deserialization
    std::string serialize() const;
    static DateTime deserialize(const std::string& serialized);

    // Formatting
    std::string format(const std::string& formatString) const override;
};

#endif
