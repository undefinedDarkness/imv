#include "trunk.hpp"
#include <FL/Enumerations.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Tiled_Image.H>

int resize_by_halfs(int heap, int min) {
  short cur = 1;
  while (1) {
    cur *= 2;
    // cout << heap << "/" << cur << " = " << heap / cur << endl;
    if ((heap / cur) < min) {
      return cur;
    }
  }
}

ImageBox::ImageBox(int x, int y, int w, int h, const char *label)
    : Fl_Box(x, y, w, h, "") {
  view = new Fl_Box(x, y, w, h, label);
}

Fl_Image *ImageBox::get_image() { return view->image(); }

int ImageBox::load_image(std::string path) {
  Fl_RGB_Image *image = NULL;
  std::string ext = extname(&path);
  if (ext == ".png") {
    image = new Fl_PNG_Image(path.c_str());
  } else if (ext == ".jpg") {
    image = new Fl_JPEG_Image(path.c_str());
  } else {
    std::cout << "Unknown image extension: " << ext << std::endl;
    return -1;
  }
  if (image == NULL) {
    std::cout << "Failed to load image: " << path << std::endl;
    return -1;
  }

  int iw = image->w();
  int ih = image->h();

  // Pixel Art Support
  if (iw < 256 && ih < 256) {
    image->RGB_scaling(FL_RGB_SCALING_NEAREST);
  }

  if (iw > w() && ih > h()) {
    int fw = resize_by_halfs(image->w(), w());
    int fh = resize_by_halfs(image->h(), h());
    int f = min(fw, fh);
    image = (Fl_RGB_Image *)image->copy(iw / f, ih / f);
  }

  if (iw < w() && ih < h()) {
    int x = (w() - iw) / 2;
    int y = (h() - ih) / 2;
    view->resize(x, y, image->w(), image->h());
  }

  view->image(image);
  redraw();

  return 0;
}