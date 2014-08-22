program 'gps_neighbour'

The program is composed from two independent parts.

First part. File Binder

The program is used to bind the separate files information.
It assossiates the gps coordinates to each obtained image via corresponding timestamps.
To run the program one would need to specify the following files:
	"img_names_file" - names of the images
	"img_time_file" - timestamps of the images
	"gps_file" - gps coordinates and corresponding timestamps (in special format)
    "output_file" -  output filename
RETURN: text file with image names and corresponding latitude lontitude

Second part. GPS Neighbour

The programm searches in specified database the image, which are in range of query image(s).
INPUT:
	"RANGE"  - range (km) in which the images should be searched 
	"DB_file" - file with images and GPS coordinates
	"QRY_file" - file with images and GPS coordinates
	"OUT_file" - the name of the output file
RETURN: the text file with images and GPS coordinates, that are in RANGE.
