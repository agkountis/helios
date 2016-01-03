#ifndef HELIOS_IMAGE_H
#define HELIOS_IMAGE_H

#include <vector>

class Image {
private:
    unsigned long width = 0;
    unsigned long height = 0;

    std::vector<unsigned char> pixels;

public:
    Image(unsigned long width, unsigned long height) : width(width), height(height)
    { }

    bool save_as_ppm(std::string file_name);
};

#endif //HELIOS_IMAGE_H
