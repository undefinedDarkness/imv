// -- Import C++ Libraries --
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

// -- Import FLTK --
#include <FL/Fl_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <Fl/Fl_Pixmap.H>
#include <Fl/Fl_Tiled_Image.H>
#include <Fl/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Multi_Label.H>
#include <FL/Fl_Widget.H>
#include <Fl/Fl_Menu_Item.H>
#include <FL/fl_message.H>
#include <FL/Fl_Window.H>

const short WIN_W = 800;
const short WIN_H = 650;
const short WIN_BAR_SIZE = 50;

const short CUSTOM_RESIZE_EVENT = 44;

const char *extname(const char *filename);
std::string extname(string *filename);
vector<string> walk(string *dir);

void about_info(Fl_Widget *_, void *__);
void image_info(Fl_Widget *_, void *__);

class EventWindow: public Fl_Window {
        public:

                EventWindow(int width, int height, const char*label);
                int handle(int e) override;
                void resize(int X, int Y, int W, int H) override;

};

class ImageBox : public Fl_Box {
    private:
        Fl_Box *view;
    public:
        ImageBox(int x, int y, int w, int h, const char*label);
        int load_image(std::string path);
        Fl_Image *get_image();
};