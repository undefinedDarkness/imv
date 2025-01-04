#include "trunk.hpp"
#include <cstring>
#include <dirent.h>
#include <filesystem>

std::vector<std::string> walk(const std::string& dir) {
    using namespace std;
    namespace fs = std::filesystem;

    cout << "READING DIRECTORY: " << dir << endl;

    vector<string> paths;

    try {
        for (const auto& entry : fs::directory_iterator(dir)) {
            if (entry.is_regular_file()) {
                auto ext = entry.path().extension().string();
                if (ext == ".png" || ext == ".jpg") {
                    paths.push_back(entry.path().string());
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        cerr << "Filesystem error: " << e.what() << endl;
    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

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

std::string extname(std::string &filename) {
  int l = filename.find_last_of('.');
  return filename.substr(l, filename.size() - l);
}

std::vector<std::string> cmdl(int argc, char** argv) {

  // Get full path to current working directorry
	std::string parent_dir;
	std::string filename;
	std::string path;

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

  auto images = walk(parent_dir);
  return images;
}
