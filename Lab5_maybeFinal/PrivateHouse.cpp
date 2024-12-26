#include "PrivateHouse.h"

PrivateHouse::PrivateHouse(string City, string Street, int BuildingNumber)
    : Address(City, Street, BuildingNumber) {}

string PrivateHouse::GetType() const {
    return "Private";
}
string PrivateHouse::toString() const {
    return "Private: " + city + " " + street + " " + to_string(buildingNumber);
}
