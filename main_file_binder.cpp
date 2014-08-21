#include "file_binder.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

//TODO: pass paramerters from script as [argv, argc]
const string DATA_DIR_W = "/home/olga/projects/sceneMatching_local/freiburgcar-seasons/log_12_12_2012_____12_56_59/";
const string DATA_DIR_S = "/home/olga/projects/sceneMatching_local/freiburgcar-seasons/log_24_5_2012_____11_11_47/";


int main(int argc, char *argv[])
{
    if(argc != 5)
    {
        cerr << "\n USE: ./gps_file_binder img_names_file img_time_file gps_file output_file \n" << endl;

        cout << "img_names_file: path to the file with image names" << endl;
        cout << "img_time_file: path to the file with image timestamps" << endl;
        cout << "gps_file: the file with the gps coordinates in a special format. See README for details." << endl;
        cout << "output_file: the name of the output file" << endl;
        return 0;

    }
    cout << "\t Binding the GPS information to images" << endl;
    const string NAMES_FILE = argv[1];
    const string TIMES_FILE = argv[2];
    const string GPS_FILE = argv[3];
    const string OUT_FILE  = argv[4];


    cout << "You have entered: " << endl;
    cout << "\t img_names_file: " << NAMES_FILE << endl;
    cout << "\t img_time_file: " << TIMES_FILE << endl;
    cout << "\t gps_file: " << GPS_FILE << endl;
    cout << "\t output_file: " << OUT_FILE << endl;

    // FileBinder winter_db, summer_db;
    // winter_db.init(DATA_DIR_W + "pictures_names_Cam0_sort", DATA_DIR_W + "pictures_timestamp", DATA_DIR_W + "winter_gps.txt");
    // winter_db.relate_gps_to_img();
    // winter_db.write_to_file("../results/img_gps_winter.txt");

    // summer_db.init(DATA_DIR_S + "pictures_names_Cam0_sort", DATA_DIR_S + "pictures_timestamp", DATA_DIR_S + "summer_gps.txt");
    // summer_db.relate_gps_to_img();
    // summer_db.write_to_file("../results/img_gps_summer.txt");


    cout << "\t Done." << endl;
}
