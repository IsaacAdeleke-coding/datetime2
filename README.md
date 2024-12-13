# DateTime Utility Suite

A C++ library for handling dates and times with support for advanced features like time zone conversion, calendar operations, and serialization/deserialization.

---

## Features

### Date Class
- Add or subtract days, months, and years.
- Handle leap years and month boundaries.
- Calculate the number of days in a month.
- Determine the day of the week using Zeller's Congruence.

### Time Class
- Add or subtract seconds, minutes, and hours.
- Handle time overflow and underflow.

### DateTime Class
- Combine `Date` and `Time` into a unified class.
- Adjust for time zones and daylight saving time.
- Serialize and deserialize `DateTime` objects to and from strings.
- Format `DateTime` with custom formats like `YYYY-MM-DD` or `HH:MM`.

---

## Installation

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd DateTimeUtilitySuite
Compile the code:

g++ -o datetime datetime_main.cpp datetime.cpp

Usage

Example

#include "datetime.hpp"
#include <iostream>
using namespace std;

int main() {
    DateTime dt1(2023, 12, 10, 23, 59, 59, -300); // EST Time Zone
    DateTime dt2(2023, 12, 9, 12, 30, 0, 0);      // UTC Time Zone

    cout << "DateTime 1: " << dt1.date.toString() << " " << dt1.time.toString() << endl;
    cout << "DateTime 2: " << dt2.date.toString() << " " << dt2.time.toString() << endl;

    dt1.adjustToTimeZone(0); // Convert to UTC
    cout << "DateTime 1 (Converted to UTC): " << dt1.date.toString() << " " << dt1.time.toString() << endl;

    cout << "Day of the Week (dt2): " << dt2.date.dayOfWeek() << endl;

    cout << "Serialized dt1: " << dt1.serialize() << endl;
    DateTime dt3 = DateTime::deserialize("2023-12-10T23:59:59Z-300");
    cout << "Deserialized dt3: " << dt3.date.toString() << " " << dt3.time.toString() << endl;

    return 0;
}

Output

DateTime 1: 2023-12-10 23:59:59
DateTime 2: 2023-12-09 12:30:00
DateTime 1 (Converted to UTC): 2023-12-11 04:59:59
Day of the Week (dt2): Saturday
Serialized dt1: 2023-12-10T23:59:59Z-300
Deserialized dt3: 2023-12-10 23:59:59

Contributing

Feel free to open issues or submit pull requests for improvements or bug fixes.


