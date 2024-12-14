//
//  main.cpp
//  datetime2
//
//  Created by Isaac Adeleke on 12/12/24.
//

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
