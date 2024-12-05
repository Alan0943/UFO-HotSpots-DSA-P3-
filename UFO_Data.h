#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <unordered_map>
#include <map>
#include <vector>
using namespace std;

// used for grid_map
struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        // hash func is adding the hashes of the two integers
        // two integers will be floor of inputted latitude and longitude (floored to nearest multiple of 10 - and converted to int from double)
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
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

    // temporary remove after implementing real sort
    vector<UFO::Row> tempSort(vector<UFO::Row> vec, string datatype);

};




