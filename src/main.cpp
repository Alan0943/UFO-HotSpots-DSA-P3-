#include "UFO_Data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_map>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        // hash func is adding the hashes of the two integers
        // two integers will be floor of inputted latitude and longitude (floored to nearest multiple of 10 - and converted to int from double)
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

// not sure if we need this
struct PairEqual {
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};


int main() {

    filesystem::path filepath = "C:/Users/seann/Documents/Project3/src/ufo_sightings.csv";

    ifstream file(filepath);

    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // use for testing csv reading
//    string line;
//    bool isHeader = true;
//    int lineCount = 0;
//
//    while (getline(file, line)) {
//        if (isHeader) {
//            isHeader = false;
//            continue;
//        }
//
//        lineCount++;
//        if (lineCount >= 50) {
//            break;
//        }
//    }
//
//    file.close();


    vector<UFO> ufoList;
    string line;
    bool isHeader = true;

    while (getline(file, line)) {

        // Skip the header line
        if (isHeader) {
            isHeader = false;
            continue;
        }

        stringstream ss(line);
        UFO ufo;
        string field;

        // Read each field based on column headers
        getline(ss, ufo.city, ',');
        getline(ss, ufo.state, ',');
        getline(ss, ufo.country, ',');

        getline(ss, ufo.shape, ',');
        getline(ss, ufo.duration, ',');
        getline(ss, ufo.description, ',');

        // removes commas so lat/long can be converted to double
        getline(ss, field, ',');
        ufo.latitude = stod(field);
        getline(ss, field, ',');
        ufo.longitude = stod(field);

        getline(ss, ufo.year, ',');
        getline(ss, ufo.month, ',');
        getline(ss, ufo.day, ',');
        getline(ss, ufo.hour, ',');
        getline(ss, ufo.minute, ',');

        getline(ss, ufo.year_doc, ',');
        getline(ss, ufo.month_doc, ',');
        getline(ss, ufo.day_doc, ',');

        ufoList.push_back(ufo);
    }

    cout << ufoList[6009].longitude << endl;

    // Testing

    // hash table implementation in main:

    unordered_map<pair<int,int>, vector<UFO>, PairHash, PairEqual> my_hashtable;




}


