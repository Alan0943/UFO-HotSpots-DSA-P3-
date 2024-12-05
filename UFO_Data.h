#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;

// https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-pairs-in-c/
// used for grid_map and a map in sortHelper2 (both have a pair for their key)
struct PairHash {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        // Hash the first element
        size_t hash1 = hash<T1>{}(p.first);
        // Hash the second element
        size_t hash2 = hash<T2>{}(p.second);
        // Combine the two hash values
        return hash1
               ^ (hash2 + 0x9e3779b9 + (hash1 << 6)
                  + (hash1 >> 2));
    }
};

// struct that handles all UFO operations
struct UFO {

    // struct that stores each row data line's attributes as variables
    struct Row {

        string city;
        string state;
        string country;

        string shape;
        double duration;
        string description;

        double latitude;
        double longitude;

        string year;
        string month;
        string day;
        string hour;
        string minute;

        string year_doc;
        string month_doc;
        string day_doc;

        double distance;
        int city_count;

    };

    // map data structure
    // keys are grids with an area of latitude 10 by longitude 10
    // grids cover continental U.S from 50N,-120W to 20N,-60W
    // theoretical maximum of 21 grids
    unordered_map<pair<int,int>, vector<Row>, PairHash> grid_map;

    UFO();

    void insert(double lat, double lon, vector<string> vec);

    double distanceCalc(double lat1, double lon1, double lat2, double lon2);

    vector<UFO::Row> sortHelper(double lat, double lon, int radius);

    vector<UFO::Row> sortHelper_2(vector<UFO::Row> vec);

    vector<UFO::Row> grid_map_to_vec();

    void merge(vector<UFO::Row>& vec, int left, int mid, int right, const string& data_type);

    void mergeSort(vector<UFO::Row>& vec,int left, int right, const string& data_type);

    void quickSort(vector<UFO::Row> &vec, int low, int high, string datatype);

    int partition(vector<UFO::Row> &vec, int up, int down, string datatype);

};




