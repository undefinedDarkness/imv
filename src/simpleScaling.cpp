#include "trunk.hpp"
#include <FL/Enumerations.H>
#include <FL/Fl_Image.H>
#include <FL/Fl_Tiled_Image.H>
#include <cstring>

int resize_by_halfs(int heap, int min) {
  short cur = 1;
  while (1) {
    cur *= 2;
    if ((heap / cur) < min) {
      return cur;
    }
  }
}

ImageBox::ImageBox(int x, int y, int w, int h, const char *label)
    : Fl_Box(x, y, w, h, label) {
  view = new Fl_Box(x, y, w, h, "PBOX-IMG-INTERNAL");
}

Fl_Image *ImageBox::get_image() { 
  return view->image();
}

int ImageBox::adapt(Fl_Image *image) {
  return ImageBox::adapt(image, this, view);
}

int ImageBox::adapt(Fl_Image *image, Fl_Widget *self, Fl_Widget* view) {
  if (image == NULL) {
    return -1;
  }
  int iw = image->w();
  int ih = image->h();

  // Pixel Art Support
  if (iw < 256 && ih < 256) {
    image->RGB_scaling(FL_RGB_SCALING_NEAREST);
  }

  if (iw > self->w() && ih > self->h()) {
    int fw = resize_by_halfs(image->w(), self->w());
    int fh = resize_by_halfs(image->h(), self->h());
    int f = min(fw, fh);
    auto _image = (Fl_RGB_Image *)image->copy(iw / f, ih / f);
    delete image; // Delete old copy
    image = _image;
  }

  if (iw < self->w() && ih < self->h()) {
    int x = (self->w() - iw) / 2;
    int y = (self->h() - ih) / 2;
    view->resize(x, y, image->w(), image->h());
  }

  auto current = view->image();
  delete current; // Delete old image
  view->image(image);
  view->redraw();
  self->redraw();
  return 0;
}

int ImageBox::load_image(char* path) {
  Fl_RGB_Image *image = NULL;
  char* ext = extname(path);
  if (strcmp(ext, ".png") == 0) {
    image = new Fl_PNG_Image(path);
  } else if (strcmp(ext, ".jpg") == 0) {
    image = new Fl_JPEG_Image(path);
  } else {
    std::cout << "Unknown image extension: " << ext << std::endl;
    return -1;
  }

  return adapt(image);
}