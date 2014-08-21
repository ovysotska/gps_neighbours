# run file binder script

# # winter dataset
# DATA_DIR="/home/olga/projects/sceneMatching_local/freiburgcar-seasons/log_12_12_2012_____12_56_59/"
# gps_file="winter_gps.txt"
# output_file="../results/img_gps_winter_small.txt"
# folder_name="/home/olga/projects/sceneMatching_local/freiburgcar-seasons/testData/database_winter"

# summer dataset
DATA_DIR="/home/olga/projects/sceneMatching_local/freiburgcar-seasons/log_24_5_2012_____11_11_47/"
gps_file="summer_gps.txt"
output_file="../results/img_gps_summer_all.txt"
folder_name="/home/olga/projects/sceneMatching_local/freiburgcar-seasons/testData/test_summer"


img_names_file="pictures_names_Cam0_sort"
img_time_file="pictures_timestamp"



# # bind the whole dataset
# ./../bin/gps_file_binder $DATA_DIR$img_names_file $DATA_DIR$img_time_file  $DATA_DIR$gps_file $output_file

# bind from the folder
./../bin/gps_file_binder $DATA_DIR$img_names_file $DATA_DIR$img_time_file  $DATA_DIR$gps_file $output_file $folder_name