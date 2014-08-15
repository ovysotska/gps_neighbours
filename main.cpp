#include "gps_neighbour.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>



using namespace std;

const string data_dir_w = "/home/olga/projects/sceneMatching/freiburgcar-seasons/log_12_12_2012_____12_56_59/";
const string data_dir_s = "/home/olga/projects/sceneMatching/freiburgcar-seasons/log_24_5_2012_____11_11_47/";
int main()
{
    cout << "Finding nearest images in database based on query image gps" << endl;

    Database winter_db, summer_db;
    winter_db.init(data_dir_w + "pictures_names_Cam0_sort", data_dir_w + "pictures_timestamp", data_dir_w + "winter_gps.txt");
    summer_db.init(data_dir_s + "pictures_names_Cam0_sort", data_dir_s + "pictures_timestamp", data_dir_s + "summer_gps.txt");
    cout << "Done." << endl;
}