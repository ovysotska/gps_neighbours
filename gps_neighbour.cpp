#include "gps_neighbour.h"
#include <iomanip>          // for cout precision
using namespace std;

//TODO: check the neigbouring based on distance

void Database::read_images(const string &img_name_file)
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

void Database::read_timestamps(const string &timestamp_file)
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
            img_times_.push_back(timestamp);
        }
        in.close();
    }
}
double string_to_double(string s)
{
    double value;
    stringstream is(s);
    if (!(is >> value))
    {
        cout << "ERROR: trying to read not double in \"get_value_from_string\" function"<<endl;
    }
    return value;
}


// function read a file , where each line has such a format:
//     time=1355314012.609550,utctime=[3x1]{11,4,38},lat=48.007660,lon=7.828823,qual=1,sats=10,hdop=0.8
void Database::read_gps(const string &gps_file)
{
    string line;
    ifstream in(gps_file.c_str());
    if(!in)
    {
        cout<<"Unable to open a file \n\"" << gps_file << "\"" << endl;
    }
    else
    {
        // read the file
        while( !in.eof() )
        {
            string line;
            in >> line;
            typedef boost::tokenizer<boost::char_separator<char> >  Tokenizer;
            boost::char_separator<char> sep(",");
            Tokenizer tokens(line, sep);
            BOOST_FOREACH (const string& t, tokens)
            {
                boost::char_separator<char> s("=");
                Tokenizer tok(t, s);
                for (Tokenizer::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter)
                {
                    if (*tok_iter == "time")
                    {
                        string v = *(++tok_iter);
                        gps_times_.push_back(string_to_double(v));
                    }
                    else if (*tok_iter == "lat")
                    {
                        gps_lat_.push_back(string_to_double( *(++tok_iter)));
                    }
                    else if (*tok_iter == "lon")
                    {
                        gps_lon_.push_back(string_to_double( *(++tok_iter)));
                    }
                }

            }
        }
        cout <<"GPS data is read: times: " << gps_times_.size() << " lat " << gps_lat_.size() << " lon "<< gps_lon_.size()<< endl;
        in.close();
    }
}

void Database::init(
        const std::string &img_name_file,
        const std::string &timestamp_file,
        const std::string &gps_file)
{
    read_images(img_name_file);
    read_timestamps(timestamp_file);
    read_gps(gps_file);
    cout<< "Number of images: "<< img_names_.size() << " timestamps size " << img_times_.size() << endl;

    relate_gps2img();
    cout << "GPS coordinates were related to the images" << endl;
}

void Database::relate_gps2img()
{
    int gps_idx = 0;
    for(int i = 0; i < img_times_.size(); i++)
    {
        while( floor(img_times_[i]) > floor(gps_times_[gps_idx]))
        {
            gps_idx++;
        }
        img_lon_.push_back(gps_lon_[gps_idx]);
        img_lat_.push_back(gps_lat_[gps_idx]);
    }
    img_times_.clear();
    gps_lon_.clear();
    gps_lat_.clear();
    gps_times_.clear();
}

void Database::find_img_in_km(double lat, double lon,  double range,  vector<int> &img_idx)
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
        }
    }
    cout<< " "<< img_idx.size() << " images were chosen out of " << img_names_.size() << endl;
}

//TODO: maybe this can be done better. 
void deleteDuplicates(vector<int> &v)
{
    std::sort(v.begin(), v.end()); 
    std::vector<int>::iterator it;
    it = std::unique (v.begin(), v.end());   
    v.resize( std::distance(v.begin(),it) ); 
}

void Database::find_neigh( std::vector<double> lat,
                            std::vector<double> lon,
                            std::vector<std::string> &img_in_range,
                            double range)
{
    if(lat.size() != lon.size())
    {
        cout << "The GPS data is not consistent"<<endl;
        return;
    }
    vector<int> idx, img_idx;
    for( int i = 0; i < lat.size(); i++)
    {
        cout << "For Query image: " << i << endl;
        find_img_in_km(lat[i], lon[i], range, idx);
        img_idx.insert(img_idx.end(), idx.begin(), idx.end());      //appending one vector to another
        deleteDuplicates(img_idx);
        idx.clear();
    }

    cout<< "Total "<< img_idx.size() << " images were chosen out of " << img_names_.size() << endl;
    for(int i=0; i < img_idx.size(); i++)
    {
        img_in_range.push_back(img_names_[img_idx[i]]);
    }
}

void Database::get_img_coord(vector<double> &img_lat,
        vector<double> &img_lon)
{
    img_lon = img_lon_;
    img_lat = img_lat_;
}
