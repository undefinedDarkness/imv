#include "trunk.hpp"
#include <iostream>

const short WIN_W = 800;
const short WIN_H = 650;
const short WIN_BAR_SIZE = 50;

void panic(const char *msg) {
  std::cout << msg;
  exit(0);
}

class App : public Fl_Window {
private:
  vector<char*> images;
  ImageBox *picture_box;
  Widget *info_box;
  // Widget *counter;
  Widget *size_display;
  int current = -1;
  Fl_Menu_Item *items;
  void build_ui();
  void build_menu();
public:
  App(vector<char*> images);
  int handle(int event) override;
  void run();
  ~App();
  void next_image();
};

App::~App() {
  // Cleanup memory before dieing

  free(items);
  for (auto i : images) {
    free(i);
  }
  auto i = picture_box->get_image();
  delete i;
}

void App::next_image() {
  current++;
  if (current >= (int)images.size()) {
    current = 0;
  }

  char* path = images[current];

  picture_box->load_image(path);
  Fl_Image *image = picture_box->get_image();

  char size_display_str[100];
  snprintf(size_display_str, 100, "%d x %d", image->w(), image->h());
  size_display->label(size_display_str);

  //info_box->label(basename(path.c_str()));
  //info_box->redraw();
}

int App::handle(int event) {
  switch (event) {
  case FL_PUSH:
    if (Fl::event_button() == FL_LEFT_MOUSE) {
      next_image();
    } else if (Fl::event_button() == FL_RIGHT_MOUSE) {
      auto x = items->popup(50,50);
      if (x != NULL && x->callback() != NULL) {
        x->do_callback(this);
      }
    }
  default:
    Fl_Window::handle(event);
  }
  return 0;
}

App::App(vector<char*> _images) : Fl_Window(WIN_W, WIN_H, "imv") {
  images = _images;
  build_ui();
  build_menu();
}

void App::build_menu() {

  auto dither_m = [](Fl_Widget *_, void* __){
    auto picture_box = _->as_group()->array()[0];
    auto picture_box_view = _->as_group()->array()[1];
    auto dithered = dither(picture_box_view->image());
    ImageBox::adapt(dithered, picture_box, picture_box_view);
  };

  auto grayscale_m = [](Fl_Widget *_, void*__) {
    auto picture_box = _->as_group()->array()[0];
    auto picture_box_view = _->as_group()->array()[1];
    picture_box_view->image()->desaturate();
    picture_box_view->redraw();
    picture_box->redraw();
  };

  items = (Fl_Menu_Item*)malloc(sizeof(Fl_Menu_Item) * 4);
  items[0] = {"Test",0,0,0};
  items[1] = {"Dither",0,dither_m,0};
  items[2] = {"Greyscale", 0, grayscale_m, 0};
  items[3] = {0};
}

void App::build_ui() {
  color(0x00000000);

  picture_box = new ImageBox(0, 0, WIN_W, WIN_H - WIN_BAR_SIZE, "PBOX");

  info_box = new Fl_Box(0, WIN_H - WIN_BAR_SIZE, WIN_W, WIN_BAR_SIZE, "");
  info_box->box(FL_FLAT_BOX);
  info_box->color(0x87CEEB00);

  size_display = new Fl_Box(WIN_BAR_SIZE, WIN_H - WIN_BAR_SIZE,
                            WIN_BAR_SIZE / 2, WIN_BAR_SIZE, "");
  size_display->labelfont(FL_COURIER);
  size_display->labelcolor(fl_darker(fl_darker(0x87CEEB00)));
  end();
  show();
}

void App::run() { Fl::run(); }

#include <unistd.h>
int main(int argc, char **argv) {
  vector<char*> images = cmdl(argc, argv);
  auto a = new App(images);
  a->next_image();
  a->run();
  delete a;
}