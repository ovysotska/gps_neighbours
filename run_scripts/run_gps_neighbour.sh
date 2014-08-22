DATA_DIR="/home/olga/projects/sceneMatching_local/gps_neighbours/results/"
RANGE=0.05
DB_file="img_gps_winter_small.txt"
QRY_file="img_gps_summer_small.txt"
OUT_file="rest_winter_in_"$RANGE"_range_from_small.txt"


./../bin/gps_neighbour ${RANGE} ${DATA_DIR}${DB_file} ${DATA_DIR}${QRY_file} ${DATA_DIR}${OUT_file}