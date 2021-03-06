#include "file_binder.h"
#include "list_dir.h"

#include <iomanip>          // for cout precision
#include <ctime>
using namespace std;



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

void img_cut_path(string &img_name)
{
    unsigned pos = img_name.find_last_of("/");
    img_name = img_name.substr(pos+1);
}


void FileBinder::read_images(const string &img_name_file)
{
    string img_name;
    ifstream in(img_name_file.c_str());
    if (in.is_open())
    {
        while ( !in.eof() )
        {
            in >> img_name;
            img_cut_path(img_name);
            img_names_.push_back(img_name);
        }
        in.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}

void FileBinder::read_timestamps(const string &timestamp_file)
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



// function read a file , where each line has such a format:
//     time=1355314012.609550,utctime=[3x1]{11,4,38},lat=48.007660,lon=7.828823,qual=1,sats=10,hdop=0.8
void FileBinder::read_gps(const string &gps_file)
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
        in.close();
    }
}

void FileBinder::init(
        const std::string &img_name_file,
        const std::string &timestamp_file,
        const std::string &gps_file)
{
    read_images(img_name_file);
    read_timestamps(timestamp_file);
    read_gps(gps_file);
    cout << "Init DONE. \t images: "<< img_names_.size() << "\t GPS coord: "<< gps_lon_.size() << endl;
}

void FileBinder::relate_gps_to_img()
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
    cout << "GPS coordinates were related to the images" << endl;
}


void FileBinder::write_to_file(const string &file_name)
{
    ofstream out(file_name.c_str());
    if(out)
    {
        if(img_lon_.size() != img_lat_.size())
        {
            cout << "Wrong GPS data assosiations lat != lon" << endl;
            return;
        }
        for(int i = 0; i < img_lon_.size(); i++)
        {
            out << img_names_[i] << "\t" << img_lat_[i] << "\t" << img_lon_[i] << endl;
        }
        cout << "Image GPS coordinates were written to: " << file_name << endl; 
        out.close();
    }
    else
    {
        cout << "Unable to open a file "<< file_name << endl;
        return;
    }
}

void FileBinder::bind_from_folder(const string &folder_path, const string &out_bind_file)
{
    vector<string> img_in_folder;
    listDir(folder_path, img_in_folder);
    ofstream out(out_bind_file.c_str());
    if(!out)
    {
        cout << "Couldn't open a file: "<< out_bind_file << endl;
        return;
    }
    for(int i=0; i < img_in_folder.size(); i++)
    {
        for(int j=0; j < img_names_.size(); j++)
        {
            if(img_in_folder[i] == img_names_[j])
            {
                out << img_names_[j] << "\t" << img_lat_[j] << "\t" << img_lon_[j] << endl;
                j=i+1;
                break;
            }
        }
    }
    cout << "Images and GPS coordinates were written to: " << out_bind_file << endl;
    out.close();
}