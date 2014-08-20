#include "file_binder.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define RANGE 0.2

using namespace std;

//TODO: pass paramerters from script as [argv, argc]
const string DATA_DIR_W = "/home/olga/projects/sceneMatching_local/freiburgcar-seasons/log_12_12_2012_____12_56_59/";
const string DATA_DIR_S = "/home/olga/projects/sceneMatching_local/freiburgcar-seasons/log_24_5_2012_____11_11_47/";
const string neighbourFile = "../results/neigh_images.txt";


int main()
{
    cout << "\t Finding nearest images in database based on query image gps" << endl;

    FileBinder winter_db, summer_db;
    winter_db.init(DATA_DIR_W + "pictures_names_Cam0_sort", DATA_DIR_W + "pictures_timestamp", DATA_DIR_W + "winter_gps.txt");
    winter_db.relate_gps_to_img();
    winter_db.write_to_file("../results/img_gps.txt");

    // summer_db.init(DATA_DIR_S + "pictures_names_Cam0_sort", DATA_DIR_S + "pictures_timestamp", DATA_DIR_S + "summer_gps.txt");


    cout << "\t Done." << endl;
}
