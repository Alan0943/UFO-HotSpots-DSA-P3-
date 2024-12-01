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
    // menu item 1: user inputs coords, circle of area - outputs all sightings, sorted by distance
    // for sightings with same distance sort by time?
    // menu item 2: user inputs coords - outputs ALL sightings, sorted by distance
    // menu item 3: outputs all sightings sorted by duration length
    // menu item 4: outputs all sightings sorted by time

    // error check inputs

    int choice;
    double lat,lon,radius;
    vector<UFO::Row> temp;
    vector<UFO::Row> output;

    while (true) {
        std::cout << "Welcome to the UFO Sightings Program!\n";
        std::cout << "1. Search sightings by coordinates and radius\n";
        std::cout << "2. Search all sightings by coordinates\n";
        std::cout << "3. Show all sightings sorted by duration\n";
        std::cout << "4. Show all sightings sorted by time\n";
        std::cout << "5. Exit\n";

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {

            // error check
            std::cout << "Enter latitude: ";
            std::cin >> lat;
            std::cout << "Enter longitude: ";
            std::cin >> lon;
            std::cout << "Enter radius in miles: ";
            std::cin >> radius;

            temp = test.sortHelper(lat,lon,radius,"distance");
            output = test.mergeSort(temp);

            //display output

        }

        else if (choice == 2) {

            // error check
            std::cout << "Enter latitude: ";
            std::cin >> lat;
            std::cout << "Enter longitude: ";
            std::cin >> lon;

            temp = test.sortHelper(lat,lon,0,"distance");
            output = test.mergeSort(temp);

            //display output

        }

        else if (choice == 5) {
            std::cout << "Goodbye!" << std::endl;
            break;
        }

        else {
            cout << "Invalid Input" << endl;
        }
    }



}


