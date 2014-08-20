#include "gps_neighbour.h"

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <stdlib.h>     /* atof */

// #define RANGE 1.0

using namespace std;

// const string DATA_DIR = "../results/";


int main(int argc, char *argv[])
{
    if(argc < 3 || argc > 3)
    {
        cerr << "./gps_neighbour RANGE NEIGH_OUT_FILENAME" << endl;

        cout << "RANGE: range for neighbour search, km" << endl;
        cout << "NEIGH_OUT_FILENAME: the filename, where the neigbouring image names will be stored" << endl;
        return 0;

    }
    cout << "\t Searching for the nearest images based on GPS" << endl;
    const double RANGE = atof(argv[1]);
    const string DATA_DIR = argv[2];

    cout << "You have specified:" << endl;
    cout << "NEIGH_OUT_FILENAME: " << DATA_DIR << endl;
    cout << "RANGE: " << RANGE << endl;



    GPSNeighbour data_w, data_s;
    data_w.init_db(DATA_DIR + "img_gps_winter.txt");
    data_s.init_db(DATA_DIR + "img_gps_summer.txt");

    vector<double> lat_s, lon_s;
    data_s.get_img_coord(lat_s, lon_s);
    std::vector<std::string> img_in_range;
    data_w.find_neighbours( lat_s, lon_s, img_in_range, RANGE);
    print_neighbours(img_in_range, DATA_DIR + "winter_in_range.txt");


    cout << "\t Done." << endl;
    return 0;
}
