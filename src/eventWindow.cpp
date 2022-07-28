#include "trunk.hpp"

EventWindow::EventWindow(int w, int h, const char * lbl): Fl_Window(w,h,lbl) {}

void EventWindow::resize(int X, int Y, int W, int H) {
    Fl_Window::resize(X,Y,W,H);
    int e = CUSTOM_RESIZE_EVENT;
    Fl::awake(&e);
}

int EventWindow::handle(int e) {
    switch (e) {
        case FL_PUSH:
            Fl::awake(&e);
            return 0;
        default:
            return Fl_Window::handle(e);
    }
}