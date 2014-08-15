#include "gps_neighbour.h"
using namespace std;

void Database::read_images(string img_name_file)
{
    string img_name;
    ifstream in(img_name_file.c_str());
    if (in.is_open())
    {
        while ( !in.eof() )
        {
            in >> img_name;
            img_names_.push_back(img_name);
        }
        in.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}

void Database::read_timestamps(string timestamp_file)
{ 
    double timestamp;
    ifstream in(timestamp_file.c_str());
    if(!in)
    {
        cout<<"Unable to open a file \n" << timestamp_file << endl;
    } 
    else
    {
        while ( !in.eof() )
        {
            in >> timestamp;
            timestamps_.push_back(timestamp);
        }
        in.close();
    }
}


void Database::read_gps(string gps_file)
{
    

}

void Database::init(string img_name_file, string timestamp_file, string gps_file)
{
    read_images(img_name_file);
    read_timestamps(timestamp_file);
    read_gps(string gps_file);

    cout<< "Number of images: "<< img_names_.size() << " timestamps size " << timestamps_.size() << endl;
}
