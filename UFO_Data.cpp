#include "UFO_Data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cmath>
#include <algorithm>

// automatically (it's a constructor) inserts data from csv into grid_map
UFO::UFO() {
    // data set
    filesystem::path filepath = "../resources/ufo_sightings.csv";
    
    // opens file
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
    }

    string line;
    int lat,lon;
    bool isHeader = true;

    // inputs file data into grid_map
    while (getline(file, line)) {

        // Skip the header line
        if (isHeader) {
            isHeader = false;
            continue;
        }

        stringstream ss(line);
        Row data;
        string field;

        // Read each field based on column headers
        getline(ss, data.city, ',');
        getline(ss, data.state, ',');
        getline(ss, data.country, ',');

        getline(ss, data.shape, ',');

        getline(ss, field, ',');
        data.duration = stod(field);

        getline(ss, data.description, ',');

        // removes commas so lat/long can be converted to double
        getline(ss, field, ',');
        data.latitude = stod(field);
        getline(ss, field, ',');
        data.longitude = stod(field);

        getline(ss, data.year, ',');
        getline(ss, data.month, ',');
        getline(ss, data.day, ',');
        getline(ss, data.hour, ',');
        getline(ss, data.minute, ',');

        getline(ss, data.year_doc, ',');
        getline(ss, data.month_doc, ',');
        getline(ss, data.day_doc, ',');

        // gets key value, which is lat,lon of lower left corner of grid
        // does this by dividing lat/lon by 10, flooring it, then * 10
        lat = int(floor(data.latitude / 10)) * 10;
        lon = int(floor(data.longitude / 10)) * 10;

        grid_map[{lat, lon}].push_back(data);

    }
}

// inserts new data
void UFO::insert(double lat, double lon, vector<string> vec) {

    int new_lat = int(floor(lat / 10)) * 10;
    int new_lon = int(floor(lon / 10)) * 10;

    // error checks to see if coords are out of bounds
    if (new_lat > 50 || new_lat < 20 || new_lon < -130 || new_lon > -60) {
        cout << "Invalid Input: Lat 20-50, Lon -130 to -60." << endl;
        return;
    }

    Row data;

    data.city = vec[0];
    data.state = vec[1];
    data.country = vec[2];

    data.shape = vec[3];
    data.duration = stod(vec[4]);
    data.description = vec[5];

    data.latitude = lat;
    data.longitude = lon;

    data.year = vec[8];
    data.month = vec[9];
    data.day = vec[10];
    data.hour = vec[11];
    data.minute = vec[12];

    data.year_doc = vec[13];
    data.month_doc = vec[14];
    data.day_doc = vec[15];

    grid_map[pair(new_lat,new_lon)].push_back(data);

    cout << "Successful Input" << endl;

}

// https://www.geeksforgeeks.org/haversine-formula-to-find-distance-between-two-points-on-a-sphere/
// uses haversine formula to calculate the distance between two sets of lats,lons
double UFO::distanceCalc(double lat1, double lon1, double lat2, double lon2) {

    // finds distance between lats/lons
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply haversine formula
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);

    // mean radius in terms of miles
    double rad = 3959.0;

    double c = 2 * asin(sqrt(a));
    return rad * c;
}

