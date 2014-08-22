#ifndef GPS_NEIGHBOUR_H
#define GPS_NEIGHBOUR_H

#include <vector>
#include <string>


// constants that transform km to lat and lon
//TODO: make it math correct. This is a dirty estimate
#define KM2LAT 0.0090465
#define KM2LON 0.008983


class GPSNeighbour
{
public:
    void init_db(std::vector<std::string> &img_names,
                std::vector<double> &img_lon, 
                std::vector<double> &img_lat);
    void init_db(const std::string &filename);
    void find_neighbours(
        std::vector<double> &lat,
        std::vector<double> &lon,
        std::vector<std::vector<int> > &qu_neighs,
        double range);
    void get_img_coord(std::vector<double> &img_lat,
        std::vector<double> &img_lon);
    void print_neighbours_full(std::vector< std::vector<int> > &qu_neighs, const std::string &filename);
    void write_query_neighbours(
        std::vector<std::vector<int> > &qu_neighs,
        const std::string &filename);

private:
    void find_img_in_km(
        double lat, 
        double lon, 
        double km, 
        std::vector<int> &img_idx);

    std::vector<std::string> img_names_;
    std::vector<double> img_lon_;
    std::vector<double> img_lat_;
};


void print_neighbours(std::vector<std::string> &img_in_range, const std::string &filename);
#endif //GPS_NEIGHBOUR_H
