#ifndef HELIOS_PPM_IMAGE_H
#define HELIOS_PPM_IMAGE_H

#include "image.h"

class PpmImage : public Image {
private:
    static const int max_color_value = 255;

public:
    PpmImage(unsigned int width, unsigned int height)
            : Image(width, height)
    { }

    bool save(const std::string &file_name);
};

#endif //HELIOS_PPM_IMAGE_H
