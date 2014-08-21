#ifndef FILE_BINDER_H
#define FILE_BINDER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>

class FileBinder
{
public:
    void init(
        const std::string &img_name_file,
        const std::string &timestamp_file,
        const std::string &gps_file);

    void relate_gps_to_img();
    void write_to_file(const std::string &file_name);
    void bind_from_folder(
        const std::string &folder_path, 
        const std::string &out_bind_file);

private:
	void read_images(const std::string &img_name_file);
	void read_timestamps(const std::string &timestamp_file);
	void read_gps(const std::string &gps_file);


    std::vector<std::string> img_names_;
    std::vector<double> img_times_;
    std::vector<double> gps_lon_;
    std::vector<double> gps_lat_;
    std::vector<double> gps_times_;
    std::vector<double> img_lon_;
    std::vector<double> img_lat_;

};

#endif //FILE_BINDER_H