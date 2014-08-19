#ifndef GPS_NEIGHBOUR_H
#define GPS_NEIGHBOUR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>


class Database
{
public:
    std::vector<std::string> img_names_;
    std::vector<double> img_times_;
    std::vector<double> gps_lon_;
    std::vector<double> gps_lat_;
    std::vector<double> gps_times_;

    void init(
        const std::string &img_name_file,
        const std::string &timestamp_file,
        const std::string &gps_file);

private:
	void read_images(const std::string &img_name_file);
	void read_timestamps(const std::string &timestamp_file);
	void read_gps(const std::string &gps_file);

};

#endif //GPS_NEIGHBOUR_H
