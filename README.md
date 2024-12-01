UFO_Data.H
There are three classes within UFO_Data.h. PairHash (used for the hash table) and UFO (stores all row's data and houses functions).

UFO_Data.cpp
There is the constructor, insert, distanceCalc, sortHelper, merge/quick sort, and tempSort. The constructor pulls all the data from the csv into the hash table,
insert allows the addition of new data, distanceCalc calculates the distance between two points, sortHelper gets all the data from all adjacent grids that fit inside the radius,
and merge/quick sort sorts data but is not implemented, and tempSort works but will be removed.

main.cpp
At the top there is an example of adding new data and printing out the total keys/key data and an example of calculating the distance between two points (with lat and long).
The bottom houses the menu that currently has 6 choices, need to finish.

Summary of Program
Basically the UFO class is called, automatically calling the constructor which puts the data into the hash table, grid_map. The user is then asked to choose a menu option, the
only one implemented as of right now is menu 1, which asks for coordinates and a radius. The coordinates/radius is error checked then the input is passed into sortHelper, which
returns a vector of all sightings within that radius. This vector is then sorted and outputted to the user. Menu options 2-5 will be implemented in a similar fashion.

How to Access Program
When Download/Clone Repo DO NOT make a new configuration file / add to new cmake project. The configuration should be UFO_HotSpots_DSA_P3__test and if that doesn't work make 
make a new config file.
   
