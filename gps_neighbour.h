#ifndef GPS_NEIGHBOUR_H
#define GPS_NEIGHBOUR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

// constants that transform km to lat and lon
//TODO: make it math correct. This is a dirty estimate
#define KM2LAT 0.0090465
#define KM2LON 0.008983


class Database
{
public:
    void init(
        const std::string &img_name_file,
        const std::string &timestamp_file,
        const std::string &gps_file);
    void find_neigh(
        std::vector<double> lat,
        std::vector<double> lon,
        std::vector<std::string> &img_in_range,
        double range);
    void get_img_coord(std::vector<double> &img_lat,
        std::vector<double> &img_lon);

private:
	void read_images(const std::string &img_name_file);
	void read_timestamps(const std::string &timestamp_file);
	void read_gps(const std::string &gps_file);
    void find_img_in_km(
        double lat, 
        double lon, 
        double km, 
        std::vector<int> &img_idx);
    void relate_gps2img();

    std::vector<std::string> img_names_;
    std::vector<double> img_times_;
    std::vector<double> gps_lon_;
    std::vector<double> gps_lat_;
    std::vector<double> gps_times_;
    std::vector<double> img_lon_;
    std::vector<double> img_lat_;

};

#endif //GPS_NEIGHBOUR_H