// used for menu option 1 and 2
// gets all data within radius and returns it as a vector
vector<UFO::Row> UFO::sortHelper(double lat, double lon, int radius) {

    // Determine the key of the current grid
    int lat_key = int(floor(lat / 10)) * 10;
    int lon_key = int(floor(lon / 10)) * 10;

    vector<Row> result;
    double current_dist;

    // List of all grid keys to check (current grid + adjacent grids)
    vector<pair<int, int>> grids_to_check = {
            {lat_key, lon_key},                 // current grid
            {lat_key - 10, lon_key},            // north
            {lat_key + 10, lon_key},            // south
            {lat_key, lon_key - 10},            // west
            {lat_key, lon_key + 10},            // east
            {lat_key - 10, lon_key - 10},       // north-west
            {lat_key - 10, lon_key + 10},       // north-east
            {lat_key + 10, lon_key - 10},       // south-west
            {lat_key + 10, lon_key + 10}        // south-east
    };

    // Loop through each grid to check
    for (auto& grid : grids_to_check) {

        // Check if the grid exists in the map
        if (grid_map.find(grid) != grid_map.end()) {

            for ( auto& i : grid_map[grid]) {

                // Calculate the distance between the current location and the sighting
                current_dist = distanceCalc(lat, lon, i.latitude, i.longitude);

                // If the distance is within the radius, add the sighting to the result
                if (current_dist <= radius) {
                    i.distance = current_dist;
                    result.push_back(i);
                }
            }
        }
    }

    return result;
}

// used for menu option 2
// reduces to unique cities only and updates city_count for each city and returns as a vector
vector<UFO::Row> UFO::sortHelper_2(vector<UFO::Row> vec) {

    // creates an unordered_map with a city as key and city count and distance as data
    unordered_map<string, pair<int, double>> city_map;
    vector<UFO::Row> return_vec;

    // goes through vec and adds new city
    // if a duplicate city appears, it adds to the first data point, and stores distance
    // since its a map it doesn't keep duplicates
    for (auto& i : vec) {
        city_map[i.city].first++;
        city_map[i.city].second = i.distance;
    }

    // goes through city_map
    for (auto& [city, data] : city_map) {

        // creates a new UFO object and gets the city, city_count, and distance from city_map
        UFO::Row new_ufo;

        new_ufo.city = city;
        new_ufo.city_count = data.first;
        new_ufo.distance = data.second;
        return_vec.push_back(new_ufo);
    }

    return return_vec;

}

// returns a vector with every single sighting
vector<UFO::Row> UFO::grid_map_to_vec() {
    vector<UFO::Row> return_vec;

    // Iterates over each grid in the map, and then each Row object gets appended to return_vec
    for (auto& i : grid_map) {
        for (auto& j: i.second) {
            return_vec.push_back(j);
        }
    }

    return return_vec;

}

// https://www.geeksforgeeks.org/merge-sort/ and lecture slides
// merges vec[left to mid] and vec[mid+1 to right] and sorts them at the same time
void UFO::merge(vector<UFO::Row>& vec, int left, int mid, int right, const string& data_type) {

    // n1 is the space for right array
    // n2 is the space for left array
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<UFO::Row> l_vec(n1), r_vec(n2);

    // copies left/right half of vec into l_vec and r_vec, using n1 and n2
    for (int i = 0; i < n1; i++) {
        l_vec[i] = vec[left + i];
    }
    for (int j = 0; j < n2; j++) {
        r_vec[j] = vec[mid + 1 + j];
    }

    int i, j, k;
    i = 0;
    j = 0;
    k = left;

    // actual sorting/merge part; different attribute of Row class is sorted depending on data_type (sorting logic is same for all though)
    // sees if l_vec[i].attribute than r_vec's, add it to vec and increment l_vec's index (i), if it isn't, add r_vec to vec and increment r_vec's index (j)
    // basically keep on incrementing left or right's index if its smaller, then add respective smaller data to vec and repeat until i or j reaches end of vec
    while (i < n1 && j < n2) {

        // sorts on distance attribute
        if (data_type == "distance") {
            if (l_vec[i].distance <= r_vec[j].distance) {
                vec[k] = l_vec[i];
                i++;
            }
            else {
                vec[k] = r_vec[j];
                j++;
            }
            k++;
        }

        // sorts on city_count attribute; descend
        else if (data_type == "city_count") {
            if (l_vec[i].city_count >= r_vec[j].city_count) {
                vec[k] = l_vec[i];
                i++;
            }
            else {
                vec[k] = r_vec[j];
                j++;
            }
            k++;

        }

        // sorts on duration attribute; descend
        else if (data_type == "duration") {
            if (l_vec[i].duration >= r_vec[j].duration) {
                vec[k] = l_vec[i];
                i++;
            }
            else {
                vec[k] = r_vec[j];
                j++;
            }
            k++;

        }
    }

    // if one vector finished before the other, copy remaining elements
    while (i < n1) {
        vec[k] = l_vec[i];
        i++;
        k++;
    }
    while (j < n2) {
        vec[k] = r_vec[j];
        j++;
        k++;
    }

}

