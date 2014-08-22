#include "gps_neighbour.h"

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <stdlib.h>     /* atof */


using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 5)
    {
        cerr << "./gps_neighbour RANGE DB_file QRY_file OUT_file" << endl;

        cout << "RANGE: range for neighbour search, km" << endl;
        cout << "DB_file: text file with binded images and gps for DATABASE" << endl;
        cout << "QRY_file: text file with binded images and gps for QRY" << endl;
        cout << "OUT_file: the name of the file, where the found neighbours are stored" << endl;
        return 0;

    }
    cout << "\t ---------------------------------------------" << endl;
    cout << "\t Searching for the nearest images based on GPS" << endl;
    cout << "\t ---------------------------------------------" << endl;
    const double RANGE = atof(argv[1]);
    const string DB_file = argv[2];
    const string QRY_file = argv[3];
    const string OUT_file = argv[4];

    cout << "You have specified:" << endl;
    cout << "RANGE: " << RANGE << endl;
    cout << "DB_file: " << DB_file << endl;
    cout << "QRY_file: " << QRY_file << endl;
    cout << "OUT_file: " << OUT_file << endl;



    GPSNeighbour data_w, data_s;
    data_w.init_db(DB_file);
    data_s.init_db(QRY_file);

    vector<double> lat_s, lon_s;
    data_s.get_img_coord(lat_s, lon_s);
    std::vector< std::vector<int> > idx_in_range;
    data_w.find_neighbours( lat_s, lon_s, idx_in_range, RANGE);
    // data_w.print_neighbours_full(idx_in_range, OUT_file);
    data_w.write_query_neighbours(idx_in_range, OUT_file);

    cout << "\t DONE." << endl;
    return 0;
}
