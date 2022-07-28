#include "trunk.hpp"
#include <FL/Enumerations.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_ask.H>

void about_info(Fl_Widget *_, void *__) {
    fl_message_title("About");
    fl_message("imv:\n"
               "A simple image viewer written in C++ w/ FLTK.\n");
}

const char *extname(const char *filename) {
  const char *slash = strrchr(filename, '/');
  const char *loc = strrchr(slash ? slash : filename, '.');
  return loc ? loc : "";
}

std::string extname(string *filename) {
  int l = filename->find_last_of('.');
  return filename->substr(l, filename->size() - l);
}