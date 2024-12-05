#include "UFO_Data.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

//test
int main() {

    // declaration of UFO class
    UFO ufo;

    string choice;
    string lat_str, lon_str, radius_str, sort_choice;
    double lat, lon, radius;

    // menu
    while (true) {

        cout << "Welcome to the UFO Sightings Program!\n";
        cout << "1. View all sightings within a radius (max 500 miles) (input coordinates).\n";
        cout << "2. View cities with most sightings within a radius (max 500 miles) (input coordinates).\n";
        cout << "3. View Top 50 cities sorted by most sightings.\n";
        cout << "4. View Top 50 cities sorted by viewing duration.\n";
        cout << "5. Insert New Sighting.\n";

        cout << "6. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;
        cout << endl;

        if (choice == "1") {

            cout << "Merge Sort (M) or Quick Sort (Q)? (Enter M or Q only): ";
            cin >> sort_choice;

            // input
            cout << "Enter latitude: ";
            cin >> lat_str;
            cout << endl;

            cout << "Enter longitude: ";
            cin >> lon_str;
            cout << endl;

            cout << "Enter radius in miles: ";
            cin >> radius_str;
            cout << endl;

            // error checks for if it's a double or not
            try {
                lat = stod(lat_str);
                lon = stod(lon_str);
                radius = stod(radius_str);
            }
            catch (const std::invalid_argument& e) {
                cout << "Invalid input: Please enter valid numeric values for latitude, longitude, and radius." << endl;
            }

            // error checks distance
            if (lat > 50 || lat < 20 || lon < -130 || lon > -60 || radius > 501 || radius < 1) {
                cout << "Invalid Input: Radius <= 500, Lat 20-50, Lon -130 to -60." << endl;
                continue;
            }

            // gets all applicable sightings
            vector<UFO::Row> rows_vec = ufo.sortHelper(lat,lon,radius);

            // merge sort or quick sort option
            if (sort_choice == "M") {
                ufo.mergeSort(rows_vec, 0 , rows_vec.size()-1, "distance");
            }
            else if (sort_choice == "Q") {
                ufo.quickSort(rows_vec, 0, rows_vec.size() - 1, "distance");
            }

            for (auto & i : rows_vec) {
                cout << i.city << " " << i.state << " " << i.distance << endl;
            }

        }

        else if (choice == "2") {

            cout << "Merge Sort (M) or Quick Sort (Q)? (Enter M or Q only): ";
            cin >> sort_choice;

            // input
            cout << "Enter latitude:    ";
            cin >> lat_str;
            cout << endl;

            cout << "Enter longitude:   ";
            cin >> lon_str;
            cout << endl;

            cout << "Enter radius in miles: ";
            cin >> radius_str;
            cout << endl;

            // error checks for if its a double or not
            try {
                lat = stod(lat_str);
                lon = stod(lon_str);
                radius = stod(radius_str);
            }
            catch (const std::invalid_argument& e) {
                cout << "Invalid input: Please enter valid numeric values for latitude, longitude, and radius." << endl;
            }

            // error checks distance
            if (lat > 50 || lat < 20 || lon < -130 || lon > -60 || radius > 501 || radius < 1) {
                cout << "Invalid Input: Radius <= 500, Lat 20-50, Lon -130 to -60." << endl;
                continue;
            }

            // gets all applicable sightings
            vector<UFO::Row> rows_vec = ufo.sortHelper(lat,lon,radius);

            // condenses rows_vec so thats its unique cities and each UFO::Row has city_count updated
            vector<UFO::Row> city_vec = ufo.sortHelper_2(rows_vec);

            // merge sort or quick sort option
            if (sort_choice == "M") {
                ufo.mergeSort(city_vec, 0, city_vec.size()-1, "city_count");
            }
            else if (sort_choice == "Q") {
                ufo.quickSort(city_vec, 0, city_vec.size()-1, "city_count");
            }

            for (auto & i : city_vec) {
                cout << i.city << " " << i.city_count << " " << i.distance << i.state << endl;
            }
        }

        else if (choice == "3") {

            cout << "Merge Sort (M) or Quick Sort (Q)? (Enter M or Q only): ";
            cin >> sort_choice;

            // gets every single sighting in this vector
            vector<UFO::Row> UFO_all = ufo.grid_map_to_vec();

            // condenses UFO_all so that it is only unique cities and each UFO::Row has city_count updated
            vector<UFO::Row> city_vec = ufo.sortHelper_2(UFO_all);

            // merge sort or quick sort option
            if (sort_choice == "M") {
                ufo.mergeSort(city_vec, 0, city_vec.size()-1, "city_count");
            }
            else if (sort_choice == "Q") {
                ufo.quickSort(city_vec, 0, city_vec.size()-1, "city_count");
            }

            for (int i = 0; i < 50; i++) {
                cout << city_vec[i].city << " " << city_vec[i].state << " " << city_vec[i].city_count << endl;
            }
        }

        else if (choice == "4") {

            cout << "Merge Sort (M) or Quick Sort (Q)? (Enter M or Q only): ";
            cin >> sort_choice;

            // gets every single sighting in this vector
            vector<UFO::Row> UFO_all = ufo.grid_map_to_vec();

            // merge sort or quick sort option
            if (sort_choice == "M") {
                ufo.mergeSort(UFO_all, 0 , UFO_all.size()-1, "duration");
            }
            else if (sort_choice == "Q") {
                ufo.quickSort(UFO_all, 0, UFO_all.size()-1, "duration");
            }

            for (int i = 0; i < 50; i++) {
                cout << UFO_all[i].city << " " << UFO_all[i].state << " " << UFO_all[i].duration << endl;
            }
        }

        else if (choice == "5") {

            // vector that stores all row attributes
            vector<string> insert_vec;

            cout << "Enter City (string): ";
            string city;
            cin >> city;
            insert_vec.push_back(city);

            cout << "Enter State (string): ";
            string state;
            cin >> state;
            insert_vec.push_back(state);

            cout << "Enter Country (string): ";
            string country;
            cin >> country;
            insert_vec.push_back(country);

            cout << "Enter Shape of UFO (string): ";
            string shape;
            cin >> shape;
            insert_vec.push_back(shape);

            cout << "Enter Duration (string): ";
            string duration;
            cin >> duration;
            insert_vec.push_back(duration);

            cout << "Enter Description (string): ";
            string description;
            cin >> description;
            insert_vec.push_back(description);

            cout << "Enter Latitude (double): ";
            string latitude;
            cin >> latitude;
            insert_vec.push_back(latitude);

            cout << "Enter Longitude (double): ";
            string longitude;
            cin >> longitude;
            insert_vec.push_back(longitude);

            cout << "Enter Year of Sight (string): ";
            string year;
            cin >> year;
            insert_vec.push_back(year);

            cout << "Enter Month of Sight (string): ";
            string month;
            cin >> month;
            insert_vec.push_back(month);

            cout << "Enter Day of Sight (string): ";
            string day;
            cin >> day;
            insert_vec.push_back(day);

            cout << "Enter Hour of Sight (string): ";
            string hour;
            cin >> hour;
            insert_vec.push_back(hour);

            cout << "Enter Minute of Sight (string): ";
            string minute;
            cin >> minute;
            insert_vec.push_back(minute);

            cout << "Enter Year of Documentation (string): ";
            string year_doc;
            cin >> year_doc;
            insert_vec.push_back(year_doc);

            cout << "Enter Month of Documentation (string): ";
            string month_doc;
            cin >> month_doc;
            insert_vec.push_back(month_doc);

            cout << "Enter Day of Documentation (string): ";
            string day_doc;
            cin >> day_doc;
            insert_vec.push_back(day_doc);

            // error checks
            try {
                ufo.insert(stod(insert_vec[6]), stod(insert_vec[7]), insert_vec);
            } catch (const std::invalid_argument& e) {
                cout << "Error: Invalid argument. Please enter valid numeric values for latitude and longitude." << endl;
            } catch (const exception& e) {
                cout << "Error: An unexpected error occurred: " << e.what() << endl;
            }
            continue;
        }

        else if (choice == "6") {
            cout << "End!" << endl;
            break;
        }

        // error checks choice
        else {
            cout << "Invalid Input - Insert a Number Between 1 and 6\n" << endl;
        }
    }
}


