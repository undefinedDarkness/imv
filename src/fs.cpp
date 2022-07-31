#include "trunk.hpp"
#include <cstring>
#include <dirent.h>

vector<char*> walk(const char* dir) {
  cout << "READING DIRECTORY: " << dir << endl;
  DIR *d = opendir(dir);
  dirent *entry;
  vector<char*> paths;
  int path_size = strlen(dir) + 1 + 50 + 1;
  while ((entry = readdir(d))) {
    if (entry->d_type == DT_REG) {
      if (strcmp(extname(entry->d_name), ".png") == 0 ||
          strcmp(extname(entry->d_name), ".jpg") == 0) {
          char *path = (char*)malloc(path_size);
          strcpy(path, dir);
          strcat(path, "/");
          strcat(path, entry->d_name);
          paths.push_back(path);
      }
    }
  }

  closedir(d);
  return paths;
}

// Get the extension of a file name, e.g. ".png". using char*
char *extname(char *filename) {
  char *ext = strrchr(filename, '.');
  if (ext == NULL) {
    return (char*)"";
  }
  return ext;
}

std::string extname(string &filename) {
  int l = filename.find_last_of('.');
  return filename.substr(l, filename.size() - l);
}

vector<char*> cmdl(int argc, char** argv) {

  // Get full path to current working directorry
  string parent_dir;
  string filename;
  string path;

  if (argc == 1) {
    char cwd[1024];
    getcwd(cwd, 1024);
    parent_dir = cwd;
    parent_dir += "/";
  } else {
    char *t = (char*)malloc(300);
    realpath(argv[1], t);
    path = t;
    free(t);
    filename = basename(path.c_str());
    parent_dir = path;
    parent_dir.resize(parent_dir.length() - filename.length());
  }

  vector<char*> images = walk(parent_dir.c_str());
  return images;
}