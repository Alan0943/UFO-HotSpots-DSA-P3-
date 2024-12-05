# H1 COP3530 Project 3: UFO Sightings Data Analysis Program
### H3 by Alan Skrypek, Caden Koster, Sean Ng

## H2 Overview
This program analyzes UFO sightings data and provides various functionalities such as viewing sightings within a radius, sorting sightings by different attributes, and inserting new sightings into the dataset. This program uses an unordered map (built in) for the datastructure, and compares merge and quick sort (built from scratch). Uses data set ufo_sightings.csv from [link](https://corgis-edu.github.io/corgis/csv/ufo_sightings/)

## H2 Instructions for Running Code
1. Clone the repository or download the zip file.
2. Open the program and make sure to not make a new configuration (config should say UFO_HotSpots_DSA_P3__test or something similar)
3. Run the program (if "Error opening file" go to UFO_Data.cpp and put absolute path to ufo_sightings.csv)

## H2 Menu Interface
Once the program is ran, a menu interface with a text box labled input will appear with these options:

1. View all sightings within a radius (max 500 miles) (input coordinates)
2. View unique cities with most sightings within a radius (input coordinates)
3. View top 50 cities sorted by sightings (descending order)
4. View top 50 sightings sorted by duration (descending order)
5. Insert new sighting.

Select a option and if it says input, input the necessary data to the data input box
After input, press the enter key and the output will display

## H2 Features
1. View all sightings within a radius
   -Input a set of coordinates (latitude 20 - 50, longtiude -130 - -60) and a radius (max 500 miles)
   -Displays all UFO sightings within the specified radius, sorted by distance
2.  View unique cities with most sightings within a radius
   - Input a set of coordinates and a radius (max 500 miles)
   - Displays a list of unique cities, sorted by the number of sightings attributed to each city, along with their distance from the input coordinates
3. View top 50 cities sorted by sightings
   - Displays the top 50 cities with the highest number of sightings in the dataset
   - Sorted in descending order by the number of sightings
4. View top 50 sightings sorted by duration
   - Displays the top 50 cities with the highest duration in the dataset
   - Sorted in descending order by the number of sightings
