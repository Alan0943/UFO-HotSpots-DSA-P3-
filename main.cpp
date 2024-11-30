#include "UFO_Data.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main() {

    UFO test;

    // test insert
    std::vector<std::string> vec = {
            "11111City", "StateName", "CountryName", "Triangle", "5 minutes", "Bright light",
            "33.6008333", "-85.831667", "2024", "10", "01", "14", "30",
            "2024", "10", "01"
    };
    test.insert(33.6008333,-85.831667, vec);

//     testing keys
    for (const auto& entry : test.grid_map) {
        const pair<int, int>& key = entry.first;
        cout << "Key: (" << key.first << ", " << key.second << ")" << endl;
    }

//     testing indvidual key
    for (const auto& sighting : test.grid_map[pair(30,-90)]) {
        cout << "City: " << sighting.city << ", State: " << sighting.state << ", Country: "
             << sighting.country << endl;
    }

    // make a main menu, with a while loop that asks for input / outputs

}


