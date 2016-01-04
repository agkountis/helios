#ifndef HELIOS_IMAGE_H
#define HELIOS_IMAGE_H

#include <string>
#include <vector>

class Image {
protected:
    unsigned int width;
    unsigned int height;

    char *pixels = nullptr;

public:
    Image(unsigned int width, unsigned int height) : width(width), height(height)
    { }

    virtual ~Image() {};

    virtual bool save(std::string file_name) = 0;
};

#endif //HELIOS_IMAGE_H
