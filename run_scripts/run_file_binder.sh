# run file binder script
DATA_DIR = "/home/olga/projects/sceneMatching_local/freiburgcar-seasons/log_12_12_2012_____12_56_59/"
# DATA_DIR = "/home/olga/projects/sceneMatching_local/freiburgcar-seasons/log_24_5_2012_____11_11_47/";

img_names_file="pictures_names_Cam0_sort"
img_time_file="pictures_timestamp"
gps_file="winter_gps.txt"
output_file="../results/img_gps_winter_all.txt"
# output_file="../results/img_gps_summer_all.txt"


./../bin/gps_file_binder $DATA_DIR$img_names_file $DATA_DIR$img_time_file  $DATA_DIR$gps_file $DATA_DIR$output_file