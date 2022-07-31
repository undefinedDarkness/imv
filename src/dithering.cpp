#include "trunk.hpp"

Fl_Image *dither(Fl_Image *target) {
    auto copy = target->copy();
    cout << "DEPTH: " << copy->d() << endl;
    int line = copy->w();
    int lines = copy->h();
    int pixels = line * lines;
    copy->desaturate();
    byte *imd = (byte*)copy->data()[0]; 
    byte *nimd = (byte*)malloc(pixels);
    //byte nimd[pixels]; -- This creates garbage.

    for (int r = 0; r < lines-1; r++) {
        for (int c = 0; c < line-1; c++) {
            auto pixel = imd[r*line + c] < 128 ? 0 : 255;
            auto err = (imd[r*line + c] - pixel) / 8;
            nimd[r*line + c] = pixel;
            imd[r*line + c + 1] += err;
            imd[r*line + c + 2] += err;

            if (r+1 < lines) {
                imd[(r+1)*line + c - 1] += err;
                imd[(r+1)*line + c] += err;
                imd[(r+1)*line + c + 1] += err;
            
                if ((r+2) < lines)
                    imd[(r+2)*line + c] += err;
            }

        }
    }

    auto x = new Fl_RGB_Image(nimd, line, lines, 1);
    
    free(nimd);
    delete copy;

    if (x == NULL || x->fail() != 0) {
        cout << "FAILED TO DITHER IMAGE!" << endl;
        return target;
    }

    return x;
}