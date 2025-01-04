#ifndef TRUNK_H
#define TRUNK_H
// -- Import C++ Libraries --
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <memory>

#include <unistd.h>


// -- Import FLTK --
#include <FL/Fl_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <Fl/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <Fl/Fl_Menu_Item.H>
#include <FL/Fl_Window.H>

// typedef unsigned char byte;
typedef Fl_Box Widget;
char *extname(char *filename);
std::string extname(std::string &filename);
std::vector<char*> walk(const char* dir);

void about_info(Fl_Widget *_, void *__);
void image_info(Fl_Widget *_, void *__);
Fl_Image *dither(Fl_Image *target);

std::vector<std::string> cmdl(int argc, char** argv);

class ImageBox : public Fl_Box {
    private:
        Fl_Box *view;
    public:
        ImageBox(int x, int y, int w, int h, const char*label);
        Fl_Image *get_image();
        int load_image(char*path);
        int adapt(Fl_Image *image);
        static int adapt(Fl_Image *image, Fl_Widget* self, Fl_Widget *view);
};

class ImageBox;
#endif
