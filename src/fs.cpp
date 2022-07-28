#include "trunk.hpp"
#include <dirent.h>

vector<string> walk(string *dir) {
  DIR *d = opendir(dir->c_str());
  dirent *entry;
  vector<string> paths;

  while ((entry = readdir(d))) {
    if (entry->d_type == DT_REG) {
      if (strcmp(extname(entry->d_name), ".png") == 0 ||
          strcmp(extname(entry->d_name), ".jpg") == 0) {
        paths.push_back(string(entry->d_name));
      }
    }
  }

  closedir(d);
  return paths;
}