// https://www.geeksforgeeks.org/merge-sort/ and lecture slides
// recursively calls merge
void UFO::mergeSort(vector<UFO::Row>& vec,int left, int right, const string& data_type) {

    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid, data_type);
        mergeSort(vec, mid + 1, right, data_type);

        // merge sorted subarrays
        merge(vec, left, mid, right, data_type);
    }

}


// quick sort - inspiration from Sorting notes
void UFO::quickSort(vector<UFO::Row> &vec, int low, int high, string datatype) {
    if (low < high) {
        int piv = partition(vec, low, high, datatype); // look at vec type!
        quickSort(vec, low, piv - 1, datatype);
        quickSort(vec, piv + 1, high, datatype);
    }
}

// partition func for quick sort - inspiration from Sorting notes
int UFO::partition(vector<UFO::Row> &vec, int low, int high, string datatype) { // vec of UFO::Row?

    auto piv = vec[low];
    int up = low;
    int down = high;

    while (up < down) {

        if (datatype == "distance") {
            // iterates up until it reaches value greater than piv
            for (int j = up; j < high; j++) {
                if (vec[up].distance > piv.distance) {
                    break;
                }
                up++;
            }
            // iterates down until it reaches a val less than piv (starts at end of vec and works backwards)
            for (int j = high; j > low; j--) {
                if (vec[down].distance < piv.distance) {
                    break;
                }
                down--;
            }
            // swap up and down if nec
            if (up < down) {
                swap(vec[up], vec[down]);
            }

        }
        else if (datatype == "city_count") {
            // iterates up until it reaches value greater than piv
            for (int j = up; j < high; j++) {
                if (vec[up].city_count < piv.city_count) {
                    break;
                }
                up++;
            }
            // iterates down until it reaches a val less than piv (starts at end of vec and works backwards)
            for (int j = high; j > low; j--) {
                if (vec[down].city_count > piv.city_count) {
                    break;
                }
                down--;
            }
            // swap up and down if nec
            if (up < down) {
                swap(vec[up], vec[down]);
            }
        }
        else if (datatype == "duration") {
            // iterates up until it reaches value greater than piv
            for (int j = up; j < high; j++) {
                if (vec[up].duration < piv.duration) {
                    break;
                }
                up++;
            }
            // iterates down until it reaches a val less than piv (starts at end of vec and works backwards)
            for (int j = high; j > low; j--) {
                if (vec[down].duration > piv.duration) {
                    break;
                }
                down--;
            }
            // swap up and down if nec
            if (up < down) {
                swap(vec[up], vec[down]);
            }
        }
    }
    swap(vec[low], vec[down]);
    return down;
}


// temporary remove after implementing real sort
vector<UFO::Row> UFO::tempSort(vector<UFO::Row> vec, string datatype) {

    if (datatype == "distance") {
        sort(vec.begin(), vec.end(), [](const Row& a, const Row& b) {
            return a.distance < b.distance;
        });
    }
    else if (datatype == "city_count") {
        sort(vec.begin(), vec.end(), [](const Row& a, const Row& b) {
            return a.city_count < b.city_count;
        });
    }

    else if (datatype == "city_count_descend") {
        sort(vec.begin(), vec.end(), [](const Row& a, const Row& b) {
            return a.city_count > b.city_count;
        });
    }
    else if (datatype == "duration") {
        sort(vec.begin(), vec.end(), [](const Row& a, const Row& b) {
            return a.duration > b.duration;
        });
    }

    return vec;
}





