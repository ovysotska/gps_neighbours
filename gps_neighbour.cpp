#include "gps_neighbour.h"
using namespace std;

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
        cout <<"Everything is read: times: " << gps_times_.size() << " lat " << gps_lat_.size() << " lon "<< gps_lon_.size()<< endl;
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
}
