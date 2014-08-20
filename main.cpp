#include "gps_neighbour.h"

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

void writeToFile(vector<string> &img_names, const string &file_name)
{
	ofstream out(file_name.c_str());
	if (out)
	{
		for(vector<string>::iterator iter = img_names.begin();  iter!= img_names.end(); ++iter)
		{
			out << *iter << endl;
		}
		cout << "Selected neighbouring image names were written to " << file_name << endl; 
	}
	else
	{
		cout << "Unable to open a file "<< file_name << endl;
		return;
	}
}


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

    writeToFile(img_in_range, neighbourFile);

    cout << "\t Done." << endl;
}
