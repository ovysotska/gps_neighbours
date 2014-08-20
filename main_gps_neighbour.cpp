#include "gps_neighbour.h"

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#define RANGE 0.2

using namespace std;

//TODO: pass paramerters from script as [argv, argc]
// const string DATA_DIR_W = "/home/olga/projects/sceneMatching_local/freiburgcar-seasons/log_12_12_2012_____12_56_59/";
// const string DATA_DIR_S = "/home/olga/projects/sceneMatching_local/freiburgcar-seasons/log_24_5_2012_____11_11_47/";
const string DATA_DIR = "../results/";


int main()
{
    cout << "\t Searching for the nearest images based on GPS" << endl;
    GPSNeighbour data_w, data_s;
    data_w.init_db(DATA_DIR + "img_gps_winter.txt");
    data_s.init_db(DATA_DIR + "img_gps_summer.txt");

    vector<double> lat_s, lon_s;
    data_s.get_img_coord(lat_s, lon_s);
    std::vector<std::string> img_in_range;
    data_w.find_neighbours( lat_s, lon_s, img_in_range, RANGE);
    print_neighbours(img_in_range, DATA_DIR + "winter_in_range.txt");


    cout << "\t Done." << endl;
}
