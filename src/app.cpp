#include "trunk.hpp"
#include <FL/Enumerations.H>
#include <FL/Fl_Pixmap.H>
#include <FL/Fl_Tiled_Image.H>
#include <FL/fl_utf8.h>

void panic(const char *msg) {
  std::cout << msg;
  exit(0);
}

#include <unistd.h>
int main(int argc, char **argv) {

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
    path = realpath(argv[1], NULL);
    filename = basename(path.c_str());
    parent_dir = path;
    parent_dir.resize(parent_dir.length() - filename.length());
  }

  EventWindow *window = new EventWindow(WIN_W, WIN_H, "imv");
  window->resizable(window);
  window->color(0x00000000);

  vector<string> images = walk(&parent_dir);
  int ti = images.size();
  if (path.empty()) {
    path = parent_dir + images[0];
    cout << path;
    filename = basename(path.c_str());
  }

  ImageBox *pbox = new ImageBox(0, 0, WIN_W, WIN_H - WIN_BAR_SIZE, "");
  pbox->load_image(path);

  Fl_Box *ibox = new Fl_Box(0, WIN_H - WIN_BAR_SIZE, WIN_W, WIN_BAR_SIZE,
                            filename.c_str());
  ibox->box(FL_FLAT_BOX);
  ibox->color(0x87CEEB00);

  string count = "1/";
  count += to_string(ti);

  Fl_Box *counter = new Fl_Box(WIN_W - WIN_BAR_SIZE, WIN_H - WIN_BAR_SIZE,
                               WIN_BAR_SIZE / 2, WIN_BAR_SIZE, count.c_str());
  counter->labelfont(FL_COURIER_BOLD);
  counter->labelcolor(fl_darker(fl_darker(0x87CEEB00)));

  Fl_Box *size_display = new Fl_Box(WIN_BAR_SIZE, WIN_H - WIN_BAR_SIZE,
                                    WIN_BAR_SIZE / 2, WIN_BAR_SIZE, "");
  size_display->labelfont(FL_COURIER);
  size_display->labelcolor(fl_darker(fl_darker(0x87CEEB00)));

  int cursor = 0;

  Fl::lock();
  window->end();
  window->show();
  int *message;

  Fl_Menu_Item menu_items[] = {{"About", 0, about_info, 0},
                               {"Help", 0, 0, 0},
                               //  {"Image Info", 0, image_info, 0},
                               {0}};

  while (Fl::wait()) {
    if ((message = (int *)Fl::thread_message()) == NULL) {
      continue;
    }

    if (*message == CUSTOM_RESIZE_EVENT) {
      pbox->redraw();
      continue;
    }

    if (Fl::event_button() == FL_LEFT_MOUSE) {
      cursor++;

      if (cursor >= ti) {
        cursor = 0;
        continue;
      }

      pbox->load_image(parent_dir + images[cursor]);
      auto image = pbox->get_image();

      counter->label(
          (std::to_string(cursor + 1) + "/" + std::to_string(ti)).c_str());
      counter->redraw_label();

      size_display->label(
          (std::to_string(image->w()) + "x" + std::to_string(image->h()))
              .c_str());
      size_display->redraw_label();

      ibox->label(images[cursor].c_str());

      if (cursor + 1 == ti) {
        cursor = -1;
      }

    } else if (Fl::event_button() == FL_RIGHT_MOUSE) {

      const Fl_Menu_Item *p = menu_items->popup(50, 50);
      if (p != NULL) {
        auto cb = p->callback();
        if (cb != NULL)
          cb(window, p->user_data());
      }
    }
  }
}