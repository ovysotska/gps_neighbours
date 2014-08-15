#include "gps_neighbour.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>



using namespace std;

const string data_dir = "/home/olga/projects/sceneMatching/freiburgcar-seasons/log_12_12_2012_____12_56_59/";
int main()
{
    cout << "Finding nearest images in database based on query image gps" << endl;

    Database winter_db;
    winter_db.init(data_dir + "pictures_names_Cam0_sort", data_dir + "pictures_timestamp", " ");
    cout << "Done." << endl;
}