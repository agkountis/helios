#ifndef HELIOS_PPM_IMAGE_H
#define HELIOS_PPM_IMAGE_H

#include "image.h"

class PpmImage : public Image {
private:
    unsigned int max_color_value;

public:
    PpmImage(unsigned int width, unsigned int height, unsigned int max_color_value)
            : Image(width, height), max_color_value(max_color_value)
    { }

    bool save(std::string file_name);
};

#endif //HELIOS_PPM_IMAGE_H
