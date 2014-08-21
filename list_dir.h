#ifndef LIST_DIR_H
#define LIST_DIR_H

#include <iostream>
#include <string>
#include <dirent.h>


void listDir(const std::string &dir_name, std::vector<std::string> &img_names)
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (dir_name.c_str())) != NULL) {
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
	    // printf ("%s\n", ent->d_name);
	    img_names.push_back(ent->d_name);
	  }
	  std::sort(img_names.begin(), img_names.end());
	  closedir (dir);
	} else {
	  /* could not open directory */
	  std::cerr << "Couldn't open a directory: " << dir_name << std::endl;
	  return;
	}
}



#endif //LIST_DIR_H