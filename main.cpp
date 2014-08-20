#include "gps_neighbour.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define RANGE 1.0

using namespace std;

const string DATA_DIR_W = "/home/olga/projects/sceneMatching_local/freiburgcar-seasons/log_12_12_2012_____12_56_59/";
const string DATA_DIR_S = "/home/olga/projects/sceneMatching_local/freiburgcar-seasons/log_24_5_2012_____11_11_47/";
int main()
{
    cout << "\t Finding nearest images in database based on query image gps" << endl;

    Database winter_db, summer_db;
    winter_db.init(DATA_DIR_W + "pictures_names_Cam0_sort", DATA_DIR_W + "pictures_timestamp", DATA_DIR_W + "winter_gps.txt");
    summer_db.init(DATA_DIR_S + "pictures_names_Cam0_sort", DATA_DIR_S + "pictures_timestamp", DATA_DIR_S + "summer_gps.txt");


    vector<string> img_in_range;
    vector<double> sum_img_lon, sum_img_lat;
    summer_db.get_img_coord(sum_img_lat, sum_img_lon);
    winter_db.find_neigh(sum_img_lat, sum_img_lon, img_in_range, RANGE);


    cout << "\t Done." << endl;
}
