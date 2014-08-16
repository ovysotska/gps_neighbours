#include "gps_neighbour.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>



using namespace std;

const string DATA_RID_W = "/home/olga/projects/sceneMatching/freiburgcar-seasons/log_12_12_2012_____12_56_59/";
const string DATA_DIR_S = "/home/olga/projects/sceneMatching/freiburgcar-seasons/log_24_5_2012_____11_11_47/";
int main()
{
    cout << "Finding nearest images in database based on query image gps" << endl;

    Database winter_db, summer_db;
    winter_db.init(DATA_RID_W + "pictures_names_Cam0_sort", DATA_RID_W + "pictures_timestamp", DATA_RID_W + "winter_gps.txt");
    summer_db.init(DATA_DIR_S + "pictures_names_Cam0_sort", DATA_DIR_S + "pictures_timestamp", DATA_DIR_S + "summer_gps.txt");
    cout << "Done." << endl;
}
