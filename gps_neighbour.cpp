#include "gps_neighbour.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


void deleteDuplicates(vector<int> &v)
{
    std::sort(v.begin(), v.end()); 
    std::vector<int>::iterator it;
    it = std::unique (v.begin(), v.end());   
    v.resize( std::distance(v.begin(),it) ); 
}

// initialize an instance of the class with image names of the database
// to further search for the neighbouring images in it.
void GPSNeighbour::init_db(std::vector<std::string> &img_names,
                std::vector<double> &img_lon, 
                std::vector<double> &img_lat)
{
    img_names_ = img_names;
    img_lon_ = img_lon;
    img_lat_ = img_lat;
}

void GPSNeighbour::init_db(const string &filename)
{
    ifstream in(filename.c_str());
    if(!in)
    {
        cout << "File: " << filename << " was NOT found" << endl;
        return;
    }
    cout << "Reading file "<< filename << endl;
    while(!in.eof())
    {
        string name;
        double lat, lon;
        in >> name >> lat >> lon;
        if(name != "")
        {
            img_names_.push_back(name);
            img_lat_.push_back(lat);
            img_lon_.push_back(lon);
        }

    }
    cout << "Image names and gps were read."<<endl;
    cout << img_names_.size() << "\t" << img_lat_.size() << "\t" << img_lon_.size() << endl;

    in.close();
}



void GPSNeighbour::find_img_in_km(double lat, double lon,  double range,  vector<int> &img_idx)
{
    double lat_start,lon_start, lat_finish, lon_finish;
    lat_start = lat - range * KM2LAT;
    lat_finish = lat + range * KM2LAT;
    lon_start = lon - range * KM2LON;
    lon_finish = lon + range * KM2LON;
    // cout << lat_start << " < " << lat << " < " << lat_finish << endl;
    // cout << lon_start << " < " << lon << " < " << lon_finish << endl;

    if (img_lat_.size() != img_lon_.size())
    {
        cout << "Wrong GPS data. "<<endl;
        return;
    }
    if (img_lat_.size() != img_names_.size())
    {
        cout << "Wrong GPS data image names assosiations "<<endl;
        return;
    }
    for(int i=0; i < img_lat_.size(); i++)
    {
        // if both measurements are in square of 'km' kilometers
        if ( (lat_start <= img_lat_[i] &&  img_lat_[i] <= lat_finish) &&
            (lon_start <= img_lon_[i] && img_lon_[i] <= lon_finish) )
        {
            // img_in_range.push_back(img_names_[i]);
            img_idx.push_back(i);
            if(i > 92)
            {
                cerr << "Out of range" << endl;
            }
        }
    }
    cout<< " "<< img_idx.size() << " images were chosen out of " << img_names_.size() << endl;
}


// returns the indices of the images from the database that were chosen as neighbours
//TODO: rewrite this, to store for each query its own neighbours
void GPSNeighbour::find_neighbours( std::vector<double> &lat,
                            std::vector<double> &lon,
                            std::vector<vector<int> > &qu_neighs,
                            double range)
{
    if(lat.size() != lon.size())
    {
        cout << "The GPS data is not consistent"<<endl;
        return;
    }
    vector<int> qu_neigh_idx;
    //for each query coordinate
    for( int i = 0; i < lat.size(); i++)
    {
        cout << "For Query image: " << i << "\t";
        // finds neighbours for each query image
        find_img_in_km(lat[i], lon[i], range, qu_neigh_idx);
        qu_neighs.push_back(qu_neigh_idx);
        // img_idx.insert(img_idx.end(), idx.begin(), idx.end());      //appending one vector to another
        // deleteDuplicates(img_idx);
        qu_neigh_idx.clear();
    }
}

//prints the names and coordinates of the image (lat, lon)
void GPSNeighbour::print_neighbours_full(std::vector<vector<int> > &qu_neighs, const string &filename)
{
    ofstream out(filename.c_str());
    if(!out)
    {
        cout << "File " << filename << " has NOT been opened. No neighbours are stored"<<endl;
        return;
    }
     // for each query
    for( int i = 0; i < qu_neighs.size(); ++i)
    {
        // for each neighbour of query i
        for(int j=0; j < qu_neighs[i].size(); ++j)
        {
            out << i << "\t" << img_names_[qu_neighs[i][j]] 
                     << "\t" << img_lat_[qu_neighs[i][j]] 
                     << "\t" << img_lon_[qu_neighs[i][j]] << endl;
        }
    }
    out.close();
    cout << "Full version of neighbouring images is written to " << filename << endl;
}

void GPSNeighbour::write_query_neighbours(vector<vector<int> > &qu_neighs, const string &filename)
{
    ofstream out(filename.c_str());
    if(!out)
    {
        cout << "File " << filename << " has NOT been opened. No neighbours are stored"<<endl;
        return;
    }
    // for each query
    for( int i = 0; i < qu_neighs.size(); ++i)
    {
        out << i << "\t" << qu_neighs[i].size() << "\t";
        // for each neighbour of query i
        for(int j=0; j < qu_neighs[i].size(); ++j)
        {
            out << qu_neighs[i][j] << "\t";
        }
        out << endl;
    }
    out.close();
    cout << "Short version of neighbours is written to: "<< filename << endl;
}


void GPSNeighbour::get_img_coord(vector<double> &img_lat, vector<double> &img_lon)
{
    img_lat = img_lat_;
    img_lon = img_lon_;
}
