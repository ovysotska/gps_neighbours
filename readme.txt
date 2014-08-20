program 'gps_neighbour'

This programs reads the log files and assosiate with each image the GPS coordinates, where it potentially could have been done.
For running a program one would need:

Files
 - DATA_DIR_W - directory, where the first database of images and coordinates are stored (here winter dataset)
 - DATA_DIR_S - directory, where the second database of images and coordinates are stored (here summer dataset)

<< winter_db.init(DATA_DIR_W + "pictures_names_Cam0_sort", DATA_DIR_W + "pictures_timestamp", DATA_DIR_W + "winter_gps.txt"); >>

	"pictures_names_Cam0_sort" -  name of the file, where the names of the images are stored
	"pictures_timestamp"       -  name of the file, where the timestamps of the images are stored.
	"winter_gps.txt"           -  name of the file, where the GPS info in format:	
				"time=1355314012.609550,utctime=[3x1]{11,4,38},lat=48.007660,lon=7.828823,qual=1,sats=10,hdop=0.8" is stored.

What it does?

1) Read the files.
2) Relate the gps coordinates to images via timestamp
3) For a second database of images searches for the images in first database, which are located in range of RANGE.
