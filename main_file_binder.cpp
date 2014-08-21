#include "file_binder.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;


int main(int argc, char *argv[])
{
    if(argc < 5)
    {
        cerr << "\n USE: ./gps_file_binder img_names_file img_time_file gps_file output_file  folder_name\n" << endl;

        cout << "img_names_file: path to the file with image names" << endl;
        cout << "img_time_file: path to the file with image timestamps" << endl;
        cout << "gps_file: the file with the gps coordinates in a special format. See README for details." << endl;
        cout << "output_file: the name of the output file" << endl;
        cout << "folder_name(opt): the name of the folder, to use a smaller dataset" << endl;
        return 0;

    }
    cout << "\t -------------------------------------" << endl;
    cout << "\t Binding the GPS information to images" << endl;
    cout << "\t -------------------------------------" << endl;
    const string NAMES_FILE = argv[1];
    const string TIMES_FILE = argv[2];
    const string GPS_FILE = argv[3];
    const string OUT_FILE  = argv[4];

    cout << "You have entered: " << endl;
    cout << "\t img_names_file: " << NAMES_FILE << endl;
    cout << "\t img_time_file: " << TIMES_FILE << endl;
    cout << "\t gps_file: " << GPS_FILE << endl;
    cout << "\t output_file: " << OUT_FILE << endl << endl;


    FileBinder file_binder;
    file_binder.init(NAMES_FILE, TIMES_FILE, GPS_FILE);
    file_binder.relate_gps_to_img();


    if(argc == 6)
    {
    	const string FOLDER_NAME = argv[5];
    	cout << "\nBinding with a folder..." << endl;
    	cout << "\t folder_name: " << FOLDER_NAME << endl;
    	file_binder.bind_from_folder(FOLDER_NAME, OUT_FILE);
    }
    else
    {
    	file_binder.write_to_file(OUT_FILE);
    }

    cout << "\n\t DONE." << endl;
}
